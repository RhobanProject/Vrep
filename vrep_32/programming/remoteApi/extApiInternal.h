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

#ifndef __EXTAPIINTERNAL_
#define __EXTAPIINTERNAL_

#include "extApiPlatform.h"

/* Out buffer for messages */
simxChar* _messageToSend;
simxInt _messageToSend_bufferSize;
simxInt _messageToSend_dataSize;

/* Temp buffer for split commands to send */
simxChar* _splitCommandsToSend;
simxInt _splitCommandsToSend_bufferSize;
simxInt _splitCommandsToSend_dataSize;

/* In buffer for messages */
simxChar* _messageReceived;
simxInt _messageReceived_bufferSize;
simxInt _messageReceived_dataSize;

/* Temp buffer for split commands received */
simxChar* _splitCommandsReceived;
simxInt _splitCommandsReceived_bufferSize;
simxInt _splitCommandsReceived_dataSize;

/* Temp buffer for last fetched command */
simxChar* _commandReceived;
simxInt _commandReceived_bufferSize;
simxInt _commandReceived_simulationTime;

/* Other variables */
simxChar _communicationThreadRunning;
simxInt _nextMessageIDToSend;
simxInt _waitBeforeSendingAgainWhenMessageIDArrived;
simxInt _lastReceivedMessageID;
simxInt _connectionID;
const simxChar* _tempConnectionAddress;
simxInt _tempConnectionPort;
simxChar _tempDoNotReconnectOnceDisconnected;

#endif /* __EXTAPIINTERNAL_ */
