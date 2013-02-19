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

#include "v_repExtBubbleRob.h"
#include "bubbleRobDialog.h"
#include "access.h"
#include "v_repLib.h"


IMPLEMENT_DYNAMIC(CBubbleRobDialog, CDialog)

CBubbleRobDialog::CBubbleRobDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CBubbleRobDialog::IDD, pParent)
{
	_isVisible=false;
	dialogMenuItemHandle=-1;
}

CBubbleRobDialog::~CBubbleRobDialog()
{
}

void CBubbleRobDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MAX_VELOCITY, m_maxVelocity);
	DDX_Control(pDX, IDC_BUBBLEROB_LIST, m_bubbleRobList);
}


BEGIN_MESSAGE_MAP(CBubbleRobDialog, CDialog)
	ON_LBN_SELCHANGE(IDC_BUBBLEROB_LIST, &CBubbleRobDialog::OnLbnSelchangeBubblerobList)
	ON_EN_KILLFOCUS(IDC_MAX_VELOCITY, &CBubbleRobDialog::OnEnKillfocusMaxVelocity)
END_MESSAGE_MAP()


void CBubbleRobDialog::refresh()
{ // This refreshed the dialog's items:

	int lastSel=simGetObjectLastSelection();

	m_bubbleRobList.ResetContent();
	for (int i=0;i<CAccess::bubbleRobContainer->getCount();i++)
	{
		CBubbleRob* bubbleRob=CAccess::bubbleRobContainer->getFromIndex(i);
		int sceneObjectHandle=bubbleRob->getAssociatedObject();
		std::string txt="Object: ";
		char* name=NULL;
		if (sceneObjectHandle!=-1)
			name=simGetObjectName(sceneObjectHandle);
		if (name==NULL)
			txt+="Unassociated";
		else
		{
			txt+="Associated with ";
			txt+=name;
			simReleaseBuffer(name);
		}
		int index=m_bubbleRobList.AddString(txt.c_str());
		m_bubbleRobList.SetItemData(index,(DWORD)bubbleRob->getID());
	}
	CBubbleRob* taggedObj=NULL;
	if (lastSel!=-1)
	{
		taggedObj=CAccess::bubbleRobContainer->getFromAssociatedObject(lastSel);
		if (taggedObj==NULL)
			selectObjectInList(-1);
		else
			selectObjectInList(taggedObj->getID());
	}
	else
		selectObjectInList(-1);
	taggedObj=CAccess::bubbleRobContainer->getFromID(getSelectedObjectInList());
	m_maxVelocity.EnableWindow(taggedObj!=NULL);
	if (taggedObj!=NULL)
	{
		CString tmp;
		tmp.Format("%0.2f",120.0f*taggedObj->getMaxVelocity()/3.1415f); // display it in RPM
		m_maxVelocity.SetWindowText(tmp);
	}
	else
		m_maxVelocity.SetWindowText("");
}

void CBubbleRobDialog::selectObjectInList(int objectHandle)
{
	m_bubbleRobList.SetCurSel(-1);
	for (int i=0;i<m_bubbleRobList.GetCount();i++)
	{
		if (m_bubbleRobList.GetItemData(i)==objectHandle)
		{
			m_bubbleRobList.SetCurSel(i);
			break;
		}
	}
}

int CBubbleRobDialog::getSelectedObjectInList()
{
	int cs=m_bubbleRobList.GetCurSel();
	if (cs==LB_ERR)
		return(-1);
	int data=int(m_bubbleRobList.GetItemData(cs));
	CBubbleRob* bubbleRob=CAccess::bubbleRobContainer->getFromID(data);
	if (bubbleRob!=NULL)
		return(bubbleRob->getID());
	return(-1);
}

bool CBubbleRobDialog::getVisible()
{
	return(_isVisible);
}

void CBubbleRobDialog::setVisible(bool isVisible)
{
	_isVisible=isVisible;
	if (isVisible)
		ShowWindow(SW_SHOW);
	else
		ShowWindow(SW_HIDE);
	// Reflect the visibility state in the menu bar item:
	simSetModuleMenuItemState(dialogMenuItemHandle,(_isVisible?3:1),"BubbleRob Properties");
}

void CBubbleRobDialog::OnCancel()
{ // We closed the dialog
	simLockInterface(1);
	setVisible(false);
	simLockInterface(0);
}

void CBubbleRobDialog::OnOK()
{
	simLockInterface(1);
	simLockInterface(0);
}

void CBubbleRobDialog::OnLbnSelchangeBubblerobList()
{
	simLockInterface(1);
	int objectHandle=getSelectedObjectInList();
	simRemoveObjectFromSelection(sim_handle_all,-1);
	CBubbleRob* bubbleRob=CAccess::bubbleRobContainer->getFromID(objectHandle);
	if (bubbleRob!=NULL)
	{
		int sceneObjHandle=bubbleRob->getAssociatedObject();
		if (sceneObjHandle!=-1)
			simAddObjectToSelection(sim_handle_single,sceneObjHandle);
	}
	simLockInterface(0);
}

void CBubbleRobDialog::OnEnKillfocusMaxVelocity()
{
	simLockInterface(1);
	CBubbleRob* bubbleRob=CAccess::bubbleRobContainer->getFromAssociatedObject(simGetObjectLastSelection());
	if (bubbleRob!=NULL)
	{
		CString tmp;
		GetDlgItemText(IDC_MAX_VELOCITY,tmp);
		char* last;
		float v=float(strtod(tmp,&last));
		if (last[0]==0)
		{
			bubbleRob->setMaxVelocity(3.1415f*v/120.0f); // we had it displayed in RPM 
			simAnnounceSceneContentChange(); // this is so that V-REP registers a new undo-point here
		}
	}
	refresh();
	simLockInterface(0);
}

