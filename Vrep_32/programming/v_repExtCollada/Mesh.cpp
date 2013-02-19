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

#include "Mesh.h"

const std::string& Mesh::getID() const
{
	return m_ID;
}

void Mesh::setID(const std::string& ID)
{
	m_ID = ID;
}

std::vector<TriangleGroup>& Mesh::getTriangleGroups()
{
	return m_TriangleGroups;
}
const std::vector<TriangleGroup>& Mesh::getTriangleGroups() const
{
	return m_TriangleGroups;
}

std::vector<vec3>& Mesh::getVertices()
{
	return m_Vertices;
}

const std::vector<vec3>& Mesh::getVertices() const
{
	return m_Vertices;
}

const std::string& Mesh::getName() const
{
	return m_Name;
}

void Mesh::setName(const std::string& Name)
{
	m_Name = Name;
}

bool Mesh::hasName() const
{
	return m_Name.length()>0;
}

std::vector<PolygonGroup>& Mesh::getPolygonGroups()
{
	return m_PolygonGroups;
}

const std::vector<PolygonGroup>& Mesh::getPolygonGroups() const
{
	return m_PolygonGroups;
}
