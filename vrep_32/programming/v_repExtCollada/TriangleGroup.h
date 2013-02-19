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

#pragma once

#include <vector>
#include <string>
#include "vec3.h"
class TriangleGroup
{
private:	
	
	std::vector<vec3> m_Normals;
	std::vector<int> m_TriangleIndices;	
	std::vector<int> m_NormalIndices;
	std::string m_MaterialSymbol;
public:	
	std::vector<int>& getTriangleIndices();
	const std::vector<int>& getTriangleIndices() const;
	std::vector<vec3>& getNormals();
	const std::vector<vec3>& getNormals() const;
	std::vector<int>& getNormalIndices();
	const std::vector<int>& getNormalIndices() const;
	std::string getMaterialSymbol() const;
	void setMaterialSymbol(const std::string& MaterialSymbol);
};
