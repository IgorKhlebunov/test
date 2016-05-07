QT -= core gui

CONFIG += c++11

TARGET = test
CONFIG -= console app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    consolelineparser.cpp \
    abstractcommandoption.cpp

HEADERS += \
    consolelineparser.h \
    abstractcommandoption.h \
    commandsoption.hpp \
    worker.hpp
