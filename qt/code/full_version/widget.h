#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QTimer>
#include <QTextEdit>
#include <QCheckBox>
#include <QLineEdit>
#include <QPushButton>
#include <QSpinBox>
#include <QComboBox>
#include <QLabel>
#include <QDateTime>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    // ===== 串口控制 =====
    void on_pushButton_Closeser_clicked();  // 打开/关闭串口

    // ===== 发送功能 =====
    void on_pushButton_Saveget_send_clicked();  // 发送按钮
    void sendData();                              // 实际发送逻辑
    void sendMultiText(int index);                // 快捷发送（多文本面板）
    void onTimedSend();                           // 定时发送触发
    void onLoopSend();                            // 循环发送触发
    void on_checkBox_timeSend_stateChanged(int state);  // 定时发送勾选

    // ===== 接收功能 =====
    void onReadyRead();                           // 串口有数据到达
    void on_pushButton_Clearget_clicked();        // 清空接收区
    void on_pushButton_Saveget_clicked();         // 保存接收内容
    void on_checkBox_HEK_stateChanged(int state); // HEX显示切换
    void on_checkBox_TIME_stateChanged(int state);// 时间戳显示切换

    // ===== 多文本面板 =====
    void on_pushButton_3_clicked();  // 保存多文本
    void on_pushButton_clicked();    // 重置多文本
    void on_pushButton_2_clicked();  // 载入多文本
    void on_checkBox_stateChanged(int state);  // 循环发送勾选

    // ===== 快捷发送按钮 =====
    void on_pushButton1_clicked();
    void on_pushButton2_clicked();
    void on_pushButton3_clicked();
    void on_pushButton4_clicked();
    void on_pushButton_11_clicked();
    void on_pushButton6_clicked();
    void on_pushButton7_clicked();
    void on_pushButton8_clicked();
    void on_pushButton9_clicked();

    // ===== 其他功能 =====
    void on_pushButton_Yincmb_clicked();   // 隐藏面板
    void on_pushButton_Yincls_clicked();   // 隐藏历史
    void on_checkBox_ZDHH_stateChanged(int state); // 自动换行

private:
    // ===== 初始化方法 =====
    void initSerialPort();        // 初始化串口对象
    void initComboBoxes();        // 填充串口参数下拉框
    void refreshPortList();       // 刷新可用串口列表
    void initConnections();       // 连接所有信号槽
    void updateStatusLabel();     // 更新底部状态栏

    // ===== 工具方法 =====
    QByteArray hexStringToBytes(const QString &hexStr);  // HEX字符串转字节
    QString bytesToHexString(const QByteArray &data);     // 字节转HEX显示字符串
    void saveMultiTextToFile(const QString &filePath);    // 多文本保存到文件
    void loadMultiTextFromFile(const QString &filePath);  // 多文本从文件载入

    // ===== 成员变量 =====
    Ui::Widget *ui;
    QSerialPort *m_serial;          // 串口对象
    QTimer *m_sendTimer;            // 定时发送计时器
    QTimer *m_loopTimer;            // 循环发送计时器
    int m_receivedCount;            // 接收字节计数
    int m_sentCount;                // 发送字节计数
    bool m_isSerialOpen;            // 串口是否打开
    QTimer *m_timeTimer = nullptr;   // 时间刷新定时器
};

#endif // WIDGET_H
