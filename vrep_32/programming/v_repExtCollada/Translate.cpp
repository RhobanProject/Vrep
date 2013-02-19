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

#include "Translate.h"

Translate::Translate() : Transformation(Transformation::Translate)
{

}

Translate::Translate(const vec3& v) : Transformation(Transformation::Translate)
{
	m_Translation = v;
}

Translate::Translate(double X, double Y, double Z) : Transformation(Transformation::Translate)
{
	m_Translation.set(X,Y,Z);
}

const vec3& Translate::getTranslation() const
{
	return m_Translation;
}

void Translate::setTranslation(const vec3& v)
{
	m_Translation = v;
}

void Translate::setTranslation(double X, double Y, double Z)
{
	m_Translation.set(X,Y,Z);
}


Transformation* Translate::clone() const
{
	return new Translate(*this);
}
