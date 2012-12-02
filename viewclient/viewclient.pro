#-------------------------------------------------
#
# Project created by QtCreator 2012-11-25T22:12:39
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = viewclient
TEMPLATE = app

INCLUDEPATH += \
    $${PWD}/../libraries/Object/

LIBS += \
    -L$${OUT_PWD}/../libs -lObject

SOURCES += main.cpp\
        viewclient.cpp \
        basicobjectview.cpp \
    clearcontainer.cpp \
    scene.cpp

HEADERS  += viewclient.h \
        basicobjectview.h \
    clearcontainer.h \
    scene.h

FORMS    += viewclient.ui
