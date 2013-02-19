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

#include <vector>
#include "k3Container.h"

#ifdef _WIN32 // only the Windows version has a dialog!
	#include "k3Dialog.h"
#endif // _WIN32

class CAccess  
{
public:
	CAccess();
	virtual ~CAccess();

	static void createNonGui();
	static void destroyNonGui();
	static void createGui();
	static void destroyGui();

	// Following functions are helper functions to insert/extract items to/from scene objects.
	// Following is how this developer stores data under his/her header:
	// data saved under the DEVELOPER_DATA_HEADER header: item1ID,item1DataLengthInBytes,item1Data,item2ID,item2DataLengthInBytes,item2Data, etc.
	static void insertSerializationData(std::vector<unsigned char>& buffer,int dataName,const std::vector<unsigned char>& data);
	static bool extractSerializationData(std::vector<unsigned char>& buffer,int dataName,std::vector<unsigned char>& data);
	static int getDataLocationAndSize(const std::vector<unsigned char>& buffer,int dataName,int& theSize);
	static void push_int(std::vector<unsigned char>& buffer,int data);
	static void push_float(std::vector<unsigned char>& buffer,float data);
	static int pop_int(std::vector<unsigned char>& buffer);
	static float pop_float(std::vector<unsigned char>& buffer);

	static CK3Container* k3Container; 

#ifdef _WIN32 // only the Windows version has a dialog!
	static CK3Dialog* k3Dialog; // This is the dialog for k3
#endif // _WIN32
};
