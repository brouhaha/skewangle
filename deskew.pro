# deskew
# Copyright 2022 Eric Smith <spacewar@gmail.com
# SPDX-License-Identifier: GPL-3.0-only

TEMPLATE = app
TARGET = deskew
DEPENDPATH += .
INCLUDEPATH += .

CONFIG += debug

QT += widgets

# Input
HEADERS += deskew.h
SOURCES += deskew.cpp main.cpp
