#-------------------------------------------------
#
# Project created by QtCreator 2019-05-21T11:01:44
#
#-------------------------------------------------

QT       += core gui
QT += network
CONFIG += mobility
QT += multimedia
MOBILITY += multimedia
QT  += multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Client
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
    clientsocket.cpp \
    chatwidget.cpp \
    client.cpp \
    clientsocketmanager.cpp \
    protocol.cpp \
    loginwidget.cpp \
    mainwidget.cpp \
    roomdialog.cpp \
    danmudialog.cpp \
    giftdialog.cpp \
    barrage.cpp \
    updatepswddialog.cpp \
    sendvoice.cpp \
    receivevoice.cpp \
    receivevideo.cpp \
    sendvideo.cpp \
    videiosurface.cpp

HEADERS += \
    clientsocket.h \
    chatwidget.h \
    client.h \
    clientsocketmanager.h \
    protocol.h \
    loginwidget.h \
    mainwidget.h \
    roomdialog.h \
    danmudialog.h \
    giftdialog.h \
    barrage.h \
    updatepswddialog.h \
    sendvoice.h \
    receivevoice.h \
    receivevideo.h \
    sendvideo.h \
    videiosurface.h

FORMS += \
    chatwidget.ui \
    loginwidget.ui \
    mainwidget.ui \
    roomdialog.ui \
    danmudialog.ui \
    giftdialog.ui \
    updatepswddialog.ui \
    receivevideo.ui \
    sendvideo.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    file.qrc

DISTFILES +=
