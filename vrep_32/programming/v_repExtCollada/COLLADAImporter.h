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

#include "Mesh.h"
#include <string>
#include <vector>
#include <boost/unordered_map.hpp>
#include "tinyxml2.h"
#include "Material.h"
#include "SceneNode.h"
#include "VisualScene.h"
#include "Matrix.h"
#include "Translate.h"
#include "Scale.h"
#include "Rotate.h"

class COLLADAImporter
{
private:
	std::vector<Mesh> m_Meshes;
	boost::unordered_map<std::string,Material> m_Materials;
	std::vector<VisualScene> m_VisualScenes;
	std::string m_PrimarySceneID;

	Matrix LoadXMLMatrix(tinyxml2::XMLElement* matrix);
	Translate LoadXMLTranslation(tinyxml2::XMLElement* translation);
	Rotate LoadXMLRotation(tinyxml2::XMLElement* rotation);
	Scale  LoadXMLScale(tinyxml2::XMLElement* scale);
	bool LoadGeometry(tinyxml2::XMLElement* geometryNode,boost::unordered_map <std::string, std::vector<float> >& floatarrays);
	bool LoadMaterial(tinyxml2::XMLElement* colladaRootNode,const std::string& id);	
	void LoadScene(tinyxml2::XMLElement* sceneNode);
	void visitNode(tinyxml2::XMLElement* node,SceneNode* parentNode,std::vector<SceneNode>& rootScene);
	void LoadFloatArrays(tinyxml2::XMLElement *geometryNode, boost::unordered_map<std::string, std::vector<float> >& map);
public:
	bool  LoadFile(const std::string& filename);
	const std::vector<Mesh>& getMeshes() const;	
	const boost::unordered_map<std::string,Material>& getMaterials() const;
	const std::vector<VisualScene>& getVisualScenes() const;
	const std::string& getPrimarySceneID() const;
};
