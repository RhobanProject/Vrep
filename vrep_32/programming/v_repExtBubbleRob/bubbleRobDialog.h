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

class CBubbleRobDialog : public CDialog
{
	DECLARE_DYNAMIC(CBubbleRobDialog)

public:
	CBubbleRobDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~CBubbleRobDialog();
	enum { IDD = IDD_BUBBLEROB_DIALOG };

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
	CEdit m_maxVelocity;
	CListBox m_bubbleRobList;
	afx_msg void OnLbnSelchangeBubblerobList();
	afx_msg void OnEnKillfocusMaxVelocity();
};
