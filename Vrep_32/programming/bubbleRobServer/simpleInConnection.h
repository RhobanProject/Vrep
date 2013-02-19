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
#include "simplePorting.h"

class CSimpleInConnection
{
public:
	CSimpleInConnection(int theConnectionPort,WORD maxPacketSize=250,char headerID1=59,char headerID2=57);
	virtual ~CSimpleInConnection();

	bool connectToClient();
	char* receiveData(int& dataSize);
	bool replyToReceivedData(char* data,int dataSize);

	std::string getConnectedMachineIP();

protected:
	bool _sendSimplePacket(char* packet,int packetLength,WORD packetsLeft);
	int _receiveSimplePacket(std::vector<char>& packet);

	_SOCKET _socketServer;
	_SOCKET _socketClient;
	struct sockaddr_in _socketLocal;

	fd_set _socketTheSet;
	_timeval _socketTimeOut;
#ifdef _WIN32
	WSADATA _socketWsaData;
#endif /* _WIN32 */

	int _socketConnectionPort;
	bool _socketConnectWasOk;
	std::string _socketConnectedMachineIP;

	char _headerByte1;
	char _headerByte2;
	WORD _maxPacketSize;
};
