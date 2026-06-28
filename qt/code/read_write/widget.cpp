#include "widget.h"
#include "ui_widget.h"

#include <QFile>

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



void Widget::on_pushButton_clicked()
{
    //1. 打开文件
     QFile file("F:/LinuxEDStudy/qt/text.txt");
     if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) return;
    //2. 读取文件
     char context[100] = {'\0'};
     if( file.read(context,100) == -1) return;
     //3. 输出文件内容
     qDebug() << context;

    //4. 关闭内容
     file.close();
}

void Widget::on_pushButton_2_clicked()
{
    //1. 打开文件
     QFile file;
      file.setFileName("F:/LinuxEDStudy/qt/text2.txt");
     if(!file.open(QIODevice::WriteOnly | QIODevice::Text))return;
     file.write("xxxxxxaaaabbbcccdd");
     // 3. 关闭
     file.close();


}

void Widget::on_pushButton_3_clicked()
{
    //1. 打开文件
     QFile file("F:/LinuxEDStudy/qt/text.txt");
     if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) return;
     //读取文件内容
     QTextStream in(&file);
     in.setCodec("UTF-8");

     //读取文件大小的
     QString sizefile=file.read(file.size());
    qDebug()<<sizefile;
     // 读取全部内容
    // QByteArray allData = file.readAll();
     // qDebug()<<allData;


     //逐行读取
    // while (!in.atEnd()) {
        // QString line = in.readLine();
        // qDebug()<<line;}

}



void Widget::on_pushButton_4_clicked()
{
    //1. 打开文件
     QFile file("F:/LinuxEDStudy/qt/text3.txt");
     if (!file.open(QIODevice::ReadWrite | QIODevice::Text)) return;
     //stream写入
     QTextStream out(&file);
     out<<"1213141411qqqqq";
     QString sizefile=file.read(file.size());
     qDebug()<<sizefile;
     file.close();
}
