#-------------------------------------------------
#
# Project created by QtCreator 2012-11-21T22:09:30
#
#-------------------------------------------------

QT       -= gui

TARGET = Config

TEMPLATE = lib

DEFINES += CONFIG_LIBRARY

SOURCES += config.cpp

HEADERS += \
    Config_global.h \
    config.h

OTHER_FILES += \
    config.proto

DESTDIR = $$OUT_PWD/libs
