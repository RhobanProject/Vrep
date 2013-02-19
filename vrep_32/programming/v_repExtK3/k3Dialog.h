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

#pragma once
#include "resource.h"
#include "afxwin.h"

class CK3Dialog : public CDialog
{
	DECLARE_DYNAMIC(CK3Dialog)

public:
	CK3Dialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~CK3Dialog();
	enum { IDD = IDD_K3_DIALOG };

	void refresh();
	bool getVisible();
	void setVisible(bool isVisible);
	void OnCancel();
	void OnOK();

	void selectObjectInList(int sceneObjectHandle);
	int getSelectedObjectInList();

	int dialogMenuItemHandle;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	bool _isVisible;

	DECLARE_MESSAGE_MAP()
	CListBox m_k3List;
	afx_msg void OnLbnSelchangeK3List();
};
