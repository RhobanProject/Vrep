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

#include "simplefilterdialog.h"
#include "ui_simplefilterdialog.h"
#include "v_repLib.h"

CSimpleFilterDialog::CSimpleFilterDialog(QWidget *parent) :
	QDialog(parent,Qt::Tool),
	ui(new Ui::CSimpleFilterDialog)
{
    ui->setupUi(this);
}

CSimpleFilterDialog::~CSimpleFilterDialog()
{
    delete ui;
}

void CSimpleFilterDialog::refresh()
{

	ui->qqSize->setText(QString::number(sizeValue));
	ui->qqThreshold->setText(QString::number(thresholdValue));
}


void CSimpleFilterDialog::on_qqSize_editingFinished()
{
	bool ok;
	int v=ui->qqSize->text().toInt(&ok);
	if (ok)
	{
		if (v<1)
			v=1;
		if (v>100)
			v=100;
		sizeValue=v;
	}
	refresh();
}

void CSimpleFilterDialog::on_qqThreshold_editingFinished()
{
	bool ok;
	float v=ui->qqThreshold->text().toFloat(&ok);
	if (ok)
	{
		if (v<0.0f)
			v=0.0f;
		if (v>1.0f)
			v=1.0f;
		thresholdValue=v;
	}
	refresh();
}

void CSimpleFilterDialog::on_qqOkCancel_accepted()
{
	done(QDialog::Accepted);
}

void CSimpleFilterDialog::on_qqOkCancel_rejected()
{
	done(QDialog::Rejected);
}
