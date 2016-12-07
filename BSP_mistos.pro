QT += core
QT += opengl
QT -= gui

CONFIG += c++11

TARGET = BSP_mistos
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

LIBS+= -L/usr/X11R6/lib/ -lGL -lGLU -lglut


SOURCES += main.cpp \
    poligono.cpp \
    nodo.cpp \
    interseccao_retas.cpp \
    labirinto.cpp \
    ponto.cpp
SOURCES +=
SOURCES +=
SOURCES +=

HEADERS += \
    interseccao_retas.h \
    ponto.h \
    poligono.h \
    nodo.h \
    labirinto.h \
    vetor.h
