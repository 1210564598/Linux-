#include "widget.h"
#include "ui_widget.h"

#include <QDir>




//==============================================================================
//  模块一：构造函数与初始化
//  功能：创建串口对象、填充参数下拉框、连接信号槽、初始化多文本 QList
//==============================================================================

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
    , m_serial(nullptr)
    , m_isSerialOpen(false)
    , m_receivedCount(0)
    , m_sentCount(0)
    , m_sendTimer(nullptr)
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

    // --- 5. for 循环遍历多文本区 9 行控件，存入 QList ---
    for (int i = 0; i < 9; i++) {
        // 按钮：设 property + 连信号到 on_command_button_clicked
        QPushButton *btn = findChild<QPushButton *>(QString("pushButton%1").arg(i + 1));
        if (btn) {
            btn->setProperty("buttonId", i + 1);
            buttons.append(btn);
            connect(btn, SIGNAL(clicked()), this, SLOT(on_command_button_clicked()));
        }
        // lineEdit：按规律 lineEdit1~9
        QLineEdit *edit = findChild<QLineEdit *>(QString("lineEdit%1").arg(i + 1));
        lineEdits.append(edit);
        // checkBox：按规律 checkBox1~9
        QCheckBox *cb = findChild<QCheckBox *>(QString("checkBox%1").arg(i + 1));
        checkBoxs.append(cb);
    }

    // --- 6. 循环发送定时器 ---
    buttonsConTimer = new QTimer(this);
    connect(buttonsConTimer, &QTimer::timeout, this, &Widget::buttons_handler);

    // --- 7. 系统时间更新定时器（1000ms 刷新） ---
    QTimer *sysTimer = new QTimer(this);
    connect(sysTimer, &QTimer::timeout, this, &Widget::time_reflash);
    sysTimer->start(1000);
}





Widget::~Widget()
{
    // 如果串口还开着，先关闭
    if (m_serial && m_serial->isOpen()) {
        m_serial->close();
    }
    delete ui;
}



//==============================================================================
//  模块二：初始化辅助方法
//  功能：initSerialPort / initComboBoxes / refreshPortList / initConnections
//==============================================================================

void Widget::initSerialPort()
{
    m_serial = new QSerialPort(this);
}
// 设置默认参数
void Widget::initComboBoxes()
{
    // --- 刷新可用串口列表 ---
    refreshPortList();

    // --- 波特率下拉框 ---
    ui->comboBox_BT->addItem("1200",   QSerialPort::Baud1200);
    ui->comboBox_BT->addItem("2400",   QSerialPort::Baud2400);
    ui->comboBox_BT->addItem("4800",   QSerialPort::Baud4800);
    ui->comboBox_BT->addItem("9600",   QSerialPort::Baud9600);
    ui->comboBox_BT->addItem("19200",  QSerialPort::Baud19200);
    ui->comboBox_BT->addItem("38400",  QSerialPort::Baud38400);
    ui->comboBox_BT->addItem("57600",  QSerialPort::Baud57600);
    ui->comboBox_BT->addItem("115200", QSerialPort::Baud115200);
    ui->comboBox_BT->setCurrentIndex(3);  // 默认9600

    // --- 数据位下拉框 ---
    ui->comboBox_SJ->addItem("8", QSerialPort::Data8);
    ui->comboBox_SJ->addItem("7", QSerialPort::Data7);
    ui->comboBox_SJ->addItem("6", QSerialPort::Data6);
    ui->comboBox_SJ->addItem("5", QSerialPort::Data5);
    ui->comboBox_SJ->setCurrentIndex(0);  // 默认8位

    // --- 校验位下拉框 ---
    ui->comboBox_XY->addItem("None", QSerialPort::NoParity);
    ui->comboBox_XY->addItem("Even", QSerialPort::EvenParity);
    ui->comboBox_XY->addItem("Odd",  QSerialPort::OddParity);
    ui->comboBox_XY->addItem("Mark", QSerialPort::MarkParity);
    ui->comboBox_XY->addItem("Space",QSerialPort::SpaceParity);
    ui->comboBox_XY->setCurrentIndex(0);

    // --- 停止位下拉框 ---
    ui->comboBox_TJ->addItem("1",   QSerialPort::OneStop);
    ui->comboBox_TJ->addItem("1.5", QSerialPort::OneAndHalfStop);
    ui->comboBox_TJ->addItem("2",   QSerialPort::TwoStop);
    ui->comboBox_TJ->setCurrentIndex(0);

    // --- 流控下拉框 ---
    ui->comboBox_LK->addItem("None",    QSerialPort::NoFlowControl);
    ui->comboBox_LK->addItem("RTS/CTS", QSerialPort::HardwareControl);
    ui->comboBox_LK->addItem("XON/XOFF",QSerialPort::SoftwareControl);
    ui->comboBox_LK->setCurrentIndex(0);
}

// 串口端口列表 —— 扫描电脑上的 COM 口
void Widget::refreshPortList()
{
    ui->comboBoxSerial->clear();
    QList<QSerialPortInfo> ports = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &info : ports) {
        // 显示格式：端口名
        QString displayName = info.portName();
      // 显示用 name，实际传给串口的是 portName
        ui->comboBoxSerial->addItem(displayName, info.portName());
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
    QObject::connect(ui->comboBoxSerial, QOverload<int>::of(&QComboBox::activated),
                     this, [this]() {
                        refreshPortList(); // 可以在此刷新，但activated在选中后才触发
                     });


    // --- 定时发送计时器 ---
    m_sendTimer = new QTimer(this);
    QObject::connect(m_sendTimer, &QTimer::timeout,
                     this, &Widget::onTimedSend);
    // 上面只是创建，还没启动。启动在勾选"定时发送"时触发。

    // ===== 定时发送间隔输入框变化时，动态更新定时器 =====
    connect(ui->lineEditRate, &QLineEdit::textChanged, this, [this]() {
            if (ui->checkBox_timeSend->isChecked()) {
                int ms = ui->lineEditRate->text().toInt();
                if (ms > 0) m_sendTimer->setInterval(ms);
            }
        });

    // ===== 循环发送勾选框手动连接（UI名称为 checkBox，非 checkBox_send） =====
    connect(ui->checkBox, &QCheckBox::clicked, this, &Widget::on_checkBox_send_clicked);
}




//==============================================================================
//  模块三：串口控制
//  功能：打开/关闭串口、读取 UI 参数并配置串口
//==============================================================================
void Widget::on_pushButton_Open_Closeser_clicked()
{

    //关闭串口
    if(m_isSerialOpen){
        // ===== 关闭串口 =====
        m_sendTimer->stop();       // 停止定时发送
        m_serial->close();          // 关串口
        m_isSerialOpen=false;
        ui->pushButton_Open_Closeser->setText("打开串口");

        // 锁定下拉框（串口打开后不允许修改参数）
        ui->comboBoxSerial->setEnabled(true);
        ui->comboBox_BT->setEnabled(true);
        ui->comboBox_LK->setEnabled(true);
        ui->comboBox_SJ->setEnabled(true);
        ui->comboBox_XY->setEnabled(true);
        ui->comboBox_TJ->setEnabled(true);
        ui->label_D1->setText("串口已关闭");
    }else{
        //=====打开串口
        //检查是否有可用串口
        if (ui->comboBoxSerial->currentData().toString().isEmpty()) {
            QMessageBox::information(this, "提示", "没有可用的串口，请检查设备连接");
            return;
        }


        //1.设置串口名称
        m_serial->setPortName(ui->comboBoxSerial->currentData().toString());

        // 2. 设置波特率
        m_serial->setBaudRate(static_cast<QSerialPort::BaudRate>(
                                  ui->comboBox_BT->currentData().toInt()));

        // 3. 设置数据位
        m_serial->setDataBits(static_cast<QSerialPort::DataBits>(
                                  ui->comboBox_SJ->currentData().toInt()));

        // 4. 设置校验位
        m_serial->setParity(static_cast<QSerialPort::Parity>(
                                ui->comboBox_XY->currentData().toInt()));

        // 5. 设置停止位
        m_serial->setStopBits(static_cast<QSerialPort::StopBits>(
                                  ui->comboBox_TJ->currentData().toInt()));

        // 6. 设置流控
        m_serial->setFlowControl(static_cast<QSerialPort::FlowControl>(
                                     ui->comboBox_LK->currentData().toInt()));

        // 7. 尝试打开串口
        if (m_serial->open(QIODevice::ReadWrite)) {
            qDebug()<<"打开成功";
            m_isSerialOpen = true;
            ui->pushButton_Open_Closeser->setText("关闭串口");

            // 锁定下拉框（串口打开后不允许修改参数）
            ui->comboBoxSerial->setEnabled(false);//启用或禁用控件的方法
            ui->comboBox_BT->setEnabled(false);
            ui->comboBox_LK->setEnabled(false);
            ui->comboBox_SJ->setEnabled(false);
            ui->comboBox_XY->setEnabled(false);
            ui->comboBox_TJ->setEnabled(false);

            ui->label_D1->setText("串口已打开 " + ui->comboBoxSerial->currentData().toString());
        }

    }
      updateStatusLabel();
}

//==============================================================================
//  模块四：发送功能
//  功能：普通发送、HEX发送、新行发送、定时发送
//==============================================================================

// --- 发送按钮点击槽 ---
void Widget::on_pushButton_Saveget_send_clicked()
{
    // 1.安全检查
    if(!m_isSerialOpen||!m_serial->isOpen()){//isOpen()判断串口是否真实打开了
        //QMessageBox::warning显示警告对话框
        QMessageBox::warning(this, "提示", "请先打开串口");
        return;
    }
    // 2.获取发送框文本
    QString text=ui->lineEditText->text();
    if (text.isEmpty()) {
        return;
    }

    //3. 把文字转换成字节
    QByteArray data;
    if (ui->checkBox_HekSend->isChecked()) {
        // HEX 模式：用户输入的是 "AA BB CC" 这样的十六进制字符串
        data = hexStringToBytes(text);
        if (data.isEmpty()) {
            QMessageBox::warning(this, "格式错误",
                                "HEX格式错误，请输入如: AA BB CC 或 AABBCC");
            return;
        }
    } else {
        // 文本模式：直接转 UTF-8 字节
        data = text.toUtf8();
    }

    // 4. 发送新行/追加换行
    if (ui->checkBox_sendNew->isChecked()) {
        data.append("\r\n");
    }

    // 5. 写入串口
    qint64 written = m_serial->write(data);

    if (written >= 0) {
        // 6.更新发送计数
        m_sentCount += written;
        ui->label_D3->setText("Sent:" + QString::number(m_sentCount));


        // 7. 在接收区回显（蓝色字，方便看到自己发了什么）
         ui->textEditRev->append("<font color='blue'>" + text + "</font>");


         // 8.更新状态栏 + 记录到历史
         ui->label_D1->setText("send ok! " + QDateTime::currentDateTime().toString("hh:mm:ss"));
         ui->textEdit_2->append("[发送] " + text);
}
}
// --- 定时发送触发（由 m_sendTimer 调用） ---
void Widget::onTimedSend(){
    // 检查定时发送是否仍然勾选
    if (ui->checkBox_timeSend->isChecked() && m_isSerialOpen) {
        on_pushButton_Saveget_send_clicked();// 复用发送逻辑
    }
}
// --- 定时发送勾选状态变化 ---
void Widget::on_checkBox_timeSend_stateChanged(int state)
{
    if (state == Qt::Checked && m_isSerialOpen) {
        int ms = ui->lineEditRate->text().toInt();
        if (ms < 10) ms = 1000;  // 默认1000ms
        m_sendTimer->start(ms);
    } else {
        m_sendTimer->stop();
    }
}


//==============================================================================
//  模块五：多文本快捷发送 + 循环发送 + 面板控制
//  功能：快捷发送 / 循环发送 / 保存/载入/重置多文本 / 隐藏面板/历史
//==============================================================================

// 多文本发送 —— 9 个按钮共用一个槽，通过 sender() 判断是哪个按钮
void Widget::on_command_button_clicked()
{
    QPushButton *btn = qobject_cast<QPushButton *>(sender());
    if (!btn) return;

    int num = btn->property("buttonId").toInt();  // 1~9

    // 取文本并填入主发送框
    if (num - 1 < lineEdits.size() && lineEdits[num - 1]) {
        QString text = lineEdits[num - 1]->text();
        if (!text.isEmpty()) {
            ui->lineEditText->setText(text);
        }
    }

    // 同步 HEX 状态
    if (num - 1 < checkBoxs.size() && checkBoxs[num - 1]) {
        ui->checkBox_HekSend->setChecked(checkBoxs[num - 1]->isChecked());
    }

    // 复用主发送
    on_pushButton_Saveget_send_clicked();
}

// 循环发送勾选
void Widget::on_checkBox_send_clicked(bool checked)
{
    if (checked && m_isSerialOpen) {
        ui->spinBox->setEnabled(false);
        buttonsConTimer->start(ui->spinBox->value()); // spinBox 的值(ms)
    } else {
        ui->spinBox->setEnabled(true);
        buttonsConTimer->stop();
    }
}

// 循环发送定时触发 —— 按顺序模拟点击每个按钮
void Widget::buttons_handler()
{
    if (buttonIndex < buttons.size()) {
        QPushButton *btn = buttons[buttonIndex];
        if (btn) emit btn->clicked();   // 模拟点击
        buttonIndex++;
    } else {
        buttonIndex = 0;                 // 一轮发完，回到第一个
    }
}

// 保存多文本到文件（一行一条，格式：勾选状态|文本）
void Widget::on_pushButton_3_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, "保存多文本",
                                                     QDir::homePath() + "/multi_text.txt",
                                                     "文本文件 (*.txt)");
    if (fileName.isEmpty()) return;

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) return;

    QTextStream out(&file);
    for (int i = 0; i < lineEdits.size(); i++) {
        int checked = (checkBoxs[i] && checkBoxs[i]->isChecked()) ? 1 : 0;
        out << checked << "|" << lineEdits[i]->text() << "\n";
    }
    file.close();
}

// 载入多文本从文件
void Widget::on_pushButton_2_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "载入多文本",
                                                     QDir::homePath(),
                                                     "文本文件 (*.txt)");
    if (fileName.isEmpty()) return;

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) return;

    QTextStream in(&file);
    int i = 0;
    while (!in.atEnd() && i < lineEdits.size()) {
        QString line = in.readLine();
        QStringList parts = line.split("|");
        if (parts.count() == 2) {
            if (checkBoxs[i]) checkBoxs[i]->setChecked(parts[0].toInt());
            lineEdits[i]->setText(parts[1]);
        }
        i++;
    }
    file.close();
}

// 重置多文本面板（带确认对话框）
void Widget::on_pushButton_clicked()
{
    for (int i = 0; i < lineEdits.size(); i++) {
        lineEdits[i]->clear();
        if (checkBoxs[i]) checkBoxs[i]->setChecked(false);
    }
}

// 隐藏面板
void Widget::on_pushButton_Yincmb_clicked()
{
    bool visible = ui->groupBox_Down2->isVisible();
    ui->groupBox_Down2->setVisible(!visible);
    ui->groupBox_Down3->setVisible(!visible);
    ui->pushButton_Yincmb->setText(visible ? "显示面板" : "隐藏面板");
}

// 隐藏历史
void Widget::on_pushButton_Yincls_clicked()
{
    bool visible = ui->groupBoxRecord3->isVisible();
    ui->groupBoxRecord3->setVisible(!visible);
    ui->pushButton_Yincls->setText(visible ? "显示历史" : "隐藏历史");
}



//==============================================================================
//  模块六：接收功能
//  功能：数据接收回调、HEX/文本显示切换、时间戳、自动换行、清空/保存接收区
//==============================================================================

// --- 核心：串口有数据到达时的处理 ---
void Widget::onReadyRead()
{
    // 1.一次性读完所有到达的数据
    QByteArray data = m_serial->readAll();

    // 2.统计字节数
    m_receivedCount += data.size();
    ui->label_D2->setText("Received:" + QString::number(m_receivedCount));

    // 3.根据用户的勾选决定显示格式
    QString displayText;
    if (ui->checkBox_HEK->isChecked()) {
        // HEX显示模式
        displayText = bytesToHexString(data);
    } else {
        // 普通文本模式
        displayText = QString::fromUtf8(data);
    }

   // 4.加时间戳
    if (ui->checkBox_TIME->isChecked()) {
        QString timeStr = QDateTime::currentDateTime().toString("hh:mm:ss.zzz");
        displayText = "[" + timeStr + "] " + displayText;
    }

    // 5. 加自动换行
    if (ui->checkBox_ZDHH->isChecked()) {
        displayText += "\n";
    }

    // 6.追加到接收区（用 insertPlainText 而不是 append，避免强制换行）
    ui->textEditRev->insertPlainText(displayText);
}

//清空按钮
void Widget::on_pushButton_Clearget_clicked()
{
    ui->textEditRev->clear();
    m_receivedCount = 0;
    ui->label_D2->setText("Received:0");
}


//保存接收
void Widget::on_pushButton_Saveget_clicked()
{
    //弹出对话框，选择文件保存位置
    QString fileName = QFileDialog::getSaveFileName(this, "保存接收内容",
                                                    "D:/QT/serialData.txt",
                                                    "文本文件 (*.txt)");
    if (fileName.isEmpty()) return;

    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out << ui->textEditRev->toPlainText();
        file.close();
    }
}


//HEK显示切换
void Widget::on_checkBox_HEK_clicked(bool checked)
{
    QString currentText = ui->textEditRev->toPlainText();
    if (currentText.isEmpty()) return;

    if (checked) {
        // 文本 → HEX 显示
        QByteArray data = currentText.toUtf8();
        ui->textEditRev->setText(bytesToHexString(data));
    } else {
        // HEX → 文本
        QByteArray data = hexStringToBytes(currentText);
        if (!data.isEmpty()) {
            ui->textEditRev->setText(QString::fromUtf8(data));
        }
        // 数据为空则不转换（说明当前内容不是有效HEX）
    }
}





//==============================================================================
//  模块七：工具函数
//  功能：状态栏更新 / HEX转换 / 时间刷新
//==============================================================================
// --- 更新状态栏 ---
void Widget::updateStatusLabel(){
    ui->label_D2->setText("Received:" + QString::number(m_receivedCount));//QString::number用于将整数转换为字符串。
    ui->label_D3->setText("Sent:" + QString::number(m_sentCount));
}

// --- HEX字符串转字节数组 ---
// 用户输入 `"AA BB CC"` → 转成真正的三个字节 `\xAA \xBB \xCC` 发送出去。
QByteArray Widget::hexStringToBytes(const QString &hexStr)
{
    // 去掉所有空格，得到 "AABBCC"
    QString cleaned = hexStr.simplified().remove(' ');

    // 十六进制两位一组，长度必须是偶数
    if (cleaned.length() % 2 != 0) {
        return QByteArray(); // 长度必须是偶数
    }


    QByteArray result;
    bool ok;
    for (int i = 0; i < cleaned.length(); i += 2) {
        quint8 byte = cleaned.mid(i, 2).toUInt(&ok, 16);
        if (!ok) return QByteArray();
        result.append(static_cast<char>(byte));
    }
    return result;
}

// --- 字节数组转HEX显示字符串 ---
// 收到 `\x41 \x42 \x43` → 在屏幕上显示 `"41 42 43"`。
QString Widget::bytesToHexString(const QByteArray &data)
{
    QString result;
    for (int i = 0; i < data.size(); i++) {
        result += QString("%1 ").arg(static_cast<quint8>(data.at(i)), 2, 16, QChar('0')).toUpper();
    }
    return result.trimmed();
}

//定时器 每 1000ms 触发一次
void Widget::time_reflash()
{
    ui->label_D4->setText(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm"));
}
