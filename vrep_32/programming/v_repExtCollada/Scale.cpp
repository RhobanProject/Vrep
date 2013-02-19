// This file is part of the COLLADA PLUGIN for V-REP
// 
// Copyright 2006-2013 Dr. Marc Andreas Freese. All rights reserved. 
// marc@coppeliarobotics.com
// www.coppeliarobotics.com
// 
// The COLLADA PLUGIN is licensed under the terms of GNU GPL:
// 
// -------------------------------------------------------------------
// The COLLADA PLUGIN is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// The COLLADA PLUGIN is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with the COLLADA PLUGIN.  If not, see <http://www.gnu.org/licenses/>.
// -------------------------------------------------------------------
//
// This file was automatically created for V-REP release V3.0.1 on January 20th 2013

// Written by Alex Doumanoglou on behalf of Dr. Marc Freese

#include "Scale.h"

Scale::Scale() : Transformation(Transformation::Scale)
{
	m_Scale.set(1,1,1);
}

Scale::Scale(const vec3& v) : Transformation(Transformation::Scale)
{
	m_Scale = v;
}

Scale::Scale(double X, double Y, double Z) : Transformation(Transformation::Scale)
{
	m_Scale.set(X,Y,Z);
}

const vec3& Scale::getScale() const
{
	return m_Scale;
}

void Scale::setScale(const vec3& v)
{
	m_Scale = v;
}

void Scale::setScale(double X, double Y, double Z)
{
	m_Scale.set(X,Y,Z);
}

Transformation* Scale::clone() const
{
	return new Scale(*this);
}

