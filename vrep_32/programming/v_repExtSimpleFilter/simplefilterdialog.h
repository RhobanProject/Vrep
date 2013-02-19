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

#ifndef SIMPLEFILTERDIALOG_H
#define SIMPLEFILTERDIALOG_H

#include <QDialog>

namespace Ui {
	class CSimpleFilterDialog;
}

class CSimpleFilterDialog : public QDialog
{
    Q_OBJECT

public:
	explicit CSimpleFilterDialog(QWidget *parent = 0);
	~CSimpleFilterDialog();

	void refresh();

	int sizeValue;
	float thresholdValue;

private slots:


	void on_qqSize_editingFinished();

	void on_qqThreshold_editingFinished();

	void on_qqOkCancel_accepted();

	void on_qqOkCancel_rejected();

private:
	Ui::CSimpleFilterDialog *ui;
};

#endif // SIMPLEFILTERDIALOG_H
