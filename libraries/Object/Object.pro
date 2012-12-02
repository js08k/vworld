#-------------------------------------------------
#
# Project created by QtCreator 2012-11-22T08:47:47
#
#-------------------------------------------------

QT       -= gui

TARGET = Object
TEMPLATE = lib

DESTDIR = $${OUT_PWD}/../../libs

DEFINES += OBJECT_LIBRARY

LIBS += \
    -larmadillo

SOURCES += \
    basicobject.cpp \
    point.cpp

HEADERS +=\
    Object_global.h \
    basicobject.h \
    point.h



