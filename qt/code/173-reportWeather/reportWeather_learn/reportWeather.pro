QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    citycodeutils.cpp \
    day.cpp \
    main.cpp \
    widget.cpp

HEADERS += \
    citycodeutils.h \
    day.h \
    widget.h

FORMS += \
    widget.ui

RESOURCES += \
    citycode.qrc \
    res.qrc
