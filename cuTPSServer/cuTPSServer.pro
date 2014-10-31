#-------------------------------------------------
#
# Project created by QtCreator 2014-10-23T11:55:59
#
#-------------------------------------------------

QT       += core
QT       += network
QT       += sql

TARGET = cuTPSServer
# CONFIG   += console # might not be needed
CONFIG   += qt
CONFIG   -= app_bundle

# TEMPLATE = app # already default


SOURCES += \
    DBManager.cc \
    Controller.cc \
    main.cc \
    ConnectionServer.cc \
    ../common/Serializer.cc \
    ../common/Student.cc \
    ../common/Textbook.cc \
    ../common/Chapter.cc \
    ../common/Section.cc \
    ../common/Content.cc \
    ../common/Invoice.cc \
    ../common/User.cc

OTHER_FILES +=

HEADERS += \
    headers/DBManager.h \
    headers/Controller.h \
    headers/ConnectionServer.h \
    ../common/headers/Serializer.h \
    ../common/headers/User.h \
    ../common/headers/Student.h \
    ../common/headers/Content.h \
    ../common/headers/Textbook.h \
    ../common/headers/Content.h \
    ../common/headers/Textbook.h \
    ../common/headers/Chapter.h \
    ../common/headers/Section.h \
    ../common/headers/User.h \
    ../common/headers/Definitions.h \
    ../common/headers/Invoice.h
