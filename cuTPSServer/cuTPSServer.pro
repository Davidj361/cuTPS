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
CONFIG   += qt
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += \
    DBManager.cc \
    Controller.cc \
    main.cc \
    ConnectionServer.cc \
    ../common/Student.cc \
    ../common/Textbook.cc

OTHER_FILES +=

HEADERS += \
    headers/DBManager.h \
    headers/Controller.h \
    headers/ConnectionServer.h \
    ../common/User.h \
    ../common/Student.h \
    ../common/Content.h \
    ../common/Textbook.h
