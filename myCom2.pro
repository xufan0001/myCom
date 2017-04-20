#-------------------------------------------------
#
# Project created by QtCreator 2017-03-04T09:22:32
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = myCom2
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    qextserialbase.cpp \
    posix_qextserialport.cpp

HEADERS  += widget.h \
    qextserialbase.h \
    posix_qextserialport.h

FORMS    += widget.ui
