QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    accesories.cpp \
    body.cpp \
    createavatar.cpp \
    foots.cpp \
    hands.cpp \
    head.cpp \
    legs.cpp \
    main.cpp \
    login.cpp \
    persona.cpp \
    profile.cpp \
    registeravatar.cpp \
    registro.cpp

HEADERS += \
    accesories.h \
    body.h \
    createavatar.h \
    foots.h \
    hands.h \
    head.h \
    legs.h \
    login.h \
    persona.h \
    profile.h \
    registeravatar.h \
    registro.h

FORMS += \
    accesories.ui \
    body.ui \
    createavatar.ui \
    foots.ui \
    hands.ui \
    head.ui \
    legs.ui \
    login.ui \
    profile.ui \
    registeravatar.ui \
    registro.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
