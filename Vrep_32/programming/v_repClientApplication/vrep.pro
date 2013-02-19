# This file is part of V-REP, the Virtual Robot Experimentation Platform.
# 
# Copyright 2006-2013 Dr. Marc Andreas Freese. All rights reserved. 
# marc@coppeliarobotics.com
# www.coppeliarobotics.com
# 
# V-REP is dual-licensed, under the terms of EITHER (at your option):
#   1. V-REP commercial license (contact us for details)
#   2. GNU GPL (see below)
# 
# GNU GPL license:
# -------------------------------------------------------------------
# V-REP is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
# 
# V-REP is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with V-REP.  If not, see <http://www.gnu.org/licenses/>.
# -------------------------------------------------------------------
#
# This file was automatically created for V-REP release V3.0.1 on January 20th 2013

DEFINES += COMPILING_WITH_QT
QT       += core
QT       -= gui

TARGET = vrep
CONFIG   += console
CONFIG   += app_bundle

TEMPLATE = app

DEFINES += QT_FRAMEWORK


INCLUDEPATH += "../include"

# Following required to have Lua extension libraries work under LINUX. Very strange indeed.
unix:!macx {
        contains(QMAKE_HOST.arch, x86_64):{ # 64 Bit
                INCLUDEPATH += **your lua5.1 64"include" folder**
                LIBS += -Llua5_1_4_Linux26g4_64_lib/ -llua5.1
        }
        !contains(QMAKE_HOST.arch, x86_64):{ # 32 Bit
                INCLUDEPATH += **your lua5.1 32"include" folder**
                LIBS += -Llua5_1_4_Linux26g4_lib/ -llua5.1
        }
	DEFINES += LINUX_VREP
}

SOURCES += main.cpp \
    ../common/v_repLib.cpp

HEADERS += ../include/v_repLib.h





