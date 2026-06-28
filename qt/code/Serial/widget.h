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
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>


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
    void on_pushButton_Open_Closeser_clicked();// 打开/关闭串口

    // ===== 发送功能 =====
    void on_pushButton_Saveget_send_clicked(); // 发送按钮
    void  onTimedSend();// 定时发送触发
    void on_checkBox_timeSend_stateChanged(int state);  // 定时发送勾选

    // ===== 多文本发送 =====
    void on_command_button_clicked();         // 9个按钮共用一个槽（通sener()判断哪个按钮）
    void on_checkBox_send_clicked(bool checked); //循环发送勾选
    void buttons_handler();                   // 循环发送定时触发
    void on_pushButton_3_clicked();           // 保存多文本到文件
    void on_pushButton_2_clicked();           // 载入多文本从文件
    void on_pushButton_clicked();             // 重置多文本面板
    void on_pushButton_Yincmb_clicked();      // 隐藏面板
    void on_pushButton_Yincls_clicked();      // 隐藏历史


    //===== 接收功能 =====
    void onReadyRead();             // 串口有数据到达
    //工具方法
    void on_checkBox_HEK_clicked(bool checked);//HEK切换
    void on_pushButton_Clearget_clicked();//清空文本
    void on_pushButton_Saveget_clicked();//保存文本


    // ===== 工具函数 =====
    QByteArray hexStringToBytes(const QString &hexStr);  // HEX字符串→字节
    QString bytesToHexString(const QByteArray &data);    // 字节→HEX显示字符串
    void time_reflash();//控制系统时间实时刷新

private:
    // ===== 初始化方法 =====
    void initSerialPort();        // 初始化串口对象
    void initComboBoxes();          // 设置默认参数
    void initConnections();        // 连接所有信号槽
    void updateStatusLabel();       // 更新底部状态栏
    void refreshPortList();       // 刷新可用串口列表

    // ===== 成员变量 =====
    QSerialPort *m_serial = nullptr;    // 串口对象（=nullptr 防止野指针）
    bool m_isSerialOpen = false;        // 串口是否打开
    int m_receivedCount = 0;            // 接收字节计数
    int m_sentCount = 0;                // 发送字节计数
    QTimer *m_sendTimer = nullptr;      // 定时发送计时器
private:
    Ui::Widget *ui;

    // ===== 多文本面板用的 QList（在构造函数里用 for 循环填充） =====
    QList<QPushButton *> buttons;
    QList<QLineEdit *> lineEdits;
    QList<QCheckBox *> checkBoxs;

    // ===== 循环发送 =====
    QTimer *buttonsConTimer = nullptr;
    int buttonIndex = 0;
};
#endif // WIDGET_H
