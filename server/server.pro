#-------------------------------------------------
#
# Project created by QtCreator 2014-10-23T11:55:59
#
#-------------------------------------------------

QT       += core
QT       += network
QT       += sql

TARGET = server
# CONFIG   += console # might not be needed
CONFIG   += qt
CONFIG   += debug 
CONFIG   -= app_bundle

# TEMPLATE = app # already default


SOURCES += \
    main.cc \
    databaseManagement/DBManager.cc \
    databaseManagement/DBController.cc \
    serverConnection/ConnectionServer.cc \
    serverConnection/ServerConnectionController.cc \
    ../common/Serializer.cc \
    ../common/Student.cc \
    ../common/Textbook.cc \
    ../common/Chapter.cc \
    ../common/Section.cc \
    ../common/Content.cc \
    ../common/Invoice.cc \
    ../common/User.cc \
    serverConnection/ServerSerializer.cc

OTHER_FILES +=

HEADERS += \
    databaseManagement/DBManager.h \
    databaseManagement/DBController.h \
    serverConnection/ConnectionServer.h \
    serverConnection/ServerConnectionController.h \
    ../common/headers/Serializer.h \
    ../common/headers/Student.h \
    ../common/headers/Content.h \
    ../common/headers/Textbook.h \
    ../common/headers/Chapter.h \
    ../common/headers/Section.h \
    ../common/headers/User.h \
    ../common/headers/Definitions.h \
    ../common/headers/Invoice.h \
    serverConnection/ServerSerializer.h
