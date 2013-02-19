// This file is part of the REMOTE API
// 
// Copyright 2006-2013 Dr. Marc Andreas Freese. All rights reserved. 
// marc@coppeliarobotics.com
// www.coppeliarobotics.com
// 
// The REMOTE API is licensed under the terms of GNU GPL:
// 
// -------------------------------------------------------------------
// The REMOTE API is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// The REMOTE API is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with the REMOTE API.  If not, see <http://www.gnu.org/licenses/>.
// -------------------------------------------------------------------
//
// This file was automatically created for V-REP release V3.0.1 on January 20th 2013

#include "stdafx.h"
#include "simxUtils.h"

short littleEndianShortConversion(short v,bool otherSideIsBigEndian)
{
	short retV=v;
	if (otherSideIsBigEndian)
	{
		((BYTE*)&retV)[0]=((BYTE*)&v)[1];
		((BYTE*)&retV)[1]=((BYTE*)&v)[0];
	}
	return(retV);
}

WORD littleEndianWordConversion(WORD v,bool otherSideIsBigEndian)
{
	WORD retV=v;
	if (otherSideIsBigEndian)
	{
		((BYTE*)&retV)[0]=((BYTE*)&v)[1];
		((BYTE*)&retV)[1]=((BYTE*)&v)[0];
	}
	return(retV);
}

int littleEndianIntConversion(int v,bool otherSideIsBigEndian)
{
	int retV=v;
	if (otherSideIsBigEndian)
	{
		((BYTE*)&retV)[0]=((BYTE*)&v)[3];
		((BYTE*)&retV)[1]=((BYTE*)&v)[2];
		((BYTE*)&retV)[2]=((BYTE*)&v)[1];
		((BYTE*)&retV)[3]=((BYTE*)&v)[0];
	}
	return(retV);
}

float littleEndianFloatConversion(float v,bool otherSideIsBigEndian)
{
	float retV=v;
	if (otherSideIsBigEndian)
	{
		((BYTE*)&retV)[0]=((BYTE*)&v)[3];
		((BYTE*)&retV)[1]=((BYTE*)&v)[2];
		((BYTE*)&retV)[2]=((BYTE*)&v)[1];
		((BYTE*)&retV)[3]=((BYTE*)&v)[0];
	}
	return(retV);
}

double littleEndianDoubleConversion(double v,bool otherSideIsBigEndian)
{
	double retV=v;
	if (otherSideIsBigEndian)
	{
		((BYTE*)&retV)[0]=((BYTE*)&v)[7];
		((BYTE*)&retV)[1]=((BYTE*)&v)[6];
		((BYTE*)&retV)[2]=((BYTE*)&v)[5];
		((BYTE*)&retV)[3]=((BYTE*)&v)[4];
		((BYTE*)&retV)[4]=((BYTE*)&v)[3];
		((BYTE*)&retV)[5]=((BYTE*)&v)[2];
		((BYTE*)&retV)[6]=((BYTE*)&v)[1];
		((BYTE*)&retV)[7]=((BYTE*)&v)[0];
	}
	return(retV);
}

WORD getCRC(const char* data,int length)
{
	WORD crc=0;
	int p=0;
	for (int i=0;i<length;i++)
	{
		crc=crc^(((WORD)data[p])<<8);
		for (int j=0;j<8;j++)
		{
			if (crc&WORD(0x8000))
				crc=(crc<<1)^WORD(0x1021);
			else
				crc<<=1;
		}
		p++;
	}
	return(crc);
}
