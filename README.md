# deskew - compute skew angle of scanned image

Copyright 2009 Syd Logan All rights reserved
Copyright 2022 Eric Smith <spacewar@gmail.com>

SPDX-License-Identifier: BSD-3-Clause

deskew development is hosted at the
[deskew Github repository](https://github.com/brouhaha/deskew/).

## Introduction

This program takes a grayscale image of a document (consisting of mostly
text) as input, and computes the skew angle in degress.

The core of the program is by Syd Logan, from his web page:
http://www.sydlogan.com/deskew.html

I've made only minor changes, and added a main.cpp which allows it to
be run from the command line.

Note that the program only computes the skew angle, but does not actually
perform the image rotation necessary to deskew the image.

## Building from source

The program requires Qt 6, which requires C++ 17. It has been tested
with the GCC 11.2.1 compiler and Qt 6.2.3.

Make sure `qmake` is the right executable for use with qt6. It's possible
that the qt6 qmake might be installed under another name, e.g. on systems
that allow parallel installation of multiple major versions of qmake. If
necessary, substitute the correct name or path for Qt6 qmake in the command
listed below.

To build:

- `qmake`
- `make`
