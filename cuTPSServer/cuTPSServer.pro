#-------------------------------------------------
#
# Project created by QtCreator 2014-10-23T11:55:59
#
#-------------------------------------------------

QT       += core
QT       += network
QT       += sql

QT       -= gui

TARGET = cuTPSServer
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += \
    Serializer.cc \
    DBManager.cc \
    Controller.cc \
    main.cc \
    ConnectionServer.cc

OTHER_FILES +=

HEADERS += \
    headers/Serializer.h \
    headers/DBManager.h \
    headers/Controller.h \
    headers/ConnectionServer.h
