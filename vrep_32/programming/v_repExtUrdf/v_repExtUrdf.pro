# This file is part of the URDF PLUGIN for V-REP
#  
# Copyright 2006-2013 Dr. Marc Andreas Freese. All rights reserved. 
# marc@coppeliarobotics.com
# www.coppeliarobotics.com
# 
# A big thanks to Ignacio Tartavull for his precious help!
# 
# The URDF PLUGIN is licensed under the terms of GNU GPL:
# 
# -------------------------------------------------------------------
# The URDF PLUGIN is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
# 
# The URDF PLUGIN is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with the URDF PLUGIN.  If not, see <http://www.gnu.org/licenses/>.
# -------------------------------------------------------------------

#
# This file was automatically created for V-REP release V3.0.1 on January 20th 2013

# The URDF plugin is courtesy of Ignacio Tartavull. A few modifications by Marc.

TARGET = v_repExtUrdf
TEMPLATE = lib

DEFINES -= UNICODE
QT       += network
QMAKE_CXXFLAGS_RELEASE += -O3
CONFIG += shared
INCLUDEPATH += "../include"
INCLUDEPATH += "../v_repMath"

win32 {
    DEFINES += WIN_VREP
    INCLUDEPATH += "d:/boost_1_45_0"
}

macx {
    DEFINES += MAC_VREP
}

unix:!macx {
    DEFINES += LIN_VREP
    INCLUDEPATH += "../../boost_1_49_0" #probably not needed when installing boost with sudo apt-get install libboost-all-dev
}

SOURCES += \
	v_repExtUrdf.cpp \
        urdfdialog.cpp \
	tinyxml2.cpp \
	robot.cpp \
	link.cpp \
	joint.cpp \
	sensor.cpp \
	commonFunctions.cpp \
    ../v_repMath/3Vector.cpp \
    ../v_repMath/3X3Matrix.cpp \
    ../v_repMath/4Vector.cpp \
    ../v_repMath/4X4FullMatrix.cpp \
    ../v_repMath/4X4Matrix.cpp \
    ../v_repMath/7Vector.cpp \
    ../v_repMath/MyMath.cpp \
    ../common/v_repLib.cpp \

HEADERS +=\
	v_repExtUrdf.h \
        urdfdialog.h \
	tinyxml2.h \
	robot.h \
	link.h \
	joint.h \
	sensor.h \
	commonFunctions.h \
    ../v_repMath/3Vector.h \
    ../v_repMath/3X3Matrix.h \
    ../v_repMath/4Vector.h \
    ../v_repMath/4X4FullMatrix.h \
    ../v_repMath/4X4Matrix.h \
    ../v_repMath/7Vector.h \
    ../v_repMath/MyMath.h \
    ../include/v_repLib.h \

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}

FORMS += \
    urdfdialog.ui


















