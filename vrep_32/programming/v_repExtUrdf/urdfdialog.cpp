// This file is part of the URDF PLUGIN for V-REP
//  
// Copyright 2006-2013 Dr. Marc Andreas Freese. All rights reserved. 
// marc@coppeliarobotics.com
// www.coppeliarobotics.com
// 
// A big thanks to Ignacio Tartavull for his precious help!
// 
// The URDF PLUGIN is licensed under the terms of GNU GPL:
// 
// -------------------------------------------------------------------
// The URDF PLUGIN is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// The URDF PLUGIN is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with the URDF PLUGIN.  If not, see <http://www.gnu.org/licenses/>.
// -------------------------------------------------------------------

//
// This file was automatically created for V-REP release V3.0.1 on January 20th 2013

// The URDF plugin is courtesy of Ignacio Tartavull. A few modifications by Marc.

#include "urdfdialog.h"
#include "ui_urdfdialog.h"
#include "v_repLib.h"
#include "tinyxml2.h"
#include <string>
#include "robot.h"

bool CUrdfDialog::hideCollisionLinks=true;
bool CUrdfDialog::hideJoints=true;
bool CUrdfDialog::convexDecompose=true;
bool CUrdfDialog::showConvexDecompositionDlg=false;
bool CUrdfDialog::createVisualIfNone=true;
bool CUrdfDialog::centerModel=true;
bool CUrdfDialog::prepareModel=true;
bool CUrdfDialog::noSelfCollision=true;
bool CUrdfDialog::positionCtrl=true;

CUrdfDialog::CUrdfDialog(QWidget *parent) :
	QDialog(parent,Qt::Tool),
    ui(new Ui::CUrdfDialog)
{
    ui->setupUi(this);
	refresh();
}

CUrdfDialog::~CUrdfDialog()
{
    delete ui;
}

void CUrdfDialog::refresh()
{
	bool simStopped=(simGetSimulationState()==sim_simulation_stopped);

	ui->qqAlternateMasks->setEnabled(simStopped);
	ui->qqCenterModel->setEnabled(simStopped);
	ui->qqCollisionLinksHidden->setEnabled(simStopped);
	ui->qqConvexDecompose->setEnabled(simStopped);
	ui->qqConvexDecomposeDlg->setEnabled(simStopped&&convexDecompose);
	ui->qqCreateVisualLinks->setEnabled(simStopped);
	ui->qqImport->setEnabled(simStopped);
	ui->qqJointsHidden->setEnabled(simStopped);
	ui->qqModelDefinition->setEnabled(simStopped);
	ui->qqPositionCtrl->setEnabled(simStopped);

	ui->qqAlternateMasks->setChecked(!noSelfCollision);
	ui->qqCenterModel->setChecked(centerModel);
	ui->qqCollisionLinksHidden->setChecked(hideCollisionLinks);
	ui->qqConvexDecompose->setChecked(convexDecompose);
	ui->qqConvexDecomposeDlg->setChecked(showConvexDecompositionDlg);
	ui->qqCreateVisualLinks->setChecked(createVisualIfNone);
	ui->qqJointsHidden->setChecked(hideJoints);
	ui->qqModelDefinition->setChecked(prepareModel);
	ui->qqPositionCtrl->setChecked(positionCtrl);
}

void CUrdfDialog::makeVisible(bool visible)
{
	setVisible(visible);
	// Reflect the visibility state in the menu bar item:
	simSetModuleMenuItemState(dialogMenuItemHandle,(visible?3:1),"URDF import...");
}

bool CUrdfDialog::getVisible()
{
	return(isVisible());
}


void CUrdfDialog::reject()
{
	// Reflect the visibility state in the menu bar item:
	simSetModuleMenuItemState(dialogMenuItemHandle,1,"URDF import...");
	done(0);
}

void CUrdfDialog::on_qqImport_clicked()
{
	simChar* pathAndFile=simFileDialog(sim_filedlg_type_load,"URDF PLUGIN LOADER","","","URDF Files","urdf");
	if (pathAndFile!=NULL)
	{
		std::string fileURDF(pathAndFile);
		simReleaseBuffer(pathAndFile);
		// The full path and filename is in pathAndFile!
		// Here we can import from that file
		robot Robot(fileURDF,hideCollisionLinks,hideJoints,convexDecompose,createVisualIfNone,showConvexDecompositionDlg,centerModel,prepareModel,noSelfCollision,positionCtrl);
	}
}

void CUrdfDialog::on_qqCollisionLinksHidden_clicked()
{
	hideCollisionLinks=!hideCollisionLinks;
	refresh();
}

void CUrdfDialog::on_qqJointsHidden_clicked()
{
	hideJoints=!hideJoints;
	refresh();
}

void CUrdfDialog::on_qqConvexDecompose_clicked()
{
	convexDecompose=!convexDecompose;
	if (!convexDecompose)
		simMsgBox(sim_msgbox_type_warning,sim_msgbox_buttons_ok,"WARNING","It is highly recommended to perform a convex decomposition: convex collidables are more stable and faster than random collidables.");
	refresh();
}

void CUrdfDialog::on_qqConvexDecomposeDlg_clicked()
{
	showConvexDecompositionDlg=!showConvexDecompositionDlg;
	refresh();
}

void CUrdfDialog::on_qqCreateVisualLinks_clicked()
{
	createVisualIfNone=!createVisualIfNone;
	refresh();
}

void CUrdfDialog::on_qqCenterModel_clicked()
{
	centerModel=!centerModel;
	refresh();
}

void CUrdfDialog::on_qqModelDefinition_clicked()
{
	prepareModel=!prepareModel;
	refresh();
}

void CUrdfDialog::on_qqAlternateMasks_clicked()
{
	noSelfCollision=!noSelfCollision;
	refresh();
}

void CUrdfDialog::on_qqPositionCtrl_clicked()
{
	positionCtrl=!positionCtrl;
	refresh();
}
