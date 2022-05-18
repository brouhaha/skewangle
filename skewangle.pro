# skewangle
# Copyright 2022 Eric Smith <spacewar@gmail.com
# SPDX-License-Identifier: BSD-3-Clause

TEMPLATE = app
TARGET = skewangle
DEPENDPATH += .
INCLUDEPATH += .

CONFIG += debug

QT += widgets

# Input
HEADERS += skewangle.h
SOURCES += skewangle.cpp main.cpp
