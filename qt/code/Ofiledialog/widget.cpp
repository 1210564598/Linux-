#include "widget.h"
#include "ui_widget.h"
#include <qDebug>
#include <QFileDialog>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

//单文件打开
void Widget::on_pushButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "openfile", "F:/LinuxEDStudy/qt", "Text (*.txt);;All (*.*)");
     qDebug()<<fileName;


     QFile file(fileName);//打开文件
     if (!file.open(QIODevice::ReadWrite | QIODevice::Text)) return;
    QTextStream in(&file);
    while (!in.atEnd()) {
          QString line = in.readLine();
          qDebug()<<line;}


}

void Widget::on_pushButton_2_clicked()
{
   //选择多文件打开
   // QStringList fileName = QFileDialog::getOpenFileNames(this, "openfile", "F:/LinuxEDStudy/qt", "Text (*.txt);;All (*.*)");

    // 创建一个 QFileDialog 实例
    QFileDialog fileNames(this);
    fileNames.setWindowTitle("选择多个文件");
    fileNames.setDirectory("F:/LinuxEDStudy/qt");
    // 关键：设置文件模式为“已存在的多个文件”
    fileNames.setFileMode(QFileDialog::ExistingFiles);   // 多选
        // 其他可选模式：
        // QFileDialog::AnyFile          - 任意文件（保存对话框常用）
        // QFileDialog::ExistingFile     - 单个已存在文件
        // QFileDialog::Directory        - 选择目录
        // QFileDialog::ExistingFiles    - 多个已存在文件

    // 设置文件过滤器
    fileNames.setNameFilter("Text (*.txt);;Images (*.png *.jpg);;All files(*)");
    fileNames.exec();
    //exec() 是 QDialog 的方法，通常用于模态显示对话框。
    QStringList fileName = fileNames.selectedFiles();
    //selectedFiles() 是 Qt 中 QFileDialog 类的一个成员函数，用于获取用户在文件对话框中最终选中并确认的文件或目录的路径列表。
    qDebug() << "opt file：" << fileName;
    for(QString &filepath:fileName){//遍历fileName容器 逐个输出容器中的fileNe
        qDebug() << filepath;
        //打开文件
        QFile file(filepath);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) return;
        //file.open(QIODevice::ReadOnly | QIODevice::Text以只读且文本模式打开文件。}
        QTextStream in(&file);
        if(!in.atEnd()){
            QString line=in.readLine();
             qDebug() <<line;
        }
    }

}

void Widget::on_pushButton_3_clicked()
{
       QString filesave=QFileDialog::getSaveFileName(this,
                                                     tr("savefile"),
                                                     "F:/LinuxEDStudy/qt",
                                                     ("Text (*.txt);;Word文档 (*.doc)") );
        qDebug()<<filesave;

        QFile file(filesave);
        if(!file.open(QIODevice::ReadWrite | QIODevice::Text))return;
        QTextStream out(&file);
        out<<"123456";


}
