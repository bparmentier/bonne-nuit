#-------------------------------------------------
#
# Project created by QtCreator 2015-09-16T11:28:27
#
#-------------------------------------------------

QT       += core gui svg

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = bonne_nuit
TEMPLATE = app

CONFIG += c++11

SOURCES += main.cpp\
    business/piece.cpp \
    o_sdo/sujetdobservation.cpp \
    business/game.cpp \
    ui/gameconfigdialog.cpp \
    ui/gameobserver.cpp \
    ui/mainwindow.cpp \
    ui/qstarpawn.cpp

HEADERS  += \
    o_sdo/observateur.h \
    business/color.h \
    business/gamestate.h \
    business/piece.h \
    business/gameaction.h \
    o_sdo/sujetdobservation.h \
    business/game.h \
    ui/gameconfigdialog.h \
    ui/gameobserver.h \
    ui/mainwindow.h \
    ui/qstarpawn.h

FORMS    += \
    ui/gameconfigdialog.ui \
    ui/mainwindow.ui

RESOURCES += \
    resources.qrc
