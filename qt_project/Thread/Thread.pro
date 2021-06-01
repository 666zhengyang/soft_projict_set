#-------------------------------------------------
#
# Project created by QtCreator 2018-01-16T11:04:34
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Thread
TEMPLATE = app


SOURCES += main.cpp\
        threaddialog.cpp \
    workthread.cpp

HEADERS  += threaddialog.h \
    workthread.h

FORMS    += threaddialog.ui
