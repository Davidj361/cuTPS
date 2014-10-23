#-------------------------------------------------
#
# Project created by QtCreator 2014-10-23T11:55:59
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = cuTPSServer
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    Server.cc \
    Serializer.cc \
    DBManager.cc \
    Controller.cc \
    Connection.cc

OTHER_FILES +=

HEADERS += \
    headers/Serializer.h \
    headers/DBManager.h \
    headers/Controller.h \
    headers/Connection.h
