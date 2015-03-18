#-------------------------------------------------
#
# Project created by QtCreator 2015-02-02T20:32:31
#
#-------------------------------------------------

QT       += core gui serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = WalkingIMUSystem
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

INCLUDEPATH += $$quote(D:\LIB\Qwt-6.1.2\include)

Release : LIBS += $$quote(D:\LIB\Qwt-6.1.2\lib\qwt.lib)
