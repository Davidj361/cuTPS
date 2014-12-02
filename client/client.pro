#-------------------------------------------------
#
# Project created by QtCreator 2014-10-23T15:12:39
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = client
TEMPLATE = app


SOURCES += main.cc\
    MainWindow.cc \
    ../common/Textbook.cc \
    ../common/Section.cc \
    ../common/Content.cc \
    ../common/Chapter.cc \
    ../common/Serializer.cc \
    ../common/User.cc \
    ../common/Invoice.cc \
    storage/StorageControl.cc \
    ../common/Course.cc \
    storage/ClientSerializer.cc \
    storage/ConnectionClient.cc

HEADERS  += \
    headers/MainWindow.h \
    ../common/headers/Textbook.h \
    ../common/headers/Section.h \
    ../common/headers/Definitions.h \
    ../common/headers/Content.h \
    ../common/headers/Chapter.h \
    ../common/headers/Serializer.h \
    ../common/headers/User.h \
    ../common/headers/Invoice.h \
    storage/StorageControl.h \
    ../common/headers/Course.h \
    storage/ClientSerializer.h \
    ../common/headers/Serializable.h \
    storage/ConnectionClient.h

FORMS    += mainwindow.ui