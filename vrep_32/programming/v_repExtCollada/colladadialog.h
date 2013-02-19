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

#ifndef COLLADADIALOG_H
#define COLLADADIALOG_H

#include <QDialog>
#include "COLLADAImporter.h"
#include "COLLADAExporter.h"

namespace Ui {
    class CColladaDialog;
}

class CColladaDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CColladaDialog(QWidget *parent = 0);
    ~CColladaDialog();

	void refresh();

	void makeVisible(bool visible);
	bool getVisible();

	int dialogMenuItemHandle;

	void reject();

	int getVertices(const COLLADAImporter* importer,const mat4& parentMatrix,const SceneNode* node,std::vector<float>& vertices,int& nodeCount);
	bool addNodeToScene(const COLLADAImporter* importer,const mat4& parentMatrix,int parentObjectID,const SceneNode* node,float jointAndDummySizes,bool onlyShapes,std::vector<float>* _allVert,std::vector<int>* _allInd,float importScale);
	SceneNode* addObjectNodeForExport(int objectID,int parentObjectID);
	void addAllMeshesToExporter(COLLADAExporter* exp);

	void simulationAboutToStart();
	void mainScriptAboutToBeCalled();
	void renderingPassAboutToBeCalled();
	void simulationEnded();

	int importSingleGroupedShape(const char* pathAndFile,bool preserveColors,float scaling);

private:
	float _importScaling;
	float _exportScaling;
	bool _mergeImported;
	bool _ungroupImported;
	bool _importMeshesOnly;
	bool _exportAnimation;
	bool _exportShapesOnly;

private slots:


	void on_qqMergeImport_clicked();

	void on_qqImportMeshesOnly_clicked();

	void on_qqImportScalingFactor_editingFinished();

	void on_qqImport_clicked();

	void on_qqExportAnimation_clicked();

	void on_qqExportShapesOnly_clicked();

	void on_qqExportScalingFactor_editingFinished();

	void on_qqExport_clicked();

	void on_qqImportUngroup_clicked();

private:
    Ui::CColladaDialog *ui;
};

#endif // COLLADADIALOG_H
