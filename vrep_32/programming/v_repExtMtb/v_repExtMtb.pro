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

TARGET = v_repExtMtb
TEMPLATE = lib

DEFINES -= UNICODE
QT       += network
QMAKE_CXXFLAGS_RELEASE += -O3
CONFIG += shared
INCLUDEPATH += "../include"


SOURCES += \
    outConnection.cpp \
    mtbRobotContainer.cpp \
    mtbRobot.cpp \
    Access.cpp \
    ../common/v_repLib.cpp \
    v_repExtMtb.cpp \
    mtbrobotdialog.cpp

HEADERS +=\
    outConnection.h \
    mtbRobotContainer.h \
    mtbRobot.h \
    Access.h \
    ../include/v_repLib.h \
    v_repExtMtb.h \
    mtbrobotdialog.h

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}

FORMS += \
    mtbrobotdialog.ui


















