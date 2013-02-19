// Copyright 2006-2013 Dr. Marc Andreas Freese. All rights reserved. 
// marc@coppeliarobotics.com
// www.coppeliarobotics.com
// 
// -------------------------------------------------------------------
// This file is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// 
// You are free to use/modify/distribute this file for whatever purpose!
// -------------------------------------------------------------------
//
// This file was automatically created for V-REP release V3.0.1 on January 20th 2013

#include "mtbrobotdialog.h"
#include "ui_mtbrobotdialog.h"
#include "v_repLib.h"
#include "Access.h"

CMtbRobotDialog::CMtbRobotDialog(QWidget *parent) :
	QDialog(parent,Qt::Tool),
    ui(new Ui::CMtbRobotDialog)
{
    ui->setupUi(this);
	inRefreshRoutine=false;
}

CMtbRobotDialog::~CMtbRobotDialog()
{
    delete ui;
}

void CMtbRobotDialog::refresh()
{
	inRefreshRoutine=true;
	// Get handle of last selected object:
	int lastSel=simGetObjectLastSelection();

	updateObjectsInList();

	// Now initialized other dialog elements:
	CMtbRobot* taggedObj=NULL;
	ui->qqRobotProgram->setPlainText("");

	ui->qqAutomatic->setChecked(false);
	if (lastSel!=-1)
	{
		taggedObj=CAccess::mtbRobotContainer->getFromAssociatedObject(lastSel);
		if (taggedObj==NULL)
			selectObjectInList(-1);
		else
		{ // The last selected object is the base object of a MTB model!
			selectObjectInList(taggedObj->getID());
			std::string prg(taggedObj->getProgram());
			ui->qqRobotProgram->setPlainText(prg.c_str());
			ui->qqAutomatic->setChecked((taggedObj->getOptions()&1)!=0);
		}
	}
	else
		selectObjectInList(-1);
	ui->qqRobotProgram->setEnabled((taggedObj!=NULL)&&(simGetSimulationState()==sim_simulation_stopped));
	ui->qqAutomatic->setEnabled((taggedObj!=NULL)&&(simGetSimulationState()==sim_simulation_stopped));
	inRefreshRoutine=false;
}

void CMtbRobotDialog::makeVisible(bool visible)
{
	setVisible(visible);
	// Reflect the visibility state in the menu bar item:
	simSetModuleMenuItemState(dialogMenuItemHandle,(visible?3:1),"MTB Robot Properties");
}

bool CMtbRobotDialog::getVisible()
{
	return(isVisible());
}

void CMtbRobotDialog::selectObjectInList(int objectHandle)
{ // select an item in the list control:
	for (int i=0;i<ui->qqRobotList->count();i++)
	{
		QListWidgetItem* it=ui->qqRobotList->item(i);
		if (it!=NULL)
		{
			if (it->data(Qt::UserRole).toInt()==objectHandle)
			{
				it->setSelected(true);
				break;
			}
		}
	}
}

int CMtbRobotDialog::getSelectedObjectInList()
{ // get the item selected in the list control:
	QList<QListWidgetItem*> sel=ui->qqRobotList->selectedItems();
	if (sel.size()>0)
	{
		int data=sel.at(0)->data(Qt::UserRole).toInt();
		CMtbRobot* mtbRobot=CAccess::mtbRobotContainer->getFromID(data);
		if (mtbRobot!=NULL)
			return(mtbRobot->getID());
	}
	return(-1);
}

void CMtbRobotDialog::updateObjectsInList()
{
	ui->qqRobotList->clear();
	for (int i=0;i<CAccess::mtbRobotContainer->getCount();i++)
	{
		CMtbRobot* mtbRobot=CAccess::mtbRobotContainer->getFromIndex(i);
		int sceneObjectHandle=mtbRobot->getAssociatedObject();
		std::string txt;
		char* name=NULL;
		if (sceneObjectHandle!=-1)
			name=simGetObjectName(sceneObjectHandle);
		if (name==NULL)
			txt="Error";
		else
		{
			txt=name;
			simReleaseBuffer(name);
		}
		QListWidgetItem* itm=new QListWidgetItem(txt.c_str());
		itm->setData(Qt::UserRole,QVariant(mtbRobot->getID()));
		itm->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
		ui->qqRobotList->addItem(itm);
	}
}

void CMtbRobotDialog::on_qqAutomatic_clicked()
{
	simLockInterface(1);
	int objectHandle=getSelectedObjectInList();
	if (objectHandle!=-1)
	{
		CMtbRobot* mtbRobot=CAccess::mtbRobotContainer->getFromID(objectHandle);
		if (mtbRobot!=NULL)
		{
			mtbRobot->setOptions(mtbRobot->getOptions()^1);
			simAnnounceSceneContentChange(); // so that we have an undo point here
		}
	}
	simLockInterface(0);
}

void CMtbRobotDialog::on_qqRobotList_itemSelectionChanged()
{
	if (!inRefreshRoutine)
	{
		simLockInterface(1);
		int objectHandle=getSelectedObjectInList();
		simRemoveObjectFromSelection(sim_handle_all,-1);
		CMtbRobot* mtbRobot=CAccess::mtbRobotContainer->getFromID(objectHandle);
		if (mtbRobot!=NULL)
		{
			int sceneObjHandle=mtbRobot->getAssociatedObject();
			if (sceneObjHandle!=-1)
				simAddObjectToSelection(sim_handle_single,sceneObjHandle); // select the associated scene object!
		}
		simLockInterface(0);
	}
}

void CMtbRobotDialog::reject()
{
	// Reflect the visibility state in the menu bar item:
	simSetModuleMenuItemState(dialogMenuItemHandle,1,"MTB Robot Properties");
	done(0);
}


void CMtbRobotDialog::on_qqRobotProgram_textChanged()
{
	simLockInterface(1);
	int objectHandle=getSelectedObjectInList();
	if (objectHandle!=-1)
	{
		CMtbRobot* mtbRobot=CAccess::mtbRobotContainer->getFromID(objectHandle);
		if (mtbRobot!=NULL)
		{
			std::string prg=ui->qqRobotProgram->toPlainText().toStdString();
			mtbRobot->setProgram(prg); // Update the program
//			simAnnounceSceneContentChange(); // we don't allow for undo points here (otherwise every single char could be undone)
		}
	}
	simLockInterface(0);
}
