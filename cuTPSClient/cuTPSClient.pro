#-------------------------------------------------
#
# Project created by QtCreator 2014-10-23T15:12:39
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = cuTPSClient
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    ConnectionClient.cc

HEADERS  += headers/mainwindow.h \
    headers/ConnectionClient.h

FORMS    += mainwindow.ui
