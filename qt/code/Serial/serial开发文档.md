# 串口调试助手 —— 新手开发文档

> 本文档带你从零开始，一步步写出一个可用的串口调试助手。每个章节对应一个功能模块，依次完成即可。

---

## 开发前的准备

### 你要做的东西

一个通过串口收发数据的桌面工具，界面已经用 Qt Designer 搭好了，现在需要写 C++ 代码让每个按钮、下拉框、显示区"活起来"。

### 你需要哪些文件

| 文件 | 谁产生的 | 你要改吗 |
|------|---------|:------:|
| `widget.ui` | 你在 Designer 里拖出来的界面 | 只做一件事（见下文） |
| `widget.h` | 你写 | ✅ 要写 |
| `widget.cpp` | 你写 | ✅ 要写 |
| `Serial.pro` | 你写 | ✅ 改一行 |
| `main.cpp` | Qt 自动生成 | ❌ 不用改 |

### 动工前先改两样东西

**第一件：`Serial.pro` 加上 `serialport` 模块**

```qmake
QT += core gui serialport    # 不加这行，后面 QSerialPort 会报找不到
```

**第二件：清空 Designer 里的 QComboBox 选项**

你的界面上有 6 个下拉框：串口端口、波特率、数据位、校验位、停止位、流控。在 Qt Designer 里双击每一个，把里面手动添加的选项**全部删掉**，让它们变成空的。

为什么要这样做：后面我们用代码给每个选项绑定一个"隐藏的枚举值"，如果 Designer 里残留了没有枚举值的选项，串口打开时会因为参数无效而失败。

---

## 第一章：搭好框架 —— widget.h

### 1.1 需要引入的头文件

把下面这些全部写到 `widget.h` 最顶上：

```cpp
#include <QWidget>          // 所有窗口控件的基类
#include <QSerialPort>      // 串口对象
#include <QSerialPortInfo>  // 用来扫描电脑上有哪些串口
#include <QTimer>           // 定时发送用的计时器
#include <QComboBox>        // 下拉框
#include <QCheckBox>        // 勾选框
#include <QLineEdit>        // 单行输入框
#include <QPushButton>      // 按钮
#include <QTextEdit>        // 多行文本框（接收区）
#include <QLabel>           // 文字标签（状态栏）
#include <QSpinBox>         // 数字调节框
#include <QDateTime>        // 获取当前时间
#include <QMessageBox>      // 弹窗提示
#include <QFileDialog>      // 保存文件对话框
#include <QDebug>           // 调试输出 qDebug()
```

### 1.2 成员变量 —— 程序运行期间要记住的数据

在 `class Widget` 的 `private:` 区域写：

```cpp
private:
    Ui::Widget *ui;                     // Designer 生成的所有控件都在这里面

    QSerialPort *m_serial = nullptr;    // 整个程序就靠这一个串口对象
    bool m_isSerialOpen = false;        // 记住串口是开着还是关着
    int m_receivedCount = 0;            // 收到多少字节了
    int m_sentCount = 0;                // 发出多少字节了
    QTimer *m_sendTimer = nullptr;      // 定时发送的计时器
```

指针类型（`m_serial`, `m_sendTimer`）**必须写 `= nullptr`**，否则析构时 `if(m_serial)` 可能读到垃圾值导致行为错乱。`bool` 和 `int` 也要赋初值，不然栈上的随机值会让程序一开始就出 bug。

### 1.3 声明我们要写的函数

所有的槽函数和工具函数，分成几组写在 `private slots:` 和 `private:` 里：

```cpp
private slots:
    // 串口开关
    void on_pushButton_Open_Closeser_clicked();

    // 发送
    void on_pushButton_Saveget_send_clicked();
    void onTimedSend();
    void on_checkBox_timeSend_stateChanged(int state);

    // 接收
    void onReadyRead();
    void on_checkBox_HEK_clicked(bool checked);
    void on_pushButton_Clearget_clicked();
    void on_pushButton_Saveget_clicked();

private:
    // 初始化（构造函数里依次调用）
    void initSerialPort();
    void initComboBoxes();
    void initConnections();

    // 工具
    void updateStatusLabel();
    void refreshPortList();
    QByteArray hexStringToBytes(const QString &hexStr);
    QString bytesToHexString(const QByteArray &data);
```

---

## 第二章：构造函数 —— 程序启动时做什么

```cpp
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
    , m_serial(nullptr)
    , m_isSerialOpen(false)
    , m_receivedCount(0)
    , m_sentCount(0)
    , m_sendTimer(nullptr)
{
    ui->setupUi(this);           // 把 Designer 画的界面加载进来

    initSerialPort();            // ① 创建串口对象
    initComboBoxes();            // ② 填充下拉框的选项
    initConnections();           // ③ 连接信号与槽
}
```

构造函数只做一件事：按顺序调用三个初始化函数。记住这个顺序很重要——串口对象必须先创建，后面两个函数才能用它。

---

## 第三章：初始化（一）—— 创建串口对象

```cpp
void Widget::initSerialPort()
{
    m_serial = new QSerialPort(this);
    // this 作为 parent：窗口关闭时 Qt 会自动 delete 掉 m_serial
}
```

只有一行代码。把 `m_serial` 从 `nullptr` 变成一个可用的 `QSerialPort` 对象。之后所有的收发都通过它。

---

## 第四章：初始化（二）—— 填充下拉框

这是整项目最重要的一个设计决策。下拉框有两个方法添加选项：

- **Qt Designer 双击编辑**：方便但选项不带隐含数据
- **代码 `addItem("文字", 隐含数据)`**：每个选项绑一个枚举值

我们选第二种。先看代码：

```cpp
void Widget::initComboBoxes()
{
    // ===== ① 串口端口列表 =====
    refreshPortList();  // 扫描电脑上有哪些 COM 口，见 4.1

    // ===== ② 波特率 =====
    ui->comboBox_BT->addItem("1200",   QSerialPort::Baud1200);
    ui->comboBox_BT->addItem("2400",   QSerialPort::Baud2400);
    ui->comboBox_BT->addItem("4800",   QSerialPort::Baud4800);
    ui->comboBox_BT->addItem("9600",   QSerialPort::Baud9600);
    ui->comboBox_BT->addItem("19200",  QSerialPort::Baud19200);
    ui->comboBox_BT->addItem("38400",  QSerialPort::Baud38400);
    ui->comboBox_BT->addItem("57600",  QSerialPort::Baud57600);
    ui->comboBox_BT->addItem("115200", QSerialPort::Baud115200);
    ui->comboBox_BT->setCurrentIndex(3);    // 默认选第4项(9600)，索引从0开始

    // ===== ③ 数据位 =====
    ui->comboBox_SJ->addItem("8", QSerialPort::Data8);
    ui->comboBox_SJ->addItem("7", QSerialPort::Data7);
    ui->comboBox_SJ->addItem("6", QSerialPort::Data6);
    ui->comboBox_SJ->addItem("5", QSerialPort::Data5);
    ui->comboBox_SJ->setCurrentIndex(0);    // 默认8位

    // ===== ④ 校验位 =====
    ui->comboBox_XY->addItem("None", QSerialPort::NoParity);
    ui->comboBox_XY->addItem("Even", QSerialPort::EvenParity);
    ui->comboBox_XY->addItem("Odd",  QSerialPort::OddParity);
    ui->comboBox_XY->addItem("Mark", QSerialPort::MarkParity);
    ui->comboBox_XY->addItem("Space",QSerialPort::SpaceParity);
    ui->comboBox_XY->setCurrentIndex(0);

    // ===== ⑤ 停止位 =====
    ui->comboBox_TJ->addItem("1",   QSerialPort::OneStop);
    ui->comboBox_TJ->addItem("1.5", QSerialPort::OneAndHalfStop);
    ui->comboBox_TJ->addItem("2",   QSerialPort::TwoStop);
    ui->comboBox_TJ->setCurrentIndex(0);

    // ===== ⑥ 流控 =====
    ui->comboBox_LK->addItem("None",    QSerialPort::NoFlowControl);
    ui->comboBox_LK->addItem("RTS/CTS", QSerialPort::HardwareControl);
    ui->comboBox_LK->addItem("XON/XOFF",QSerialPort::SoftwareControl);
    ui->comboBox_LK->setCurrentIndex(0);
}
```

**关键知识点：`addItem("显示文字", 隐藏数据)`**

`addItem` 的第二个参数是一个 `QVariant`（可以存任意类型）。我们存的是 `QSerialPort` 的枚举值。后面读取时只需要：

```cpp
int value = comboBox->currentData().toInt();  // 直接拿到枚举值
```

不需要写一堆 `if(文字=="9600")` 来判断——这才是正确的做法。

### 4.1 串口端口列表 —— 扫描电脑上的 COM 口

```cpp
void Widget::refreshPortList()
{
    ui->comboBoxSerial->clear();    // 先清空旧列表
    QList<QSerialPortInfo> ports = QSerialPortInfo::availablePorts();

    for (const QSerialPortInfo &info : ports) {
        QString name = info.portName();           // 例如 "COM3"
        if (!info.description().isEmpty()) {
            name += " - " + info.description();  // 例如 "COM3 - USB-SERIAL CH340"
        }
        // 显示用 name，实际传给串口的是 portName
        ui->comboBoxSerial->addItem(name, info.portName());
    }
}
```

---

## 第五章：初始化（三）—— 连接信号与槽

Qt 有两种连接方式：**自动连接**（靠命名规则）和**手动连接**（写 `connect`）。

自动连接不需要写代码，命名格式是 `on_控件名_信号名`，比如按钮 `pushButton_Send` 的点击事件就写 `on_pushButton_Send_clicked()`。但串口和定时器不是 UI 控件，必须手动 `connect`。

```cpp
void Widget::initConnections()
{
    // ===== ① 串口收到数据的信号 =====
    // 当对方发来数据时，Qt 自动调用 onReadyRead()
    connect(m_serial, &QSerialPort::readyRead, this, &Widget::onReadyRead);

    // ===== ② 创建定时器 =====
    m_sendTimer = new QTimer(this);
    connect(m_sendTimer, &QTimer::timeout, this, &Widget::onTimedSend);
    // 上面只是创建，还没启动。启动在勾选"定时发送"时触发。

    // ===== ③ 定时发送间隔输入框变化时，动态更新定时器 =====
    connect(ui->lineEditRate, &QLineEdit::textChanged, this, [this]() {
            if (ui->checkBox_timeSend->isChecked()) {
                int ms = ui->lineEditRate->text().toInt();
                if (ms > 0) m_sendTimer->setInterval(ms);
            }
        });

    // ===== ④ 循环发送勾选框手动连接（UI名称为 checkBox，非 checkBox_send） =====
    connect(ui->checkBox, &QCheckBox::clicked, this, &Widget::on_checkBox_send_clicked);
}
```

**③ 用到了 Lambda 表达式**。`[this]() { ... }` 的意思是"捕获外面的 this 指针，让花括号里的代码可以访问 ui 和 m_sendTimer"。如果不用 Lambda，就得单独写一个槽函数，麻烦很多。

---

## 第六章：打开和关闭串口

这是整个程序最重要的槽函数。

```cpp
void Widget::on_pushButton_Open_Closeser_clicked()
{
    if (m_isSerialOpen) {
        // ==================== 关闭串口 ====================
        m_sendTimer->stop();                      // 停掉定时发送
        m_serial->close();                        // 关串口
        m_isSerialOpen = false;
        ui->pushButton_Open_Closeser->setText("打开串口");

        // 解锁所有参数下拉框，允许用户修改
        ui->comboBoxSerial->setEnabled(true);
        ui->comboBox_BT->setEnabled(true);
        ui->comboBox_SJ->setEnabled(true);
        ui->comboBox_XY->setEnabled(true);
        ui->comboBox_TJ->setEnabled(true);
        ui->comboBox_LK->setEnabled(true);

        ui->label_D1->setText("串口已关闭");

    } else {
        // ==================== 打开串口 ====================
        // 先看有没有可用串口
        if (ui->comboBoxSerial->currentData().toString().isEmpty()) {
            QMessageBox::information(this, "提示", "没有可用的串口");
            return;
        }

        // 依次把 6 个下拉框的参数配给串口
        m_serial->setPortName(ui->comboBoxSerial->currentData().toString());
        m_serial->setBaudRate((QSerialPort::BaudRate)ui->comboBox_BT->currentData().toInt());
        m_serial->setDataBits((QSerialPort::DataBits)ui->comboBox_SJ->currentData().toInt());
        m_serial->setParity((QSerialPort::Parity)ui->comboBox_XY->currentData().toInt());
        m_serial->setStopBits((QSerialPort::StopBits)ui->comboBox_TJ->currentData().toInt());
        m_serial->setFlowControl((QSerialPort::FlowControl)ui->comboBox_LK->currentData().toInt());

        // 真正打开
        if (m_serial->open(QIODevice::ReadWrite)) {
            m_isSerialOpen = true;
            ui->pushButton_Open_Closeser->setText("关闭串口");

            // 锁定下拉框，串口打开时不允许改参数
            ui->comboBoxSerial->setEnabled(false);
            ui->comboBox_BT->setEnabled(false);
            ui->comboBox_SJ->setEnabled(false);
            ui->comboBox_XY->setEnabled(false);
            ui->comboBox_TJ->setEnabled(false);
            ui->comboBox_LK->setEnabled(false);

            ui->label_D1->setText("串口已打开 " + ui->comboBoxSerial->currentData().toString());
        }
        // 如果 open 失败（比如端口被占用），m_isSerialOpen 保持 false，
        // 用户看到按钮还是"打开串口"，可以换端口重试
    }
    updateStatusLabel();  // 刷新底部状态栏
}
```

**执行流程图：**
```
点击按钮
  ├─ m_isSerialOpen == true?  → 关闭串口，解锁参数
  └─ m_isSerialOpen == false? → 检查串口列表是否为空
                                  ├─ 空 → 弹窗提示
                                  └─ 有 → 配置参数 → open()
                                           ├─ 成功 → 锁定参数，按钮变"关闭串口"
                                           └─ 失败 → 什么都不做（m_isSerialOpen 仍为 false）
```

---

## 第七章：发送数据

### 7.1 发送按钮 —— 核心发送逻辑

```cpp
void Widget::on_pushButton_Saveget_send_clicked()
{
    // ① 安全检查
    if (!m_isSerialOpen || !m_serial->isOpen()) {
        QMessageBox::warning(this, "提示", "请先打开串口");
        return;
    }

    // ② 读取输入框文本
    QString text = ui->lineEditText->text();
    if (text.isEmpty()) return;

    // ③ 把文字转换成字节
    QByteArray data;
    if (ui->checkBox_HekSend->isChecked()) {
        // HEX 模式：用户输入的是 "AA BB CC" 这样的十六进制字符串
        data = hexStringToBytes(text);
        if (data.isEmpty()) {
            QMessageBox::warning(this, "格式错误", "HEX格式: AA BB CC");
            return;
        }
    } else {
        // 普通文本模式
        data = text.toUtf8();
    }

    // ④ 追加换行
    if (ui->checkBox_sendNew->isChecked()) {
        data.append("\r\n");
    }

    // ⑤ 写入串口
    qint64 written = m_serial->write(data);

    if (written >= 0) {
        // ⑥ 更新发送计数
        m_sentCount += written;
        ui->label_D3->setText("Sent:" + QString::number(m_sentCount));

        // ⑦ 在接收区回显（蓝色字，方便看到自己发了什么）
        ui->textEditRev->append("<font color='blue'>[发送] " + text + "</font>");

        // ⑧ 更新状态栏 + 记录到历史
        ui->label_D1->setText("send ok! " + QDateTime::currentDateTime().toString("hh:mm:ss"));
        ui->textEdit_2->append("[发送] " + text);
    }
}
```

**流程图：**
```
点发送 → 串口开着吗? → 文本框有字吗? → HEX模式转字节 / 文本转字节
       → 加换行? → m_serial->write() → 更新计数 → 回显
```

### 7.2 定时发送

需要两个槽函数配合：

```cpp
// 勾选框状态变化时触发
void Widget::on_checkBox_timeSend_stateChanged(int state)
{
    if (state == Qt::Checked && m_isSerialOpen) {
        int ms = ui->lineEditRate->text().toInt();
        if (ms < 10) ms = 1000;         // 默认 1000ms
        m_sendTimer->start(ms);         // 启动定时器
    } else {
        m_sendTimer->stop();            // 停止
    }
}

// 定时器每次触发时调用
void Widget::onTimedSend()
{
    if (ui->checkBox_timeSend->isChecked() && m_isSerialOpen) {
        on_pushButton_Saveget_send_clicked();  // 复用发送逻辑
    }
}
```

---

## 第八章：接收数据

### 8.1 核心回调 —— 串口来数据了

```cpp
void Widget::onReadyRead()
{
    // ① 一次性读完所有到达的数据
    QByteArray data = m_serial->readAll();

    // ② 统计字节数
    m_receivedCount += data.size();
    ui->label_D2->setText("Received:" + QString::number(m_receivedCount));

    // ③ 根据用户的勾选决定显示格式
    QString displayText;
    if (ui->checkBox_HEK->isChecked()) {
        displayText = bytesToHexString(data);    // "41 42 43"
    } else {
        displayText = QString::fromUtf8(data);   // "ABC"
    }

    // ④ 加时间戳
    if (ui->checkBox_TIME->isChecked()) {
        QString t = QDateTime::currentDateTime().toString("hh:mm:ss.zzz");
        displayText = "[" + t + "] " + displayText;
    }

    // ⑤ 加自动换行
    if (ui->checkBox_ZDHH->isChecked()) {
        displayText += "\n";
    }

    // ⑥ 追加到接收区（用 insertPlainText 而不是 append，避免强制换行）
    ui->textEditRev->insertPlainText(displayText);
}
```

**`insertPlainText` vs `append` 的区别：**

- `append()` 总是自动在末尾加 `\n`，多收几次数据行间距会很大
- `insertPlainText()` 不自动换行，由你的"自动换行"复选框来控制

### 8.2 配套按钮

```cpp
// 清空接收区
void Widget::on_pushButton_Clearget_clicked()
{
    ui->textEditRev->clear();
    m_receivedCount = 0;
    ui->label_D2->setText("Received:0");
}

// 保存接收内容到文件
void Widget::on_pushButton_Saveget_clicked()
{
    QString path = QFileDialog::getSaveFileName(this, "保存接收内容",
                                                 "D:/serialData.txt",
                                                 "文本文件 (*.txt)");
    if (path.isEmpty()) return;

    QFile file(path);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out << ui->textEditRev->toPlainText();
        file.close();
    }
}

// HEX 显示切换（点击时转换当前已有内容的显示格式）
void Widget::on_checkBox_HEK_clicked(bool checked)
{
    QString currentText = ui->textEditRev->toPlainText();
    if (currentText.isEmpty()) return;

    if (checked) {
        // 文本 → HEX：把已有文字转成十六进制字符串显示
        ui->textEditRev->setText(bytesToHexString(currentText.toUtf8()));
    } else {
        // HEX → 文本：把十六进制字符串还原成文字
        QByteArray data = hexStringToBytes(currentText);
        if (!data.isEmpty()) {
            ui->textEditRev->setText(QString::fromUtf8(data));
        }
    }
}
```

---

## 第九章：工具函数

### 9.1 状态栏更新

```cpp
void Widget::updateStatusLabel()
{
    ui->label_D2->setText("Received:" + QString::number(m_receivedCount));
    ui->label_D3->setText("Sent:" + QString::number(m_sentCount));
    ui->label_D4->setText(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm"));
}
```

### 9.2 HEX 字符串 → 字节数组

用户输入 `"AA BB CC"` → 转成真正的三个字节 `\xAA \xBB \xCC` 发送出去。

```cpp
QByteArray Widget::hexStringToBytes(const QString &hexStr)
{
    // 去掉所有空格，得到 "AABBCC"
    QString cleaned = hexStr.simplified().remove(' ');

    // 十六进制两位一组，长度必须是偶数
    if (cleaned.length() % 2 != 0) return QByteArray();

    QByteArray result;
    bool ok;
    for (int i = 0; i < cleaned.length(); i += 2) {
        quint8 byte = cleaned.mid(i, 2).toUInt(&ok, 16);  // "AA" → 170
        if (!ok) return QByteArray();  // 碰到非法字符（不是0-9 A-F）
        result.append((char)byte);
    }
    return result;
}
```

### 9.3 字节数组 → HEX 显示字符串

收到 `\x41 \x42 \x43` → 在屏幕上显示 `"41 42 43"`。

```cpp
QString Widget::bytesToHexString(const QByteArray &data)
{
    QString result;
    for (int i = 0; i < data.size(); i++) {
        // arg(v, 2, 16, QChar('0')) → 宽度2，16进制，不足两位用'0'补齐
        // .toUpper() → 小写变大写
        result += QString("%1 ").arg((quint8)data.at(i), 2, 16, QChar('0')).toUpper();
    }
    return result.trimmed();  // 去掉最后一个空格
}
```

### 9.4 系统时间实时刷新

#### 1. 在 `widget.h` 里声明函数

```
private slots:
    // ... 已有的槽函数 ...
    void time_reflash();    
```

------

#### 2.在 `widget.h` 里声明定时器指针

```
private:
    // ... 已有的成员变量 ...
    QTimer *m_timeTimer = nullptr;   // ← 时间刷新定时器
```

------

#### 3. 在 `initConnections()` 里创建定时器并连接

```
void Widget::initConnections()
{

    // ===== 时间刷新定时器（新增） =====
    m_timeTimer = new QTimer(this);
    connect(m_timeTimer, &QTimer::timeout, this, &Widget::time_reflash);
    m_timeTimer->start(1000);   // 每秒刷新一次（1000ms）
    // 注意：你想刷"分"的话用 60000（每分钟），刷"秒"的话用 1000
}
```

#### 4 .写方法

```
void Widget::time_reflash()
{
    ui->label_D4->setText(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm"));
}

```

---

## 第十章：析构函数 —— 优雅退出

```cpp
Widget::~Widget()
{
    if (m_serial && m_serial->isOpen()) {
        m_serial->close();    // 窗口关闭前先关串口
    }
    delete ui;
}
```

不关串口直接退出，可能导致串口资源被占用，下次打不开。

---

## 第十一章：多文本快捷发送区

### 一、这个模块有什么

界面右上角的多文本区，总共 3 组控件 × 9 行 = 27 个控件：

```
┌──────┬──────────────┬──────┐
│ HEX  │   字符串      │ 发送 │  ← 表头
├──────┼──────────────┼──────┤
│ □    │ [lineEdit_1] │ [1]  │  ← 第1行
│ □    │ [lineEdit_2] │ [2]  │  ← 第2行
│ □    │ [lineEdit_3] │ [3]  │  ← 第3行
│ ...  │              │      │
│ □    │ [lineEdit_9] │ [9]  │  ← 第9行
├──────┴──────────────┴──────┤
│ □ 循环发送  [100] ms       │  ← 底部控制
│ [保存]  [载入]  [重置]     │
└────────────────────────────┘
```

每行 3 个控件：QCheckBox + QLineEdit + QPushButton

---

### 二、新手的写法

```cpp
// 头文件里要声明 9 个槽
private slots:
    void on_pushButton1_clicked();
    void on_pushButton2_clicked();
    void on_pushButton3_clicked();
    void on_pushButton4_clicked();
    void on_pushButton5_clicked();
    void on_pushButton6_clicked();
    void on_pushButton7_clicked();
    void on_pushButton8_clicked();
    void on_pushButton9_clicked();

// 实现文件里写 9 个几乎一样的函数
void Widget::on_pushButton1_clicked() {
    QString text = ui->lineEdit1->text();
    if (text.isEmpty()) return;
    m_serial->write(text.toUtf8());
}
void Widget::on_pushButton2_clicked() {
    QString text = ui->lineEdit2->text();
    if (text.isEmpty()) return;
    m_serial->write(text.toUtf8());
}
// ... 重复到第9个
```

问题：重复代码多，改起来容易漏，而且文件变得很长。

#### 3.1 存引用：用三个 QList 代替 27 个 ui->xxx

```cpp
// widget.h — 声明三个列表
QList<QPushButton *> buttons;   // 存 9 个按钮
QList<QLineEdit *> lineEdits;   // 存 9 个输入框
QList<QCheckBox *> checkBoxs;   // 存 9 个勾选框
```

#### 3.2 一个循环填充三个列表

在构造函数里，用 `findChild` 按名字动态查找控件：

```cpp
for (int i = 0; i < 9; i++) {
    // 查找按钮 pushButton1 ~ pushButton9
    QPushButton *btn = findChild<QPushButton *>(QString("pushButton%1").arg(i + 1));
    if (btn) {
        btn->setProperty("buttonId", i + 1);           // 打标记：第几行
        buttons.append(btn);                            // 存到列表
        connect(btn, SIGNAL(clicked()), this, SLOT(on_command_button_clicked())); // 连信号
    }
    // 查找 lineEdit
    QLineEdit *edit = findChild<QLineEdit *>(QString("lineEdit%1").arg(i + 1));
    lineEdits.append(edit);                             // 存到列表

    // 查找 checkBox
    QCheckBox *cb = findChild<QCheckBox *>(QString("checkBox%1").arg(i + 1));
    checkBoxs.append(cb);                               // 存到列表
}
```

**代码量对比：**

```
新手写法：27 行手动赋值 + 9 个槽函数声明 + 9 个槽函数实现 → 约 80 行
优化写法：上面这段 for 循环 → 约 17 行
```

#### 3.3 三个技巧解读

| 技巧                             | 代码         | 作用                                   |
| -------------------------------- | ------------ | -------------------------------------- |
| `QString("pushButton%1").arg(i)` | 动态拼控件名 | 用循环变量生成控件名字符串             |
| `findChild<T *>(名字)`           | 按名字查控件 | 不需要 `ui->xxx`，名字是字符串就行     |
| `setProperty("buttonId", i)`     | 给控件打标记 | 槽函数里通过 property 知道是第几个按钮 |

#### 3.4 9 个按钮共用一个槽

```cpp
// 头文件只声明这一个槽就够了
void on_command_button_clicked();

// 实现
void Widget::on_command_button_clicked()
{
    // sender() = 返回触发这个槽的那个控件指针
    QPushButton *btn = qobject_cast<QPushButton *>(sender());
    if (!btn) return;

    // 从按钮上读出之前打好的标记
    int num = btn->property("buttonId").toInt();  // 1~9

    // 取第 num 行的文本，填入主发送框
    if (num - 1 < lineEdits.size() && lineEdits[num - 1]) {
        QString text = lineEdits[num - 1]->text();
        if (!text.isEmpty()) {
            ui->lineEditText->setText(text);
        }
    }

    // 同步该行的 HEX 勾选状态到主发送区
    if (num - 1 < checkBoxs.size() && checkBoxs[num - 1]) {
        ui->checkBox_HekSend->setChecked(checkBoxs[num - 1]->isChecked());
    }

    // 复用主发送逻辑
    on_pushButton_Saveget_send_clicked();
}
```

**`sender()` 是什么？**

点击 `pushButton3`，Qt 调用 `on_command_button_clicked()`，此时 `sender()` 返回的就是 `pushButton3` 的指针。然后 `property("buttonId")` 读出之前存好的 `3`，就知道是第 3 行。

你把 9 个按钮的 clicked 信号都连到这一个槽，Qt 用 `sender()` 帮你区分是谁触发的。

---

### 四、循环发送

#### 4.1 勾选"循环发送" → 启动定时器

```cpp
void Widget::on_checkBox_send_clicked(bool checked)
{
    if (checked && m_isSerialOpen) {
        ui->spinBox->setEnabled(false);                     // 锁住间隔输入
        buttonsConTimer->start(ui->spinBox->value());       // 启动定时器
    } else {
        ui->spinBox->setEnabled(true);
        buttonsConTimer->stop();
    }
}
```

#### 4.2 定时器触发 → 按顺序模拟点击

```cpp
void Widget::buttons_handler()
{
    if (buttonIndex < buttons.size()) {
        QPushButton *btn = buttons[buttonIndex];
        if (btn) emit btn->clicked();    // 代码模拟点击
        buttonIndex++;
    } else {
        buttonIndex = 0;                 // 发完一轮，回到第一个
    }
}
```

**`emit btn->clicked()`** — 用代码触发按钮的 clicked 信号，效果和用户手动点击完全一样。clicked 信号又触发了 `on_command_button_clicked()`，进而执行发送逻辑。

#### 4.3 需要的成员变量

```cpp
// widget.h 中声明
QTimer *buttonsConTimer = nullptr;   // 循环发送定时器
int buttonIndex = 0;                  // 当前发到第几行了

// 构造函数中创建和连接
buttonsConTimer = new QTimer(this);
connect(buttonsConTimer, &QTimer::timeout, this, &Widget::buttons_handler);
```

---

### 五、保存 / 载入 / 重置

#### 5.1 保存

```cpp
void Widget::on_pushButton_3_clicked()      // "保存"按钮
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
```

**保存的文件格式：**

```
0|AT+GMR
1|AT+CWLAP
0|AT+RST
```

`0` = 没勾选，`1` = 勾选了（HEX模式）。用 `|` 分隔，方便解析。

#### 5.2 载入

```cpp
void Widget::on_pushButton_2_clicked()      // "载入"按钮
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
        QStringList parts = line.split("|");       // "1|AT+GMR" → ["1", "AT+GMR"]
        if (parts.count() == 2) {
            if (checkBoxs[i]) checkBoxs[i]->setChecked(parts[0].toInt());
            lineEdits[i]->setText(parts[1]);
        }
        i++;
    }
    file.close();
}
```

#### 5.3 重置

```cpp
void Widget::on_pushButton_clicked()         // "重置"按钮
{
    for (int i = 0; i < lineEdits.size(); i++) {
        lineEdits[i]->clear();                     // 清空文本
        if (checkBoxs[i]) checkBoxs[i]->setChecked(false);  // 取消勾选
    }
}
```

**保存/载入/重置 为什么这么简单？** 因为已经把控件存到 `QList` 里了，遍历列表就行，不用写 9 遍。

---

### 六、完整代码

#### widget.h 中需要添加的部分

```cpp
// ===== private slots: 区域加 =====
void on_command_button_clicked();              // 9个按钮共用一个槽
void on_checkBox_send_clicked(bool checked);  // 循环发送勾选
void buttons_handler();                       // 循环发送定时触发
void on_pushButton_3_clicked();               // 保存多文本
void on_pushButton_2_clicked();               // 载入多文本
void on_pushButton_clicked();                 // 重置多文本
void on_pushButton_Yincmb_clicked();          // 隐藏面板
void on_pushButton_Yincls_clicked();          // 隐藏历史

// ===== private: 成员变量区域加 =====
QList<QPushButton *> buttons;       // 存 9 个按钮
QList<QLineEdit *> lineEdits;       // 存 9 个输入框
QList<QCheckBox *> checkBoxs;       // 存 9 个勾选框
QTimer *buttonsConTimer = nullptr;  // 循环发送定时器
int buttonIndex = 0;                // 循环发送索引
```

#### widget.cpp 构造函数中加

```cpp
// for 循环填充 QList
for (int i = 0; i < 9; i++) {
    QPushButton *btn = findChild<QPushButton *>(QString("pushButton%1").arg(i + 1));
    if (btn) {
        btn->setProperty("buttonId", i + 1);
        buttons.append(btn);
        connect(btn, SIGNAL(clicked()), this, SLOT(on_command_button_clicked()));
    }
    lineEdits.append(findChild<QLineEdit *>(QString("lineEdit%1").arg(i + 1)));
    checkBoxs.append(findChild<QCheckBox *>(QString("checkBox%1").arg(i + 1)));
}

// 循环发送定时器
buttonsConTimer = new QTimer(this);
connect(buttonsConTimer, &QTimer::timeout, this, &Widget::buttons_handler);
```

### 七、知识点速查

| 知识点         | 代码                                    | 说明               |
| -------------- | --------------------------------------- | ------------------ |
| 按名字查控件   | `findChild<QPushButton *>("name")`      | 不需要 `ui->name`  |
| 动态拼接字符串 | `QString("pushButton%1").arg(i)`        | `%1` 被 `i` 替换   |
| 给控件存数据   | `btn->setProperty("key", value)`        | 存任意类型         |
| 读控件数据     | `btn->property("key").toInt()`          | 取出来转类型       |
| 判断谁触发的槽 | `qobject_cast<T *>(sender())`           | 多个控件共用一个槽 |
| 代码触发点击   | `emit btn->clicked()`                   | 模拟用户点击按钮   |
| 字符串分割     | `"1|abc".split("|")`                    | 返回 `{"1","abc"}` |
| 遍历 QList     | `for (int i = 0; i < list.size(); i++)` | 所有控件统一操作   |

---

## 第十二章：隐藏面板 / 隐藏历史

两个按钮分别控制中间面板区（`groupBox_Down2` + `groupBox_Down3`）和历史记录区（`groupBoxRecord3`）的显示/隐藏。

```cpp
// 隐藏/显示面板（中间的按钮区和发送区）
void Widget::on_pushButton_Yincmb_clicked()
{
    bool visible = ui->groupBox_Down2->isVisible();
    ui->groupBox_Down2->setVisible(!visible);
    ui->groupBox_Down3->setVisible(!visible);
    ui->pushButton_Yincmb->setText(visible ? "显示面板" : "隐藏面板");
}

// 隐藏/显示历史记录
void Widget::on_pushButton_Yincls_clicked()
{
    bool visible = ui->groupBoxRecord3->isVisible();
    ui->groupBoxRecord3->setVisible(!visible);
    ui->pushButton_Yincls->setText(visible ? "显示历史" : "隐藏历史");
}
```

**`setVisible` 与 `hide()/show()`：** 效果一样，`setVisible(!visible)` 是取反切换，比 if-else 更简洁。

**`groupBox_Down2` 和 `groupBox_Down3`** 分别是控制按钮区和发送区。`groupBoxRecord3` 是历史记录区。

---

## 第十三章：串口错误处理

当前代码里串口出错没有提示，用户可能一头雾水。在 `initConnections()` 里加一段：

```cpp
    // ===== 串口错误处理（新增） =====
    connect(m_serial, &QSerialPort::errorOccurred, this,
            [this](QSerialPort::SerialPortError error) {
                if (error != QSerialPort::NoError && m_isSerialOpen) {
                    QMessageBox::warning(this, "串口错误", m_serial->errorString());
                    // 出错了自动关串口
                    m_sendTimer->stop();
                    m_loopTimer->stop();
                    m_serial->close();
                    m_isSerialOpen = false;
                    ui->pushButton_Open_Closeser->setText("打开串口");
                    // 恢复参数下拉框
                    ui->comboBoxSerial->setEnabled(true);
                    ui->comboBox_BT->setEnabled(true);
                    ui->comboBox_SJ->setEnabled(true);
                    ui->comboBox_XY->setEnabled(true);
                    ui->comboBox_TJ->setEnabled(true);
                    ui->comboBox_LK->setEnabled(true);
                    ui->label_D1->setText("串口错误: " + m_serial->errorString());
                }
            });
```

**什么时候会触发？** 比如串口线被拔了、对方设备断电了、USB 转串口被弹出了——这时候 Qt 会抛出 `errorOccurred` 信号。

---

## 第十四章：关闭串口时也要停循环定时器

回顾第六章的关闭分支，把循环定时器也停掉：

```cpp
    if (m_isSerialOpen) {
        m_sendTimer->stop();         // 停止定时发送
        buttonsConTimer->stop();     // ← 停止循环发送
        m_serial->close();
        ...
    }
```

---

## 完整文件结构总览（当前代码）

```
widget.h   (约94行)
    ├── #include 头文件
    ├── class Widget 声明
    │   ├── 构造/析构
    │   ├── private slots: 18个
    │   ├── private: 初始化方法（5个）
    │   ├── private: 工具函数（3个）
    │   └── private: 成员变量（8个 + 3个QList）

widget.cpp (约580行)
    ├── 模块一：构造函数（含 for 循环填充多文本 QList）
    ├── 模块二：初始化辅助方法
    ├── 模块三：串口控制（打开/关闭）
    ├── 模块四：发送功能（普通/HEX/新行/定时）
    ├── 模块五：多文本快捷发送 + 循环发送 + 面板控制
    │   ├── 9个按钮共用一个槽（findChild + sender + property）
    │   ├── 循环发送（emit btn->clicked 模拟点击）
    │   ├── 保存/载入/重置多文本（QList 遍历）
    │   └── 隐藏面板/历史（setVisible 切换）
    ├── 模块六：接收功能（回调/HEX显示/时间戳/换行/清空/保存）
    └── 模块七：工具函数（状态栏/HEX转换/时间刷新）
```

---

## 你现在能用哪些功能了

| 功能 | 操作 |
|------|------|
| 打开串口 | 选好参数 → 点"打开串口"按钮 |
| 发送文本 | 输入文字 → 点"发送" |
| 发送 HEX | 勾选"HEK发送" → 输入如 `AA BB CC` → 点发送 |
| 发送换行 | 勾选"发送新行" → 发送时自动追加 `\r\n` |
| 定时发送 | 勾选"定时发送" → 输入间隔 ms |
| 快捷发送 | 在右侧 9 行里预填内容 → 点行末按钮 |
| 循环发送 | 勾选某些行的 QCheckBox → 勾选"循环发送" → 设好间隔 |
| 多文本保存 | 点"保存"按钮 → 选路径 → 9 行内容存为 .txt |
| 多文本载入 | 点"载入"按钮 → 选 .txt 文件 → 自动填到 9 行 |
| 多文本重置 | 点"重置"按钮 → 清空全部 9 行 |
| 接收显示 | 自动显示在接收区 |
| HEX 显示 | 勾选"HEK显示" |
| 时间戳 | 勾选"接收时间" |
| 自动换行 | 勾选"自动换行" |
| 清空接收 | 点"清空接收"按钮 |
| 保存接收 | 点"保存接收"按钮 |
| 隐藏面板 | 点"隐藏面板" → 中间区域消失，按钮变"显示面板" |
| 隐藏历史 | 点"隐藏历史" → 历史区消失，按钮变"显示历史" |
| 串口错误提示 | 串口异常自动弹窗 + 关闭串口 |

---



