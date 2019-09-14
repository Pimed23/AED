#-------------------------------------------------
#
# Project created by QtCreator 2019-09-14T16:24:41
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TiendaFinal
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
        buscar.cpp \
        database.cpp \
        devolver.cpp \
        main.cpp \
        mainwindow.cpp \
        rentar.cpp \
        stock.cpp \
        titulo.cpp \
        videolisttype.cpp \
        videotype.cpp

HEADERS += \
        buscar.h \
        database.h \
        devolver.h \
        linkedlisttype.h \
        mainwindow.h \
        rentar.h \
        stock.h \
        titulo.h \
        unorderedlinkedlist.h \
        videolisttype.h \
        videotype.h

FORMS += \
        buscar.ui \
        database.ui \
        devolver.ui \
        mainwindow.ui \
        rentar.ui \
        stock.ui \
        titulo.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    datosVideo
