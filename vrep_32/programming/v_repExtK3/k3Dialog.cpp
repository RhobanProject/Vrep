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

#include "stdafx.h"
#include "v_repExtK3.h"
#include "k3Dialog.h"
#include "v_repLib.h"
#include "access.h"


IMPLEMENT_DYNAMIC(CK3Dialog, CDialog)

CK3Dialog::CK3Dialog(CWnd* pParent /*=NULL*/)
	: CDialog(CK3Dialog::IDD, pParent)
{
	_isVisible=false;
	dialogMenuItemHandle=-1;
}

CK3Dialog::~CK3Dialog()
{
}

void CK3Dialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_K3_LIST, m_k3List);
}


BEGIN_MESSAGE_MAP(CK3Dialog, CDialog)
	ON_LBN_SELCHANGE(IDC_K3_LIST, &CK3Dialog::OnLbnSelchangeK3List)
END_MESSAGE_MAP()


void CK3Dialog::refresh()
{ // This refreshed the dialog's items:

	int lastSel=simGetObjectLastSelection();

	m_k3List.ResetContent();
	for (int i=0;i<CAccess::k3Container->getCount();i++)
	{
		CK3* k3=CAccess::k3Container->getFromIndex(i);
		int sceneObjectHandle=k3->getAssociatedObject();
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
		int index=m_k3List.AddString(txt.c_str());
		m_k3List.SetItemData(index,(DWORD)k3->getID());
	}
	CK3* taggedObj=NULL;
	if (lastSel!=-1)
	{
		taggedObj=CAccess::k3Container->getFromAssociatedObject(lastSel);
		if (taggedObj==NULL)
			selectObjectInList(-1);
		else
			selectObjectInList(taggedObj->getID());
	}
	else
		selectObjectInList(-1);
	taggedObj=CAccess::k3Container->getFromID(getSelectedObjectInList());

}

void CK3Dialog::selectObjectInList(int objectHandle)
{
	m_k3List.SetCurSel(-1);
	for (int i=0;i<m_k3List.GetCount();i++)
	{
		if (m_k3List.GetItemData(i)==objectHandle)
		{
			m_k3List.SetCurSel(i);
			break;
		}
	}
}

int CK3Dialog::getSelectedObjectInList()
{
	int cs=m_k3List.GetCurSel();
	if (cs==LB_ERR)
		return(-1);
	int data=int(m_k3List.GetItemData(cs));
	CK3* k3=CAccess::k3Container->getFromID(data);
	if (k3!=NULL)
		return(k3->getID());
	return(-1);
}

bool CK3Dialog::getVisible()
{
	return(_isVisible);
}

void CK3Dialog::setVisible(bool isVisible)
{
	_isVisible=isVisible;
	if (isVisible)
		ShowWindow(SW_SHOW);
	else
		ShowWindow(SW_HIDE);
	// Reflext the visibility state in the menu bar item:
	simSetModuleMenuItemState(dialogMenuItemHandle,(_isVisible?3:1),"Khepera III Properties");
}

void CK3Dialog::OnCancel()
{ // We closed the dialog
	simLockInterface(1);
	setVisible(false);
	simLockInterface(0);
}

void CK3Dialog::OnOK()
{
	simLockInterface(1);
	simLockInterface(0);
}

void CK3Dialog::OnLbnSelchangeK3List()
{
	simLockInterface(1);
	int objectHandle=getSelectedObjectInList();
	simRemoveObjectFromSelection(sim_handle_all,-1);
	CK3* k3=CAccess::k3Container->getFromID(objectHandle);
	if (k3!=NULL)
	{
		int sceneObjHandle=k3->getAssociatedObject();
		if (sceneObjHandle!=-1)
			simAddObjectToSelection(sim_handle_single,sceneObjHandle);
	}
	simLockInterface(0);
}
