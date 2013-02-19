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
#include "simxContainer.h"
#include "porting.h"

#ifdef _WIN32
	#include <afxmt.h> // required for critical section thing
#endif /* _WIN32 */
#if defined (__linux) || defined (__APPLE__)
	#include <pthread.h>
#endif /* __linux || __APPLE__ */

class CSimxSocket
{
public:
	CSimxSocket(int portNb,bool simulationOnly,bool debug,int maxPacketSize,bool waitForTriggerFunctionAuthorized);
	virtual ~CSimxSocket();

	void start();

	void mainScriptAboutToBeCalled();
	void instancePass();

	void getInfo(int info[5]);
	int getStatus();
	int getPortNb();
	bool getActiveOnlyDuringSimulation();

	void setWaitForTrigger(bool w);
	bool getWaitForTrigger();
	void setWaitForTriggerEnabled(bool e);
	bool getWaitForTriggerEnabled();
	bool getWaitForTriggerAuthorized();

	void addErrorString(const char* err);
	char* getAndClearFullErrorStringBuffer(int& size);

protected:
	void* _run();
	void _lock();
	void _unlock();

	void _stop();
	void _executeCommands();

	volatile bool _commThreadLaunched;
	volatile bool _commThreadEnded;
	volatile bool clientIsConnected;
	bool otherSideIsBigEndian;
	int _portNb;
	bool _simulationOnly;
	bool _debug;
	int _maxPacketSize;
	int _auxConsoleHandle;
	bool _waitForTrigger;
	bool _waitForTriggerFunctionEnabled;
	bool _waitForTriggerFunctionAuthorized;

	int _lastReceivedMessage_time;
	int _lastSentMessage_time;
	int _successiveReception_time;
	int _lastReceivedMessage_cmdCnt;
	int _lastSentMessage_cmdCnt;

	std::vector<std::string> _textToPrintToConsole;
	std::vector<std::string> _last50Errors;
	
	CSimxContainer* _receivedCommands;
	CSimxContainer* _dataToSend;


	int _lockLevel;
#ifdef _WIN32
	static DWORD WINAPI _staticThreadProc(LPVOID arg);
	CCriticalSection _cs;
	DWORD _lockThreadId;
#endif /* _WIN32 */
#if defined (__linux) || defined (__APPLE__)
	static void* _staticThreadProc(void *arg);
	pthread_mutex_t _mutex;
	pthread_t _lockThreadId;
	pthread_t _theThread;
#endif /* __linux || __APPLE__ */
};
