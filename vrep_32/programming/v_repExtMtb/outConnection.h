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
#include <string>
#include <QTcpSocket>

class COutConnection  
{
public:
	COutConnection(const char* theConnectionAddress,int theConnectionPort,unsigned short maxPacketSize=250,char headerID1=59,char headerID2=57);
	virtual ~COutConnection();

	int connectToServer();
	bool sendData(char* data,int dataSize);
	char* receiveReplyData(int& dataSize);

protected:
	bool _sendSimplePacket(char* packet,int packetLength,unsigned short packetsLeft);
	int _receiveSimplePacket(std::vector<char>& packet);

	int _getTimeInMs();

	std::string			_socketConnectionAddress;
	int					_socketConnectionPort;

	QTcpSocket* _socket;

	char _headerByte1;
	char _headerByte2;
	unsigned short _maxPacketSize;
};
