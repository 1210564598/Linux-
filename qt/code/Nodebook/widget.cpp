#include "widget.h"
#include "ui_widget.h"

#include <QFileDialog>
#include <QDebug>
#include <qmessagebox.h>
#include <QShortcut>



Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{


    //快捷键
    QShortcut *shortcutOpen = new QShortcut(QKeySequence("Ctrl+o"), this);
    QShortcut *shortcutsave = new QShortcut(QKeySequence("Ctrl+s"), this);

    connect(shortcutOpen, &QShortcut::activated, [this]() {
        on_btnFileOpen_clicked();  // 直接调用已有槽函数
    });
        connect(shortcutsave, &QShortcut::activated, [this]() {
              on_btnSave_clicked();  // 直接调用已有槽函数
    });

        // 放大字体（Ctrl++ 或 Ctrl+=）
        QShortcut *shortcutZoomIn = new QShortcut(QKeySequence("Ctrl+shift++"), this);
        connect(shortcutZoomIn, &QShortcut::activated, [this]() {
                zoomIn();

        });

        // 缩小字体（Ctrl+-）
        QShortcut *shortcutZoomOut = new QShortcut(QKeySequence("Ctrl+shift+-"), this);
        connect(shortcutZoomOut, &QShortcut::activated, [this]() {
                  zoomOut();

        });


    ui->setupUi(this);
    //虽然上面一行代码进行widget和ui的窗口关联，但是如果发生窗口大小变化的时候，里面的布局不会随之变化
    //通过下面这行代码进行显示说明，让窗口变化时，布局及其子控件随之调整
    this->setLayout(ui->verticalLayout);

    connect(ui->comboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(on_currentIndexChanged(int)));
    connect(ui->textEdit,SIGNAL(cursorPositionChanged()),this,SLOT(on_cursorPositionChanged()));

}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_btnFileOpen_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                    "F:/LinuxEDStudy/qt",
                                                    tr("Text (*.txt)"));

    ui->textEdit->clear();//清空

    file.setFileName(fileName);
    if(!file.open(QIODevice::ReadWrite  | QIODevice::Text)){
        qDebug() << "file open error";
    }
    this->setWindowTitle(fileName+"  Notebook");

    QTextStream in(&file);
    in.setCodec(ui->comboBox->currentText().toStdString().c_str());
    //in.setCodec("ANSI");
    while(!in.atEnd()){
        QString context = in.readLine();
       // qDebug() << qPrintable(context);
       // ui->textEdit->setText(context);//覆盖
        ui->textEdit->append(context);//追加
    }
}

void Widget::on_btnSave_clicked()
{
    if(!file.isOpen()){
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                                "F:/LinuxEDStudy/qt",
                                tr("Text (*.txt *.doc)"));


    file.setFileName(fileName);
    if(!file.open(QIODevice::ReadWrite  | QIODevice::Text)){
        qDebug() << "file open error";
    }
    this->setWindowTitle(fileName+"  Notebook");
    }
    QTextStream out(&file);
    out.setCodec(ui->comboBox->currentText().toStdString().c_str());
    QString context = ui->textEdit->toPlainText();//ui->textEdit->toPlainText()获取 QTextEdit 控件纯文本内容的函数。
    out << context;
}


void Widget::on_btnClose_clicked()
{

    if (ui->textEdit->document()->isModified()) {
           QMessageBox::StandardButton reply;
           reply = QMessageBox::question(this,
                                         tr("Modifieding NO save"),
                                         tr("Modifieding save yes/no"),
                                         QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
           if (reply == QMessageBox::Save) {
                       on_btnSave_clicked();
            }else if (reply == QMessageBox::Discard) {
               if (file.isOpen()) {
                       file.close();
                   }
                   ui->textEdit->clear();
                   this->setWindowTitle("Notebook");
           }else if (reply == QMessageBox::Cancel) {
                    return;
           }else{}


    }
}

void Widget::on_currentIndexChanged(int text)
{
    qDebug() << "currentItSignal";
    if (!file.isOpen()) return;//没有打开文件  则触发也不改变
    ui->textEdit->clear();//清空原有内容

    QTextStream in(&file);//打开新文件
   // in.setCodec(ui->comboBox->currentText().toStdString().c_str());
    in.setCodec(ui->comboBox->currentText().toUtf8().constData());
    //setCodec(char *)
    //ui->comboBox->currentText() 获取当前选中的文本
    //toStdString()将QString 转为c++中的String
    //c_str()将c++中的String 转为char *

    //currentText() → 拿到选中的文字，是 QString 类型（Qt 自己的字符串）。
    //.toUtf8() → 把文字转成 UTF-8 编码的字节数组（QByteArray），就像把汉字或字母变成一个个字节，末尾自动加一个 \0。
   // .constData() → 取出这个字节数组的内部地址，也就是 const char*，C 风格字符串的指针。
    //整个链式调用写在一行，保证指针使用的时候内存还没被释放。
   in.seek(0);
    while(!in.atEnd()){
        QString context = in.readLine();

        ui->textEdit->append(context);//追加
    }


}

void Widget::on_cursorPositionChanged()
{
    QTextCursor cursorpos=ui->textEdit->textCursor();
    //textCursor()：QTextEdit 的成员函数，返回一个表示当前光标位置、选中区域及文本编辑状态的 QTextCursor 对象。

    QString blockNum = QString::number(cursorpos.blockNumber()+1);
    QString columnNum = QString::number(cursorpos.columnNumber()+1);
    QString labelMes="L"+blockNum+",C"+columnNum+"  ";
    //QString::number(...)：将整数转换为 QString 字符串
    //blockNumber()：返回光标所在的文本块（block）的编号。在纯文本文档中，一个 block 通常对应一行（按换行符分隔）。
    //columnNumber():用于获取光标在当前行中的逻辑列号。
    ui->labelPosition->setText(labelMes);

    //设置当前行高亮
    QList<QTextEdit::ExtraSelection> extraSelections;
    QTextEdit::ExtraSelection selection;
    //知道当前行
    selection.cursor=ui->textEdit->textCursor();
    //设置颜色
    QColor lineColor = QColor(230, 240, 255); // 淡蓝色
    selection.format.setBackground(lineColor);
    selection.format.setProperty(QTextFormat::FullWidthSelection, true);
    //
    extraSelections.append(selection);
    ui->textEdit->setExtraSelections(extraSelections);
    //setBackground() 是 QTextCharFormat 的成员函数，用于设置背景画刷（QBrush）
}

void Widget::zoomIn()
{
    QFont font = ui->textEdit->font();
    int newSize = font.pointSize() + 1;
    if (newSize <= 72) {  // 限制最大字号，避免过大
        font.setPointSize(newSize);
        ui->textEdit->setFont(font);
    }
}

void Widget::zoomOut()
{
    QFont font = ui->textEdit->font();
    int newSize = font.pointSize() - 1;
    if (newSize >= 6) {   // 限制最小字号
        font.setPointSize(newSize);
        ui->textEdit->setFont(font);
    }
}


//重写关闭事件
void Widget::closeEvent(QCloseEvent *event)
{
    int ret = QMessageBox::warning(this, tr("My Application"),
                                   tr("close the window\n"
                                      "Do you want to close the window?"),
                                   QMessageBox::Ok | QMessageBox::No
                                   );
    switch(ret){
    case QMessageBox::Ok:
        event->accept();
        break;
    case QMessageBox::No:
        event->ignore();
        break;
    }
}

