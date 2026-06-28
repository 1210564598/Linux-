/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.12.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "mytextedit.h"

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QWidget *widgetButtons;
    QWidget *layoutWidget1;
    QHBoxLayout *hlLayoutButtons;
    QPushButton *btnFileOpen;
    QPushButton *btnSave;
    QPushButton *btnClose;
    QSpacerItem *horizontalSpacer;
    MyTextEdit *textEdit;
    QWidget *widgetBottom;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_2;
    QLabel *labelPosition;
    QComboBox *comboBox;
    QSpacerItem *horizontalSpacer_3;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->resize(800, 600);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icon/note.png"), QSize(), QIcon::Normal, QIcon::Off);
        Widget->setWindowIcon(icon);
        layoutWidget = new QWidget(Widget);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(0, 0, 801, 601));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        widgetButtons = new QWidget(layoutWidget);
        widgetButtons->setObjectName(QString::fromUtf8("widgetButtons"));
        widgetButtons->setMinimumSize(QSize(0, 50));
        widgetButtons->setStyleSheet(QString::fromUtf8("background-color: rgb(70, 70, 70);"));
        layoutWidget1 = new QWidget(widgetButtons);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(20, 0, 751, 50));
        hlLayoutButtons = new QHBoxLayout(layoutWidget1);
        hlLayoutButtons->setObjectName(QString::fromUtf8("hlLayoutButtons"));
        hlLayoutButtons->setContentsMargins(0, 0, 0, 0);
        btnFileOpen = new QPushButton(layoutWidget1);
        btnFileOpen->setObjectName(QString::fromUtf8("btnFileOpen"));
        btnFileOpen->setMinimumSize(QSize(45, 45));
        btnFileOpen->setStyleSheet(QString::fromUtf8("QPushButton { border-image: url(:/icon/o1.png); }\n"
"\n"
"QPushButton:hover { border-image: url(:/icon/o2.png); }\n"
"\n"
"QPushButton:pressed { border-image: url(:/icon/o3.png); }"));

        hlLayoutButtons->addWidget(btnFileOpen);

        btnSave = new QPushButton(layoutWidget1);
        btnSave->setObjectName(QString::fromUtf8("btnSave"));
        btnSave->setMinimumSize(QSize(45, 48));
        btnSave->setStyleSheet(QString::fromUtf8("QPushButton { border-image: url(:/icon/s1.png); }\n"
"\n"
"QPushButton:hover { border-image: url(:/icon/s2.png); }\n"
"\n"
"QPushButton:pressed { border-image: url(:/icon/s3.png); }"));

        hlLayoutButtons->addWidget(btnSave);

        btnClose = new QPushButton(layoutWidget1);
        btnClose->setObjectName(QString::fromUtf8("btnClose"));
        btnClose->setMinimumSize(QSize(45, 45));
        btnClose->setStyleSheet(QString::fromUtf8("QPushButton { border-image: url(:/icon/c1.png); }\n"
"\n"
"QPushButton:hover { border-image: url(:/icon/c2.png); }\n"
"\n"
"QPushButton:pressed { border-image: url(:/icon/c3.png); }"));

        hlLayoutButtons->addWidget(btnClose);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hlLayoutButtons->addItem(horizontalSpacer);


        verticalLayout->addWidget(widgetButtons);

        textEdit = new MyTextEdit(layoutWidget);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));

        verticalLayout->addWidget(textEdit);

        widgetBottom = new QWidget(layoutWidget);
        widgetBottom->setObjectName(QString::fromUtf8("widgetBottom"));
        widgetBottom->setMinimumSize(QSize(0, 35));
        widgetBottom->setLayoutDirection(Qt::LeftToRight);
        widgetBottom->setAutoFillBackground(false);
        widgetBottom->setStyleSheet(QString::fromUtf8("background-color: rgb(70, 70, 70);"));
        horizontalLayout = new QHBoxLayout(widgetBottom);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer_2 = new QSpacerItem(614, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        labelPosition = new QLabel(widgetBottom);
        labelPosition->setObjectName(QString::fromUtf8("labelPosition"));

        horizontalLayout->addWidget(labelPosition);

        comboBox = new QComboBox(widgetBottom);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName(QString::fromUtf8("comboBox"));

        horizontalLayout->addWidget(comboBox);

        horizontalSpacer_3 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);


        verticalLayout->addWidget(widgetBottom);


        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Notebook", nullptr));
        btnFileOpen->setText(QString());
        btnSave->setText(QString());
        btnClose->setText(QString());
        labelPosition->setText(QApplication::translate("Widget", "\347\254\2541\350\241\214\347\254\2541\345\210\227", nullptr));
        comboBox->setItemText(0, QApplication::translate("Widget", "UTF-8", nullptr));
        comboBox->setItemText(1, QApplication::translate("Widget", "UTF-16", nullptr));
        comboBox->setItemText(2, QApplication::translate("Widget", "ANSI", nullptr));
        comboBox->setItemText(3, QApplication::translate("Widget", "GBK", nullptr));

    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
