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
    ConnectionClient.cc \
    MainWindow.cpp

HEADERS  += \
    headers/ConnectionClient.h \
    headers/MainWindow.h

FORMS    += mainwindow.ui