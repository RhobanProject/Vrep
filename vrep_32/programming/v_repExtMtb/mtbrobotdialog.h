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

#ifndef MTBROBOTDIALOG_H
#define MTBROBOTDIALOG_H

#include <QDialog>

namespace Ui {
    class CMtbRobotDialog;
}

class CMtbRobotDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CMtbRobotDialog(QWidget *parent = 0);
    ~CMtbRobotDialog();

	void refresh();

	void makeVisible(bool visible);
	bool getVisible();
	void updateObjectsInList();
	void selectObjectInList(int objectHandle);
	int getSelectedObjectInList();

	int dialogMenuItemHandle;
	bool inRefreshRoutine;

	void reject();

private slots:

	void on_qqAutomatic_clicked();

	void on_qqRobotList_itemSelectionChanged();

	void on_qqRobotProgram_textChanged();

private:
    Ui::CMtbRobotDialog *ui;
};

#endif // MTBROBOTDIALOG_H
