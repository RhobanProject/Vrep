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

//**************************************************
// This static class basically contains all objects
// of the plugin. In particular, it holds
// the dialog of the plugin, and also all
// K3 objects related to K3's models
// in V-REP. Each K3 model in V-REP should
// have its corresponding object (CK3) in
// this plugin. 
//**************************************************

#include "stdafx.h"
#include "access.h"
#include "v_repLib.h"

#ifdef _WIN32 // only the Windows version has a dialog!
	#include "resource.h"
#endif // _WIN32

CK3Container* CAccess::k3Container=NULL;

#ifdef _WIN32 // only the Windows version has a dialog!
	CK3Dialog* CAccess::k3Dialog=NULL; // K3 dialog
#endif // _WIN32

CAccess::CAccess()
{ // Fully static class
}

CAccess::~CAccess()
{ // Fully static class
}

void CAccess::createNonGui()
{ // Set-up of data structures:
	k3Container=new CK3Container();
}

void CAccess::destroyNonGui()
{ // Clean-up all non-GUI stuff
	delete k3Container;
	k3Container=NULL;
}

void CAccess::createGui()
{
#ifdef _WIN32 // only the Windows version has a dialog!
	k3Dialog=new CK3Dialog(); // The plugin dialog
	k3Dialog->Create(IDD_K3_DIALOG,CWnd::FromHandle((HWND)simGetMainWindow(0)));
	simAddModuleMenuEntry("",1,&k3Dialog->dialogMenuItemHandle);
	simSetModuleMenuItemState(k3Dialog->dialogMenuItemHandle,1,"Khepera III Properties");
#endif // _WIN32
}

void CAccess::destroyGui()
{ // Clean-up GUI
#ifdef _WIN32 // only the Windows version has a dialog!
	delete k3Dialog;
	k3Dialog=NULL;
#endif // _WIN32
}

int CAccess::getDataLocationAndSize(const std::vector<unsigned char>& buffer,int dataName,int& theSize)
{
	int p=0;
	while (p<=int(buffer.size()-8))
	{
		int n,l;
		for (int i=0;i<4;i++)
			((unsigned char*)&n)[i]=buffer[p+i];
		for (int i=0;i<4;i++)
			((unsigned char*)&l)[i]=buffer[p+4+i];
		if (n==dataName)
		{
			if (l!=0)
			{
				theSize=l;
				return(p+8);
			}
			return(-1); // shouldn't happen if data saved correctly
		}
		p+=8+l;
	}
	return(-1); // data not present
}

bool CAccess::extractSerializationData(std::vector<unsigned char>& buffer,int dataName,std::vector<unsigned char>& data)
{ // Extracts the data saved under the dataName item (see header file on data organization)
	data.clear();
	int l;
	int p=getDataLocationAndSize(buffer,dataName,l);
	if (p!=-1)
	{
		for (int i=0;i<l;i++)
			data.push_back(buffer[p+i]);
		buffer.erase(buffer.begin()+p-8,buffer.begin()+p+l);
		return(true);
	}
	return(false); // that data was not present!
}

void CAccess::insertSerializationData(std::vector<unsigned char>& buffer,int dataName,const std::vector<unsigned char>& data)
{ // Inserts data under the dataName item (see header file on data organization)
	// 1. We remove the old data:
	std::vector<unsigned char> dummyBuffer;
	extractSerializationData(buffer,dataName,dummyBuffer);
	// 2. and insert the new data:
	// 2.1 data name:
	for (int i=0;i<4;i++)
		buffer.push_back(((unsigned char*)&dataName)[i]);
	// 2.2 Data length:
	int l=int(data.size());
	for (int i=0;i<4;i++)
		buffer.push_back(((unsigned char*)&l)[i]);
	// 2.3 The data itself:
	for (int i=0;i<l;i++)
		buffer.push_back(data[i]);
}

void CAccess::push_int(std::vector<unsigned char>& buffer,int data)
{
	for (unsigned int i=0;i<sizeof(data);i++)
		buffer.push_back(((unsigned char*)&data)[i]);
}

void CAccess::push_float(std::vector<unsigned char>& buffer,float data)
{
	for (unsigned int i=0;i<sizeof(data);i++)
		buffer.push_back(((unsigned char*)&data)[i]);
}

int CAccess::pop_int(std::vector<unsigned char>& buffer)
{
	int retVal=0;
	if (buffer.size()<sizeof(retVal))
		return(retVal);
	for (int i=int(sizeof(retVal))-1;i>=0;i--)
	{
		((unsigned char*)&retVal)[i]=buffer[buffer.size()-1];
		buffer.pop_back();
	}
	return(retVal);
}

float CAccess::pop_float(std::vector<unsigned char>& buffer)
{
	float retVal=0.0f;
	if (buffer.size()<sizeof(retVal))
		return(retVal);
	for (int i=int(sizeof(retVal))-1;i>=0;i--)
	{
		((unsigned char*)&retVal)[i]=buffer[buffer.size()-1];
		buffer.pop_back();
	}
	return(retVal);
}
