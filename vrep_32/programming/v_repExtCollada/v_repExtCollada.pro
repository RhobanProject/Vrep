# This file is part of the COLLADA PLUGIN for V-REP
# 
# Copyright 2006-2013 Dr. Marc Andreas Freese. All rights reserved. 
# marc@coppeliarobotics.com
# www.coppeliarobotics.com
# 
# The COLLADA PLUGIN is licensed under the terms of GNU GPL:
# 
# -------------------------------------------------------------------
# The COLLADA PLUGIN is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
# 
# The COLLADA PLUGIN is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with the COLLADA PLUGIN.  If not, see <http://www.gnu.org/licenses/>.
# -------------------------------------------------------------------
#
# This file was automatically created for V-REP release V3.0.1 on January 20th 2013

TARGET = v_repExtCollada
TEMPLATE = lib

DEFINES -= UNICODE
QT       += network
QMAKE_CXXFLAGS_RELEASE += -O3
CONFIG += shared
INCLUDEPATH += "../include"
INCLUDEPATH += "../v_repMath"
INCLUDEPATH += "tinyxml2"

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
    COLLADAExporter.cpp \
    COLLADAImporter.cpp \
    mat4.cpp \
    Matrix.cpp \
    Mesh.cpp \
    Polygon.cpp \
    PolygonGroup.cpp \
    Rotate.cpp \
    Scale.cpp \
    SceneNode.cpp \
    Source.cpp \
    StringHelper.cpp \
    Translate.cpp \
    TriangleGroup.cpp \
    VisualScene.cpp \
    XMLHelper.cpp \
    colladadialog.cpp \
    tinyxml2/tinyxml2.cpp \
	v_repExtCollada.cpp \
    ../v_repMath/3Vector.cpp \
    ../v_repMath/3X3Matrix.cpp \
    ../v_repMath/4Vector.cpp \
    ../v_repMath/4X4FullMatrix.cpp \
    ../v_repMath/4X4Matrix.cpp \
    ../v_repMath/7Vector.cpp \
    ../v_repMath/MyMath.cpp \
    ../common/v_repLib.cpp \

HEADERS +=\
    COLLADAExporter.h \
    COLLADAImporter.h \
    Hash.h \
    mat4.h \
    Material.h \
    Matrix.h \
    Mesh.h \
    Polygon.h \
    PolygonGroup.h \
    Rotate.h \
    Scale.h \
    SceneNode.h \
    Source.h \
    StringHelper.h \
    Transformation.h \
    Translate.h \
    TriangleGroup.h \
    vec3.h \
    VisualScene.h \
    XMLHelper.h \
    colladadialog.h \
    tinyxml2/tinyxml2.h \
	v_repExtCollada.h \
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
    colladadialog.ui


















