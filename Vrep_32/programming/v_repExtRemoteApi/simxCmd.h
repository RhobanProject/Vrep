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

#pragma once

#include <string>
#include <vector>
#include "porting.h"

class CSimxSocket; // forward declaration

class CSimxCmd
{
public:
	CSimxCmd(int commandID,WORD delayOrSplit,int dataSize,const char* dataPointer);
	CSimxCmd();
	virtual ~CSimxCmd();

	int getRawCommand();
	int getOperationMode();
	void setLastTimeProcessed(DWORD t);
	DWORD getLastTimeProcessed();

	bool areCommandAndCommandDataSame(const CSimxCmd* otherCmd);
	void appendYourData(std::vector<char>& dataString,bool otherSideIsBigEndian);
	bool appendYourMemorizedSplitData(bool calledFromContainer,std::vector<char>& dataString,bool& removeCommand,bool otherSideIsBigEndian);
	CSimxCmd* copyYourself();
	void setDataReply_nothing(bool success);
	void setDataReply_custom_transferBuffer(char* customData,int customDataSize,bool success);
	void setDataReply_custom_copyBuffer(char* customData,int customDataSize,bool success);
	void setDataReply_1float(float floatVal,bool success,bool otherSideIsBigEndian);
	void setDataReply_1int(int intVal,bool success,bool otherSideIsBigEndian);
	void setDataReply_2int(int intVal1,int intVal2,bool success,bool otherSideIsBigEndian);
	void setDataReply_3int(int intVal1,int intVal2,int intVal3,bool success,bool otherSideIsBigEndian);

	CSimxCmd* execute(CSimxSocket* sock,bool otherSideIsBigEndian);

protected:
	CSimxCmd* _executeCommand(CSimxSocket* sock,bool otherSideIsBigEndian);

	int _opMode;

	int _rawCmdID;

	// Following is command data:
	char _cmdData[8];
	std::string _cmdString;

	// Following is pure data:
	char* _pureData;
	int _pureDataSize;

	BYTE _status;
	WORD _processingDelayOrMaxDataSize;
	DWORD _lastTimeProcessed;
	int _dataSizeLeftToBeSent; // for simx_opmode_continuous_split
	int _executionTime; // in simulation time (in ms), or 0 if simulation is not running
	CSimxCmd* _memorizedSplitCmd;
};
