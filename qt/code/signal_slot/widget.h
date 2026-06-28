#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<iostream>
using namespace std;

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
    void on_pushButton_clicked();
    void on_btnCon_clickedMyself();
    void on_func_clicked();

private:
    Ui::Widget *ui;
};


#endif // WIDGET_H
