#ifndef WIDGET_H
#define WIDGET_H

#include <QFile>
#include <QWidget>
#include <QCloseEvent>
#include <QTextEdit>
#include "mytextedit.h"
QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    QFile file;
    Widget(QWidget *parent = nullptr);
    ~Widget();

protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    void on_btnFileOpen_clicked();

    void on_btnSave_clicked();

    void on_btnClose_clicked();

    void on_currentIndexChanged(int txt);

    void on_cursorPositionChanged();

    void zoomIn();

    void zoomOut();


private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
