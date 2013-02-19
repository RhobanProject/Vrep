// This file is part of V-REP, the Virtual Robot Experimentation Platform.
// 
// Copyright 2006-2013 Dr. Marc Andreas Freese. All rights reserved. 
// marc@coppeliarobotics.com
// www.coppeliarobotics.com
// 
// V-REP is dual-licensed, under the terms of EITHER (at your option):
//   1. V-REP commercial license (contact us for details)
//   2. GNU GPL (see below)
// 
// GNU GPL license:
// -------------------------------------------------------------------
// V-REP is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// V-REP is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with V-REP.  If not, see <http://www.gnu.org/licenses/>.
// -------------------------------------------------------------------
//
// This file was automatically created for V-REP release V3.0.1 on January 20th 2013

#include "MyMath.h"

CMath::CMath()
{
}

CMath::~CMath()
{
}

void CMath::limitValue(float minValue,float maxValue,float &value)
{
	if (value>maxValue)
		value=maxValue;
	if (value<minValue) 
		value=minValue;
}

void CMath::limitValue(int minValue,int maxValue,int &value)
{
	if (value>maxValue) 
		value=maxValue;
	if (value<minValue) 
		value=minValue;
}

float CMath::robustAsin(float v)
{
	if (!isFloatNumberOk(v))
	{
		// GENERATE AN ERROR MESSAGE HERE: IDSNOTR_NO_NUMBER_ERROR1
		return(0.0f);
	}
	if (v>=1.0f)
		return(piVal*0.5f);
	if (v<=-1.0f)
		return(-piVal*0.5f);
	return(asinf(v));
}

float CMath::robustAcos(float v)
{
	if (!isFloatNumberOk(v))
	{
		// GENERATE AN ERROR MESSAGE HERE: IDSNOTR_NO_NUMBER_ERROR2
		return(0.0f);
	}
	if (v>=1.0f)
		return(0.0f);
	if (v<=-1.0f)
		return(piVal);
	return(acosf(v));
}

float CMath::robustFmod(float v,float w)
{
	if ( (!isFloatNumberOk(v))||(!isFloatNumberOk(w)) )
	{
		// GENERATE AN ERROR MESSAGE HERE: IDSNOTR_NO_NUMBER_ERROR3
		return(0.0f);
	}
	if (w==0.0f)
		return(0.0f);
	return(fmod(v,w));
}

double CMath::robustmod(double v,double w)
{
	if ( (!isDoubleNumberOk(v))||(!isDoubleNumberOk(w)) )
	{
		// GENERATE AN ERROR MESSAGE HERE: IDSNOTR_NO_NUMBER_ERROR4
		return(0.0);
	}
	if (w==0.0)
		return(0.0);
	return(fmod(v,w));
}

bool CMath::isFloatNumberOk(float v)
{
	return ( (!VREP_IS_NAN(v))&&(fabs(v)!=std::numeric_limits<float>::infinity()) );	
}

bool CMath::isDoubleNumberOk(double v)
{
	return ( (!VREP_IS_NAN(v))&&(fabs(v)!=std::numeric_limits<double>::infinity()) );	
}
