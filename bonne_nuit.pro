#-------------------------------------------------
#
# Project created by QtCreator 2015-09-16T11:28:27
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = bonne_nuit
TEMPLATE = app

CONFIG += c++11

SOURCES += main.cpp\
        mainwindow.cpp \
    game.cpp \
    piece.cpp

HEADERS  += mainwindow.h \
    o_sdo/observateur.h \
    o_sdo/sujetdobservation.h \
    game.h \
    color.h \
    gamestate.h \
    piece.h \
    gameaction.h

FORMS    += mainwindow.ui
