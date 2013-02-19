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

#include <winsock2.h>
#include <vector>
#pragma message("-----------------------> Adding library: Winmm.lib") 
#pragma comment(lib,"Winmm.lib")
#pragma message("-----------------------> Adding library: Ws2_32.lib")
#pragma comment(lib,"Ws2_32.lib")

class CInConnection  
{
public:
	CInConnection(int theConnectionPort,WORD maxPacketSize=250,char headerID1=59,char headerID2=57);
	CInConnection(const char* thePipeName,WORD maxPacketSize=1024,char headerID1=59,char headerID2=57);
	virtual ~CInConnection();

	bool connectToClient();
	char* receiveData(int& dataSize);
	bool replyToReceivedData(char* data,int dataSize);

	std::string getConnectedMachineIP();

protected:
	bool _sendSimplePacket(char* packet,int packetLength,WORD packetsLeft);
	int _receiveSimplePacket(std::vector<char>& packet);

	SOCKET			_socketServer;
	SOCKET			_socketClient;
	WSADATA			_socketWsaData;
	sockaddr_in		_socketLocal;
	fd_set			_socketTheSet;
	timeval			_socketTimeOut;
	int				_socketConnectionPort;
	bool			_socketConnectWasOk;
	std::string		_socketConnectedMachineIP;

	std::string		_pipeName;
	HANDLE			_pipeThePipe;
	bool			_pipeConnectWasOk;

	bool _usingSockets; // if false, we have pipes
	char _headerByte1;
	char _headerByte2;
	WORD _maxPacketSize;
};