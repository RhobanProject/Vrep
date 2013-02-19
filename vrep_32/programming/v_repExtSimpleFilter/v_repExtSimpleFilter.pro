# Copyright 2006-2013 Dr. Marc Andreas Freese. All rights reserved. 
# marc@coppeliarobotics.com
# www.coppeliarobotics.com
# 
# -------------------------------------------------------------------
# This file is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
# 
# You are free to use/modify/distribute this file for whatever purpose!
# -------------------------------------------------------------------
#
# This file was automatically created for V-REP release V3.0.1 on January 20th 2013

TARGET = v_repExtSimpleFilter
TEMPLATE = lib

DEFINES -= UNICODE
QMAKE_CXXFLAGS_RELEASE += -O3
CONFIG += shared
INCLUDEPATH += "../include"


SOURCES += \
    ../common/v_repLib.cpp \
    v_repExtSimpleFilter.cpp \
    simplefilterdialog.cpp

HEADERS +=\
    ../include/v_repLib.h \
    v_repExtSimpleFilter.h \
    simplefilterdialog.h

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}

FORMS += \
    simplefilterdialog.ui


















