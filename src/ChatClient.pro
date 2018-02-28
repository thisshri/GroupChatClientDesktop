#-------------------------------------------------
#
# Project created by QtCreator 2016-10-29T20:24:11
#
#-------------------------------------------------

QT       += core gui network websockets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ChatClient
TEMPLATE = app


SOURCES += main.cpp\
        loginwindow.cpp \
    regwindow.cpp \
    adminchat.cpp \
    chat.cpp \
    regex.cpp \
    forgotpassword.cpp

HEADERS  += loginwindow.h \
    regwindow.h \
    global.h \
    adminchat.h \
    chat.h \
    regex.h \
    forgotpassword.h

FORMS    += loginwindow.ui \
    regwindow.ui \
    adminchat.ui \
    chat.ui \
    forgotpassword.ui
