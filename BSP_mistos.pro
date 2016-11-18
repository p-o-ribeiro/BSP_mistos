QT += core
QT -= gui

CONFIG += c++11

TARGET = BSP_mistos
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    poligono.cpp \
    nodo.cpp
SOURCES +=
SOURCES +=
SOURCES +=

HEADERS += \
    interseccao_retas.h \
    ponto.h \
    poligono.h \
    nodo.h
