#-------------------------------------------------
#
# Project created by QtCreator 2019-01-03T12:39:24
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Cafe-Sales
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
    mainwindow.cpp \
    logindialog.cpp \
    outbound2widget.cpp \
    outbound3widget.cpp \
    staffwidget.cpp \
    userswidget.cpp \
    inventorywidget.cpp \
    inboundwidget.cpp \
    outboundwidget.cpp \

HEADERS += \
    mainwindow.h \
    logindialog.h \
    const.h \
    outbound2widget.h \
    outbound3widget.h \
    staffwidget.h \
    userswidget.h \
    inventorywidget.h \
    inboundwidget.h \
    outboundwidget.h \

FORMS += \
    mainwindow.ui \
    logindialog.ui \
    outbound2widget.ui \
    outbound3widget.ui \
    staffwidget.ui \
    userswidget.ui \
    inventorywidget.ui \
    inboundwidget.ui \
    outboundwidget.ui \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
