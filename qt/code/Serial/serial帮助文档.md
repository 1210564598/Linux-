# Qt串口调试助手 —— 内部组件完整手册

> 每个组件列出：**常用函数**（含参数/返回值）、**信号**、**枚举常量**、**代码示例**

------

## 一、串口通信

### 1. QSerialPort

**头文件：** `#include <QSerialPort>`
**模块：** `QT += serialport`

#### 构造函数

| 函数                                     | 说明                             |
| :--------------------------------------- | :------------------------------- |
| `QSerialPort(QObject *parent = nullptr)` | 创建串口对象，parent负责内存管理 |

#### 设置参数

| 函数                                           | 参数             | 返回值 | 说明               |
| :--------------------------------------------- | :--------------- | :----- | :----------------- |
| `setPortName(QString name)`                    | 端口名，如"COM3" | `void` | 设置串口设备名     |
| `setBaudRate(qint32 baudRate)`                 | 波特率数值       | `bool` | 设置波特率         |
| `setBaudRate(qint32 baudRate, Directions dir)` | 波特率 + 方向    | `bool` | 分别设置收发波特率 |
| `setDataBits(DataBits dataBits)`               | 数据位枚举       | `void` | 设置数据位         |
| `setParity(Parity parity)`                     | 校验位枚举       | `void` | 设置校验位         |
| `setStopBits(StopBits stopBits)`               | 停止位枚举       | `void` | 设置停止位         |
| `setFlowControl(FlowControl flow)`             | 流控枚举         | `void` | 设置流控           |

#### 打开/关闭/状态

| 函数                  | 参数                   | 返回值    | 说明             |
| :-------------------- | :--------------------- | :-------- | :--------------- |
| `open(OpenMode mode)` | `QIODevice::ReadWrite` | `bool`    | 打开串口         |
| `close()`             | 无                     | `void`    | 关闭串口         |
| `isOpen()`            | 无                     | `bool`    | 是否已打开       |
| `isWritable()`        | 无                     | `bool`    | 是否可写         |
| `isReadable()`        | 无                     | `bool`    | 是否可读         |
| `errorString()`       | 无                     | `QString` | 最后一次错误描述 |

#### 读写数据

| 函数                                      | 参数            | 返回值       | 说明                     |
| :---------------------------------------- | :-------------- | :----------- | :----------------------- |
| `write(const QByteArray &data)`           | 要发送的数据    | `qint64`     | 发送数据，返回实际字节数 |
| `write(const char *data, qint64 maxSize)` | 数据指针 + 长度 | `qint64`     | 发送指定长度数据         |
| `readAll()`                               | 无              | `QByteArray` | 读取所有可用数据         |
| `read(qint64 maxSize)`                    | 最大读取字节数  | `QByteArray` | 读取指定长度             |
| `readLine(qint64 maxSize = 0)`            | 最大读取长度    | `QByteArray` | 读一行（遇到换行停止）   |
| `bytesAvailable()`                        | 无              | `qint64`     | 可读字节数               |
| `bytesToWrite()`                          | 无              | `qint64`     | 等待发送的字节数         |
| `clear()`                                 | 无              | `void`       | 清空所有缓冲区           |
| `flush()`                                 | 无              | `bool`       | 立即发送所有缓冲数据     |

#### 信号

| 信号                                   | 参数       | 说明               |
| :------------------------------------- | :--------- | :----------------- |
| `readyRead()`                          | 无         | 有新数据可读时触发 |
| `errorOccurred(SerialPortError error)` | 错误枚举   | 发生错误时触发     |
| `bytesWritten(qint64 bytes)`           | 写入字节数 | 数据已写入时触发   |

#### 枚举常量

cpp

```
// 波特率
QSerialPort::Baud1200
QSerialPort::Baud2400
QSerialPort::Baud4800
QSerialPort::Baud9600
QSerialPort::Baud19200
QSerialPort::Baud38400
QSerialPort::Baud57600
QSerialPort::Baud115200

// 数据位
QSerialPort::Data5
QSerialPort::Data6
QSerialPort::Data7
QSerialPort::Data8

// 校验位
QSerialPort::NoParity
QSerialPort::EvenParity
QSerialPort::OddParity
QSerialPort::MarkParity
QSerialPort::SpaceParity

// 停止位
QSerialPort::OneStop
QSerialPort::OneAndHalfStop
QSerialPort::TwoStop

// 流控
QSerialPort::NoFlowControl
QSerialPort::HardwareControl   // RTS/CTS
QSerialPort::SoftwareControl   // XON/XOFF

// 错误码
QSerialPort::NoError
QSerialPort::DeviceNotFoundError
QSerialPort::PermissionError
QSerialPort::OpenError
QSerialPort::WriteError
QSerialPort::ReadError
QSerialPort::ResourceError
QSerialPort::UnsupportedOperationError
QSerialPort::TimeoutError
QSerialPort::NotOpenError
```



#### 完整示例

cpp

```
// 创建
QSerialPort *serial = new QSerialPort(this);

// 配置
serial->setPortName("COM3");
serial->setBaudRate(QSerialPort::Baud9600);
serial->setDataBits(QSerialPort::Data8);
serial->setParity(QSerialPort::NoParity);
serial->setStopBits(QSerialPort::OneStop);
serial->setFlowControl(QSerialPort::NoFlowControl);

// 打开
if (serial->open(QIODevice::ReadWrite)) {
    qDebug() << "串口打开成功";
}

// 发送
QByteArray data = "Hello";
qint64 written = serial->write(data);

// 接收（在 readyRead 槽中）
QByteArray received = serial->readAll();

// 关闭
serial->close();
```



------

### 2. QSerialPortInfo

**头文件：** `#include <QSerialPortInfo>`

#### 静态函数

| 函数               | 返回值                   | 说明                 |
| :----------------- | :----------------------- | :------------------- |
| `availablePorts()` | `QList<QSerialPortInfo>` | 获取所有可用串口列表 |

#### 成员函数

| 函数                  | 返回值    | 说明                           |
| :-------------------- | :-------- | :----------------------------- |
| `portName()`          | `QString` | 端口名，如"COM3"               |
| `description()`       | `QString` | 端口描述，如"USB-SERIAL CH340" |
| `manufacturer()`      | `QString` | 制造商                         |
| `serialNumber()`      | `QString` | 序列号                         |
| `vendorIdentifier()`  | `quint16` | 厂商ID                         |
| `productIdentifier()` | `quint16` | 产品ID                         |
| `isBusy()`            | `bool`    | 是否被占用                     |
| `isNull()`            | `bool`    | 是否为空（无效）               |

#### 完整示例

cpp

```
QList<QSerialPortInfo> ports = QSerialPortInfo::availablePorts();
for (const QSerialPortInfo &info : ports) {
    qDebug() << "端口:" << info.portName()
             << "描述:" << info.description()
             << "占用:" << info.isBusy();
}
```



------

## 二、定时器

### QTimer

**头文件：** `#include <QTimer>`

#### 构造函数

| 函数                                | 说明           |
| :---------------------------------- | :------------- |
| `QTimer(QObject *parent = nullptr)` | 创建定时器对象 |

#### 常用函数

| 函数                             | 参数         | 返回值 | 说明                     |
| :------------------------------- | :----------- | :----- | :----------------------- |
| `start(int msec)`                | 间隔毫秒数   | `void` | 启动定时器               |
| `start()`                        | 无           | `void` | 用已设置的间隔启动       |
| `stop()`                         | 无           | `void` | 停止定时器               |
| `setInterval(int msec)`          | 毫秒数       | `void` | 设置间隔                 |
| `setSingleShot(bool singleShot)` | 是否单次触发 | `void` | 设为true则只触发一次     |
| `isActive()`                     | 无           | `bool` | 是否运行中               |
| `interval()`                     | 无           | `int`  | 获取当前间隔             |
| `remainingTime()`                | 无           | `int`  | 距离下次触发的剩余毫秒数 |

#### 静态函数

| 函数                                                         | 参数                 | 说明         |
| :----------------------------------------------------------- | :------------------- | :----------- |
| `singleShot(int msec, QObject *receiver, const char *member)` | 间隔、接收者、槽函数 | 单次定时触发 |

#### 信号

| 信号        | 说明             |
| :---------- | :--------------- |
| `timeout()` | 定时器到期时触发 |

#### 完整示例

cpp

```
QTimer *timer = new QTimer(this);
timer->setInterval(1000);  // 1秒

connect(timer, &QTimer::timeout, this, []() {
    qDebug() << "定时器触发";
});

timer->start();  // 开始

// 单次定时
QTimer::singleShot(3000, this, []() {
    qDebug() << "3秒后执行一次";
});

// 停止
timer->stop();
```



------

## 三、UI控件

### 1. QComboBox

**头文件：** `#include <QComboBox>`

#### 添加/删除选项

| 函数                                                     | 参数            | 返回值 | 说明               |
| :------------------------------------------------------- | :-------------- | :----- | :----------------- |
| `addItem(const QString &text)`                           | 显示文字        | `void` | 添加选项           |
| `addItem(const QString &text, const QVariant &userData)` | 文字 + 隐藏数据 | `void` | 添加选项（带数据） |
| `addItems(const QStringList &list)`                      | 字符串列表      | `void` | 批量添加           |
| `insertItem(int index, const QString &text)`             | 索引 + 文字     | `void` | 在指定位置插入     |
| `removeItem(int index)`                                  | 索引            | `void` | 删除指定选项       |
| `clear()`                                                | 无              | `void` | 清空所有选项       |

#### 读取/设置

| 函数                                  | 参数     | 返回值     | 说明                 |
| :------------------------------------ | :------- | :--------- | :------------------- |
| `currentText()`                       | 无       | `QString`  | 当前选中项的文字     |
| `currentData()`                       | 无       | `QVariant` | 当前选中项的隐藏数据 |
| `currentIndex()`                      | 无       | `int`      | 当前索引（0开始）    |
| `setCurrentIndex(int index)`          | 索引     | `void`     | 按索引选中           |
| `setCurrentText(const QString &text)` | 文字     | `void`     | 按文字选中           |
| `itemText(int index)`                 | 索引     | `QString`  | 获取指定项的文字     |
| `itemData(int index)`                 | 索引     | `QVariant` | 获取指定项的隐藏数据 |
| `count()`                             | 无       | `int`      | 选项总数             |
| `setEnabled(bool enable)`             | 是否启用 | `void`     | 启用/禁用            |

#### 信号

| 信号                                      | 参数   | 说明               |
| :---------------------------------------- | :----- | :----------------- |
| `currentIndexChanged(int index)`          | 新索引 | 选中索引变化时触发 |
| `currentTextChanged(const QString &text)` | 新文字 | 选中文字变化时触发 |
| `activated(int index)`                    | 索引   | 用户选择时触发     |

#### 完整示例

cpp

```
// 添加选项（带隐藏数据）
comboBox->addItem("9600", QSerialPort::Baud9600);
comboBox->addItem("115200", QSerialPort::Baud115200);

// 默认选中
comboBox->setCurrentIndex(0);

// 读取
QString text = comboBox->currentText();        // "9600"
int value = comboBox->currentData().toInt();   // 枚举值

// 清空
comboBox->clear();
```



------

### 2. QLineEdit

**头文件：** `#include <QLineEdit>`

#### 常用函数

| 函数                                      | 参数     | 返回值    | 说明             |
| :---------------------------------------- | :------- | :-------- | :--------------- |
| `text()`                                  | 无       | `QString` | 获取文本         |
| `setText(const QString &text)`            | 文字     | `void`    | 设置文本         |
| `clear()`                                 | 无       | `void`    | 清空             |
| `setPlaceholderText(const QString &text)` | 提示文字 | `void`    | 设置灰色占位文字 |
| `setReadOnly(bool enable)`                | 是否只读 | `void`    | 设为只读模式     |
| `setEnabled(bool enable)`                 | 是否启用 | `void`    | 启用/禁用        |
| `setMaxLength(int length)`                | 最大长度 | `void`    | 限制输入长度     |
| `setEchoMode(EchoMode mode)`              | 显示模式 | `void`    | 密码模式等       |
| `selectAll()`                             | 无       | `void`    | 全选文本         |
| `cursorPosition()`                        | 无       | `int`     | 光标位置         |

#### EchoMode 枚举

| 值                              | 说明                       |
| :------------------------------ | :------------------------- |
| `QLineEdit::Normal`             | 正常显示（默认）           |
| `QLineEdit::NoEcho`             | 不显示任何字符             |
| `QLineEdit::Password`           | 密码模式（显示圆点）       |
| `QLineEdit::PasswordEchoOnEdit` | 编辑时可见，失去焦点变圆点 |

#### 信号

| 信号                               | 参数   | 说明                             |
| :--------------------------------- | :----- | :------------------------------- |
| `textChanged(const QString &text)` | 新文本 | 文本变化时触发（程序修改也触发） |
| `textEdited(const QString &text)`  | 新文本 | 用户编辑时触发（程序修改不触发） |
| `returnPressed()`                  | 无     | 按回车时触发                     |
| `selectionChanged()`               | 无     | 选中内容变化时触发               |

#### 完整示例

cpp

```
lineEdit->setText("Hello");
lineEdit->setPlaceholderText("请输入内容");
QString str = lineEdit->text();

connect(lineEdit, &QLineEdit::textChanged, this, [](const QString &text) {
    qDebug() << "输入:" << text;
});

connect(lineEdit, &QLineEdit::returnPressed, this, []() {
    qDebug() << "按了回车";
});
```



------

### 3. QTextEdit

**头文件：** `#include <QTextEdit>`

#### 常用函数

| 函数                                          | 参数     | 返回值        | 说明                     |
| :-------------------------------------------- | :------- | :------------ | :----------------------- |
| `toPlainText()`                               | 无       | `QString`     | 获取纯文本               |
| `toHtml()`                                    | 无       | `QString`     | 获取HTML格式             |
| `setPlainText(const QString &text)`           | 纯文本   | `void`        | 设置纯文本               |
| `setHtml(const QString &html)`                | HTML     | `void`        | 设置HTML格式             |
| `append(const QString &text)`                 | 文字     | `void`        | 追加（自动换行）         |
| `insertPlainText(const QString &text)`        | 文字     | `void`        | 插入纯文本（不自动换行） |
| `clear()`                                     | 无       | `void`        | 清空                     |
| `setReadOnly(bool enable)`                    | 是否只读 | `void`        | 设为只读                 |
| `setWordWrapMode(QTextOption::WrapMode mode)` | 换行模式 | `void`        | 设置自动换行             |
| `textCursor()`                                | 无       | `QTextCursor` | 获取光标对象             |
| `moveCursor(QTextCursor::MoveOperation op)`   | 移动操作 | `void`        | 移动光标                 |
| `ensureCursorVisible()`                       | 无       | `void`        | 滚动到光标位置           |

#### 信号

| 信号                      | 参数 | 说明               |
| :------------------------ | :--- | :----------------- |
| `textChanged()`           | 无   | 内容变化时触发     |
| `cursorPositionChanged()` | 无   | 光标移动时触发     |
| `selectionChanged()`      | 无   | 选中内容变化时触发 |

#### 完整示例

cpp

```
// 显示接收数据（不自动换行）
textEdit->insertPlainText(receivedData);

// 追加日志（自动换行）
textEdit->append("[日志] 操作完成");

// 带颜色
textEdit->append("<font color='blue'>蓝色文字</font>");

// 清空
textEdit->clear();

// 滚动到底部（自动跟随最新数据）
textEdit->moveCursor(QTextCursor::End);
textEdit->ensureCursorVisible();
```



------

### 4. QCheckBox

**头文件：** `#include <QCheckBox>`

#### 常用函数

| 函数                                  | 参数         | 返回值           | 说明                 |
| :------------------------------------ | :----------- | :--------------- | :------------------- |
| `isChecked()`                         | 无           | `bool`           | 是否勾选             |
| `setChecked(bool checked)`            | 是否勾选     | `void`           | 设置勾选状态         |
| `checkState()`                        | 无           | `Qt::CheckState` | 获取状态（支持三态） |
| `setCheckState(Qt::CheckState state)` | 状态         | `void`           | 设置状态（三态）     |
| `setTristate(bool yes)`               | 是否启用三态 | `void`           | 启用三态模式         |

#### Qt::CheckState 常量

| 常量                   | 值   | 说明             |
| :--------------------- | :--- | :--------------- |
| `Qt::Unchecked`        | 0    | 未勾选           |
| `Qt::PartiallyChecked` | 1    | 部分勾选（三态） |
| `Qt::Checked`          | 2    | 勾选             |

#### 信号

| 信号                      | 参数          | 说明           |
| :------------------------ | :------------ | :------------- |
| `stateChanged(int state)` | 新状态(0/1/2) | 状态变化时触发 |
| `toggled(bool checked)`   | 是否勾选      | 开关切换时触发 |

#### 完整示例

cpp

```
// 判断
if (checkBox->isChecked()) {
    // 勾选时执行
}

// 信号连接
connect(checkBox, &QCheckBox::stateChanged, this, [](int state) {
    if (state == Qt::Checked) {
        qDebug() << "已勾选";
    } else {
        qDebug() << "未勾选";
    }
});

// 设置
checkBox->setChecked(true);
```



------

### 5. QPushButton

**头文件：** `#include <QPushButton>`

#### 常用函数

| 函数                           | 参数       | 返回值    | 说明                     |
| :----------------------------- | :--------- | :-------- | :----------------------- |
| `setText(const QString &text)` | 文字       | `void`    | 设置按钮文字             |
| `text()`                       | 无         | `QString` | 获取按钮文字             |
| `setEnabled(bool enable)`      | 是否启用   | `void`    | 启用/禁用                |
| `setIcon(const QIcon &icon)`   | 图标       | `void`    | 设置图标                 |
| `setCheckable(bool checkable)` | 是否可切换 | `void`    | 设为开关模式             |
| `isChecked()`                  | 无         | `bool`    | 开关模式下是否按下       |
| `setAutoRepeat(bool enable)`   | 是否启用   | `void`    | 长按时自动重复触发       |
| `setDefault(bool isDefault)`   | 是否默认   | `void`    | 设为默认按钮（回车触发） |

#### 信号

| 信号                    | 参数     | 说明                   |
| :---------------------- | :------- | :--------------------- |
| `clicked()`             | 无       | 点击时触发（最常用）   |
| `clicked(bool checked)` | 是否按下 | 点击时触发（开关模式） |
| `pressed()`             | 无       | 按下时触发             |
| `released()`            | 无       | 释放时触发             |
| `toggled(bool checked)` | 是否按下 | 开关模式下状态变化触发 |

#### 完整示例

cpp

```
// 修改文字
button->setText("打开串口");
button->setEnabled(false);  // 禁用

// 连接信号
connect(button, &QPushButton::clicked, this, &Widget::onButtonClick);

// 开关模式
button->setCheckable(true);
connect(button, &QPushButton::toggled, this, [](bool checked) {
    qDebug() << "状态:" << checked;
});
```



------

### 6. QLabel

**头文件：** `#include <QLabel>`

#### 常用函数

| 函数                                    | 参数     | 返回值    | 说明                     |
| :-------------------------------------- | :------- | :-------- | :----------------------- |
| `setText(const QString &text)`          | 文字     | `void`    | 设置文字                 |
| `text()`                                | 无       | `QString` | 获取文字                 |
| `setPixmap(const QPixmap &pixmap)`      | 图片     | `void`    | 显示图片                 |
| `setAlignment(Qt::Alignment alignment)` | 对齐方式 | `void`    | 设置对齐                 |
| `setWordWrap(bool wrap)`                | 是否换行 | `void`    | 自动换行                 |
| `setNum(int num)`                       | 数字     | `void`    | 显示数字（自动转字符串） |
| `setIndent(int indent)`                 | 缩进像素 | `void`    | 设置缩进                 |
| `setOpenExternalLinks(bool enable)`     | 是否允许 | `void`    | 允许点击链接打开浏览器   |

#### 完整示例

cpp

```
// 显示状态
label->setText("串口已打开 COM3");

// 带颜色
label->setText("<font color='green'>连接成功</font>");

// 显示数字
label->setNum(1024);  // 显示 "1024"

// 右对齐
label->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
```



------

### 7. QSpinBox

**头文件：** `#include <QSpinBox>`

#### 常用函数

| 函数                               | 参数      | 返回值 | 说明               |
| :--------------------------------- | :-------- | :----- | :----------------- |
| `value()`                          | 无        | `int`  | 获取当前值         |
| `setValue(int value)`              | 数值      | `void` | 设置数值           |
| `setMinimum(int min)`              | 最小值    | `void` | 设置最小值         |
| `setMaximum(int max)`              | 最大值    | `void` | 设置最大值         |
| `setRange(int min, int max)`       | 最小+最大 | `void` | 同时设置范围       |
| `setSingleStep(int step)`          | 步长      | `void` | 点击箭头变化的步长 |
| `setSuffix(const QString &suffix)` | 后缀      | `void` | 如 "ms"            |
| `setPrefix(const QString &prefix)` | 前缀      | `void` | 如 "$"             |
| `setWrapping(bool wrapping)`       | 是否循环  | `void` | 超出范围时循环     |

#### 信号

| 信号                               | 参数   | 说明           |
| :--------------------------------- | :----- | :------------- |
| `valueChanged(int value)`          | 新值   | 数值变化时触发 |
| `textChanged(const QString &text)` | 新文字 | 文字变化时触发 |

#### 完整示例

cpp

```
spinBox->setRange(10, 10000);
spinBox->setValue(1000);
spinBox->setSuffix(" ms");
spinBox->setSingleStep(100);

int ms = spinBox->value();
```



------

### 8. QGroupBox

**头文件：** `#include <QGroupBox>`

#### 常用函数

| 函数                             | 参数       | 返回值    | 说明                        |
| :------------------------------- | :--------- | :-------- | :-------------------------- |
| `setTitle(const QString &title)` | 标题       | `void`    | 设置组标题                  |
| `title()`                        | 无         | `QString` | 获取标题                    |
| `setChecked(bool checked)`       | 是否勾选   | `void`    | 勾选组（启用/禁用组内控件） |
| `isChecked()`                    | 无         | `bool`    | 是否勾选                    |
| `setCheckable(bool checkable)`   | 是否可勾选 | `void`    | 设为可勾选模式              |
| `setVisible(bool visible)`       | 是否可见   | `void`    | 显示/隐藏整个组             |
| `isVisible()`                    | 无         | `bool`    | 是否可见                    |

#### 完整示例

cpp

```
// 隐藏整个面板
groupBox->setVisible(false);

// 切换显示
bool visible = groupBox->isVisible();
groupBox->setVisible(!visible);

// 标题
groupBox->setTitle("串口参数");
```



------

## 四、数据类型

### 1. QByteArray

**头文件：** `#include <QByteArray>`

#### 构造函数

| 函数                                     | 说明           |
| :--------------------------------------- | :------------- |
| `QByteArray()`                           | 空字节数组     |
| `QByteArray(const char *data)`           | 从C字符串创建  |
| `QByteArray(const char *data, int size)` | 从指定长度创建 |
| `QByteArray(int size, char ch)`          | 用指定字符填充 |

#### 常用函数

| 函数                                   | 参数         | 返回值        | 说明                 |
| :------------------------------------- | :----------- | :------------ | :------------------- |
| `size()`                               | 无           | `int`         | 字节数               |
| `isEmpty()`                            | 无           | `bool`        | 是否为空             |
| `at(int pos)`                          | 索引         | `char`        | 取指定字节（只读）   |
| `operator[](int pos)`                  | 索引         | `char&`       | 取/改指定字节        |
| `append(const QByteArray &data)`       | 数据         | `QByteArray&` | 追加                 |
| `append(char ch)`                      | 单个字符     | `QByteArray&` | 追加字符             |
| `prepend(const QByteArray &data)`      | 数据         | `QByteArray&` | 前置插入             |
| `clear()`                              | 无           | `void`        | 清空                 |
| `remove(int pos, int len)`             | 位置 + 长度  | `QByteArray&` | 删除指定范围         |
| `left(int len)`                        | 长度         | `QByteArray`  | 取左侧N个字节        |
| `right(int len)`                       | 长度         | `QByteArray`  | 取右侧N个字节        |
| `mid(int pos, int len)`                | 位置 + 长度  | `QByteArray`  | 取中间部分           |
| `indexOf(char ch, int from)`           | 字符 + 起始  | `int`         | 查找字符位置         |
| `contains(const QByteArray &data)`     | 数据         | `bool`        | 是否包含             |
| `startsWith(char ch)`                  | 字符         | `bool`        | 是否以...开头        |
| `endsWith(char ch)`                    | 字符         | `bool`        | 是否以...结尾        |
| `toHex()`                              | 无           | `QByteArray`  | 转HEX字符串          |
| `fromHex(const QByteArray &hex)`       | HEX字符串    | `QByteArray`  | 从HEX解析（静态）    |
| `toBase64()`                           | 无           | `QByteArray`  | 转Base64             |
| `fromBase64(const QByteArray &base64)` | Base64字符串 | `QByteArray`  | 从Base64解析（静态） |

#### 完整示例

cpp

```
QByteArray data = "Hello";
data.append("\r\n");              // "Hello\r\n"
data.prepend(">> ");              // ">> Hello\r\n"

int len = data.size();            // 10
char ch = data.at(3);             // 'l'

// HEX转换
QByteArray hex = data.toHex();    // "48656c6c6f0d0a"
QByteArray original = QByteArray::fromHex(hex);

// 清空
data.clear();
```



------

### 2. QString

**头文件：** `#include <QString>`

#### 构造函数

| 函数                            | 说明           |
| :------------------------------ | :------------- |
| `QString()`                     | 空字符串       |
| `QString(const char *str)`      | 从C字符串创建  |
| `QString(const QByteArray &ba)` | 从字节数组创建 |

#### 常用函数

| 函数                             | 参数          | 返回值        | 说明                         |
| :------------------------------- | :------------ | :------------ | :--------------------------- |
| `isEmpty()`                      | 无            | `bool`        | 是否为空                     |
| `isNull()`                       | 无            | `bool`        | 是否为空指针                 |
| `length()` / `size()`            | 无            | `int`         | 字符数                       |
| `at(int pos)`                    | 索引          | `QChar`       | 取指定字符                   |
| `operator[](int pos)`            | 索引          | `QChar&`      | 取/改指定字符                |
| `append(const QString &str)`     | 字符串        | `QString&`    | 追加                         |
| `prepend(const QString &str)`    | 字符串        | `QString&`    | 前置插入                     |
| `clear()`                        | 无            | `void`        | 清空                         |
| `remove(int pos, int len)`       | 位置+长度     | `QString&`    | 删除指定范围                 |
| `remove(QChar ch)`               | 字符          | `QString&`    | 删除所有指定字符             |
| `replace(QChar old, QChar new)`  | 旧+新         | `QString&`    | 替换                         |
| `trimmed()`                      | 无            | `QString`     | 去掉首尾空白                 |
| `simplified()`                   | 无            | `QString`     | 去掉多余空格（保留一个空格） |
| `left(int len)`                  | 长度          | `QString`     | 取左侧N个字符                |
| `right(int len)`                 | 长度          | `QString`     | 取右侧N个字符                |
| `mid(int pos, int len)`          | 位置+长度     | `QString`     | 取中间部分                   |
| `split(QChar sep)`               | 分隔符        | `QStringList` | 拆分                         |
| `contains(const QString &str)`   | 子串          | `bool`        | 是否包含                     |
| `startsWith(const QString &str)` | 前缀          | `bool`        | 是否以...开头                |
| `endsWith(const QString &str)`   | 后缀          | `bool`        | 是否以...结尾                |
| `toInt(bool *ok, int base)`      | 是否成功+进制 | `int`         | 转整数                       |
| `toUInt(bool *ok, int base)`     | 是否成功+进制 | `uint`        | 转无符号整数                 |
| `toDouble(bool *ok)`             | 是否成功      | `double`      | 转浮点数                     |
| `toUtf8()`                       | 无            | `QByteArray`  | 转UTF-8字节数组              |
| `toLatin1()`                     | 无            | `QByteArray`  | 转Latin1字节数组             |
| `number(int num)`                | 数字          | `QString`     | 数字转字符串（静态）         |

#### 静态函数

| 函数                                           | 参数             | 返回值    | 说明           |
| :--------------------------------------------- | :--------------- | :-------- | :------------- |
| `number(int n)`                                | 数字             | `QString` | 数字转字符串   |
| `number(double n, char format, int precision)` | 浮点数+格式+精度 | `QString` | 浮点数转字符串 |

#### 完整示例

cpp

```
QString str = " Hello World ";
str = str.trimmed();           // "Hello World"

// 拆分
QStringList list = str.split(" ");
// list = ["Hello", "World"]

// 替换
str.replace("World", "Qt");    // "Hello Qt"

// HEX转数字
bool ok;
int val = QString("FF").toUInt(&ok, 16);  // 255

// 数字格式化
QString hex = QString("%1").arg(255, 2, 16, QChar('0')).toUpper();  // "FF"

// 转字节
QByteArray data = str.toUtf8();
```



------

### 3. QVariant

**头文件：** `#include <QVariant>`

#### 构造函数

| 函数                                | 说明             |
| :---------------------------------- | :--------------- |
| `QVariant()`                        | 空（无效）       |
| `QVariant(int value)`               | 从int创建        |
| `QVariant(const QString &value)`    | 从QString创建    |
| `QVariant(const QByteArray &value)` | 从QByteArray创建 |

#### 常用函数

| 函数            | 参数 | 返回值           | 说明         |
| :-------------- | :--- | :--------------- | :----------- |
| `toInt()`       | 无   | `int`            | 转int        |
| `toUInt()`      | 无   | `uint`           | 转uint       |
| `toLongLong()`  | 无   | `qint64`         | 转64位整数   |
| `toString()`    | 无   | `QString`        | 转字符串     |
| `toByteArray()` | 无   | `QByteArray`     | 转字节数组   |
| `toBool()`      | 无   | `bool`           | 转bool       |
| `toDouble()`    | 无   | `double`         | 转浮点数     |
| `isValid()`     | 无   | `bool`           | 是否有效     |
| `isNull()`      | 无   | `bool`           | 是否为空     |
| `type()`        | 无   | `QVariant::Type` | 获取数据类型 |

#### 完整示例

cpp

```
// 存
QVariant v1 = 9600;
QVariant v2 = QSerialPort::Baud9600;  // 存枚举
QVariant v3 = "COM3";

// 取
int val1 = v1.toInt();        // 9600
int val2 = v2.toInt();        // 枚举值
QString val3 = v3.toString(); // "COM3"
```



------

### 4. QStringList

**头文件：** `#include <QStringList>`

#### 常用函数

| 函数                                                       | 参数       | 返回值         | 说明             |
| :--------------------------------------------------------- | :--------- | :------------- | :--------------- |
| `append(const QString &str)`                               | 字符串     | `void`         | 追加             |
| `operator<<(const QString &str)`                           | 字符串     | `QStringList&` | 追加（运算符）   |
| `join(const QString &sep)`                                 | 分隔符     | `QString`      | 合并成字符串     |
| `contains(const QString &str)`                             | 子串       | `bool`         | 是否包含         |
| `filter(const QString &str)`                               | 过滤字符串 | `QStringList`  | 过滤包含子串的项 |
| `replaceInStrings(const QString &old, const QString &new)` | 旧+新      | `QStringList&` | 批量替换         |
| `removeDuplicates()`                                       | 无         | `void`         | 去重             |
| `sort()`                                                   | 无         | `void`         | 排序             |

#### 完整示例

cpp

```
QStringList list;
list << "COM1" << "COM2" << "COM3";
list.append("COM4");

QString all = list.join(", ");  // "COM1, COM2, COM3, COM4"
```



------

## 五、时间日期

### QDateTime

**头文件：** `#include <QDateTime>`

#### 静态函数

| 函数                   | 返回值      | 说明             |
| :--------------------- | :---------- | :--------------- |
| `currentDateTime()`    | `QDateTime` | 获取当前日期时间 |
| `currentDateTimeUtc()` | `QDateTime` | 获取当前UTC时间  |

#### 常用函数

| 函数                              | 参数       | 返回值      | 说明                 |
| :-------------------------------- | :--------- | :---------- | :------------------- |
| `toString(const QString &format)` | 格式字符串 | `QString`   | 格式化输出           |
| `date()`                          | 无         | `QDate`     | 获取日期部分         |
| `time()`                          | 无         | `QTime`     | 获取时间部分         |
| `toTime_t()`                      | 无         | `uint`      | 转Unix时间戳         |
| `fromTime_t(uint seconds)`        | 时间戳     | `QDateTime` | 从时间戳创建（静态） |
| `addSecs(int secs)`               | 秒数       | `QDateTime` | 加减秒数             |
| `addDays(int days)`               | 天数       | `QDateTime` | 加减天数             |
| `secsTo(const QDateTime &other)`  | 另一个时间 | `int`       | 计算秒差             |

#### 格式占位符

| 占位符      | 说明                  | 示例 |
| :---------- | :-------------------- | :--- |
| `yyyy`      | 年份（4位）           | 2026 |
| `yy`        | 年份（2位）           | 26   |
| `MM`        | 月份（2位）           | 06   |
| `M`         | 月份（1-2位）         | 6    |
| `dd`        | 日（2位）             | 18   |
| `d`         | 日（1-2位）           | 18   |
| `hh`        | 小时（2位，24小时制） | 14   |
| `h`         | 小时（1-2位）         | 14   |
| `mm`        | 分钟（2位）           | 30   |
| `m`         | 分钟（1-2位）         | 30   |
| `ss`        | 秒（2位）             | 25   |
| `s`         | 秒（1-2位）           | 25   |
| `zzz`       | 毫秒（3位）           | 123  |
| `AP` / `ap` | AM/PM                 | PM   |

#### 完整示例

cpp

```
QDateTime now = QDateTime::currentDateTime();

// 格式化
QString t1 = now.toString("hh:mm:ss");           // "14:30:25"
QString t2 = now.toString("hh:mm:ss.zzz");       // "14:30:25.123"
QString t3 = now.toString("yyyy-MM-dd hh:mm:ss");// "2026-06-18 14:30:25"

// 时间戳
uint timestamp = now.toTime_t();

// 计算时间差
QDateTime then = now.addSecs(-3600);
int diff = then.secsTo(now);  // 3600
```



------

## 六、文件操作

### 1. QFile

**头文件：** `#include <QFile>`

#### 构造函数

| 函数                         | 说明         |
| :--------------------------- | :----------- |
| `QFile(const QString &name)` | 创建文件对象 |

#### 常用函数

| 函数                             | 参数     | 返回值    | 说明         |
| :------------------------------- | :------- | :-------- | :----------- |
| `open(OpenMode mode)`            | 打开模式 | `bool`    | 打开文件     |
| `close()`                        | 无       | `void`    | 关闭文件     |
| `exists()`                       | 无       | `bool`    | 文件是否存在 |
| `remove()`                       | 无       | `bool`    | 删除文件     |
| `rename(const QString &newName)` | 新名称   | `bool`    | 重命名       |
| `size()`                         | 无       | `qint64`  | 文件大小     |
| `errorString()`                  | 无       | `QString` | 错误描述     |

#### OpenMode 模式

| 模式                   | 说明                       |
| :--------------------- | :------------------------- |
| `QIODevice::ReadOnly`  | 只读                       |
| `QIODevice::WriteOnly` | 只写                       |
| `QIODevice::ReadWrite` | 读写                       |
| `QIODevice::Append`    | 追加                       |
| `QIODevice::Truncate`  | 截断（清空后写入）         |
| `QIODevice::Text`      | 文本模式（自动转换换行符） |

------

### 2. QTextStream

**头文件：** `#include <QTextStream>`

#### 构造函数

| 函数                             | 说明             |
| :------------------------------- | :--------------- |
| `QTextStream(QFile *file)`       | 从文件创建流     |
| `QTextStream(QByteArray *array)` | 从字节数组创建流 |

#### 常用函数

| 函数                              | 参数     | 返回值         | 说明                  |
| :-------------------------------- | :------- | :------------- | :-------------------- |
| `operator<<`                      | 各种类型 | `QTextStream&` | 写入数据              |
| `operator>>`                      | 各种类型 | `QTextStream&` | 读取数据              |
| `readLine(qint64 maxSize)`        | 最大长度 | `QString`      | 读一行                |
| `readAll()`                       | 无       | `QString`      | 读取全部              |
| `atEnd()`                         | 无       | `bool`         | 是否到末尾            |
| `setCodec(const char *codecName)` | 编码名称 | `void`         | 设置编码（如"UTF-8"） |

#### 完整示例

cpp

```
// 写入
QFile file("D:/data.txt");
if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
    QTextStream out(&file);
    out << "第一行" << endl;
    out << "第二行" << endl;
    file.close();
}

// 读取
if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        qDebug() << line;
    }
    file.close();
}
```



------

### 3. QFileDialog

**头文件：** `#include <QFileDialog>`

#### 静态函数

| 函数                     | 参数                           | 返回值    | 说明           |
| :----------------------- | :----------------------------- | :-------- | :------------- |
| `getSaveFileName()`      | 父窗口、标题、默认路径、过滤器 | `QString` | 保存文件对话框 |
| `getOpenFileName()`      | 父窗口、标题、默认路径、过滤器 | `QString` | 打开文件对话框 |
| `getExistingDirectory()` | 父窗口、标题、默认路径         | `QString` | 选择目录对话框 |

#### 完整示例

cpp

```
// 保存
QString path = QFileDialog::getSaveFileName(
    this,
    "保存文件",
    "D:/data.txt",
    "文本文件 (*.txt);;所有文件 (*.*)"
);
if (!path.isEmpty()) {
    // 保存到 path
}

// 打开
QString path = QFileDialog::getOpenFileName(
    this,
    "选择文件",
    QDir::homePath(),
    "文本文件 (*.txt)"
);
```



------

## 七、对话框

### QMessageBox

**头文件：** `#include <QMessageBox>`

#### 静态函数

| 函数            | 参数               | 返回值           | 说明       |
| :-------------- | :----------------- | :--------------- | :--------- |
| `information()` | 父窗口、标题、内容 | `StandardButton` | 信息提示框 |
| `warning()`     | 父窗口、标题、内容 | `StandardButton` | 警告提示框 |
| `critical()`    | 父窗口、标题、内容 | `StandardButton` | 错误提示框 |
| `question()`    | 父窗口、标题、内容 | `StandardButton` | 询问对话框 |

#### StandardButton 返回

| 常量                   | 说明 |
| :--------------------- | :--- |
| `QMessageBox::Ok`      | 确定 |
| `QMessageBox::Cancel`  | 取消 |
| `QMessageBox::Yes`     | 是   |
| `QMessageBox::No`      | 否   |
| `QMessageBox::Save`    | 保存 |
| `QMessageBox::Discard` | 放弃 |

#### 完整示例

cpp

```
// 信息提示
QMessageBox::information(this, "提示", "操作完成");

// 警告
QMessageBox::warning(this, "错误", "请先打开串口");

// 询问
int ret = QMessageBox::question(this, "确认", "确定要删除吗？");
if (ret == QMessageBox::Yes) {
    // 执行删除
}

// 带按钮选项
QMessageBox msgBox;
msgBox.setText("文件已修改");
msgBox.setInformativeText("是否保存？");
msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
msgBox.setDefaultButton(QMessageBox::Save);
int ret = msgBox.exec();
```



------

## 快速搜索索引（按功能）

| 想做什么     | 组件                    | 函数                                 |
| :----------- | :---------------------- | :----------------------------------- |
| 创建串口对象 | `QSerialPort`           | `new QSerialPort(this)`              |
| 打开串口     | `QSerialPort`           | `open(QIODevice::ReadWrite)`         |
| 关闭串口     | `QSerialPort`           | `close()`                            |
| 发送数据     | `QSerialPort`           | `write(data)`                        |
| 接收数据     | `QSerialPort`           | `readAll()`                          |
| 扫描串口     | `QSerialPortInfo`       | `availablePorts()`                   |
| 定时执行     | `QTimer`                | `start()` / `timeout`                |
| 下拉框选参数 | `QComboBox`             | `addItem(text, userData)` / `currentData()` |
| 给控件打标记 | `QPushButton`           | `setProperty("key", value)`          |
| 读控件标记   | `QPushButton`           | `property("key").toInt()`            |
| 动态查控件   | `QWidget`               | `findChild<T *>("控件名字符串")`     |
| 判断谁触发   | `QObject`               | `qobject_cast<T *>(sender())`        |
| 模拟点击按钮 | `QPushButton`           | `emit btn->clicked()`                |
| 输入文本     | `QLineEdit`             | `text()` / `setText()`               |
| 显示数据     | `QTextEdit`             | `insertPlainText()` / `append()`     |
| 复选框开关   | `QCheckBox`             | `isChecked()` / `clicked(bool)`      |
| 按钮点击     | `QPushButton`           | `clicked` 信号                       |
| 显示状态     | `QLabel`                | `setText()`                          |
| 数字输入     | `QSpinBox`              | `value()` / `setValue()`             |
| 隐藏面板     | `QGroupBox`             | `setVisible(!visible)`               |
| HEX转字节    | `QString`               | `mid(2).toUInt(&ok, 16)`             |
| 字节转HEX    | `QString`               | `arg(value, 2, 16, QChar('0'))`      |
| 时间戳       | `QDateTime`             | `currentDateTime().toString(format)` |
| 保存文件     | `QFileDialog`           | `getSaveFileName()`                  |
| 打开文件     | `QFileDialog`           | `getOpenFileName()`                  |
| 读写文件     | `QFile` + `QTextStream` | `open()` / `<<` / `readLine()`       |
| 弹窗提示     | `QMessageBox`           | `information()` / `warning()`        |
| 调试输出     | `QDebug`                | `qDebug()`                           |
| 数据容器     | `QByteArray`            | `size()` / `append()` / `toHex()`    |
| 字符串处理   | `QString`               | `trimmed()` / `split()` / `arg()`    |
| 万能数据     | `QVariant`              | `toInt()` / `toString()`             |

---

## 八、本项目用到的进阶技巧

### 1. `findChild<T>("name")` — 按字符串动态查找控件

```cpp
// 不写 ui->pushButton1, ui->pushButton2...
// 用循环 + 字符串拼名字：
for (int i = 0; i < 9; i++) {
    QPushButton *btn = findChild<QPushButton *>(QString("pushButton%1").arg(i + 1));
    if (btn) {
        btn->setProperty("buttonId", i + 1);
        buttons.append(btn);
    }
    QLineEdit *edit = findChild<QLineEdit *>(QString("lineEdit%1").arg(i + 1));
    lineEdits.append(edit);

    QCheckBox *cb = findChild<QCheckBox *>(QString("checkBox%1").arg(i + 1));
    checkBoxs.append(cb);
}
```

> 用字符串查找控件，替代写 9 遍 `ui->xxx`

### 2. `setProperty` + `property` — 给控件存/读任意数据

```cpp
// 存：按钮按顺序打标记（哪个是第1个，哪个是第2个...）
btn->setProperty("buttonId", i + 1);

// 读：槽函数里取出标记，知道按的是第几个
int num = btn->property("buttonId").toInt();  // 1,2,...,9
```

### 3. `sender()` — 多个控件共用一个槽

```cpp
// 9 个按钮都连到这一个槽，不用声明 9 个槽函数
connect(btn, SIGNAL(clicked()), this, SLOT(on_command_button_clicked()));

// 槽里用 sender() 判断谁触发的
void Widget::on_command_button_clicked()
{
    QPushButton *btn = qobject_cast<QPushButton *>(sender());
    int num = btn->property("buttonId").toInt();  // 第几行？

    // 取该行文本 + HEX状态 + 发送
    QString text = lineEdits[num - 1]->text();
    bool hexMode = checkBoxs[num - 1]->isChecked();
    // ...
}
```

### 4. `emit btn->clicked()` — 代码模拟点击

```cpp
// 循环发送定时器触发时，顺序模拟点击 9 个按钮
void Widget::buttons_handler()
{
    if (buttonIndex < buttons.size()) {
        emit buttons[buttonIndex]->clicked();  // 跟用户鼠标点一样
        buttonIndex++;
    } else {
        buttonIndex = 0;  // 一轮结束回到开头
    }
}
```

### 5. `addItem(text, userData)` — 给下拉框绑定隐藏数据

```cpp
// 存：显示文字 + 隐藏的枚举值
ui->comboBox_BT->addItem("9600", QSerialPort::Baud9600);

// 取：不需要 if 判断文字
int baudRate = ui->comboBox_BT->currentData().toInt();  // 直接拿到枚举值
m_serial->setBaudRate((QSerialPort::BaudRate)baudRate);
```

### 6. `QList` 存同类控件 — 遍历统一操作

```cpp
// 重置按钮：遍历所有 9 行
void Widget::on_pushButton_clicked()
{
    for (int i = 0; i < lineEdits.size(); i++) {
        lineEdits[i]->clear();
        if (checkBoxs[i]) checkBoxs[i]->setChecked(false);
    }
}
```

### 7. `QString::arg` 格式化 — 数字补零转字符串

```cpp
// 输出 "0F", "1A", "FF"
QString hex = QString("%1 ").arg((quint8)data.at(i), 2, 16, QChar('0')).toUpper();

// 参数说明：
// arg(值, 最小宽度, 进制, 不足时填充的字符)
```