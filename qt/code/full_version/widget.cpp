#include "widget.h"
#include "ui_widget.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QFile>
#include <QFileInfo>

/* ============================================================================
 * 第一部分：构造函数与初始化
 * 功能：创建串口对象、填充下拉框参数、连接信号槽、设置定时器
 * ============================================================================ */

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
    , m_serial(nullptr)
    , m_sendTimer(nullptr)
    , m_loopTimer(nullptr)
    , m_receivedCount(0)
    , m_sentCount(0)
    , m_isSerialOpen(false)
{
    ui->setupUi(this);
    this->setLayout(ui->gridLayout_gol);

    // --- 1. 初始化串口对象 ---
    initSerialPort();

    // --- 2. 填充所有串口参数下拉框 ---
    initComboBoxes();

    // --- 3. 连接所有信号与槽 ---
    initConnections();

    // --- 4. 初始化状态栏时间 ---
    ui->label_D4->setText(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm"));
}

Widget::~Widget()
{
    // 如果串口还开着，先关闭
    if (m_serial && m_serial->isOpen()) {
        m_serial->close();
    }
    delete ui;
}

/* ============================================================================
 * 第二部分：初始化辅助方法
 * ============================================================================ */

// 初始化串口对象
void Widget::initSerialPort()
{
    m_serial = new QSerialPort(this);
}

// 填充串口参数下拉框
void Widget::initComboBoxes()
{
    // --- 刷新可用串口列表 ---
    refreshPortList();

    // --- 波特率下拉框 ---
    // QSerialPort::BaudRate 枚举对应的常用值
    ui->comboBox_3->addItem("1200",   QSerialPort::Baud1200);
    ui->comboBox_3->addItem("2400",   QSerialPort::Baud2400);
    ui->comboBox_3->addItem("4800",   QSerialPort::Baud4800);
    ui->comboBox_3->addItem("9600",   QSerialPort::Baud9600);
    ui->comboBox_3->addItem("19200",  QSerialPort::Baud19200);
    ui->comboBox_3->addItem("38400",  QSerialPort::Baud38400);
    ui->comboBox_3->addItem("57600",  QSerialPort::Baud57600);
    ui->comboBox_3->addItem("115200", QSerialPort::Baud115200);
    ui->comboBox_3->setCurrentIndex(3);  // 默认9600

    // --- 数据位下拉框 ---
    ui->comboBox_2->addItem("8", QSerialPort::Data8);
    ui->comboBox_2->addItem("7", QSerialPort::Data7);
    ui->comboBox_2->addItem("6", QSerialPort::Data6);
    ui->comboBox_2->addItem("5", QSerialPort::Data5);
    ui->comboBox_2->setCurrentIndex(0);  // 默认8位

    // --- 校验位下拉框 ---
    ui->comboBox_4->addItem("None", QSerialPort::NoParity);
    ui->comboBox_4->addItem("Even", QSerialPort::EvenParity);
    ui->comboBox_4->addItem("Odd",  QSerialPort::OddParity);
    ui->comboBox_4->addItem("Mark", QSerialPort::MarkParity);
    ui->comboBox_4->addItem("Space",QSerialPort::SpaceParity);
    ui->comboBox_4->setCurrentIndex(0);

    // --- 停止位下拉框 ---
    ui->comboBox_6->addItem("1",   QSerialPort::OneStop);
    ui->comboBox_6->addItem("1.5", QSerialPort::OneAndHalfStop);
    ui->comboBox_6->addItem("2",   QSerialPort::TwoStop);
    ui->comboBox_6->setCurrentIndex(0);

    // --- 流控下拉框 ---
    ui->comboBox_5->addItem("None",    QSerialPort::NoFlowControl);
    ui->comboBox_5->addItem("RTS/CTS", QSerialPort::HardwareControl);
    ui->comboBox_5->addItem("XON/XOFF",QSerialPort::SoftwareControl);
    ui->comboBox_5->setCurrentIndex(0);
}

// 刷新可用串口列表
void Widget::refreshPortList()
{
    ui->comboBox->clear();
    QList<QSerialPortInfo> ports = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &info : ports) {
        // 显示格式：端口名 + 描述信息
        QString displayName = info.portName();
        if (!info.description().isEmpty()) {
            displayName += " - " + info.description();
        }
        ui->comboBox->addItem(displayName, info.portName());
    }
}

// 连接所有信号和槽
void Widget::initConnections()
{
    // 串口数据到达信号 → 接收处理
    // QSerialPort::readyRead 在异步模式下触发
    QObject::connect(m_serial, &QSerialPort::readyRead,
                     this, &Widget::onReadyRead);

    // 点击串口下拉框打开时刷新列表（实现自动检测可用串口）
    // 策略：在下拉框展开时自动刷新
    QObject::connect(ui->comboBox, QOverload<int>::of(&QComboBox::activated),
                     this, [this]() {
                         // 可以在此刷新，但activated在选中后才触发
                     });

    // --- 定时发送计时器 ---
    m_sendTimer = new QTimer(this);
    QObject::connect(m_sendTimer, &QTimer::timeout,
                     this, &Widget::onTimedSend);

    // --- 循环发送计时器（多文本面板） ---
    m_loopTimer = new QTimer(this);
    QObject::connect(m_loopTimer, &QTimer::timeout,
                     this, &Widget::onLoopSend);

    // ===== 时间刷新定时器（新增） =====
       m_timeTimer = new QTimer(this);
       connect(m_timeTimer, &QTimer::timeout, this, &Widget::time_reflash);
       m_timeTimer->start(1000);   // 每秒刷新一次（1000ms）

    // --- 串口错误处理 ---
    QObject::connect(m_serial, &QSerialPort::errorOccurred,
                     this, [this](QSerialPort::SerialPortError error) {
                         if (error != QSerialPort::NoError && m_isSerialOpen) {
                             QMessageBox::warning(this, "串口错误",
                                                  "串口发生错误: " + m_serial->errorString());
                             m_serial->close();
                             m_isSerialOpen = false;
                             ui->pushButton_Closeser->setText("打开串口");
                             updateStatusLabel();
                         }
                     });

    // --- 定时发送间隔变更 ---
    QObject::connect(ui->lineEditRate, &QLineEdit::textChanged,
                     this, [this]() {
                         if (ui->checkBox_timeSend->isChecked()) {
                             bool ok;
                             int ms = ui->lineEditRate->text().toInt(&ok);
                             if (ok && ms > 0) {
                                 m_sendTimer->setInterval(ms);
                             }
                         }
                     });
}

/* ============================================================================
 * 第三部分：串口控制
 * 功能：打开/关闭串口、读取UI参数并配置串口
 * ============================================================================ */

void Widget::on_pushButton_Closeser_clicked()
{
     //关闭串口
    if (m_isSerialOpen) {
        // ===== 关闭串口 =====
        m_sendTimer->stop();       // 停止定时发送
        m_loopTimer->stop();       // 停止循环发送
        m_serial->close();         // 关闭串口
        m_isSerialOpen = false;
        ui->pushButton_Closeser->setText("打开串口");

        // 恢复下拉框的可用状态（允许修改参数）
        ui->comboBox->setEnabled(true);
        ui->comboBox_2->setEnabled(true);
        ui->comboBox_3->setEnabled(true);
        ui->comboBox_4->setEnabled(true);
        ui->comboBox_5->setEnabled(true);
        ui->comboBox_6->setEnabled(true);
        ui->label_D1->setText("串口已关闭");
    } else {
        // ===== 打开串口 =====
        // 检查是否有可用串口
        if (ui->comboBox->currentData().toString().isEmpty()) {
            QMessageBox::information(this, "提示", "没有可用的串口，请检查设备连接");
            return;
        }

        // 1. 设置串口名称
        m_serial->setPortName(ui->comboBox->currentData().toString());

        // 2. 设置波特率
        m_serial->setBaudRate(static_cast<QSerialPort::BaudRate>(
            ui->comboBox_3->currentData().toInt()));

        // 3. 设置数据位
        m_serial->setDataBits(static_cast<QSerialPort::DataBits>(
            ui->comboBox_2->currentData().toInt()));

        // 4. 设置校验位
        m_serial->setParity(static_cast<QSerialPort::Parity>(
            ui->comboBox_4->currentData().toInt()));

        // 5. 设置停止位
        m_serial->setStopBits(static_cast<QSerialPort::StopBits>(
            ui->comboBox_6->currentData().toInt()));

        // 6. 设置流控
        m_serial->setFlowControl(static_cast<QSerialPort::FlowControl>(
            ui->comboBox_5->currentData().toInt()));

        // 7. 尝试打开串口
        if (m_serial->open(QIODevice::ReadWrite)) {
            m_isSerialOpen = true;
            ui->pushButton_Closeser->setText("关闭串口");

            // 锁定下拉框（串口打开后不允许修改参数）
            ui->comboBox->setEnabled(false);
            ui->comboBox_2->setEnabled(false);
            ui->comboBox_3->setEnabled(false);
            ui->comboBox_4->setEnabled(false);
            ui->comboBox_5->setEnabled(false);
            ui->comboBox_6->setEnabled(false);

            ui->label_D1->setText("串口已打开 " + ui->comboBox->currentData().toString());
        } else {
            QMessageBox::critical(this, "错误", "无法打开串口: " + m_serial->errorString());
        }
    }
    updateStatusLabel();
}

/* ============================================================================
 * 第四部分：发送功能
 * 功能：普通发送、HEX发送、新行发送、定时发送、多文本快捷发送、循环发送
 * ============================================================================ */

// --- 发送按钮点击槽 ---
void Widget::on_pushButton_Saveget_send_clicked()
{
    sendData();
}

// --- 核心发送逻辑 ---
void Widget::sendData()
{
    if (!m_isSerialOpen || !m_serial->isOpen()) {
        QMessageBox::warning(this, "提示", "请先打开串口");
        return;
    }

    // 1. 获取发送框文本
    QString text = ui->lineEditText->text();
    if (text.isEmpty()) {
        return;
    }

    QByteArray data;

    // 2. 根据「HEK发送」勾选状态决定如何编码
    if (ui->checkBox_HekSend->isChecked()) {
        // HEX模式：将 "AA BB CC" 这样的字符串转为字节
        data = hexStringToBytes(text);
        if (data.isEmpty()) {
            QMessageBox::warning(this, "格式错误",
                                 "HEX格式错误，请输入如: AA BB CC 的格式");
            return;
        }
    } else {
        // 文本模式：直接转 UTF-8 字节
        data = text.toUtf8();
    }

    // 3. 根据「发送新行」勾选追加换行符
    if (ui->checkBox_sendNew->isChecked()) {
        data.append("\r\n");
    }

    // 4. 写入串口
    qint64 written = m_serial->write(data);

    if (written >= 0) {
        m_sentCount += written;
        ui->label_D3->setText("Sent:" + QString::number(m_sentCount));

        // 在接收区也回显发送的内容（蓝色标记）
        QString displayText;
        if (ui->checkBox_HekSend->isChecked()) {
            displayText = "[发送HEX] " + bytesToHexString(data);
        } else {
            displayText = "[发送] " + QString::fromUtf8(data);
        }
        ui->textEditRev->append("<font color='blue'>" + displayText + "</font>");

        ui->label_D1->setText("send ok! " + QDateTime::currentDateTime().toString("hh:mm:ss"));

        // 记录到历史
        ui->textEdit_2->append(displayText);
    }
}

// --- 定时发送触发（由 m_sendTimer 调用） ---
void Widget::onTimedSend()
{
    // 检查定时发送是否仍然勾选
    if (ui->checkBox_timeSend->isChecked() && m_isSerialOpen) {
        sendData();
    }
}

// --- 定时发送勾选状态变化 ---
void Widget::on_checkBox_timeSend_stateChanged(int state)
{
    if (state == Qt::Checked && m_isSerialOpen) {
        bool ok;
        int ms = ui->lineEditRate->text().toInt(&ok);
        if (!ok || ms < 10) ms = 1000;  // 默认1000ms
        m_sendTimer->start(ms);
    } else {
        m_sendTimer->stop();
    }
}

// --- 多文本快捷发送 ---
void Widget::sendMultiText(int index)
{
    QLineEdit *lineEdits[9] = {
        ui->lineEdit1, ui->lineEdit2, ui->lineEdit3,
        ui->lineEdit4, ui->lineEdit5, ui->lineEdit6,
        ui->lineEdit7, ui->lineEdit8, ui->lineEdit9
    };

    if (index < 0 || index >= 9) return;

    QString text = lineEdits[index]->text();
    if (text.isEmpty()) return;

    // 使用自身的发送逻辑
    if (!m_isSerialOpen || !m_serial->isOpen()) {
        QMessageBox::warning(this, "提示", "请先打开串口");
        return;
    }

    QByteArray data = text.toUtf8();
    qint64 written = m_serial->write(data);
    if (written >= 0) {
        m_sentCount += written;
        ui->label_D3->setText("Sent:" + QString::number(m_sentCount));
    }
}

// --- 循环发送触发（由 m_loopTimer 调用） ---
void Widget::onLoopSend()
{
    if (!ui->checkBox->isChecked() || !m_isSerialOpen) {
        m_loopTimer->stop();
        return;
    }

    // 遍历多文本面板的9行，找到勾选的行并发送
    QCheckBox *checkBoxes[9] = {
        ui->checkBox1, ui->checkBox2, ui->checkBox3,
        ui->checkBox4, ui->checkBox5, ui->checkBox6,
        ui->checkBox7, ui->checkBox8, ui->checkBox9
    };

    QLineEdit *lineEdits[9] = {
        ui->lineEdit1, ui->lineEdit2, ui->lineEdit3,
        ui->lineEdit4, ui->lineEdit5, ui->lineEdit6,
        ui->lineEdit7, ui->lineEdit8, ui->lineEdit9
    };

    for (int i = 0; i < 9; i++) {
        if (checkBoxes[i]->isChecked() && !lineEdits[i]->text().isEmpty()) {
            m_serial->write(lineEdits[i]->text().toUtf8());
        }
    }
}

// --- 9个快捷发送按钮 ---
void Widget::on_pushButton1_clicked() { sendMultiText(0); }
void Widget::on_pushButton2_clicked() { sendMultiText(1); }
void Widget::on_pushButton3_clicked() { sendMultiText(2); }
void Widget::on_pushButton4_clicked() { sendMultiText(3); }
void Widget::on_pushButton_11_clicked() { sendMultiText(4); }
void Widget::on_pushButton6_clicked() { sendMultiText(5); }
void Widget::on_pushButton7_clicked() { sendMultiText(6); }
void Widget::on_pushButton8_clicked() { sendMultiText(7); }
void Widget::on_pushButton9_clicked() { sendMultiText(8); }

/* ============================================================================
 * 第五部分：接收功能
 * 功能：数据接收回调、HEX/文本显示切换、时间戳、清空/保存接收区
 * ============================================================================ */

// --- 核心：串口有数据到达时的处理 ---
void Widget::onReadyRead()
{
    // 读取所有可用数据
    QByteArray data = m_serial->readAll();

    // 1. 统计接收字节
    m_receivedCount += data.size();
    ui->label_D2->setText("Received:" + QString::number(m_receivedCount));

    // 2. 构建显示文本
    QString displayText;

    if (ui->checkBox_HEK->isChecked()) {
        // HEX显示模式
        displayText = bytesToHexString(data);
    } else {
        // 普通文本模式
        displayText = QString::fromUtf8(data);
    }

    // 3. 时间戳
    if (ui->checkBox_TIME->isChecked()) {
        QString timeStr = QDateTime::currentDateTime().toString("hh:mm:ss.zzz");
        displayText = "[" + timeStr + "] " + displayText;
    }

    // 4. 自动换行
    if (ui->checkBox_ZDHH->isChecked()) {
        displayText += "\n";
    }

    // 5. 追加到接收文本框
    // 使用 insertPlainText 而不是 append，因为 append 会自动加换行
    ui->textEditRev->insertPlainText(displayText);

    // 6. 滚动到底部
    QTextCursor cursor = ui->textEditRev->textCursor();
    cursor.movePosition(QTextCursor::End);
    ui->textEditRev->setTextCursor(cursor);
}

// --- 清空接收区 ---
void Widget::on_pushButton_Clearget_clicked()
{
    ui->textEditRev->clear();
    m_receivedCount = 0;
    ui->label_D2->setText("Received:0");
}

// --- 保存接收内容到文件 ---
void Widget::on_pushButton_Saveget_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, "保存接收内容",
                                                    QDir::homePath() + "/serial_recv.txt",
                                                    "文本文件 (*.txt);;所有文件 (*)");
    if (fileName.isEmpty()) return;

    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out << ui->textEditRev->toPlainText();
        file.close();
        QMessageBox::information(this, "提示", "接收内容已保存到:\n" + fileName);
    } else {
        QMessageBox::warning(this, "错误", "无法保存文件: " + file.errorString());
    }
}

// --- HEX显示切换 ---
void Widget::on_checkBox_HEK_stateChanged(int state)
{
    Q_UNUSED(state);
    // 这里可以控制接收区后续数据的显示方式
    // QSerialPort::readyRead 槽中已经根据 checkBox_HEK 状态处理
}

// --- 时间戳显示切换 ---
void Widget::on_checkBox_TIME_stateChanged(int state)
{
    Q_UNUSED(state);
}

/* ============================================================================
 * 第六部分：辅助功能
 * 功能：多文本保存/载入/重置、循环发送勾选、面板隐藏、自动换行等
 * ============================================================================ */

// --- 保存多文本面板内容到文件 ---
void Widget::on_pushButton_3_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, "保存多文本配置",
                                                    QDir::homePath() + "/multi_text.txt",
                                                    "文本文件 (*.txt);;所有文件 (*)");
    if (fileName.isEmpty()) return;
    saveMultiTextToFile(fileName);
}

// --- 重置多文本面板 ---
void Widget::on_pushButton_clicked()
{
    QLineEdit *lineEdits[9] = {
        ui->lineEdit1, ui->lineEdit2, ui->lineEdit3,
        ui->lineEdit4, ui->lineEdit5, ui->lineEdit6,
        ui->lineEdit7, ui->lineEdit8, ui->lineEdit9
    };
    for (int i = 0; i < 9; i++) {
        lineEdits[i]->clear();
    }
}

// --- 载入多文本面板内容 ---
void Widget::on_pushButton_2_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "载入多文本配置",
                                                    QDir::homePath(),
                                                    "文本文件 (*.txt);;所有文件 (*)");
    if (fileName.isEmpty()) return;
    loadMultiTextFromFile(fileName);
}

// --- 循环发送勾选 ---
void Widget::on_checkBox_stateChanged(int state)
{
    if (state == Qt::Checked && m_isSerialOpen) {
        int interval = ui->spinBox->value();
        if (interval < 10) interval = 100; // 最小100ms
        m_loopTimer->start(interval);
    } else {
        m_loopTimer->stop();
    }
}

// --- 隐藏面板 ---
void Widget::on_pushButton_Yincmb_clicked()
{
    bool visible = ui->groupBox_Down2->isVisible();
    ui->groupBox_Down2->setVisible(!visible);
    ui->groupBox_Down3->setVisible(!visible);
    ui->pushButton_Yincmb->setText(visible ? "显示面板" : "隐藏面板");
}

// --- 隐藏历史记录 ---
void Widget::on_pushButton_Yincls_clicked()
{
    bool visible = ui->groupBoxRecord3->isVisible();
    ui->groupBoxRecord3->setVisible(!visible);
    ui->pushButton_Yincls->setText(visible ? "显示历史" : "隐藏历史");
}

// --- 自动换行切换 ---
void Widget::on_checkBox_ZDHH_stateChanged(int state)
{
    Q_UNUSED(state);
    // 接收处理中已根据此复选框状态决定是否追加换行
}

/* ============================================================================
 * 第七部分：工具函数
 * 功能：HEX转换、文件读写、状态栏更新
 * ============================================================================ */

// --- HEX字符串转字节数组 ---
// 输入："AA BB CC" 或 "AABBCC" → 输出：\xAA\xBB\xCC
QByteArray Widget::hexStringToBytes(const QString &hexStr)
{
    // 去掉所有空格和不可见字符
    QString cleaned = hexStr.simplified().remove(' ');
    QByteArray result;

    // 长度必须是偶数
    if (cleaned.length() % 2 != 0) {
        return QByteArray(); // 返回空表示格式错误
    }

    bool ok;
    for (int i = 0; i < cleaned.length(); i += 2) {
        QString byteStr = cleaned.mid(i, 2);
        quint8 byte = byteStr.toUInt(&ok, 16);
        if (!ok) return QByteArray();
        result.append(static_cast<char>(byte));
    }
    return result;
}

// --- 字节数组转HEX显示字符串 ---
QString Widget::bytesToHexString(const QByteArray &data)
{
    QString result;
    for (int i = 0; i < data.size(); i++) {
        result += QString("%1 ").arg(static_cast<quint8>(data.at(i)), 2, 16, QChar('0')).toUpper();
    }
    return result.trimmed();
}

// --- 多文本保存到文件 ---
void Widget::saveMultiTextToFile(const QString &filePath)
{
    QFile file(filePath);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        QLineEdit *lineEdits[9] = {
            ui->lineEdit1, ui->lineEdit2, ui->lineEdit3,
            ui->lineEdit4, ui->lineEdit5, ui->lineEdit6,
            ui->lineEdit7, ui->lineEdit8, ui->lineEdit9
        };
        for (int i = 0; i < 9; i++) {
            out << lineEdits[i]->text() << "\n";
        }
        file.close();
        QMessageBox::information(this, "提示", "多文本已保存到:\n" + filePath);
    }
}

// --- 多文本从文件载入 ---
void Widget::loadMultiTextFromFile(const QString &filePath)
{
    QFile file(filePath);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        QLineEdit *lineEdits[9] = {
            ui->lineEdit1, ui->lineEdit2, ui->lineEdit3,
            ui->lineEdit4, ui->lineEdit5, ui->lineEdit6,
            ui->lineEdit7, ui->lineEdit8, ui->lineEdit9
        };
        int i = 0;
        while (!in.atEnd() && i < 9) {
            lineEdits[i]->setText(in.readLine().trimmed());
            i++;
        }
        file.close();
    }
}

// --- 更新状态栏 ---
void Widget::updateStatusLabel()
{
    ui->label_D2->setText("Received:" + QString::number(m_receivedCount));
    ui->label_D3->setText("Sent:" + QString::number(m_sentCount));
    ui->label_D4->setText(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm"));
}
