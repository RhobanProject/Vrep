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

#include <string>
#include <vector>
#include "Transformation.h"

class SceneNode
{
private:
	std::string m_MeshID;
	std::string m_Name;	
	std::vector<Transformation*> m_Transformations;
	std::vector<std::pair<std::string,std::string> > m_MaterialBindings;			// symbol to material id pairs
	std::vector<SceneNode> m_Children;
public:
	
	SceneNode();
	SceneNode(const SceneNode& scnode);

	~SceneNode();
	bool containsMesh() const ;

	const std::string& getName() const;
	void setName(const std::string& Name);
	bool hasName() const;

	const std::string& getMeshID() const;
	void setMeshID(const std::string& MeshID);
	const std::vector<Transformation*>& getTransformations() const;
	void addTransformation(const Transformation& Transformation);
	
	const std::vector<std::pair<std::string,std::string> >& getMaterialBindings() const;
	std::vector<std::pair<std::string,std::string> >& getMaterialBindings();
	const std::vector<SceneNode>& getChildren() const;	
	std::vector<SceneNode>& getChildren();

	
};
