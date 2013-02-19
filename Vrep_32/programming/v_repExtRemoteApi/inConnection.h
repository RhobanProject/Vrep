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

#include <vector>
#include "porting.h"

class CInConnection
{
public:
	CInConnection(int theConnectionPort,WORD maxPacketSize=250);
	virtual ~CInConnection();

	bool connectToClient();
	char* receiveMessage(int& messageSize);
	bool replyToReceivedMessage(char* message,int messageSize);

	std::string getConnectedMachineIP();
	bool isOtherSideBigEndian();

protected:
	bool _sendSimplePacket(char* packet,int packetLength,WORD packetsLeft);
	int _receiveSimplePacket(std::vector<char>& packet);

  _SOCKET             _socketServer;
  _SOCKET             _socketClient;
  struct sockaddr_in  _socketLocal;

	fd_set			        _socketTheSet;
  _timeval			      _socketTimeOut;
#ifdef _WIN32
	WSADATA			_socketWsaData;
#endif /* _WIN32 */

	int				_socketConnectionPort;
	bool			_socketConnectWasOk;
	std::string		_socketConnectedMachineIP;

	WORD _maxPacketSize;
	bool _otherSideIsBigEndian;
};
