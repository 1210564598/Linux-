#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    //第二种方式：QObject::connect(sender,SIGNAL(signal()),receiver, SLOT(slot()));
    QObject::connect(ui->pushButton_2, SIGNAL(clicked()), this,
    SLOT(on_btnCon_clickedMyself()));
    //第三中方式：QObject::connect(sender,&Sender::signal, [=]() {/* lambda body */ });
    QObject::connect(ui->pb3, &QPushButton::clicked,
                         [=]() {
                            cout << "btnLambda点击事件" << endl;
                         });

    //第四种方式：QObject::connect(sender, &Sender::signal, receiver,&Receiver::slot);
    QObject::connect(ui->pb4,  &QPushButton::clicked,
                     this,&Widget::on_func_clicked);

}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_pushButton_clicked()
{
    cout<<"直接链接"<<endl;
}

void Widget::on_btnCon_clickedMyself(){
    cout<<"第二种方式"<<endl;
}

void Widget::on_func_clicked(){
    cout<<"第四种方式"<<endl;

}
