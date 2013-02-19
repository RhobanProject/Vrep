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

#ifndef URDFDIALOG_H
#define URDFDIALOG_H

#include <QDialog>

namespace Ui {
    class CUrdfDialog;
}

class CUrdfDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CUrdfDialog(QWidget *parent = 0);
    ~CUrdfDialog();

	void refresh();

	void makeVisible(bool visible);
	bool getVisible();

	int dialogMenuItemHandle;

	void reject();


private:
	static bool hideCollisionLinks;
	static bool hideJoints;
	static bool convexDecompose;
	static bool showConvexDecompositionDlg;
	static bool createVisualIfNone;
	static bool centerModel;
	static bool prepareModel;
	static bool noSelfCollision;
	static bool positionCtrl;

private slots:
	void on_qqImport_clicked();
	void on_qqCollisionLinksHidden_clicked();

	void on_qqJointsHidden_clicked();

	void on_qqConvexDecompose_clicked();

	void on_qqConvexDecomposeDlg_clicked();

	void on_qqCreateVisualLinks_clicked();

	void on_qqCenterModel_clicked();

	void on_qqModelDefinition_clicked();

	void on_qqAlternateMasks_clicked();

	void on_qqPositionCtrl_clicked();

private:
    Ui::CUrdfDialog *ui;
};

#endif // URDFDIALOG_H
