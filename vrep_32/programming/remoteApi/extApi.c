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

#include "extApi.h"
#include "extApiInternal.h"
#include <stdio.h>

#ifdef _Included_extApiJava
	#include "extApiJava.h"
#endif

simxInt _nextConnectionID=1;
simxInt _replyWaitTimeoutInMs=_REPLY_WAIT_TIMEOUT_IN_MS;

EXTAPI_DLLEXPORT simxInt simxStart(const simxChar* connectionAddress,simxInt connectionPort,simxChar waitUntilConnected,simxChar doNotReconnectOnceDisconnected,simxInt timeOutInMs)
{
	simxInt startTime;
	extApi_initRand();

	/* Prepare various buffers */
	_messageToSend=extApi_allocateBuffer(SIMX_INIT_BUFF_SIZE);
	_messageToSend_bufferSize=SIMX_INIT_BUFF_SIZE;
	_messageToSend_dataSize=SIMX_HEADER_SIZE;

	_splitCommandsToSend=extApi_allocateBuffer(SIMX_INIT_BUFF_SIZE);
	_splitCommandsToSend_bufferSize=SIMX_INIT_BUFF_SIZE;
	_splitCommandsToSend_dataSize=0;

	_messageReceived=extApi_allocateBuffer(SIMX_INIT_BUFF_SIZE);
	_messageReceived_bufferSize=SIMX_INIT_BUFF_SIZE;
	_messageReceived_dataSize=0;

	_splitCommandsReceived=extApi_allocateBuffer(SIMX_INIT_BUFF_SIZE);
	_splitCommandsReceived_bufferSize=SIMX_INIT_BUFF_SIZE;
	_splitCommandsReceived_dataSize=0;

	_commandReceived=extApi_allocateBuffer(SIMX_INIT_BUFF_SIZE);
	_commandReceived_bufferSize=SIMX_INIT_BUFF_SIZE;
	_commandReceived_simulationTime=0;

	_nextMessageIDToSend=0;
	_lastReceivedMessageID=-1;
	_waitBeforeSendingAgainWhenMessageIDArrived=-1; /* do not wait */

	extApi_createMutexes();

	/* Launch the socket communication thread */
	_communicationThreadRunning=1;
	_connectionID=-1;
	_tempConnectionAddress=connectionAddress;
	_tempConnectionPort=connectionPort;
	_tempDoNotReconnectOnceDisconnected=doNotReconnectOnceDisconnected;
	extApi_launchThread(_communicationThread);
	if (waitUntilConnected)
	{
		startTime=extApi_getTimeInMs();
		while ( (extApi_getTimeDiffInMs(startTime)<timeOutInMs)&&(_connectionID==-1) )
			extApi_switchThread();
		if (_connectionID==-1)
		{
			simxFinish();
			return(-1);
		}
		else
			return(_connectionID);
	}
	else
		return(0);
}

EXTAPI_DLLEXPORT simxVoid simxFinish()
{
	if (_communicationThreadRunning)
	{
		/* first wait until the communication thread ended: */
		_communicationThreadRunning=0;
		while (_communicationThreadRunning==0)
			extApi_switchThread();
		_communicationThreadRunning=0;

		/* do some clean-up: */
		extApi_deleteMutexes();
		extApi_releaseBuffer(_commandReceived);
		extApi_releaseBuffer(_splitCommandsReceived);
		extApi_releaseBuffer(_messageToSend);
		extApi_releaseBuffer(_splitCommandsToSend);
		extApi_releaseBuffer(_messageReceived);
	}
}

simxVoid _waitUntilMessageArrived(simxInt* error)
{
	simxInt startTime;
	simxInt lastReceivedMessageIDCopy;
	if (_waitBeforeSendingAgainWhenMessageIDArrived!=-1)
	{ /* wait until we received a reply, or a timeout (if we wanna wait for the reply) */
		startTime=extApi_getTimeInMs();
		while (1)
		{
			extApi_lockResources();
			lastReceivedMessageIDCopy=_lastReceivedMessageID;
			extApi_unlockResources();
			if ((extApi_getTimeDiffInMs(startTime)>=_replyWaitTimeoutInMs)||(lastReceivedMessageIDCopy>=_waitBeforeSendingAgainWhenMessageIDArrived))
				break;
			extApi_switchThread();
		}
		if (lastReceivedMessageIDCopy<_waitBeforeSendingAgainWhenMessageIDArrived)
			error[0]|=simx_error_timeout_flag;
	}
}

simxChar* _setLastFetchedCmd(simxChar* cmdPtr,simxInt* error)
{
	simxInt blockSize,incr,i,status;
	simxChar* newCommand;
	if (cmdPtr!=0)
	{
		blockSize=extApi_endianConversionInt(((simxInt*)(cmdPtr+simx_cmdheaderoffset_mem_size))[0]);
		if (blockSize>_commandReceived_bufferSize)
		{ /* we need more memory here for the fetched command buffer */
			incr=blockSize-_commandReceived_bufferSize;
			if (incr<SIMX_MIN_BUFF_INCR)
				incr=SIMX_MIN_BUFF_INCR;
			newCommand=(simxChar*)extApi_allocateBuffer(_commandReceived_bufferSize+incr);
			extApi_releaseBuffer(_commandReceived);
			_commandReceived=newCommand;
			_commandReceived_bufferSize+=incr;
		}
		for (i=0;i<blockSize;i++)
			_commandReceived[i]=cmdPtr[i];
		cmdPtr=_commandReceived;
		status=cmdPtr[simx_cmdheaderoffset_status];
		_commandReceived_simulationTime=extApi_endianConversionInt(((simxInt*)(cmdPtr+simx_cmdheaderoffset_sim_time))[0]);
		if (status&1)
			error[0]|=simx_error_remote_error_flag; /* command caused an error on the server side */
	}
	else
		error[0]|=simx_error_novalue_flag;
	return(cmdPtr);
}


simxChar* _exec_null(simxInt cmdRaw,simxInt opMode,simxChar options,simxInt* error)
{
	simxUShort delayOrSplit;
	simxChar* cmdPtr=0;

	error[0]=simx_error_noerror;
	delayOrSplit=opMode&simx_cmdmask;
	opMode-=(opMode&simx_cmdmask);

	if (opMode!=simx_opmode_buffer)
	{
		/* Check if the command is already present in the request list */
		extApi_lockResources();
		if (opMode==simx_opmode_oneshot_split)
		{
			if (delayOrSplit<_MIN_SPLIT_AMOUNT_IN_BYTES)
				delayOrSplit=_MIN_SPLIT_AMOUNT_IN_BYTES;
			cmdPtr=_getCommandPointer_(cmdRaw,_splitCommandsToSend,_splitCommandsToSend_dataSize);
			if (cmdPtr!=0)
				error[0]|=simx_error_split_progress_flag; /* Command already there */
			else
			{ /* Command not there. Add it */
				_splitCommandsToSend=_appendCommand_(cmdRaw+opMode,options,delayOrSplit,_splitCommandsToSend,&_splitCommandsToSend_bufferSize,&_splitCommandsToSend_dataSize);
			}
		}
		else
		{
			cmdPtr=_getCommandPointer_(cmdRaw,_messageToSend+SIMX_HEADER_SIZE,_messageToSend_dataSize-SIMX_HEADER_SIZE);
			if ((cmdPtr==0)||(options&1))
			{ /* Command not there (or cmd cannot be overwritten). Add it */
				_messageToSend=_appendCommand_(cmdRaw+opMode,options,delayOrSplit,_messageToSend,&_messageToSend_bufferSize,&_messageToSend_dataSize);
			}
		}

		if (opMode==simx_opmode_oneshot_wait)
			_waitBeforeSendingAgainWhenMessageIDArrived=_nextMessageIDToSend;
		extApi_unlockResources();

		/* wait until we received a reply, or a timeout (if we wanna wait for the reply) */
		if (_waitBeforeSendingAgainWhenMessageIDArrived!=-1)
			_waitUntilMessageArrived(error); 
	}

	/* Check if the command is present in the input list */
	extApi_lockResources();
	cmdPtr=_getCommandPointer_(cmdRaw,_messageReceived+SIMX_HEADER_SIZE,_messageReceived_dataSize-SIMX_HEADER_SIZE);
	cmdPtr=_setLastFetchedCmd(cmdPtr,error);
	_waitBeforeSendingAgainWhenMessageIDArrived=-1; /* make sure to enable the communication thread again! */
	extApi_unlockResources();
	if (opMode==simx_opmode_oneshot_wait) // A cmd reply stays in the inbox always.. except when the mode is simx_opmode_oneshot_wait (to avoid polluting the inbox)
		_removeCommandReply_null(cmdRaw);
	return(cmdPtr);
}

simxChar* _exec_int(simxInt cmdRaw,simxInt opMode,simxChar options,simxInt intValue,simxInt* error)
{
	simxUShort delayOrSplit;
	simxChar* cmdPtr=0;

	error[0]=simx_error_noerror;
	delayOrSplit=opMode&simx_cmdmask;
	opMode-=(opMode&simx_cmdmask);

	if (opMode!=simx_opmode_buffer)
	{
		/* Check if the command is already present in the request list */
		extApi_lockResources();
		if (opMode==simx_opmode_oneshot_split)
		{
			if (delayOrSplit<_MIN_SPLIT_AMOUNT_IN_BYTES)
				delayOrSplit=_MIN_SPLIT_AMOUNT_IN_BYTES;
			cmdPtr=_getCommandPointer_i(cmdRaw,intValue,_splitCommandsToSend,_splitCommandsToSend_dataSize);
			if (cmdPtr!=0)
				error[0]|=simx_error_split_progress_flag; /* Command already there */
			else
			{ /* Command not there. Add it */
				_splitCommandsToSend=_appendCommand_i(cmdRaw+opMode,options,intValue,delayOrSplit,_splitCommandsToSend,&_splitCommandsToSend_bufferSize,&_splitCommandsToSend_dataSize);
			}
		}
		else
		{
			cmdPtr=_getCommandPointer_i(cmdRaw,intValue,_messageToSend+SIMX_HEADER_SIZE,_messageToSend_dataSize-SIMX_HEADER_SIZE);
			if ((cmdPtr!=0)&&((options&1)==0))
			{ /* Command already there, and we can overwrite it. Update it */
				((simxInt*)(cmdPtr+simx_cmdheaderoffset_cmd))[0]=extApi_endianConversionInt(cmdRaw+opMode);
			}
			else
			{ /* Command not there. Add it */
				_messageToSend=_appendCommand_i(cmdRaw+opMode,options,intValue,delayOrSplit,_messageToSend,&_messageToSend_bufferSize,&_messageToSend_dataSize);
			}
		}

		if (opMode==simx_opmode_oneshot_wait)
			_waitBeforeSendingAgainWhenMessageIDArrived=_nextMessageIDToSend;
		extApi_unlockResources();

		/* wait until we received a reply, or a timeout (if we wanna wait for the reply) */
		if (_waitBeforeSendingAgainWhenMessageIDArrived!=-1)
			_waitUntilMessageArrived(error); 
	}

	/* Check if the command is present in the input list */
	extApi_lockResources();
	cmdPtr=_getCommandPointer_i(cmdRaw,intValue,_messageReceived+SIMX_HEADER_SIZE,_messageReceived_dataSize-SIMX_HEADER_SIZE);
	cmdPtr=_setLastFetchedCmd(cmdPtr,error);
	_waitBeforeSendingAgainWhenMessageIDArrived=-1; /* make sure to enable the communication thread again! */
	extApi_unlockResources();
	if (opMode==simx_opmode_oneshot_wait) // A cmd reply stays in the inbox always.. except when the mode is simx_opmode_oneshot_wait (to avoid polluting the inbox)
		_removeCommandReply_int(cmdRaw,intValue);
	return(cmdPtr);
}

simxChar* _exec_intint(simxInt cmdRaw,simxInt opMode,simxChar options,simxInt intValue1,simxInt intValue2,simxInt* error)
{
	simxUShort delayOrSplit;
	simxChar* cmdPtr=0;

	error[0]=simx_error_noerror;
	delayOrSplit=opMode&simx_cmdmask;
	opMode-=(opMode&simx_cmdmask);

	if (opMode!=simx_opmode_buffer)
	{
		/* Check if the command is already present in the request list */
		extApi_lockResources();
		if (opMode==simx_opmode_oneshot_split)
		{
			if (delayOrSplit<_MIN_SPLIT_AMOUNT_IN_BYTES)
				delayOrSplit=_MIN_SPLIT_AMOUNT_IN_BYTES;
			cmdPtr=_getCommandPointer_ii(cmdRaw,intValue1,intValue2,_splitCommandsToSend,_splitCommandsToSend_dataSize);
			if (cmdPtr!=0)
				error[0]|=simx_error_split_progress_flag; /* Command already there */
			else
			{ /* Command not there. Add it */
				_splitCommandsToSend=_appendCommand_ii(cmdRaw+opMode,options,intValue1,intValue2,delayOrSplit,_splitCommandsToSend,&_splitCommandsToSend_bufferSize,&_splitCommandsToSend_dataSize);
			}
		}
		else
		{
			cmdPtr=_getCommandPointer_ii(cmdRaw,intValue1,intValue2,_messageToSend+SIMX_HEADER_SIZE,_messageToSend_dataSize-SIMX_HEADER_SIZE);
			if ((cmdPtr!=0)&&((options&1)==0))
			{ /* Command already there, and we can overwrite it. Update it */
				((simxInt*)(cmdPtr+simx_cmdheaderoffset_cmd))[0]=extApi_endianConversionInt(cmdRaw+opMode);
			}
			else
			{ /* Command not there. Add it */
				_messageToSend=_appendCommand_ii(cmdRaw+opMode,options,intValue1,intValue2,delayOrSplit,_messageToSend,&_messageToSend_bufferSize,&_messageToSend_dataSize);
			}
		}

		if (opMode==simx_opmode_oneshot_wait)
			_waitBeforeSendingAgainWhenMessageIDArrived=_nextMessageIDToSend;
		extApi_unlockResources();

		/* wait until we received a reply, or a timeout (if we wanna wait for the reply) */
		if (_waitBeforeSendingAgainWhenMessageIDArrived!=-1)
			_waitUntilMessageArrived(error); 
	}

	/* Check if the command is present in the input list */
	extApi_lockResources();
	cmdPtr=_getCommandPointer_ii(cmdRaw,intValue1,intValue2,_messageReceived+SIMX_HEADER_SIZE,_messageReceived_dataSize-SIMX_HEADER_SIZE);
	cmdPtr=_setLastFetchedCmd(cmdPtr,error);
	_waitBeforeSendingAgainWhenMessageIDArrived=-1; /* make sure to enable the communication thread again! */
	extApi_unlockResources();
	if (opMode==simx_opmode_oneshot_wait) // A cmd reply stays in the inbox always.. except when the mode is simx_opmode_oneshot_wait (to avoid polluting the inbox)
		_removeCommandReply_intint(cmdRaw,intValue1,intValue2);
	return(cmdPtr);
}

simxChar* _exec_string(simxInt cmdRaw,simxInt opMode,simxChar options,const simxChar* stringValue,simxInt* error)
{
	simxUShort delayOrSplit;
	simxChar* cmdPtr=0;

	error[0]=simx_error_noerror;

	delayOrSplit=opMode&simx_cmdmask;
	opMode-=(opMode&simx_cmdmask);

	if (opMode!=simx_opmode_buffer)
	{
		/* Check if the command is already present in the request list */
		extApi_lockResources();
		if (opMode==simx_opmode_oneshot_split)
		{
			if (delayOrSplit<_MIN_SPLIT_AMOUNT_IN_BYTES)
				delayOrSplit=_MIN_SPLIT_AMOUNT_IN_BYTES;
			cmdPtr=_getCommandPointer_s(cmdRaw,stringValue,_splitCommandsToSend,_splitCommandsToSend_dataSize);
			if (cmdPtr!=0)
			{ /* Command already there */
				error[0]|=simx_error_split_progress_flag;
			}
			else
			{ /* Command not there. Add it */
				_splitCommandsToSend=_appendCommand_s(cmdRaw+opMode,options,stringValue,delayOrSplit,_splitCommandsToSend,&_splitCommandsToSend_bufferSize,&_splitCommandsToSend_dataSize);
			}
		}
		else
		{
			cmdPtr=_getCommandPointer_s(cmdRaw,stringValue,_messageToSend+SIMX_HEADER_SIZE,_messageToSend_dataSize-SIMX_HEADER_SIZE);
			if ((cmdPtr!=0)&&((options&1)==0))
			{ /* Command already there, and we can overwrite it. Update it */
				((simxInt*)(cmdPtr+simx_cmdheaderoffset_cmd))[0]=extApi_endianConversionInt(cmdRaw+opMode);
			}
			else
			{ /* Command not there. Add it */
				_messageToSend=_appendCommand_s(cmdRaw+opMode,options,stringValue,delayOrSplit,_messageToSend,&_messageToSend_bufferSize,&_messageToSend_dataSize);
			}
		}

		if (opMode==simx_opmode_oneshot_wait)
			_waitBeforeSendingAgainWhenMessageIDArrived=_nextMessageIDToSend;
		extApi_unlockResources();

		/* wait until we received a reply, or a timeout (if we wanna wait for the reply) */
		if (_waitBeforeSendingAgainWhenMessageIDArrived!=-1)
			_waitUntilMessageArrived(error); 
	}

	/* Check if the command is present in the input list */
	extApi_lockResources();
	cmdPtr=_getCommandPointer_s(cmdRaw,stringValue,_messageReceived+SIMX_HEADER_SIZE,_messageReceived_dataSize-SIMX_HEADER_SIZE);
	cmdPtr=_setLastFetchedCmd(cmdPtr,error);
	_waitBeforeSendingAgainWhenMessageIDArrived=-1; /* make sure to enable the communication thread again! */
	extApi_unlockResources();
	if (opMode==simx_opmode_oneshot_wait) // A cmd reply stays in the inbox always.. except when the mode is simx_opmode_oneshot_wait (to avoid polluting the inbox)
		_removeCommandReply_string(cmdRaw,stringValue);
	return(cmdPtr);
}

simxChar* _exec_int_int(simxInt cmdRaw,simxInt opMode,simxChar options,simxInt intValue,simxInt intValue2,simxInt* error)
{
	simxChar* cmdPtr;
	simxUShort delayOrSplit;

	error[0]=simx_error_noerror;

	delayOrSplit=opMode&simx_cmdmask;
	opMode-=(opMode&simx_cmdmask);

	if (opMode!=simx_opmode_buffer)
	{
		/* Check if the command is already present in the request list */
		extApi_lockResources();
		if (opMode==simx_opmode_oneshot_split)
		{
			if (delayOrSplit<_MIN_SPLIT_AMOUNT_IN_BYTES)
				delayOrSplit=_MIN_SPLIT_AMOUNT_IN_BYTES;
			cmdPtr=_getCommandPointer_i(cmdRaw,intValue,_splitCommandsToSend,_splitCommandsToSend_dataSize);
			if ((cmdPtr!=0)&&((options&1)==0))
			{ /* Command already there, and we can overwrite it. Update it */
				error[0]|=simx_error_split_progress_flag;
			}
			else
			{ /* Command not there. Add it */
				_splitCommandsToSend=_appendCommand_i_i(cmdRaw+opMode,options,intValue,intValue2,delayOrSplit,_splitCommandsToSend,&_splitCommandsToSend_bufferSize,&_splitCommandsToSend_dataSize);
			}
		}
		else
		{
			cmdPtr=_getCommandPointer_i(cmdRaw,intValue,_messageToSend+SIMX_HEADER_SIZE,_messageToSend_dataSize-SIMX_HEADER_SIZE);
			if (cmdPtr!=0)
			{ /* Command already there. Update it */
				((simxInt*)(cmdPtr+simx_cmdheaderoffset_cmd))[0]=extApi_endianConversionInt(cmdRaw+opMode);
				((simxInt*)(cmdPtr+SIMX_SUBHEADER_SIZE+4))[0]=extApi_endianConversionInt(intValue2);
			}
			else
			{ /* Command not there. Add it */
				_messageToSend=_appendCommand_i_i(cmdRaw+opMode,options,intValue,intValue2,delayOrSplit,_messageToSend,&_messageToSend_bufferSize,&_messageToSend_dataSize);
			}
		}

		if (opMode==simx_opmode_oneshot_wait)
			_waitBeforeSendingAgainWhenMessageIDArrived=_nextMessageIDToSend;
		extApi_unlockResources();

		/* wait until we received a reply, or a timeout (if we wanna wait for the reply) */
		if (_waitBeforeSendingAgainWhenMessageIDArrived!=-1)
			_waitUntilMessageArrived(error); 
	}

	/* Check if the command is present in the input list (we might have this situation when we want to check if there was an error on the server side) */
	extApi_lockResources();
	cmdPtr=_getCommandPointer_i(cmdRaw,intValue,_messageReceived+SIMX_HEADER_SIZE,_messageReceived_dataSize-SIMX_HEADER_SIZE);
	cmdPtr=_setLastFetchedCmd(cmdPtr,error);
	_waitBeforeSendingAgainWhenMessageIDArrived=-1; /* make sure to enable the communication thread again! */
	extApi_unlockResources();
	if (opMode==simx_opmode_oneshot_wait) // A cmd reply stays in the inbox always.. except when the mode is simx_opmode_oneshot_wait (to avoid polluting the inbox)
		_removeCommandReply_int(cmdRaw,intValue);
	return(cmdPtr);
}

simxChar* _exec_intint_int(simxInt cmdRaw,simxInt opMode,simxChar options,simxInt intValue1,simxInt intValue2,simxInt intValue3,simxInt* error)
{
	simxChar* cmdPtr;
	simxUShort delayOrSplit;

	error[0]=simx_error_noerror;

	delayOrSplit=opMode&simx_cmdmask;
	opMode-=(opMode&simx_cmdmask);

	if (opMode!=simx_opmode_buffer)
	{
		/* Check if the command is already present in the request list */
		extApi_lockResources();
		if (opMode==simx_opmode_oneshot_split)
		{
			if (delayOrSplit<_MIN_SPLIT_AMOUNT_IN_BYTES)
				delayOrSplit=_MIN_SPLIT_AMOUNT_IN_BYTES;
			cmdPtr=_getCommandPointer_ii(cmdRaw,intValue1,intValue2,_splitCommandsToSend,_splitCommandsToSend_dataSize);
			if (cmdPtr!=0)
			{ /* Command already there */
				error[0]|=simx_error_split_progress_flag;
			}
			else
			{ /* Command not there. Add it */
				_splitCommandsToSend=_appendCommand_ii_i(cmdRaw+opMode,options,intValue1,intValue2,intValue3,delayOrSplit,_splitCommandsToSend,&_splitCommandsToSend_bufferSize,&_splitCommandsToSend_dataSize);
			}
		}
		else
		{
			cmdPtr=_getCommandPointer_ii(cmdRaw,intValue1,intValue2,_messageToSend+SIMX_HEADER_SIZE,_messageToSend_dataSize-SIMX_HEADER_SIZE);
			if ((cmdPtr!=0)&&((options&1)==0))
			{ /* Command already there, and we can overwrite it. Update it */
				((simxInt*)(cmdPtr+simx_cmdheaderoffset_cmd))[0]=extApi_endianConversionInt(cmdRaw+opMode);
				((simxInt*)(cmdPtr+SIMX_SUBHEADER_SIZE+8))[0]=extApi_endianConversionInt(intValue3);
			}
			else
			{ /* Command not there. Add it */
				_messageToSend=_appendCommand_ii_i(cmdRaw+opMode,options,intValue1,intValue2,intValue3,delayOrSplit,_messageToSend,&_messageToSend_bufferSize,&_messageToSend_dataSize);
			}
		}

		if (opMode==simx_opmode_oneshot_wait)
			_waitBeforeSendingAgainWhenMessageIDArrived=_nextMessageIDToSend;
		extApi_unlockResources();

		/* wait until we received a reply, or a timeout (if we wanna wait for the reply) */
		if (_waitBeforeSendingAgainWhenMessageIDArrived!=-1)
			_waitUntilMessageArrived(error); 
	}

	/* Check if the command is present in the input list (we might have this situation when we want to check if there was an error on the server side) */
	extApi_lockResources();
	cmdPtr=_getCommandPointer_ii(cmdRaw,intValue1,intValue2,_messageReceived+SIMX_HEADER_SIZE,_messageReceived_dataSize-SIMX_HEADER_SIZE);
	cmdPtr=_setLastFetchedCmd(cmdPtr,error);
	_waitBeforeSendingAgainWhenMessageIDArrived=-1; /* make sure to enable the communication thread again! */
	extApi_unlockResources();
	if (opMode==simx_opmode_oneshot_wait) // A cmd reply stays in the inbox always.. except when the mode is simx_opmode_oneshot_wait (to avoid polluting the inbox)
		_removeCommandReply_intint(cmdRaw,intValue1,intValue2);
	return(cmdPtr);
}

simxChar* _exec_intint_buffer(simxInt cmdRaw,simxInt opMode,simxChar options,simxInt intValue1,simxInt intValue2,simxChar* buffer,simxInt bufferSize,simxInt* error)
{
	simxChar* cmdPtr;
	simxUShort delayOrSplit;

	error[0]=simx_error_noerror;

	delayOrSplit=opMode&simx_cmdmask;
	opMode-=(opMode&simx_cmdmask);

	if (opMode!=simx_opmode_buffer)
	{
		/* Check if the command is already present in the request list */
		extApi_lockResources();
		if (opMode==simx_opmode_oneshot_split)
		{
			if (delayOrSplit<_MIN_SPLIT_AMOUNT_IN_BYTES)
				delayOrSplit=_MIN_SPLIT_AMOUNT_IN_BYTES;
			cmdPtr=_getCommandPointer_ii(cmdRaw,intValue1,intValue2,_splitCommandsToSend,_splitCommandsToSend_dataSize);
			if (cmdPtr!=0)
			{ /* Command already there */
				error[0]|=simx_error_split_progress_flag;
			}
			else
			{ /* Command not there. Add it */
				_splitCommandsToSend=_appendCommand_ii_buff(cmdRaw+opMode,options,intValue1,intValue2,buffer,bufferSize,delayOrSplit,_splitCommandsToSend,&_splitCommandsToSend_bufferSize,&_splitCommandsToSend_dataSize);
			}
		}
		else
		{
			cmdPtr=_getCommandPointer_ii(cmdRaw,intValue1,intValue2,_messageToSend+SIMX_HEADER_SIZE,_messageToSend_dataSize-SIMX_HEADER_SIZE);
			if ((cmdPtr!=0)&&((options&1)==0))
			{ /* Command already there, and we can overwrite it. Remove it, we'll add it again just after */
				_removeChunkFromBuffer(_messageToSend,cmdPtr,extApi_endianConversionInt(((simxInt*)(cmdPtr+simx_cmdheaderoffset_mem_size))[0]),&_messageToSend_dataSize); /* we remove then add the command again (b/c no guarantee the buffer has the same size) */
			}
			/* Add it: */
			_messageToSend=_appendCommand_ii_buff(cmdRaw+opMode,options,intValue1,intValue2,buffer,bufferSize,delayOrSplit,_messageToSend,&_messageToSend_bufferSize,&_messageToSend_dataSize);
		}

		if (opMode==simx_opmode_oneshot_wait)
			_waitBeforeSendingAgainWhenMessageIDArrived=_nextMessageIDToSend;
		extApi_unlockResources();

		/* wait until we received a reply, or a timeout (if we wanna wait for the reply) */
		if (_waitBeforeSendingAgainWhenMessageIDArrived!=-1)
			_waitUntilMessageArrived(error); 
	}

	/* Check if the command is present in the input list (we might have this situation when we want to check if there was an error on the server side) */
	extApi_lockResources();
	cmdPtr=_getCommandPointer_ii(cmdRaw,intValue1,intValue2,_messageReceived+SIMX_HEADER_SIZE,_messageReceived_dataSize-SIMX_HEADER_SIZE);
	cmdPtr=_setLastFetchedCmd(cmdPtr,error);
	_waitBeforeSendingAgainWhenMessageIDArrived=-1; /* make sure to enable the communication thread again! */
	extApi_unlockResources();
	if (opMode==simx_opmode_oneshot_wait) // A cmd reply stays in the inbox always.. except when the mode is simx_opmode_oneshot_wait (to avoid polluting the inbox)
		_removeCommandReply_intint(cmdRaw,intValue1,intValue2);
	return(cmdPtr);
}

simxChar* _exec_int_float(simxInt cmdRaw,simxInt opMode,simxChar options,simxInt intValue,simxFloat floatValue,simxInt* error)
{
	simxChar* cmdPtr;
	simxUShort delayOrSplit;

	error[0]=simx_error_noerror;

	delayOrSplit=opMode&simx_cmdmask;
	opMode-=(opMode&simx_cmdmask);

	if (opMode!=simx_opmode_buffer)
	{
		/* Check if the command is already present in the request list */
		extApi_lockResources();
		if (opMode==simx_opmode_oneshot_split)
		{
			if (delayOrSplit<_MIN_SPLIT_AMOUNT_IN_BYTES)
				delayOrSplit=_MIN_SPLIT_AMOUNT_IN_BYTES;
			cmdPtr=_getCommandPointer_i(cmdRaw,intValue,_splitCommandsToSend,_splitCommandsToSend_dataSize);
			if (cmdPtr!=0)
			{ /* Command already there */
				error[0]|=simx_error_split_progress_flag;
			}
			else
			{ /* Command not there. Add it */
				_splitCommandsToSend=_appendCommand_i_f(cmdRaw+opMode,options,intValue,floatValue,delayOrSplit,_splitCommandsToSend,&_splitCommandsToSend_bufferSize,&_splitCommandsToSend_dataSize);
			}
		}
		else
		{
			cmdPtr=_getCommandPointer_i(cmdRaw,intValue,_messageToSend+SIMX_HEADER_SIZE,_messageToSend_dataSize-SIMX_HEADER_SIZE);
			if ((cmdPtr!=0)&&((options&1)==0))
			{ /* Command already there, and we can overwrite it. Update it */
				((simxInt*)(cmdPtr+simx_cmdheaderoffset_cmd))[0]=extApi_endianConversionInt(cmdRaw+opMode);
				((simxFloat*)(cmdPtr+SIMX_SUBHEADER_SIZE+4))[0]=extApi_endianConversionFloat(floatValue);
			}
			else
			{ /* Command not there. Add it */
				_messageToSend=_appendCommand_i_f(cmdRaw+opMode,options,intValue,floatValue,delayOrSplit,_messageToSend,&_messageToSend_bufferSize,&_messageToSend_dataSize);
			}
		}

		if (opMode==simx_opmode_oneshot_wait)
			_waitBeforeSendingAgainWhenMessageIDArrived=_nextMessageIDToSend;
		extApi_unlockResources();

		/* wait until we received a reply, or a timeout (if we wanna wait for the reply) */
		if (_waitBeforeSendingAgainWhenMessageIDArrived!=-1)
			_waitUntilMessageArrived(error); 
	}

	/* Check if the command is present in the input list (we might have this situation when we want to check if there was an error on the server side) */
	extApi_lockResources();
	cmdPtr=_getCommandPointer_i(cmdRaw,intValue,_messageReceived+SIMX_HEADER_SIZE,_messageReceived_dataSize-SIMX_HEADER_SIZE);
	cmdPtr=_setLastFetchedCmd(cmdPtr,error);
	_waitBeforeSendingAgainWhenMessageIDArrived=-1; /* make sure to enable the communication thread again! */
	extApi_unlockResources();
	if (opMode==simx_opmode_oneshot_wait) // A cmd reply stays in the inbox always.. except when the mode is simx_opmode_oneshot_wait (to avoid polluting the inbox)
		_removeCommandReply_int(cmdRaw,intValue);
	return(cmdPtr);
}

simxChar* _exec_int_buffer(simxInt cmdRaw,simxInt opMode,simxChar options,simxInt intValue,simxChar* buffer,simxInt bufferSize,simxInt* error)
{
	simxChar* cmdPtr;
	simxUShort delayOrSplit;

	error[0]=simx_error_noerror;

	delayOrSplit=opMode&simx_cmdmask;
	opMode-=(opMode&simx_cmdmask);

	if (opMode!=simx_opmode_buffer)
	{
		/* Check if the command is already present in the request list */
		extApi_lockResources();
		if (opMode==simx_opmode_oneshot_split)
		{
			if (delayOrSplit<_MIN_SPLIT_AMOUNT_IN_BYTES)
				delayOrSplit=_MIN_SPLIT_AMOUNT_IN_BYTES;
			cmdPtr=_getCommandPointer_i(cmdRaw,intValue,_splitCommandsToSend,_splitCommandsToSend_dataSize);
			if (cmdPtr!=0)
			{ /* Command already there */
				/* Now make sure we have the same command size, otherwise we have to remove the old cmd and add freshly the new */
				if (extApi_endianConversionInt(((simxInt*)(cmdPtr+simx_cmdheaderoffset_mem_size))[0])==SIMX_SUBHEADER_SIZE+4+bufferSize)
					error[0]|=simx_error_split_progress_flag; /* ok, we have the same size */
				else
				{ /* we don't have the same size! Remove the old command */
					_removeChunkFromBuffer(_splitCommandsToSend,cmdPtr,extApi_endianConversionInt(((simxInt*)(cmdPtr+simx_cmdheaderoffset_mem_size))[0]),&_splitCommandsToSend_dataSize);
					cmdPtr=0; /* so that we will add the new command in next section */
				}
			}
			if (cmdPtr==0)
				_splitCommandsToSend=_appendCommand_i_buff(cmdRaw+opMode,options,intValue,buffer,bufferSize,delayOrSplit,_splitCommandsToSend,&_splitCommandsToSend_bufferSize,&_splitCommandsToSend_dataSize);
		}
		else
		{
			cmdPtr=_getCommandPointer_i(cmdRaw,intValue,_messageToSend+SIMX_HEADER_SIZE,_messageToSend_dataSize-SIMX_HEADER_SIZE);

			if ((cmdPtr!=0)&&((options&1)==0)) /* Command already there, and we can overwrite it. We remove it and add it again */
				_removeChunkFromBuffer(_messageToSend,cmdPtr,extApi_endianConversionInt(((simxInt*)(cmdPtr+simx_cmdheaderoffset_mem_size))[0]),&_messageToSend_dataSize); /* we remove then add the command again (b/c no guarantee the buffer has the same size) */
			_messageToSend=_appendCommand_i_buff(cmdRaw+opMode,options,intValue,buffer,bufferSize,delayOrSplit,_messageToSend,&_messageToSend_bufferSize,&_messageToSend_dataSize);
		}

		if (opMode==simx_opmode_oneshot_wait)
			_waitBeforeSendingAgainWhenMessageIDArrived=_nextMessageIDToSend;
		extApi_unlockResources();

		/* wait until we received a reply, or a timeout (if we wanna wait for the reply) */
		if (_waitBeforeSendingAgainWhenMessageIDArrived!=-1)
			_waitUntilMessageArrived(error); 
	}

	/* Check if the command is present in the input list (we might have this situation when we want to check if there was an error on the server side) */
	extApi_lockResources();
	cmdPtr=_getCommandPointer_i(cmdRaw,intValue,_messageReceived+SIMX_HEADER_SIZE,_messageReceived_dataSize-SIMX_HEADER_SIZE);
	cmdPtr=_setLastFetchedCmd(cmdPtr,error);
	_waitBeforeSendingAgainWhenMessageIDArrived=-1; /* make sure to enable the communication thread again! */
	extApi_unlockResources();
	if (opMode==simx_opmode_oneshot_wait) // A cmd reply stays in the inbox always.. except when the mode is simx_opmode_oneshot_wait (to avoid polluting the inbox)
		_removeCommandReply_int(cmdRaw,intValue);
	return(cmdPtr);
}


simxChar* _exec_string_buffer(simxInt cmdRaw,simxInt opMode,simxChar options,const simxChar* stringValue,simxChar* buffer,simxInt bufferSize,simxInt* error)
{
	simxChar* cmdPtr;
	simxUShort delayOrSplit;

	error[0]=simx_error_noerror;

	delayOrSplit=opMode&simx_cmdmask;
	opMode-=(opMode&simx_cmdmask);

	if (opMode!=simx_opmode_buffer)
	{
		/* Check if the command is already present in the request list */
		extApi_lockResources();
		if (opMode==simx_opmode_oneshot_split)
		{
			if (delayOrSplit<_MIN_SPLIT_AMOUNT_IN_BYTES)
				delayOrSplit=_MIN_SPLIT_AMOUNT_IN_BYTES;
			cmdPtr=_getCommandPointer_s(cmdRaw,stringValue,_splitCommandsToSend,_splitCommandsToSend_dataSize);
			if (cmdPtr!=0)
			{ /* Command already there */
				/* Now make sure we have the same command size, otherwise we have to remove the old cmd and add freshly the new */
				if (extApi_endianConversionInt(((simxInt*)(cmdPtr+simx_cmdheaderoffset_mem_size))[0])==SIMX_SUBHEADER_SIZE+extApi_getStringLength(stringValue)+1+bufferSize)
					error[0]|=simx_error_split_progress_flag; /* ok, we have the same size */
				else
				{ /* we don't have the same size! Remove the old command */
					_removeChunkFromBuffer(_splitCommandsToSend,cmdPtr,extApi_endianConversionInt(((simxInt*)(cmdPtr+simx_cmdheaderoffset_mem_size))[0]),&_splitCommandsToSend_dataSize);
					cmdPtr=0; /* so that we will add the new command in next section */
				}
			}
			if (cmdPtr==0)
				_splitCommandsToSend=_appendCommand_s_buff(cmdRaw+opMode,options,stringValue,buffer,bufferSize,delayOrSplit,_splitCommandsToSend,&_splitCommandsToSend_bufferSize,&_splitCommandsToSend_dataSize);
		}
		else
		{
			cmdPtr=_getCommandPointer_s(cmdRaw,stringValue,_messageToSend+SIMX_HEADER_SIZE,_messageToSend_dataSize-SIMX_HEADER_SIZE);
			if ((cmdPtr!=0)&&((options&1)==0))	/* Command already there, and we can overwrite it. Remove it and add it again */
				_removeChunkFromBuffer(_messageToSend,cmdPtr,extApi_endianConversionInt(((simxInt*)(cmdPtr+simx_cmdheaderoffset_mem_size))[0]),&_messageToSend_dataSize); /* we remove then add the command again (b/c no guarantee the buffer has the same size) */
			_messageToSend=_appendCommand_s_buff(cmdRaw+opMode,options,stringValue,buffer,bufferSize,delayOrSplit,_messageToSend,&_messageToSend_bufferSize,&_messageToSend_dataSize);
		}

		if (opMode==simx_opmode_oneshot_wait)
			_waitBeforeSendingAgainWhenMessageIDArrived=_nextMessageIDToSend;
		extApi_unlockResources();

		/* wait until we received a reply, or a timeout (if we wanna wait for the reply) */
		if (_waitBeforeSendingAgainWhenMessageIDArrived!=-1)
			_waitUntilMessageArrived(error); 
	}

	/* Check if the command is present in the input list (we might have this situation when we want to check if there was an error on the server side) */
	extApi_lockResources();
	cmdPtr=_getCommandPointer_s(cmdRaw,stringValue,_messageReceived+SIMX_HEADER_SIZE,_messageReceived_dataSize-SIMX_HEADER_SIZE);
	cmdPtr=_setLastFetchedCmd(cmdPtr,error);
	_waitBeforeSendingAgainWhenMessageIDArrived=-1; /* make sure to enable the communication thread again! */
	extApi_unlockResources();
	if (opMode==simx_opmode_oneshot_wait) // A cmd reply stays in the inbox always.. except when the mode is simx_opmode_oneshot_wait (to avoid polluting the inbox)
		_removeCommandReply_string(cmdRaw,stringValue);
	return(cmdPtr);
}

simxFloat _readPureDataFloat(simxChar* commandPointer,simxInt stringCnt,simxInt byteOffset)
{
	simxFloat retVal=0.0f;
	simxInt additionalOffset=0;
	if (commandPointer!=0)
	{
		additionalOffset+=_getCmdDataSize(commandPointer);
		while (stringCnt!=0)
		{
			additionalOffset+=extApi_getStringLength(commandPointer+SIMX_SUBHEADER_SIZE+additionalOffset)+1;
			stringCnt--;
		}
		additionalOffset+=byteOffset;
		retVal=extApi_endianConversionFloat(((simxFloat*)(commandPointer+SIMX_SUBHEADER_SIZE+additionalOffset))[0]);
	}
	return(retVal);
}

simxChar _readPureDataChar(simxChar* commandPointer,simxInt stringCnt,simxInt byteOffset)
{
	simxChar retVal=0;
	simxInt additionalOffset=0;
	if (commandPointer!=0)
	{
		additionalOffset+=_getCmdDataSize(commandPointer);
		while (stringCnt!=0)
		{
			additionalOffset+=extApi_getStringLength(commandPointer+SIMX_SUBHEADER_SIZE+additionalOffset)+1;
			stringCnt--;
		}
		additionalOffset+=byteOffset;
		retVal=commandPointer[SIMX_SUBHEADER_SIZE+additionalOffset];
	}
	return(retVal);
}

simxInt _readPureDataInt(simxChar* commandPointer,simxInt stringCnt,simxInt byteOffset)
{
	simxInt retVal=0;
	simxInt additionalOffset=0;
	if (commandPointer!=0)
	{
		additionalOffset+=_getCmdDataSize(commandPointer);
		while (stringCnt!=0)
		{
			additionalOffset+=extApi_getStringLength(commandPointer+SIMX_SUBHEADER_SIZE+additionalOffset)+1;
			stringCnt--;
		}
		additionalOffset+=byteOffset;
		retVal=extApi_endianConversionInt(((simxInt*)(commandPointer+SIMX_SUBHEADER_SIZE+additionalOffset))[0]);
	}
	return(retVal);
}

simxChar* _getCommandPointer_(simxInt cmdRaw,const simxChar* commandBufferStart,simxInt commandBufferSize)
{
	simxChar* retVal=0;
	simxInt offset=0;
	while (offset<commandBufferSize)
	{
		if ((extApi_endianConversionInt(((simxInt*)(commandBufferStart+offset+simx_cmdheaderoffset_cmd))[0])&simx_cmdmask)==cmdRaw)
		{
			retVal=(simxChar*)(commandBufferStart+offset);
			break;
		}
		offset+=extApi_endianConversionInt(((simxInt*)(commandBufferStart+offset+simx_cmdheaderoffset_mem_size))[0]);
	}
	return(retVal);
}

simxChar* _getCommandPointer_i(simxInt cmdRaw,simxInt intValue,const simxChar* commandBufferStart,simxInt commandBufferSize)
{
	simxChar* retVal=0;
	simxInt offset=0;
	while (offset<commandBufferSize)
	{
		if ((extApi_endianConversionInt(((simxInt*)(commandBufferStart+offset+simx_cmdheaderoffset_cmd))[0])&simx_cmdmask)==cmdRaw)
		{
			if (((simxInt*)(commandBufferStart+offset+SIMX_SUBHEADER_SIZE))[0]==extApi_endianConversionInt(intValue))
			{
				retVal=(simxChar*)(commandBufferStart+offset);
				break;
			}
		}
		offset+=extApi_endianConversionInt(((simxInt*)(commandBufferStart+offset+simx_cmdheaderoffset_mem_size))[0]);
	}
	return(retVal);
}

simxChar* _getCommandPointer_ii(simxInt cmdRaw,simxInt intValue1,simxInt intValue2,const simxChar* commandBufferStart,simxInt commandBufferSize)
{
	simxChar* retVal=0;
	simxInt offset=0;
	while (offset<commandBufferSize)
	{
		if ((extApi_endianConversionInt(((simxInt*)(commandBufferStart+offset+simx_cmdheaderoffset_cmd))[0])&simx_cmdmask)==cmdRaw)
		{
			if (((simxInt*)(commandBufferStart+offset+SIMX_SUBHEADER_SIZE))[0]==extApi_endianConversionInt(intValue1))
			{
				if (((simxInt*)(commandBufferStart+offset+SIMX_SUBHEADER_SIZE))[1]==extApi_endianConversionInt(intValue2))
				{
					retVal=(simxChar*)(commandBufferStart+offset);
					break;
				}
			}
		}
		offset+=extApi_endianConversionInt(((simxInt*)(commandBufferStart+offset+simx_cmdheaderoffset_mem_size))[0]);
	}
	return(retVal);
}

simxChar* _getCommandPointer_s(simxInt cmdRaw,const simxChar* stringValue,const simxChar* commandBufferStart,simxInt commandBufferSize)
{
	simxChar* retVal=0;
	simxInt offset=0;
	while (offset<commandBufferSize)
	{
		if ((extApi_endianConversionInt(((simxInt*)(commandBufferStart+offset+simx_cmdheaderoffset_cmd))[0])&simx_cmdmask)==cmdRaw)
		{
			if (extApi_areStringsSame(stringValue,commandBufferStart+offset+SIMX_SUBHEADER_SIZE)!=0)
			{
				retVal=(simxChar*)(commandBufferStart+offset);
				break;
			}
		}
		offset+=extApi_endianConversionInt(((simxInt*)(commandBufferStart+offset+simx_cmdheaderoffset_mem_size))[0]);
	}
	return(retVal);
}

simxVoid _removeChunkFromBuffer(const simxChar* bufferStart,simxChar* chunkStart,simxInt chunkSize,simxInt* buffer_dataSize)
{
	simxInt i,off,l;
	off=(simxInt)(chunkStart-bufferStart);
	l=buffer_dataSize[0]-off-chunkSize;
	for (i=0;i<l;i++)
		chunkStart[i]=chunkStart[chunkSize+i];
	buffer_dataSize[0]-=chunkSize;
}

simxChar* _appendCommand_(simxInt cmd,simxChar options,simxUShort delayOrSplit,simxChar* buffer,simxInt* buffer_bufferSize,simxInt* buffer_dataSize)
{
	simxChar data[SIMX_SUBHEADER_SIZE+0];
	((simxInt*)(data+simx_cmdheaderoffset_mem_size))[0]=extApi_endianConversionInt(SIMX_SUBHEADER_SIZE+0);

	((simxInt*)(data+simx_cmdheaderoffset_full_mem_size))[0]=extApi_endianConversionInt(SIMX_SUBHEADER_SIZE+0);
	((simxUShort*)(data+simx_cmdheaderoffset_pdata_offset0))[0]=extApi_endianConversionUShort(0);
	((simxInt*)(data+simx_cmdheaderoffset_pdata_offset1))[0]=extApi_endianConversionInt(0);

	((simxInt*)(data+simx_cmdheaderoffset_cmd))[0]=extApi_endianConversionInt(cmd);
	((simxUShort*)(data+simx_cmdheaderoffset_delay_or_split))[0]=extApi_endianConversionUShort(delayOrSplit);
	data[simx_cmdheaderoffset_status]=options;
	return(_appendChunkToBuffer(data,SIMX_SUBHEADER_SIZE+0,buffer,buffer_bufferSize,buffer_dataSize));
}

simxChar* _appendCommand_i(simxInt cmd,simxChar options,simxInt intValue,simxUShort delayOrSplit,simxChar* buffer,simxInt* buffer_bufferSize,simxInt* buffer_dataSize)
{
	simxChar data[SIMX_SUBHEADER_SIZE+4];
	((simxInt*)(data+simx_cmdheaderoffset_mem_size))[0]=extApi_endianConversionInt(SIMX_SUBHEADER_SIZE+4);

	((simxInt*)(data+simx_cmdheaderoffset_full_mem_size))[0]=extApi_endianConversionInt(SIMX_SUBHEADER_SIZE+4);
	((simxUShort*)(data+simx_cmdheaderoffset_pdata_offset0))[0]=extApi_endianConversionUShort(4);
	((simxInt*)(data+simx_cmdheaderoffset_pdata_offset1))[0]=extApi_endianConversionInt(0);

	((simxInt*)(data+simx_cmdheaderoffset_cmd))[0]=extApi_endianConversionInt(cmd);
	((simxUShort*)(data+simx_cmdheaderoffset_delay_or_split))[0]=extApi_endianConversionUShort(delayOrSplit);
	data[simx_cmdheaderoffset_status]=options;
	((simxInt*)(data+SIMX_SUBHEADER_SIZE))[0]=extApi_endianConversionInt(intValue);
	return(_appendChunkToBuffer(data,SIMX_SUBHEADER_SIZE+4,buffer,buffer_bufferSize,buffer_dataSize));
}

simxChar* _appendCommand_ii(simxInt cmd,simxChar options,simxInt intValue1,simxInt intValue2,simxUShort delayOrSplit,simxChar* buffer,simxInt* buffer_bufferSize,simxInt* buffer_dataSize)
{
	simxChar data[SIMX_SUBHEADER_SIZE+8];
	((simxInt*)(data+simx_cmdheaderoffset_mem_size))[0]=extApi_endianConversionInt(SIMX_SUBHEADER_SIZE+8);

	((simxInt*)(data+simx_cmdheaderoffset_full_mem_size))[0]=extApi_endianConversionInt(SIMX_SUBHEADER_SIZE+8);
	((simxUShort*)(data+simx_cmdheaderoffset_pdata_offset0))[0]=extApi_endianConversionUShort(8);
	((simxInt*)(data+simx_cmdheaderoffset_pdata_offset1))[0]=extApi_endianConversionInt(0);

	((simxInt*)(data+simx_cmdheaderoffset_cmd))[0]=extApi_endianConversionInt(cmd);
	((simxUShort*)(data+simx_cmdheaderoffset_delay_or_split))[0]=extApi_endianConversionUShort(delayOrSplit);
	data[simx_cmdheaderoffset_status]=options;
	((simxInt*)(data+SIMX_SUBHEADER_SIZE))[0]=extApi_endianConversionInt(intValue1);
	((simxInt*)(data+SIMX_SUBHEADER_SIZE))[1]=extApi_endianConversionInt(intValue2);
	return(_appendChunkToBuffer(data,SIMX_SUBHEADER_SIZE+8,buffer,buffer_bufferSize,buffer_dataSize));
}

simxChar* _appendCommand_s(simxInt cmd,simxChar options,const simxChar* stringValue,simxUShort delayOrSplit,simxChar* buffer,simxInt* buffer_bufferSize,simxInt* buffer_dataSize)
{
	simxInt i;
	simxChar* retVal;
	simxInt strLength=extApi_getStringLength(stringValue);
	simxChar* data=extApi_allocateBuffer(SIMX_SUBHEADER_SIZE+strLength+1);
	((simxInt*)(data+simx_cmdheaderoffset_mem_size))[0]=extApi_endianConversionInt(SIMX_SUBHEADER_SIZE+strLength+1);

	((simxInt*)(data+simx_cmdheaderoffset_full_mem_size))[0]=extApi_endianConversionInt(SIMX_SUBHEADER_SIZE+strLength+1);
	((simxUShort*)(data+simx_cmdheaderoffset_pdata_offset0))[0]=extApi_endianConversionUShort(strLength+1);
	((simxInt*)(data+simx_cmdheaderoffset_pdata_offset1))[0]=extApi_endianConversionInt(0);

	((simxInt*)(data+simx_cmdheaderoffset_cmd))[0]=extApi_endianConversionInt(cmd);
	((simxUShort*)(data+simx_cmdheaderoffset_delay_or_split))[0]=extApi_endianConversionUShort(delayOrSplit);
	data[simx_cmdheaderoffset_status]=options;
	for (i=0;i<strLength;i++)
		(data+SIMX_SUBHEADER_SIZE)[i]=stringValue[i];
	(data+SIMX_SUBHEADER_SIZE)[strLength]=0; /* terminal 0 */
	retVal=_appendChunkToBuffer(data,SIMX_SUBHEADER_SIZE+strLength+1,buffer,buffer_bufferSize,buffer_dataSize);
	extApi_releaseBuffer(data);
	return(retVal);
}

simxChar* _appendCommand_i_i(simxInt cmd,simxChar options,simxInt intValue,simxInt intValue2,simxUShort delayOrSplit,simxChar* buffer,simxInt* buffer_bufferSize,simxInt* buffer_dataSize)
{
	simxChar data[SIMX_SUBHEADER_SIZE+4+4];
	((simxInt*)(data+simx_cmdheaderoffset_mem_size))[0]=extApi_endianConversionInt(SIMX_SUBHEADER_SIZE+4+4);

	((simxInt*)(data+simx_cmdheaderoffset_full_mem_size))[0]=extApi_endianConversionInt(SIMX_SUBHEADER_SIZE+4+4);
	((simxUShort*)(data+simx_cmdheaderoffset_pdata_offset0))[0]=extApi_endianConversionUShort(4);
	((simxInt*)(data+simx_cmdheaderoffset_pdata_offset1))[0]=extApi_endianConversionInt(0);

	((simxInt*)(data+simx_cmdheaderoffset_cmd))[0]=extApi_endianConversionInt(cmd);
	((simxUShort*)(data+simx_cmdheaderoffset_delay_or_split))[0]=extApi_endianConversionUShort(delayOrSplit);
	data[simx_cmdheaderoffset_status]=options;
	((simxInt*)(data+SIMX_SUBHEADER_SIZE))[0]=extApi_endianConversionInt(intValue);
	((simxInt*)(data+SIMX_SUBHEADER_SIZE))[1]=extApi_endianConversionInt(intValue2);
	return(_appendChunkToBuffer(data,SIMX_SUBHEADER_SIZE+4+4,buffer,buffer_bufferSize,buffer_dataSize));
}


simxChar* _appendCommand_ii_i(simxInt cmd,simxChar options,simxInt intValue1,simxInt intValue2,simxInt intValue3,simxUShort delayOrSplit,simxChar* buffer,simxInt* buffer_bufferSize,simxInt* buffer_dataSize)
{
	simxChar data[SIMX_SUBHEADER_SIZE+4+4+4];
	((simxInt*)(data+simx_cmdheaderoffset_mem_size))[0]=extApi_endianConversionInt(SIMX_SUBHEADER_SIZE+4+4+4);

	((simxInt*)(data+simx_cmdheaderoffset_full_mem_size))[0]=extApi_endianConversionInt(SIMX_SUBHEADER_SIZE+4+4+4);
	((simxUShort*)(data+simx_cmdheaderoffset_pdata_offset0))[0]=extApi_endianConversionUShort(4+4);
	((simxInt*)(data+simx_cmdheaderoffset_pdata_offset1))[0]=extApi_endianConversionInt(0);

	((simxInt*)(data+simx_cmdheaderoffset_cmd))[0]=extApi_endianConversionInt(cmd);
	((simxUShort*)(data+simx_cmdheaderoffset_delay_or_split))[0]=extApi_endianConversionUShort(delayOrSplit);
	data[simx_cmdheaderoffset_status]=options;
	((simxInt*)(data+SIMX_SUBHEADER_SIZE))[0]=extApi_endianConversionInt(intValue1);
	((simxInt*)(data+SIMX_SUBHEADER_SIZE))[1]=extApi_endianConversionInt(intValue2);
	((simxInt*)(data+SIMX_SUBHEADER_SIZE))[2]=extApi_endianConversionInt(intValue3);
	return(_appendChunkToBuffer(data,SIMX_SUBHEADER_SIZE+4+4+4,buffer,buffer_bufferSize,buffer_dataSize));
}


simxChar* _appendCommand_i_f(simxInt cmd,simxChar options,simxInt intValue,simxFloat floatValue,simxUShort delayOrSplit,simxChar* buffer,simxInt* buffer_bufferSize,simxInt* buffer_dataSize)
{
	simxChar data[SIMX_SUBHEADER_SIZE+4+4];
	((simxInt*)(data+simx_cmdheaderoffset_mem_size))[0]=extApi_endianConversionInt(SIMX_SUBHEADER_SIZE+4+4);

	((simxInt*)(data+simx_cmdheaderoffset_full_mem_size))[0]=extApi_endianConversionInt(SIMX_SUBHEADER_SIZE+4+4);
	((simxUShort*)(data+simx_cmdheaderoffset_pdata_offset0))[0]=extApi_endianConversionUShort(4);
	((simxInt*)(data+simx_cmdheaderoffset_pdata_offset1))[0]=extApi_endianConversionInt(0);

	((simxInt*)(data+simx_cmdheaderoffset_cmd))[0]=extApi_endianConversionInt(cmd);
	((simxUShort*)(data+simx_cmdheaderoffset_delay_or_split))[0]=extApi_endianConversionUShort(delayOrSplit);
	data[simx_cmdheaderoffset_status]=options;
	((simxInt*)(data+SIMX_SUBHEADER_SIZE))[0]=extApi_endianConversionInt(intValue);
	((simxFloat*)(data+SIMX_SUBHEADER_SIZE))[1]=extApi_endianConversionFloat(floatValue);
	return(_appendChunkToBuffer(data,SIMX_SUBHEADER_SIZE+4+4,buffer,buffer_bufferSize,buffer_dataSize));
}


simxChar* _appendCommand_i_buff(simxInt cmd,simxChar options,simxInt intValue,simxChar* buffer,simxInt bufferSize,simxUShort delayOrSplit,simxChar* destBuffer,simxInt* destBuffer_bufferSize,simxInt* destBuffer_dataSize)
{
	simxInt i;
	simxChar* retVal;
	simxChar* data=extApi_allocateBuffer(SIMX_SUBHEADER_SIZE+4+bufferSize);
	((simxInt*)(data+simx_cmdheaderoffset_mem_size))[0]=extApi_endianConversionInt(SIMX_SUBHEADER_SIZE+4+bufferSize);

	((simxInt*)(data+simx_cmdheaderoffset_full_mem_size))[0]=extApi_endianConversionInt(SIMX_SUBHEADER_SIZE+4+bufferSize);
	((simxUShort*)(data+simx_cmdheaderoffset_pdata_offset0))[0]=extApi_endianConversionUShort(4);
	((simxInt*)(data+simx_cmdheaderoffset_pdata_offset1))[0]=extApi_endianConversionInt(0);

	((simxInt*)(data+simx_cmdheaderoffset_cmd))[0]=extApi_endianConversionInt(cmd);
	((simxUShort*)(data+simx_cmdheaderoffset_delay_or_split))[0]=extApi_endianConversionUShort(delayOrSplit);
	data[simx_cmdheaderoffset_status]=options;
	((simxInt*)(data+SIMX_SUBHEADER_SIZE))[0]=extApi_endianConversionInt(intValue);
	for (i=0;i<bufferSize;i++)
		data[SIMX_SUBHEADER_SIZE+4+i]=buffer[i];
	retVal=_appendChunkToBuffer(data,SIMX_SUBHEADER_SIZE+4+bufferSize,destBuffer,destBuffer_bufferSize,destBuffer_dataSize);
	extApi_releaseBuffer(data);
	return(retVal);
}

simxChar* _appendCommand_ii_buff(simxInt cmd,simxChar options,simxInt intValue1,simxInt intValue2,simxChar* buffer,simxInt bufferSize,simxUShort delayOrSplit,simxChar* destBuffer,simxInt* destBuffer_bufferSize,simxInt* destBuffer_dataSize)
{
	simxInt i;
	simxChar* retVal;
	simxChar* data=extApi_allocateBuffer(SIMX_SUBHEADER_SIZE+4+4+bufferSize);
	((simxInt*)(data+simx_cmdheaderoffset_mem_size))[0]=extApi_endianConversionInt(SIMX_SUBHEADER_SIZE+4+4+bufferSize);

	((simxInt*)(data+simx_cmdheaderoffset_full_mem_size))[0]=extApi_endianConversionInt(SIMX_SUBHEADER_SIZE+4+4+bufferSize);
	((simxUShort*)(data+simx_cmdheaderoffset_pdata_offset0))[0]=extApi_endianConversionUShort(4+4);
	((simxInt*)(data+simx_cmdheaderoffset_pdata_offset1))[0]=extApi_endianConversionInt(0);

	((simxInt*)(data+simx_cmdheaderoffset_cmd))[0]=extApi_endianConversionInt(cmd);
	((simxUShort*)(data+simx_cmdheaderoffset_delay_or_split))[0]=extApi_endianConversionUShort(delayOrSplit);
	data[simx_cmdheaderoffset_status]=options;
	((simxInt*)(data+SIMX_SUBHEADER_SIZE))[0]=extApi_endianConversionInt(intValue1);
	((simxInt*)(data+SIMX_SUBHEADER_SIZE))[1]=extApi_endianConversionInt(intValue2);
	for (i=0;i<bufferSize;i++)
		data[SIMX_SUBHEADER_SIZE+4+4+i]=buffer[i];
	retVal=_appendChunkToBuffer(data,SIMX_SUBHEADER_SIZE+4+4+bufferSize,destBuffer,destBuffer_bufferSize,destBuffer_dataSize);
	extApi_releaseBuffer(data);
	return(retVal);
}

simxChar* _appendCommand_s_buff(simxInt cmd,simxChar options,const simxChar* stringValue,simxChar* buffer,simxInt bufferSize,simxUShort delayOrSplit,simxChar* destBuffer,simxInt* destBuffer_bufferSize,simxInt* destBuffer_dataSize)
{
	simxInt i;
	simxChar* retVal;
	simxChar* data=extApi_allocateBuffer(SIMX_SUBHEADER_SIZE+extApi_getStringLength(stringValue)+1+bufferSize);
	((simxInt*)(data+simx_cmdheaderoffset_mem_size))[0]=extApi_endianConversionInt(SIMX_SUBHEADER_SIZE+extApi_getStringLength(stringValue)+1+bufferSize);

	((simxInt*)(data+simx_cmdheaderoffset_full_mem_size))[0]=extApi_endianConversionInt(SIMX_SUBHEADER_SIZE+extApi_getStringLength(stringValue)+1+bufferSize);
	((simxUShort*)(data+simx_cmdheaderoffset_pdata_offset0))[0]=extApi_endianConversionUShort(extApi_getStringLength(stringValue)+1);
	((simxInt*)(data+simx_cmdheaderoffset_pdata_offset1))[0]=extApi_endianConversionInt(0);

	((simxInt*)(data+simx_cmdheaderoffset_cmd))[0]=extApi_endianConversionInt(cmd);
	((simxUShort*)(data+simx_cmdheaderoffset_delay_or_split))[0]=extApi_endianConversionUShort(delayOrSplit);
	data[simx_cmdheaderoffset_status]=options;
	for (i=0;i<extApi_getStringLength(stringValue)+1;i++)
		data[SIMX_SUBHEADER_SIZE+i]=stringValue[i];
	for (i=0;i<bufferSize;i++)
		data[SIMX_SUBHEADER_SIZE+extApi_getStringLength(stringValue)+1+i]=buffer[i];
	retVal=_appendChunkToBuffer(data,SIMX_SUBHEADER_SIZE+extApi_getStringLength(stringValue)+1+bufferSize,destBuffer,destBuffer_bufferSize,destBuffer_dataSize);
	extApi_releaseBuffer(data);
	return(retVal);
}

simxChar* _appendChunkToBuffer(const simxChar* chunk,simxInt chunkSize,simxChar* buffer,simxInt* buffer_bufferSize,simxInt* buffer_dataSize)
{
	simxInt i,incr;
	simxChar* retBuffer;
	if (buffer_bufferSize[0]-buffer_dataSize[0]<chunkSize)
	{ /* not enough space in the buffer. Allocate more! */
		incr=chunkSize-(buffer_bufferSize[0]-buffer_dataSize[0]);
		if (incr<SIMX_MIN_BUFF_INCR)
			incr=SIMX_MIN_BUFF_INCR;
		retBuffer=extApi_allocateBuffer(buffer_bufferSize[0]+incr);
		for (i=0;i<buffer_dataSize[0];i++)
			retBuffer[i]=buffer[i];
		extApi_releaseBuffer(buffer);
		buffer_bufferSize[0]+=incr;
	}
	else
		retBuffer=buffer;
	/* insert the data (if chunk is not NULL) */
	if (chunk!=0)
	{
		for (i=0;i<chunkSize;i++)
			retBuffer[buffer_dataSize[0]+i]=chunk[i];
	}
	buffer_dataSize[0]+=chunkSize;
	return(retBuffer);
}

simxChar* _getSameCommandPointer(const simxChar* cmdPtr,simxChar* cmdBuffer,simxInt cmdBufferSize)
{
	simxInt off,cmd1Raw,cmd2Raw;

	cmd1Raw=extApi_endianConversionInt(((simxInt*)(cmdPtr+simx_cmdheaderoffset_cmd))[0])&simx_cmdmask;
	off=0;
	while (off<cmdBufferSize)
	{
		cmd2Raw=extApi_endianConversionInt(((simxInt*)(cmdBuffer+off+simx_cmdheaderoffset_cmd))[0])&simx_cmdmask;
		if (cmd1Raw==cmd2Raw)
		{ /* The commands are same. We need to check if the command data is same too */
			if ((cmd1Raw>simx_cmd4bytes_start)&&(cmd1Raw<simx_cmd8bytes_start))
			{
				if ( ((simxInt*)(cmdPtr+SIMX_SUBHEADER_SIZE))[0]==((simxInt*)(cmdBuffer+off+SIMX_SUBHEADER_SIZE))[0] )
					return(cmdBuffer+off);
			}
			if ((cmd1Raw>simx_cmd8bytes_start)&&(cmd1Raw<simx_cmd1string_start))
			{
				if ( ((simxInt*)(cmdPtr+SIMX_SUBHEADER_SIZE))[0]==((simxInt*)(cmdBuffer+off+SIMX_SUBHEADER_SIZE))[0] )
				{
					if ( ((simxInt*)(cmdPtr+SIMX_SUBHEADER_SIZE+4))[0]==((simxInt*)(cmdBuffer+off+SIMX_SUBHEADER_SIZE+4))[0] )
						return(cmdBuffer+off);
				}
			}
			if ((cmd1Raw>simx_cmd1string_start)&&(cmd1Raw<simx_cmdreserved_start))
			{
				if (extApi_areStringsSame(cmdPtr+SIMX_SUBHEADER_SIZE,cmdBuffer+off+SIMX_SUBHEADER_SIZE)!=0)
					return(cmdBuffer+off);
			}
		}
		off+=extApi_endianConversionInt(((simxInt*)(cmdBuffer+off+simx_cmdheaderoffset_mem_size))[0]);
	}
	return(0);
}

simxInt _getCmdDataSize(simxChar* commandPointer)
{
	simxInt retVal=0;
	simxInt cmdRaw=extApi_endianConversionInt(((simxInt*)(commandPointer+simx_cmdheaderoffset_cmd))[0])&simx_cmdmask;
	if ((cmdRaw>simx_cmd4bytes_start)&&(cmdRaw<simx_cmd8bytes_start))
		retVal=4;
	if ((cmdRaw>simx_cmd8bytes_start)&&(cmdRaw<simx_cmd1string_start))
		retVal=8;
	if ((cmdRaw>simx_cmd1string_start)&&(cmdRaw<simx_cmdreserved_start))
		retVal=extApi_getStringLength(commandPointer+SIMX_SUBHEADER_SIZE)+1;
	return(retVal);
}


simxChar _sendMessage_socket(const simxChar* message,simxInt messageSize)
{ /* return 1: success */
	simxShort packetCount=0;
	simxInt s=messageSize;
	simxInt ptr=0;
	simxInt sizeToSend;

	if (messageSize==0)
		return(0);
	
	/* In Following we make sure we don't send too big packets (we might send the data in several packets) */
	while (s!=0)
	{
		packetCount++;
		if (s>SOCKET_MAX_PACKET_SIZE-SOCKET_HEADER_LENGTH)
			s-=SOCKET_MAX_PACKET_SIZE-SOCKET_HEADER_LENGTH;
		else
			s=0;
	}
	s=messageSize;
	while (s!=0)
	{
		packetCount--;
		sizeToSend=s;
		if (s>SOCKET_MAX_PACKET_SIZE-SOCKET_HEADER_LENGTH)
			sizeToSend=SOCKET_MAX_PACKET_SIZE-SOCKET_HEADER_LENGTH;
		s-=sizeToSend;
		if (_sendSimplePacket_socket(message+ptr,(simxShort)sizeToSend,packetCount)==0)
			return(0);
		ptr+=sizeToSend;
	}
	return(1);
}

simxChar* _receiveReplyMessage_socket(simxInt* messageSize)
{ /* return 0: failure */
	simxInt i,result;
	simxInt cnt=0;
	simxChar* retBuff=0;
	simxInt retBuffSize=0;
	simxChar inDat[SOCKET_MAX_PACKET_SIZE];
	simxShort inDatSize;

	while (1)
	{
		result=_receiveSimplePacket_socket(inDat,&inDatSize);
		if (result<0)
		{
			if (cnt!=0)
				extApi_releaseBuffer(retBuff);
			return(0);
		}
		if (cnt==0)
			retBuff=extApi_allocateBuffer((1+result)*SOCKET_MAX_PACKET_SIZE);
		for (i=0;i<inDatSize;i++)
			retBuff[retBuffSize+i]=inDat[i];
		retBuffSize+=inDatSize;
		if (result==0)
		{ /* ok, no more packets to receive */
			messageSize[0]=retBuffSize;
			return(retBuff);
		}
		cnt+=1;
	}
	return(0);
}

simxChar _sendSimplePacket_socket(const simxChar* packet,simxShort packetLength,simxShort packetsLeft)
{
	simxInt i;
	simxChar toSend[SOCKET_MAX_PACKET_SIZE];

	if (packetLength==0)
		return(0);

	/* Prepare the header */
	((simxShort*)toSend)[0]=extApi_endianConversionShort(1); /* Allows to detect Endianness on the other side */
	((simxShort*)toSend)[1]=extApi_endianConversionShort(packetLength);
	((simxShort*)toSend)[2]=extApi_endianConversionShort(packetsLeft);
	
	/* Prepare the rest of the packet */
	for (i=0;i<packetLength;i++)
		toSend[SOCKET_HEADER_LENGTH+i]=packet[i];

	/* Send the packet */
	if (extApi_send_socket(toSend,packetLength+SOCKET_HEADER_LENGTH)==packetLength+SOCKET_HEADER_LENGTH)
		return(1);
	return(0);
}

simxInt _receiveSimplePacket_socket(simxChar* packet,simxShort* packetSize)
{ /* Returns the number of packets left to read if >=0, otherwise error */
	/* packet should have at least SOCKET_MAX_PACKET_SIZE bytes free! */

	/* 1. Read the header and packet size */
	simxChar headerAndSize[SOCKET_HEADER_LENGTH];
	simxInt totalReceived=0;
	simxInt nb;
	simxShort dataLength,packetsLeft;
	simxInt startT=extApi_getTimeInMs();
	while(totalReceived!=SOCKET_HEADER_LENGTH)
	{
		nb=extApi_recv_socket(headerAndSize+totalReceived,SOCKET_HEADER_LENGTH-totalReceived);
		if (nb<1)
			break;
		totalReceived+=nb;
		if (extApi_getTimeDiffInMs(startT)>SOCKET_TIMEOUT_READ)
			break;
	}
	
	/* 2. Check if the header is consistent */
	if (totalReceived!=SOCKET_HEADER_LENGTH)
		return(-1);
	dataLength=extApi_endianConversionShort(((simxShort*)headerAndSize)[1]);
	packetsLeft=extApi_endianConversionShort(((simxShort*)headerAndSize)[2]);

	/* 3. Read the data with correct length */
	packetSize[0]=dataLength;
	totalReceived=0;
	startT=extApi_getTimeInMs();
	while(totalReceived!=dataLength)
	{
		nb=extApi_recv_socket(packet+totalReceived,dataLength-totalReceived);
		if (nb<1)
			break;
		totalReceived+=nb;
		if (extApi_getTimeDiffInMs(startT)>3000)
			break;
	}
	if (totalReceived!=dataLength)
		return(-1);
	return(packetsLeft);
}

SIMX_THREAD_RET_TYPE _communicationThread(simxVoid* p)
{
	simxChar* replyData;
	simxChar* tempBuffer;
	simxChar* cmdPointer;
	simxInt tempBufferDataSize;
	simxInt tempBufferBufferSize;
	simxInt replyDataSize;
	simxInt tmp,off,cmd,i,memSize,fullMemSize,memSize2;
	simxUShort crc,pureDataOffset0;
	simxInt pureDataOffset1,maxPureDataSize,pureDataSize;
	simxInt lastTime,waitBeforeSendingAgainWhenMessageIDArrived_copy;
	while (_communicationThreadRunning!=0)
	{ /* only the main thread can have this thread end! */
//		printf("Trying to connect...\n");
		if (extApi_connectToServer_socket(_tempConnectionAddress,_tempConnectionPort)==1)
		{
			_connectionID=_nextConnectionID++;
//			printf("Connected!\n");
			lastTime=extApi_getTimeInMs();
			while (_communicationThreadRunning!=0)
			{
				/* 1. Check if we should wait until the input buffer got read */
				extApi_lockResources();
				waitBeforeSendingAgainWhenMessageIDArrived_copy=_waitBeforeSendingAgainWhenMessageIDArrived;
				extApi_unlockResources();
				if ((waitBeforeSendingAgainWhenMessageIDArrived_copy!=-1)&&(_messageReceived_dataSize>=SIMX_HEADER_SIZE))
				{
					while (1)
					{
						extApi_lockResources();
						waitBeforeSendingAgainWhenMessageIDArrived_copy=_waitBeforeSendingAgainWhenMessageIDArrived;
						extApi_unlockResources();
						if ((_lastReceivedMessageID<_waitBeforeSendingAgainWhenMessageIDArrived)||(waitBeforeSendingAgainWhenMessageIDArrived_copy==-1))
							break;
						extApi_switchThread();
					}
				}

				/* 2. Make sure we don't send too many requests */
				while (extApi_getTimeDiffInMs(lastTime)<_MIN_COMMUNICATION_DELAY_IN_MS)
					extApi_switchThread();
				lastTime=extApi_getTimeInMs();

				extApi_lockSendStart(); /* if we need to guarantee that several specific commands are sent at the same time, this might be locked already! */
				/* 3. Send a request */
				extApi_lockResources();
				extApi_unlockSendStart();

				/* Take care of non-split commands first */
				tempBuffer=extApi_allocateBuffer(_messageToSend_dataSize);
				for (i=0;i<_messageToSend_dataSize;i++)
					tempBuffer[i]=_messageToSend[i];
				tempBufferDataSize=_messageToSend_dataSize;
				tempBufferBufferSize=tempBufferDataSize;
				_messageToSend_dataSize=SIMX_HEADER_SIZE; /* remove all non-split commands */

				/* Take care of split commands here */
				off=0;
				while (off<_splitCommandsToSend_dataSize)
				{
					memSize=extApi_endianConversionInt(((simxInt*)(_splitCommandsToSend+off+simx_cmdheaderoffset_mem_size))[0]);
					pureDataOffset0=extApi_endianConversionUShort(((simxUShort*)(_splitCommandsToSend+off+simx_cmdheaderoffset_pdata_offset0))[0]);
					pureDataOffset1=extApi_endianConversionInt(((simxInt*)(_splitCommandsToSend+off+simx_cmdheaderoffset_pdata_offset1))[0]);
					maxPureDataSize=extApi_endianConversionUShort(((simxUShort*)(_splitCommandsToSend+off+simx_cmdheaderoffset_delay_or_split))[0]);
					pureDataSize=memSize-SIMX_SUBHEADER_SIZE-pureDataOffset0-pureDataOffset1;
					if (pureDataSize>maxPureDataSize)
						pureDataSize=maxPureDataSize;
					tempBuffer=_appendChunkToBuffer(_splitCommandsToSend+off,SIMX_SUBHEADER_SIZE+pureDataOffset0,tempBuffer,&tempBufferBufferSize,&tempBufferDataSize);
					tempBuffer=_appendChunkToBuffer(_splitCommandsToSend+off+SIMX_SUBHEADER_SIZE+pureDataOffset0+pureDataOffset1,pureDataSize,tempBuffer,&tempBufferBufferSize,&tempBufferDataSize);
					((simxInt*)(tempBuffer+tempBufferDataSize-pureDataSize-pureDataOffset0-SIMX_SUBHEADER_SIZE+simx_cmdheaderoffset_mem_size))[0]=extApi_endianConversionInt(SIMX_SUBHEADER_SIZE+pureDataOffset0+pureDataSize);
					if (SIMX_SUBHEADER_SIZE+pureDataOffset0+pureDataOffset1+pureDataSize>=memSize)
					{ /* command completely sent, we can remove it */
						_removeChunkFromBuffer(_splitCommandsToSend,_splitCommandsToSend+off,memSize,&_splitCommandsToSend_dataSize);
					}
					else
					{ /* command not yet completely sent. Keep it, but adjust the pure data offset1 */
						pureDataOffset1+=pureDataSize;
						((simxInt*)(_splitCommandsToSend+off+simx_cmdheaderoffset_pdata_offset1))[0]=extApi_endianConversionInt(pureDataOffset1);
						off+=memSize;
					}
				}

				/* Set some message header values */
				tempBuffer[simx_headeroffset_version]=SIMX_VERSION;
				((simxInt*)(tempBuffer+simx_headeroffset_message_id))[0]=extApi_endianConversionInt(_nextMessageIDToSend++);
				((simxInt*)(tempBuffer+simx_headeroffset_client_time))[0]=extApi_endianConversionInt(extApi_getTimeInMs());
				((simxUShort*)(tempBuffer+simx_headeroffset_crc))[0]=extApi_endianConversionUShort(_getCRC(tempBuffer+2,tempBufferDataSize-2));

				/* Send the message */
				if (_sendMessage_socket(tempBuffer,tempBufferDataSize)!=1)
				{
					extApi_releaseBuffer(tempBuffer);
					extApi_unlockResources();
					break;
				}
				extApi_releaseBuffer(tempBuffer);
				extApi_unlockResources();

				/* 4. Read the reply (the server always replies!) */
				replyData=_receiveReplyMessage_socket(&replyDataSize);
				if (replyData==0)
					break;

				/* Check the CRC */
				crc=extApi_endianConversionUShort(((simxUShort*)(replyData+simx_headeroffset_crc))[0]);
				if (_getCRC(replyData+2,replyDataSize-2)==crc)
				{
					/* Place the reply into the input buffer */
					tmp=extApi_endianConversionInt(((simxInt*)(replyData+simx_headeroffset_message_id))[0]);

					if (replyDataSize>SIMX_HEADER_SIZE)
					{ /* We received a non-empty message */
						extApi_lockResources();
						/* a) Create a new buffer that will hold the merged input data */
						tempBuffer=extApi_allocateBuffer(_messageReceived_bufferSize);
						tempBufferBufferSize=_messageReceived_bufferSize;
						/* b) Copy the header from the received data, or from the existing input buffer (if id is -1) */
						if (tmp==-1)
						{
							for (i=0;i<SIMX_HEADER_SIZE;i++)
								tempBuffer[i]=_messageReceived[i];
						}
						else
						{
							for (i=0;i<SIMX_HEADER_SIZE;i++)
								tempBuffer[i]=replyData[i];
						}
						tempBufferDataSize=SIMX_HEADER_SIZE;

						/* c) go through the received data and add it (either to the temp buffer, either to the partial command buffer) */
						off=SIMX_HEADER_SIZE;
						while (off<replyDataSize)
						{
							memSize=extApi_endianConversionInt(((simxInt*)(replyData+off+simx_cmdheaderoffset_mem_size))[0]);
							fullMemSize=extApi_endianConversionInt(((simxInt*)(replyData+off+simx_cmdheaderoffset_full_mem_size))[0]);
							if (memSize==fullMemSize)
							{ /* the full data was sent at once! */
								cmd=extApi_endianConversionInt(((simxInt*)(replyData+off+simx_cmdheaderoffset_cmd))[0]);
								if ((cmd-(cmd&simx_cmdmask))!=simx_opmode_discontinue) /* only discontinue mode commands are not added */
									tempBuffer=_appendChunkToBuffer(replyData+off,extApi_endianConversionInt(((simxInt*)(replyData+off+simx_cmdheaderoffset_mem_size))[0]),tempBuffer,&tempBufferBufferSize,&tempBufferDataSize);
								cmdPointer=_getSameCommandPointer(replyData+off,_messageReceived+SIMX_HEADER_SIZE,_messageReceived_dataSize-SIMX_HEADER_SIZE);
								if (cmdPointer!=0)
								{ /* unmark this command (we already added its newer version) */
									((simxInt*)(cmdPointer+simx_cmdheaderoffset_cmd))[0]=0;
								}
							}
							else
							{ /* only partial data was sent */
								
								/* Try to merge the partial data with same data already present in the partial commands buffer */
								cmdPointer=_getSameCommandPointer(replyData+off,_splitCommandsReceived,_splitCommandsReceived_dataSize);
								if (cmdPointer!=0)
								{ /* there is previous partial data. Is it valid? */
									memSize2=extApi_endianConversionInt(((simxInt*)(cmdPointer+simx_cmdheaderoffset_mem_size))[0]);						
									if (memSize2!=fullMemSize)
									{ /* we cannot use the previous version, since it has a different size. Remove it */
										_removeChunkFromBuffer(_splitCommandsReceived,cmdPointer,memSize2,&_splitCommandsReceived_dataSize);
										cmdPointer=0;
									}
								}
								if (cmdPointer==0)
								{ /* there is not yet similar data present. Just add empty space */
									_splitCommandsReceived=_appendChunkToBuffer(0,fullMemSize,_splitCommandsReceived,&_splitCommandsReceived_bufferSize,&_splitCommandsReceived_dataSize);
									cmdPointer=_splitCommandsReceived+_splitCommandsReceived_dataSize-fullMemSize;
								}
								/* Now we have to overwrite the subheader, the command data, and the partial data */
								for (i=0;i<SIMX_SUBHEADER_SIZE;i++)
									cmdPointer[i]=replyData[off+i];
								((simxInt*)(cmdPointer+simx_cmdheaderoffset_mem_size))[0]=extApi_endianConversionInt(fullMemSize); /* Important!! */

								pureDataOffset0=extApi_endianConversionUShort(((simxUShort*)(cmdPointer+simx_cmdheaderoffset_pdata_offset0))[0]);
								for (i=0;i<pureDataOffset0;i++)
									cmdPointer[SIMX_SUBHEADER_SIZE+i]=replyData[off+SIMX_SUBHEADER_SIZE+i];

								pureDataOffset1=extApi_endianConversionInt(((simxInt*)(cmdPointer+simx_cmdheaderoffset_pdata_offset1))[0]);
								pureDataSize=memSize-SIMX_SUBHEADER_SIZE-pureDataOffset0;
								for (i=0;i<pureDataSize;i++)
									cmdPointer[SIMX_SUBHEADER_SIZE+pureDataOffset0+pureDataOffset1+i]=replyData[off+SIMX_SUBHEADER_SIZE+pureDataOffset0+i];

								/* Is the partial data complete yet? */
								if (SIMX_SUBHEADER_SIZE+pureDataOffset0+pureDataOffset1+pureDataSize>=fullMemSize)
								{ /* yes!! Copy the data from the partial command buffer to the tempBuffer, and erase it from the partial command buffer */
									tempBuffer=_appendChunkToBuffer(cmdPointer,fullMemSize,tempBuffer,&tempBufferBufferSize,&tempBufferDataSize);
									_removeChunkFromBuffer(_splitCommandsReceived,cmdPointer,fullMemSize,&_splitCommandsReceived_dataSize);
									/* make sure we unmark any similar command in the _messageReceived buffer */
									cmdPointer=_getSameCommandPointer(tempBuffer+tempBufferDataSize-fullMemSize,_messageReceived+SIMX_HEADER_SIZE,_messageReceived_dataSize-SIMX_HEADER_SIZE);
									if (cmdPointer!=0)
									{ /* unmark this command (we already added its newer version) */
										((simxInt*)(cmdPointer+simx_cmdheaderoffset_cmd))[0]=0;
									}
								}
							}
							off+=extApi_endianConversionInt(((simxInt*)(replyData+off+simx_cmdheaderoffset_mem_size))[0]);
						}
						/* d) go through the old received data, and add only commands that were not unmarked */
						off=SIMX_HEADER_SIZE;
						while (off<_messageReceived_dataSize)
						{
							cmd=extApi_endianConversionInt(((simxInt*)(_messageReceived+off+simx_cmdheaderoffset_cmd))[0]);
							if (cmd!=0)
							{ /* ok, this command was not unmarked. We add it */
								tempBuffer=_appendChunkToBuffer(_messageReceived+off,extApi_endianConversionInt(((simxInt*)(_messageReceived+off+simx_cmdheaderoffset_mem_size))[0]),tempBuffer,&tempBufferBufferSize,&tempBufferDataSize);
							}
							off+=extApi_endianConversionInt(((simxInt*)(_messageReceived+off+simx_cmdheaderoffset_mem_size))[0]);
						}
						/* e) switch buffers and release 2 of them */
						extApi_releaseBuffer(replyData);
						extApi_releaseBuffer(_messageReceived);
						_messageReceived=tempBuffer;
						_messageReceived_bufferSize=tempBufferBufferSize;
						_messageReceived_dataSize=tempBufferDataSize;
						if (tmp!=-1)
							_lastReceivedMessageID=tmp;
						extApi_unlockResources();
					}
					else
						extApi_releaseBuffer(replyData);
				}
				else
					extApi_releaseBuffer(replyData);

			}
			extApi_lockResources();
			_messageToSend_dataSize=SIMX_HEADER_SIZE;
			_splitCommandsToSend_dataSize=0;
			_messageReceived_dataSize=0;
			_splitCommandsReceived_dataSize=0;
			extApi_unlockResources();
//			printf("Disconnected\n");
			_connectionID=-1;
			extApi_cleanUp_socket();
		}
		else
			extApi_sleepMs(100);
		if (_tempDoNotReconnectOnceDisconnected)
		{ /* sit here until the other thread sets _communicationThreadRunning to 0 */
			while (_communicationThreadRunning!=0)
				extApi_sleepMs(100);
			break;
		}
	}
	_communicationThreadRunning=1; /* to indicate to the main thread that we just left */
	SIMX_THREAD_RET_LINE;
}

simxUShort _getCRC(const simxChar* data,simxInt length)
{
	simxUShort crc=0;
	simxInt i,j;
	simxInt p=0;
	for (i=0;i<length;i++)
	{
		crc=crc^(((simxUShort)data[p])<<8);
		for (j=0;j<8;j++)
		{
			if (crc&((simxUShort)0x8000))
				crc=(crc<<1)^((simxUShort)0x1021);
			else
				crc<<=1;
		}
		p++;
	}
	return(crc);
}

simxInt _removeCommandReply_null(simxInt cmdRaw)
{
	simxChar* cmdPtr;
	simxInt retVal=simx_error_noerror;
	extApi_lockResources();
	cmdPtr=_getCommandPointer_(cmdRaw,_messageReceived+SIMX_HEADER_SIZE,_messageReceived_dataSize-SIMX_HEADER_SIZE);
	if (cmdPtr!=0)
		_removeChunkFromBuffer(_messageReceived,cmdPtr,extApi_endianConversionInt(((simxInt*)(cmdPtr+simx_cmdheaderoffset_mem_size))[0]),&_messageReceived_dataSize);
	else
		retVal=simx_error_novalue_flag;
	// Data is removed, but buffer keeps same size. It will be resized next time we receive something
	extApi_unlockResources();
	return(retVal);
}

simxInt _removeCommandReply_int(simxInt cmdRaw,simxInt intValue)
{
	simxChar* cmdPtr;
	simxInt retVal=simx_error_noerror;
	extApi_lockResources();
	cmdPtr=_getCommandPointer_i(cmdRaw,intValue,_messageReceived+SIMX_HEADER_SIZE,_messageReceived_dataSize-SIMX_HEADER_SIZE);
	if (cmdPtr!=0)
		_removeChunkFromBuffer(_messageReceived,cmdPtr,extApi_endianConversionInt(((simxInt*)(cmdPtr+simx_cmdheaderoffset_mem_size))[0]),&_messageReceived_dataSize);
	else
		retVal=simx_error_novalue_flag;
	// Data is removed, but buffer keeps same size. It will be resized next time we receive something
	extApi_unlockResources();
	return(retVal);
}

simxInt _removeCommandReply_intint(simxInt cmdRaw,simxInt intValue1,simxInt intValue2)
{
	simxChar* cmdPtr;
	simxInt retVal=simx_error_noerror;
	extApi_lockResources();
	cmdPtr=_getCommandPointer_ii(cmdRaw,intValue1,intValue2,_messageReceived+SIMX_HEADER_SIZE,_messageReceived_dataSize-SIMX_HEADER_SIZE);
	if (cmdPtr!=0)
		_removeChunkFromBuffer(_messageReceived,cmdPtr,extApi_endianConversionInt(((simxInt*)(cmdPtr+simx_cmdheaderoffset_mem_size))[0]),&_messageReceived_dataSize);
	else
		retVal=simx_error_novalue_flag;
	// Data is removed, but buffer keeps same size. It will be resized next time we receive something
	extApi_unlockResources();
	return(retVal);
}

simxInt _removeCommandReply_string(simxInt cmdRaw,const char* stringValue)
{
	simxChar* cmdPtr;
	simxInt retVal=simx_error_noerror;
	extApi_lockResources();
	cmdPtr=_getCommandPointer_s(cmdRaw,stringValue,_messageReceived+SIMX_HEADER_SIZE,_messageReceived_dataSize-SIMX_HEADER_SIZE);
	if (cmdPtr!=0)
		_removeChunkFromBuffer(_messageReceived,cmdPtr,extApi_endianConversionInt(((simxInt*)(cmdPtr+simx_cmdheaderoffset_mem_size))[0]),&_messageReceived_dataSize);
	else
		retVal=simx_error_novalue_flag;
	// Data is removed, but buffer keeps same size. It will be resized next time we receive something
	extApi_unlockResources();
	return(retVal);
}


/*
**********************************************
Following are the remote API helper functions
**********************************************
*/

EXTAPI_DLLEXPORT simxInt simxGetConnectionId()
{
	if (_communicationThreadRunning==0)
		return(-1);
	return(_connectionID);
}

EXTAPI_DLLEXPORT simxInt simxGetPingTime(simxInt* pingTime)
{
	simxInt res,dummyVal;
	simxInt startTime=extApi_getTimeInMs();
	if (_communicationThreadRunning==0)
		return(0);
	res=simxGetIntegerParameter(sim_intparam_program_version,&dummyVal,simx_opmode_oneshot_wait); /* just a dummy command */
	res=(res|simx_error_remote_error_flag)-simx_error_remote_error_flag;
	pingTime[0]=extApi_getTimeDiffInMs(startTime);
	return(res);
}

EXTAPI_DLLEXPORT simxInt simxSynchronousTrigger()
{
	simxInt returnValue;
	if (_communicationThreadRunning==0)
		return(simx_error_initialize_error_flag);
	_exec_null(simx_cmd_synchronous_next,simx_opmode_oneshot_wait,0,&returnValue);
	return(returnValue);
}

EXTAPI_DLLEXPORT simxInt simxSynchronous(simxChar enable)
{
	simxInt returnValue;
	simxInt cmd=simx_cmd_synchronous_disable;
	if (_communicationThreadRunning==0)
		return(simx_error_initialize_error_flag);
	if (enable)
		cmd=simx_cmd_synchronous_enable;
	_exec_null(cmd,simx_opmode_oneshot_wait,0,&returnValue);
	return(returnValue);
}

EXTAPI_DLLEXPORT simxInt simxPauseCommunication(simxChar pause)
{
	if (_communicationThreadRunning==0)
		return(simx_error_initialize_error_flag);
	if (pause)
		extApi_lockSendStart();
	else
		extApi_unlockSendStart();
	return(0);
}

EXTAPI_DLLEXPORT simxInt simxGetLastCmdTime()
{
	return(_commandReceived_simulationTime);
}

EXTAPI_DLLEXPORT simxInt simxGetInMessageInfo(simxInt infoType,simxInt* info)
{
	simxInt retVal=-1;
	if (_communicationThreadRunning==0)
		return(-1);
	extApi_lockResources();
	if (_messageReceived_dataSize>=SIMX_HEADER_SIZE)
	{
		if ( (infoType==simx_headeroffset_message_id)||(infoType==simx_headeroffset_client_time)||(infoType==simx_headeroffset_server_time) )
		{
			info[0]=extApi_endianConversionInt(((simxInt*)(_messageReceived+infoType))[0]);
			retVal=1;
		}
		if (infoType==simx_headeroffset_scene_id)
		{
			info[0]=extApi_endianConversionUShort(((simxUShort*)(_messageReceived+infoType))[0]);
			retVal=1;
		}
		if ((infoType==simx_headeroffset_version)||(infoType==simx_headeroffset_server_state))
		{
			info[0]=(simxInt)((simxChar*)(_messageReceived+infoType))[0];
			retVal=1;
		}
	}
	extApi_unlockResources();
	return(retVal);
}

EXTAPI_DLLEXPORT simxInt simxGetOutMessageInfo(simxInt infoType,simxInt* info)
{
	simxInt retVal=-1;
	if (_communicationThreadRunning==0)
		return(-1);
	extApi_lockResources();
	if (infoType==simx_headeroffset_message_id)
	{
		info[0]=_nextMessageIDToSend;
		retVal=1;
	}
	if (infoType==simx_headeroffset_client_time)
	{
		info[0]=extApi_getTimeInMs();
		retVal=1;
	}
	if (infoType==simx_headeroffset_version)
	{
		info[0]=SIMX_VERSION;
		retVal=1;
	}
	extApi_unlockResources();
	return(retVal);
}

EXTAPI_DLLEXPORT simxChar* simxCreateBuffer(simxInt bufferSize)
{
	return(extApi_allocateBuffer(bufferSize));
}

EXTAPI_DLLEXPORT simxVoid simxReleaseBuffer(simxChar* buffer)
{
	extApi_releaseBuffer(buffer);
}

/*
**********************************************
Following are the remote API functions
**********************************************
*/

EXTAPI_DLLEXPORT simxInt simxGetJointPosition(simxInt jointHandle,simxFloat* position,simxInt operationMode)
{
	simxChar* dataPointer;
	simxInt returnValue;
	if (_communicationThreadRunning==0)
		return(simx_error_initialize_error_flag);
	if (operationMode==simx_opmode_remove)
		return(_removeCommandReply_int(simx_cmd_get_joint_position,jointHandle));
	dataPointer=_exec_int(simx_cmd_get_joint_position,operationMode,0,jointHandle,&returnValue);
	if ((dataPointer!=0)&&(returnValue==0))
		position[0]=_readPureDataFloat(dataPointer,0,0);
	return(returnValue);
}

EXTAPI_DLLEXPORT simxInt simxSetJointPosition(simxInt jointHandle,simxFloat position,simxInt operationMode)
{
	simxInt returnValue;
	if (_communicationThreadRunning==0)
		return(simx_error_initialize_error_flag);
	if (operationMode==simx_opmode_remove)
		return(_removeCommandReply_int(simx_cmd_set_joint_position,jointHandle));
	_exec_int_float(simx_cmd_set_joint_position,operationMode,0,jointHandle,position,&returnValue);
	return(returnValue);
}

EXTAPI_DLLEXPORT simxInt simxGetJointMatrix(simxInt jointHandle,simxFloat* matrix,simxInt operationMode)
{
	simxChar* dataPointer;
	simxInt returnValue,i;
	if (_communicationThreadRunning==0)
		return(simx_error_initialize_error_flag);
	if (operationMode==simx_opmode_remove)
		return(_removeCommandReply_int(simx_cmd_get_joint_matrix,jointHandle));
	dataPointer=_exec_int(simx_cmd_get_joint_matrix,operationMode,0,jointHandle,&returnValue);
	if ((dataPointer!=0)&&(returnValue==0))
	{
		for (i=0;i<12;i++)
			matrix[i]=_readPureDataFloat(dataPointer,0,4*i);
	}
	return(returnValue);
}

EXTAPI_DLLEXPORT simxInt simxSetSphericalJointMatrix(simxInt jointHandle,simxFloat* matrix,simxInt operationMode)
{
	simxInt returnValue;
	if (_communicationThreadRunning==0)
		return(simx_error_initialize_error_flag);
	if (operationMode==simx_opmode_remove)
		return(_removeCommandReply_int(simx_cmd_set_spherical_joint_matrix,jointHandle));
	_exec_int_buffer(simx_cmd_set_spherical_joint_matrix,operationMode,0,jointHandle,(simxChar*)matrix,4*12,&returnValue);
	return(returnValue);
}

EXTAPI_DLLEXPORT simxInt simxSetJointTargetVelocity(simxInt jointHandle,simxFloat targetVelocity,simxInt operationMode)
{
	simxInt returnValue;
	if (_communicationThreadRunning==0)
		return(simx_error_initialize_error_flag);
	if (operationMode==simx_opmode_remove)
		return(_removeCommandReply_int(simx_cmd_set_joint_target_velocity,jointHandle));
	_exec_int_float(simx_cmd_set_joint_target_velocity,operationMode,0,jointHandle,targetVelocity,&returnValue);
	return(returnValue);
}

EXTAPI_DLLEXPORT simxInt simxSetJointTargetPosition(simxInt jointHandle,simxFloat targetPosition,simxInt operationMode)
{
	simxInt returnValue;
	if (_communicationThreadRunning==0)
		return(simx_error_initialize_error_flag);
	if (operationMode==simx_opmode_remove)
		return(_removeCommandReply_int(simx_cmd_set_joint_target_position,jointHandle));
	_exec_int_float(simx_cmd_set_joint_target_position,operationMode,0,jointHandle,targetPosition,&returnValue);
	return(returnValue);
}

EXTAPI_DLLEXPORT simxInt simxReadProximitySensor(simxInt sensorHandle,simxChar* detectionState,simxFloat* detectedPoint,simxInt* detectedObjectHandle,simxFloat* detectedSurfaceNormalVector,simxInt operationMode)
{
	simxChar* dataPointer;
	simxInt returnValue;
	if (_communicationThreadRunning==0)
		return(simx_error_initialize_error_flag);
	if (operationMode==simx_opmode_remove)
		return(_removeCommandReply_int(simx_cmd_read_proximity_sensor,sensorHandle));
	dataPointer=_exec_int(simx_cmd_read_proximity_sensor,operationMode,0,sensorHandle,&returnValue);
	if ((dataPointer!=0)&&(returnValue==0))
	{
		if (detectionState!=0)
			detectionState[0]=_readPureDataChar(dataPointer,0,0);
		if (detectedPoint!=0)
		{
			detectedPoint[0]=_readPureDataFloat(dataPointer,0,1);
			detectedPoint[1]=_readPureDataFloat(dataPointer,0,5);
			detectedPoint[2]=_readPureDataFloat(dataPointer,0,9);
		}
		if (detectedObjectHandle!=0)
			detectedObjectHandle[0]=_readPureDataInt(dataPointer,0,13);
		if (detectedSurfaceNormalVector!=0)
		{
			detectedSurfaceNormalVector[0]=_readPureDataFloat(dataPointer,0,17);
			detectedSurfaceNormalVector[1]=_readPureDataFloat(dataPointer,0,21);
			detectedSurfaceNormalVector[2]=_readPureDataFloat(dataPointer,0,25);
		}
	}
	return(returnValue);
}

EXTAPI_DLLEXPORT simxInt simxStartSimulation(simxInt operationMode)
{
	simxInt returnValue;
	if (_communicationThreadRunning==0)
		return(simx_error_initialize_error_flag);
	if (operationMode==simx_opmode_remove)
		return(_removeCommandReply_int(simx_cmd_start_pause_stop_simulation,0));
	_exec_int(simx_cmd_start_pause_stop_simulation,operationMode,0,0,&returnValue);
	return(returnValue);
}

EXTAPI_DLLEXPORT simxInt simxPauseSimulation(simxInt operationMode)
{
	simxInt returnValue;
	if (_communicationThreadRunning==0)
		return(simx_error_initialize_error_flag);
	if (operationMode==simx_opmode_remove)
		return(_removeCommandReply_int(simx_cmd_start_pause_stop_simulation,1));
	_exec_int(simx_cmd_start_pause_stop_simulation,operationMode,0,1,&returnValue);
	return(returnValue);
}

EXTAPI_DLLEXPORT simxInt simxStopSimulation(simxInt operationMode)
{
	simxInt returnValue;
	if (_communicationThreadRunning==0)
		return(simx_error_initialize_error_flag);
	if (operationMode==simx_opmode_remove)
		return(_removeCommandReply_int(simx_cmd_start_pause_stop_simulation,2));
	_exec_int(simx_cmd_start_pause_stop_simulation,operationMode,0,2,&returnValue);
	return(returnValue);
}

EXTAPI_DLLEXPORT simxInt simxGetObjectHandle(const simxChar* objectName,simxInt* handle,simxInt operationMode)
{
	simxChar* dataPointer;
	simxInt returnValue;
	if (_communicationThreadRunning==0)
		return(simx_error_initialize_error_flag);
	if (operationMode==simx_opmode_remove)
		return(_removeCommandReply_string(simx_cmd_get_object_handle,objectName));
	dataPointer=_exec_string(simx_cmd_get_object_handle,operationMode,0,objectName,&returnValue);
	if ((dataPointer!=0)&&(returnValue==0))
		handle[0]=_readPureDataInt(dataPointer,0,0);
	return(returnValue);
}

EXTAPI_DLLEXPORT simxInt simxGetUIHandle(const simxChar* uiName,simxInt* handle,simxInt operationMode)
{
	simxChar* dataPointer;
	simxInt returnValue;
	if (_communicationThreadRunning==0)
		return(simx_error_initialize_error_flag);
	if (operationMode==simx_opmode_remove)
		return(_removeCommandReply_string(simx_cmd_get_ui_handle,uiName));
	dataPointer=_exec_string(simx_cmd_get_ui_handle,operationMode,0,uiName,&returnValue);
	if ((dataPointer!=0)&&(returnValue==0))
		handle[0]=_readPureDataInt(dataPointer,0,0);
	return(returnValue);
}

EXTAPI_DLLEXPORT simxInt simxGetVisionSensorImage(simxInt sensorHandle,simxInt* resolution,simxChar** image,simxChar options,simxInt operationMode)
{
	simxChar* dataPointer;
	simxInt returnValue;
	simxInt cmd;
	if (options&1)
		cmd=simx_cmd_get_vision_sensor_image_bw;
	else
		cmd=simx_cmd_get_vision_sensor_image_rgb;
	if (_communicationThreadRunning==0)
		return(simx_error_initialize_error_flag);
	if (operationMode==simx_opmode_remove)
		return(_removeCommandReply_int(cmd,sensorHandle));
	dataPointer=_exec_int(cmd,operationMode,0,sensorHandle,&returnValue);
	if ((dataPointer!=0)&&(returnValue==0))
	{
		resolution[0]=_readPureDataInt(dataPointer,0,0);
		resolution[1]=_readPureDataInt(dataPointer,0,4);
		image[0]=dataPointer+SIMX_SUBHEADER_SIZE+8+_getCmdDataSize(dataPointer);
	}
	return(returnValue);
}

EXTAPI_DLLEXPORT simxInt simxSetVisionSensorImage(simxInt sensorHandle,simxChar* image,simxInt bufferSize,simxChar options,simxInt operationMode)
{
	simxInt returnValue;
	simxInt cmd;
	if (options&1)
		cmd=simx_cmd_set_vision_sensor_image_bw;
	else
		cmd=simx_cmd_set_vision_sensor_image_rgb;
	if (_communicationThreadRunning==0)
		return(simx_error_initialize_error_flag);
	if (operationMode==simx_opmode_remove)
		return(_removeCommandReply_int(cmd,sensorHandle));
	_exec_int_buffer(cmd,operationMode,0,sensorHandle,image,bufferSize,&returnValue);
	return(returnValue);
}

EXTAPI_DLLEXPORT simxInt simxGetVisionSensorDepthBuffer(simxInt sensorHandle,simxInt* resolution,simxFloat** buffer,simxInt operationMode)
{
	simxChar* dataPointer;
	simxInt returnValue;
#ifdef ENDIAN_TEST
	simxInt i;
#endif
	if (_communicationThreadRunning==0)
		return(simx_error_initialize_error_flag);
	if (operationMode==simx_opmode_remove)
		return(_removeCommandReply_int(simx_cmd_get_vision_sensor_depth_buffer,sensorHandle));
	dataPointer=_exec_int(simx_cmd_get_vision_sensor_depth_buffer,operationMode,0,sensorHandle,&returnValue);
	if ((dataPointer!=0)&&(returnValue==0))
	{
		resolution[0]=_readPureDataInt(dataPointer,0,0);
		resolution[1]=_readPureDataInt(dataPointer,0,4);
		buffer[0]=(simxFloat*)(dataPointer+SIMX_SUBHEADER_SIZE+8+_getCmdDataSize(dataPointer));
#ifdef ENDIAN_TEST
		for (i=0;i<resolution[0]*resolution[1];i++)
			((simxFloat*)(buffer[0]))[i]=extApi_endianConversionFloat(((simxFloat*)(buffer[0]))[i]);
#endif
	}
	return(returnValue);
}

EXTAPI_DLLEXPORT simxInt simxJointGetForce(simxInt jointHandle,simxFloat* force,simxInt operationMode)
{
	simxChar* dataPointer;
	simxInt returnValue;
	if (_communicationThreadRunning==0)
		return(simx_error_initialize_error_flag);
	if (operationMode==simx_opmode_remove)
		return(_removeCommandReply_int(simx_cmd_get_joint_force,jointHandle));
	dataPointer=_exec_int(simx_cmd_get_joint_force,operationMode,0,jointHandle,&returnValue);
	if ((dataPointer!=0)&&(returnValue==0))
		force[0]=_readPureDataFloat(dataPointer,0,0);
	return(returnValue);
}

EXTAPI_DLLEXPORT simxInt simxSetJointForce(simxInt jointHandle,simxFloat force,simxInt operationMode)
{
	simxInt returnValue;
	if (_communicationThreadRunning==0)
		return(simx_error_initialize_error_flag);
	if (operationMode==simx_opmode_remove)
		return(_removeCommandReply_int(simx_cmd_set_joint_force,jointHandle));
	_exec_int_float(simx_cmd_set_joint_force,operationMode,0,jointHandle,force,&returnValue);
	return(returnValue);
}

EXTAPI_DLLEXPORT simxInt simxReadForceSensor(simxInt forceSensorHandle,simxChar* state,simxFloat* forceVector,simxFloat* torqueVector,simxInt operationMode)
{
	simxChar* dataPointer;
	simxInt returnValue,i;
	if (_communicationThreadRunning==0)
		return(simx_error_initialize_error_flag);
	if (operationMode==simx_opmode_remove)
		return(_removeCommandReply_int(simx_cmd_read_force_sensor,forceSensorHandle));
	dataPointer=_exec_int(simx_cmd_read_force_sensor,operationMode,0,forceSensorHandle,&returnValue);
	if ((dataPointer!=0)&&(returnValue==0))
	{
		if (state!=0)
			state[0]=_readPureDataChar(dataPointer,0,0);
		if (forceVector!=0)
		{
			for (i=0;i<3;i++)
				forceVector[i]=_readPureDataFloat(dataPointer,0,1+4*i);
		}
		if (torqueVector!=0)
		{
			for (i=0;i<3;i++)
				torqueVector[i]=_readPureDataFloat(dataPointer,0,1+12+4*i);
		}
	}
	return(returnValue);
}

EXTAPI_DLLEXPORT simxInt simxBreakForceSensor(simxInt forceSensorHandle,simxInt operationMode)
{
	simxInt returnValue;
	if (_communicationThreadRunning==0)
		return(simx_error_initialize_error_flag);
	if (operationMode==simx_opmode_remove)
		return(_removeCommandReply_int(simx_cmd_break_force_sensor,forceSensorHandle));
	_exec_int(simx_cmd_break_force_sensor,operationMode,0,forceSensorHandle,&returnValue);
	return(returnValue);
}

EXTAPI_DLLEXPORT simxInt simxReadVisionSensor(simxInt sensorHandle,simxChar* detectionState,simxFloat** auxValues,simxInt** auxValuesCount,simxInt operationMode)
{
	simxChar* dataPointer;
	simxInt returnValue,i,packetCnt,auxValCnt;
	if (_communicationThreadRunning==0)
		return(simx_error_initialize_error_flag);
	if (operationMode==simx_opmode_remove)
		return(_removeCommandReply_int(simx_cmd_read_vision_sensor,sensorHandle));
	dataPointer=_exec_int(simx_cmd_read_vision_sensor,operationMode,0,sensorHandle,&returnValue);
	if ((dataPointer!=0)&&(returnValue==0))
	{
		if (detectionState!=0)
			detectionState[0]=_readPureDataChar(dataPointer,0,0);
		if ((auxValues!=0)&&(auxValuesCount!=0))
		{
			packetCnt=_readPureDataInt(dataPointer,0,1);
			auxValuesCount[0]=(simxInt*)extApi_allocateBuffer(4*(1+packetCnt));
			auxValuesCount[0][0]=packetCnt;
			auxValCnt=0;
			for (i=0;i<packetCnt;i++)
			{
				auxValuesCount[0][1+i]=_readPureDataInt(dataPointer,0,1+4*(1+i));
				auxValCnt=auxValCnt+auxValuesCount[0][1+i];
			}
			auxValues[0]=(simxFloat*)extApi_allocateBuffer(4*auxValCnt);
			for (i=0;i<auxValCnt;i++)
				auxValues[0][i]=_readPureDataFloat(dataPointer,0,1+4*(1+packetCnt+i));
		}
	}
	return(returnValue);
}

EXTAPI_DLLEXPORT simxInt simxGetObjectParent(simxInt childObjectHandle,simxInt* parentObjectHandle,simxInt operationMode)
{
	simxChar* dataPointer;
	simxInt returnValue;
	if (_communicationThreadRunning==0)
		return(simx_error_initialize_error_flag);
	if (operationMode==simx_opmode_remove)
		return(_removeCommandReply_int(simx_cmd_get_object_parent,childObjectHandle));
	dataPointer=_exec_int(simx_cmd_get_object_parent,operationMode,0,childObjectHandle,&returnValue);
	if ((dataPointer!=0)&&(returnValue==0))
		parentObjectHandle[0]=_readPureDataInt(dataPointer,0,0);
	return(returnValue);
}

EXTAPI_DLLEXPORT simxInt simxGetObjectChild(simxInt parentObjectHandle,simxInt childIndex,simxInt* childObjectHandle,simxInt operationMode)
{
	simxChar* dataPointer;
	simxInt returnValue;
	if (_communicationThreadRunning==0)
		return(simx_error_initialize_error_flag);
	if (operationMode==simx_opmode_remove)
		return(_removeCommandReply_intint(simx_cmd_get_object_child,parentObjectHandle,childIndex));
	dataPointer=_exec_intint(simx_cmd_get_object_child,operationMode,0,parentObjectHandle,childIndex,&returnValue);
	if ((dataPointer!=0)&&(returnValue==0))
		childObjectHandle[0]=_readPureDataInt(dataPointer,0,0);
	return(returnValue);
}

EXTAPI_DLLEXPORT simxInt simxTransferFile(const simxChar* filePathAndName,const simxChar* fileName_serverSide,simxInt timeOut,simxInt operationMode)
{
	simxInt returnValue=0;
	simxInt bufferLength,tmpTimeout;
	simxChar* buffer;
	if (_communicationThreadRunning==0)
		return(simx_error_initialize_error_flag);
	if (operationMode==simx_opmode_remove)
		return(_removeCommandReply_string(simx_cmd_transfer_file,filePathAndName));
	buffer=extApi_readFile(filePathAndName,&bufferLength);
	if (buffer==0)
		return(simx_error_local_error_flag);
	tmpTimeout=_replyWaitTimeoutInMs;
	_replyWaitTimeoutInMs=timeOut;
	_exec_string_buffer(simx_cmd_transfer_file,operationMode,0,fileName_serverSide,buffer,bufferLength,&returnValue);
	_replyWaitTimeoutInMs=tmpTimeout;
	extApi_releaseBuffer(buffer);
	return(returnValue);
}

EXTAPI_DLLEXPORT simxInt simxEraseFile(const simxChar* fileName_serverSide,simxInt operationMode)
{
	simxInt returnValue;
	if (_communicationThreadRunning==0)
		return(simx_error_initialize_error_flag);
	if (operationMode==simx_opmode_remove)
		return(_removeCommandReply_string(simx_cmd_erase_file,fileName_serverSide));
	_exec_string(simx_cmd_erase_file,operationMode,0,fileName_serverSide,&returnValue);
	return(returnValue);
}

EXTAPI_DLLEXPORT simxInt simxLoadModel(const simxChar* modelPathAndName,simxChar options,simxInt* baseHandle,simxInt operationMode)
{
	simxChar* dataPointer=0;
	simxInt returnValue;
	simxChar tmpFileName[]="REMOTE_API_TEMPFILE_XXXX.ttm";
	if (_communicationThreadRunning==0)
		return(simx_error_initialize_error_flag);
	if (operationMode==simx_opmode_remove)
		return(_removeCommandReply_string(simx_cmd_load_model,modelPathAndName));
	if (options&1)
	{ /* give some pseudo-random name to the temp file: */
		tmpFileName[20]='0'+(char)(extApi_rand()*9.1f);
		tmpFileName[21]='0'+(char)(extApi_rand()*9.1f);
		tmpFileName[22]='0'+(char)(extApi_rand()*9.1f);
		tmpFileName[23]='0'+(char)(extApi_rand()*9.1f);
		returnValue=simxTransferFile(modelPathAndName,tmpFileName,60000,simx_opmode_oneshot_wait);
		if (returnValue==0)
		{
			dataPointer=_exec_string(simx_cmd_load_model,operationMode,0,tmpFileName,&returnValue);
			simxEraseFile(tmpFileName,simx_opmode_oneshot);
		}
		simxTransferFile(modelPathAndName,tmpFileName,60000,simx_opmode_remove);
	}
	else
		dataPointer=_exec_string(simx_cmd_load_model,operationMode,0,modelPathAndName,&returnValue);
	if ((dataPointer!=0)&&(returnValue==0)&&(baseHandle!=0))
		baseHandle[0]=_readPureDataInt(dataPointer,0,0);
	return(returnValue);
}

EXTAPI_DLLEXPORT simxInt simxLoadUI(const simxChar* uiPathAndName,simxChar options,simxInt* count,simxInt** uiHandles,simxInt operationMode)
{
	simxChar* dataPointer=0;
	simxInt returnValue,i;
	simxChar tmpFileName[]="REMOTE_API_TEMPFILE_XXXX.ttb";
	if (_communicationThreadRunning==0)
		return(simx_error_initialize_error_flag);
	if (operationMode==simx_opmode_remove)
		return(_removeCommandReply_string(simx_cmd_load_ui,uiPathAndName));
	if (options&1)
	{ /* give some pseudo-random name to the temp file: */
		tmpFileName[20]='0'+(char)(extApi_rand()*9.1f);
		tmpFileName[21]='0'+(char)(extApi_rand()*9.1f);
		tmpFileName[22]='0'+(char)(extApi_rand()*9.1f);
		tmpFileName[23]='0'+(char)(extApi_rand()*9.1f);
		returnValue=simxTransferFile(uiPathAndName,tmpFileName,60000,simx_opmode_oneshot_wait);
		if (returnValue==0)
		{
			dataPointer=_exec_string(simx_cmd_load_ui,operationMode,0,tmpFileName,&returnValue);
			simxEraseFile(tmpFileName,simx_opmode_oneshot);
		}
		simxTransferFile(uiPathAndName,tmpFileName,60000,simx_opmode_remove);
	}
	else
		dataPointer=_exec_string(simx_cmd_load_ui,operationMode,0,uiPathAndName,&returnValue);
	if ((dataPointer!=0)&&(returnValue==0))
	{
		count[0]=_readPureDataInt(dataPointer,0,0);
		uiHandles[0]=(simxInt*)extApi_allocateBuffer(4*count[0]);
		for (i=0;i<count[0];i++)
			((simxInt*)(uiHandles[0]))[i]=_readPureDataInt(dataPointer,0,4+4*i);
	}
	return(returnValue);
}

EXTAPI_DLLEXPORT simxInt simxLoadScene(const simxChar* scenePathAndName,simxChar options,simxInt operationMode)
{
	simxInt returnValue;
	simxChar tmpFileName[]="REMOTE_API_TEMPFILE_XXXX.ttt";
	if (_communicationThreadRunning==0)
		return(simx_error_initialize_error_flag);
	if (operationMode==simx_opmode_remove)
		return(_removeCommandReply_string(simx_cmd_load_scene,scenePathAndName));
	if (options&1)
	{ /* give some pseudo-random name to the temp file: */
		tmpFileName[20]='0'+(char)(extApi_rand()*9.1f);
		tmpFileName[21]='0'+(char)(extApi_rand()*9.1f);
		tmpFileName[22]='0'+(char)(extApi_rand()*9.1f);
		tmpFileName[23]='0'+(char)(extApi_rand()*9.1f);
		returnValue=simxTransferFile(scenePathAndName,tmpFileName,60000,simx_opmode_oneshot_wait);
		if (returnValue==0)
		{
			_exec_string(simx_cmd_load_scene,operationMode,0,tmpFileName,&returnValue);
			simxEraseFile(tmpFileName,simx_opmode_oneshot);
		}
		simxTransferFile(scenePathAndName,tmpFileName,60000,simx_opmode_remove);
	}
	else
		_exec_string(simx_cmd_load_scene,operationMode,0,scenePathAndName,&returnValue);
	return(returnValue);
}

EXTAPI_DLLEXPORT simxInt simxGetUISlider(simxInt uiHandle,simxInt uiButtonID,simxInt* position,simxInt operationMode)
{
	simxChar* dataPointer;
	simxInt returnValue;
	if (_communicationThreadRunning==0)
		return(simx_error_initialize_error_flag);
	if (operationMode==simx_opmode_remove)
		return(_removeCommandReply_intint(simx_cmd_get_ui_slider,uiHandle,uiButtonID));
	dataPointer=_exec_intint(simx_cmd_get_ui_slider,operationMode,0,uiHandle,uiButtonID,&returnValue);
	if ((dataPointer!=0)&&(returnValue==0))
		position[0]=_readPureDataInt(dataPointer,0,0);
	return(returnValue);
}

EXTAPI_DLLEXPORT simxInt simxSetUISlider(simxInt uiHandle,simxInt uiButtonID,simxInt position,simxInt operationMode)
{
	simxInt returnValue;
	if (_communicationThreadRunning==0)
		return(simx_error_initialize_error_flag);
	if (operationMode==simx_opmode_remove)
		return(_removeCommandReply_intint(simx_cmd_set_ui_slider,uiHandle,uiButtonID));
	_exec_intint_int(simx_cmd_set_ui_slider,operationMode,0,uiHandle,uiButtonID,position,&returnValue);
	return(returnValue);
}

EXTAPI_DLLEXPORT simxInt simxGetUIEventButton(simxInt uiHandle,simxInt* uiEventButtonID,simxInt* auxValues,simxInt operationMode)
{
	simxChar* dataPointer;
	simxInt returnValue;
	if (_communicationThreadRunning==0)
		return(simx_error_initialize_error_flag);
	if (operationMode==simx_opmode_remove)
		return(_removeCommandReply_int(simx_cmd_get_ui_event_button,uiHandle));
	dataPointer=_exec_int(simx_cmd_get_ui_event_button,operationMode,0,uiHandle,&returnValue);
	if ((dataPointer!=0)&&(returnValue==0))
	{
		uiEventButtonID[0]=_readPureDataInt(dataPointer,0,0);
		if (auxValues!=0)
		{
			auxValues[0]=_readPureDataInt(dataPointer,0,4);
			auxValues[1]=_readPureDataInt(dataPointer,0,8);
		}
		//******* SPECIAL CASE FOR THIS COMMAND ONLY !! ********
		if ((operationMode==simx_opmode_buffer)&&(uiEventButtonID[0]!=-1))
			_removeCommandReply_int(simx_cmd_get_ui_event_button,uiHandle); // We received an event! The continuous command was automatically deactivated on the server side. We remove the reply  in the input buffer on the client here!
		//******************************************************
	}
	return(returnValue);
}

EXTAPI_DLLEXPORT simxInt simxGetUIButtonProperty(simxInt uiHandle,simxInt uiButtonID,simxInt* prop,simxInt operationMode)
{
	simxChar* dataPointer;
	simxInt returnValue;
	if (_communicationThreadRunning==0)
		return(simx_error_initialize_error_flag);
	if (operationMode==simx_opmode_remove)
		return(_removeCommandReply_intint(simx_cmd_get_ui_button_property,uiHandle,uiButtonID));
	dataPointer=_exec_intint(simx_cmd_get_ui_button_property,operationMode,0,uiHandle,uiButtonID,&returnValue);
	if ((dataPointer!=0)&&(returnValue==0))
		prop[0]=_readPureDataInt(dataPointer,0,0);
	return(returnValue);
}

EXTAPI_DLLEXPORT simxInt simxSetUIButtonProperty(simxInt uiHandle,simxInt uiButtonID,simxInt prop,simxInt operationMode)
{
	simxInt returnValue;
	if (_communicationThreadRunning==0)
		return(simx_error_initialize_error_flag);
	if (operationMode==simx_opmode_remove)
		return(_removeCommandReply_intint(simx_cmd_set_ui_button_property,uiHandle,uiButtonID));
	_exec_intint_int(simx_cmd_set_ui_button_property,operationMode,0,uiHandle,uiButtonID,prop,&returnValue);
	return(returnValue);
}

EXTAPI_DLLEXPORT simxInt simxAddStatusbarMessage(const simxChar* message,simxInt operationMode)
{
	simxInt returnValue;
	if (_communicationThreadRunning==0)
		return(simx_error_initialize_error_flag);
	if (operationMode==simx_opmode_remove)
		return(_removeCommandReply_string(simx_cmd_add_statusbar_message,message));
	_exec_string(simx_cmd_add_statusbar_message,operationMode,0,message,&returnValue);
	return(returnValue);
}

EXTAPI_DLLEXPORT simxInt simxAuxiliaryConsoleOpen(const simxChar* title,simxInt maxLines,simxInt mode,simxInt* position,simxInt* size,simxFloat* textColor,simxFloat* backgroundColor,simxInt* consoleHandle,simxInt operationMode)
{
	simxChar* dataPointer;
	simxInt returnValue;
	simxChar buffer[12*4];
	if (_communicationThreadRunning==0)
		return(simx_error_initialize_error_flag);
	if (operationMode==simx_opmode_remove)
		return(_removeCommandReply_string(simx_cmd_aux_console_open,title));
	((simxInt*)buffer)[0]=extApi_endianConversionInt(maxLines);
	((simxInt*)buffer)[1]=extApi_endianConversionInt(mode);
	((simxInt*)buffer)[2]=extApi_endianConversionInt(98765);
	if (position!=0)
	{
		((simxInt*)buffer)[2]=extApi_endianConversionInt(position[0]);
		((simxInt*)buffer)[3]=extApi_endianConversionInt(position[1]);
	}
	((simxInt*)buffer)[4]=extApi_endianConversionInt(98765);
	if (size!=0)
	{
		((simxInt*)buffer)[4]=extApi_endianConversionInt(size[0]);
		((simxInt*)buffer)[5]=extApi_endianConversionInt(size[1]);
	}
	((simxFloat*)buffer)[6]=extApi_endianConversionFloat(-10.0f);
	if (textColor!=0)
	{
		((simxFloat*)buffer)[6]=extApi_endianConversionFloat(textColor[0]);
		((simxFloat*)buffer)[7]=extApi_endianConversionFloat(textColor[1]);
		((simxFloat*)buffer)[8]=extApi_endianConversionFloat(textColor[2]);
	}
	((simxFloat*)buffer)[9]=extApi_endianConversionFloat(-10.0f);
	if (backgroundColor!=0)
	{
		((simxFloat*)buffer)[9]=extApi_endianConversionFloat(backgroundColor[0]);
		((simxFloat*)buffer)[10]=extApi_endianConversionFloat(backgroundColor[1]);
		((simxFloat*)buffer)[11]=extApi_endianConversionFloat(backgroundColor[2]);
	}
	dataPointer=_exec_string_buffer(simx_cmd_aux_console_open,operationMode,0,title,buffer,12*4,&returnValue);
	if ((dataPointer!=0)&&(returnValue==0))
		consoleHandle[0]=_readPureDataInt(dataPointer,0,0);
	return(returnValue);
}

EXTAPI_DLLEXPORT simxInt simxAuxiliaryConsoleClose(simxInt consoleHandle,simxInt operationMode)
{
	simxInt returnValue;
	if (_communicationThreadRunning==0)
		return(simx_error_initialize_error_flag);
	if (operationMode==simx_opmode_remove)
		return(_removeCommandReply_int(simx_cmd_aux_console_close,consoleHandle));
	_exec_int(simx_cmd_aux_console_close,operationMode,0,consoleHandle,&returnValue);
	return(returnValue);
}

EXTAPI_DLLEXPORT simxInt simxAuxiliaryConsolePrint(simxInt consoleHandle,const simxChar* txt,simxInt operationMode)
{
	simxInt returnValue;
	if (_communicationThreadRunning==0)
		return(simx_error_initialize_error_flag);
	if (operationMode==simx_opmode_remove)
		return(_removeCommandReply_int(simx_cmd_aux_console_print,consoleHandle));
	if (txt==0)
		_exec_int_buffer(simx_cmd_aux_console_print,operationMode,1,consoleHandle,0,0,&returnValue);
	else
		_exec_int_buffer(simx_cmd_aux_console_print,operationMode,1,consoleHandle,(simxChar*)txt,extApi_getStringLength(txt)+1,&returnValue);
	return(returnValue);
}

EXTAPI_DLLEXPORT simxInt simxAuxiliaryConsoleShow(simxInt consoleHandle,simxChar showState,simxInt operationMode)
{
	simxInt returnValue;
	if (_communicationThreadRunning==0)
		return(simx_error_initialize_error_flag);
	if (operationMode==simx_opmode_remove)
		return(_removeCommandReply_int(simx_cmd_aux_console_show,consoleHandle));
	_exec_int_int(simx_cmd_aux_console_show,operationMode,0,consoleHandle,(simxInt)showState,&returnValue);
	return(returnValue);
}

EXTAPI_DLLEXPORT simxInt simxGetObjectOrientation(simxInt objectHandle,simxInt relativeToObjectHandle,simxFloat* eulerAngles,simxInt operationMode)
{
	simxChar* dataPointer;
	simxInt returnValue;
	if (_communicationThreadRunning==0)
		return(simx_error_initialize_error_flag);
	if (operationMode==simx_opmode_remove)
		return(_removeCommandReply_int(simx_cmd_get_object_orientation,objectHandle));
	dataPointer=_exec_int_int(simx_cmd_get_object_orientation,operationMode,0,objectHandle,relativeToObjectHandle,&returnValue);
	if ((dataPointer!=0)&&(returnValue==0))
	{
		eulerAngles[0]=_readPureDataFloat(dataPointer,0,0);
		eulerAngles[1]=_readPureDataFloat(dataPointer,0,4);
		eulerAngles[2]=_readPureDataFloat(dataPointer,0,8);
	}
	return(returnValue);
}

EXTAPI_DLLEXPORT simxInt simxGetObjectPosition(simxInt objectHandle,simxInt relativeToObjectHandle,simxFloat* position,simxInt operationMode)
{
	simxChar* dataPointer;
	simxInt returnValue;
	if (_communicationThreadRunning==0)
		return(simx_error_initialize_error_flag);
	if (operationMode==simx_opmode_remove)
		return(_removeCommandReply_int(simx_cmd_get_object_position,objectHandle));
	dataPointer=_exec_int_int(simx_cmd_get_object_position,operationMode,0,objectHandle,relativeToObjectHandle,&returnValue);
	if ((dataPointer!=0)&&(returnValue==0))
	{
		position[0]=_readPureDataFloat(dataPointer,0,0);
		position[1]=_readPureDataFloat(dataPointer,0,4);
		position[2]=_readPureDataFloat(dataPointer,0,8);
	}
	return(returnValue);
}

EXTAPI_DLLEXPORT simxInt simxSetObjectOrientation(simxInt objectHandle,simxInt relativeToObjectHandle,const simxFloat* eulerAngles,simxInt operationMode)
{
	simxInt returnValue;
	simxChar buffer[4*4];
	if (_communicationThreadRunning==0)
		return(simx_error_initialize_error_flag);
	if (operationMode==simx_opmode_remove)
		return(_removeCommandReply_int(simx_cmd_set_object_orientation,objectHandle));
	((simxInt*)buffer)[0]=extApi_endianConversionInt(relativeToObjectHandle);
	((simxFloat*)buffer)[1]=extApi_endianConversionFloat(eulerAngles[0]);
	((simxFloat*)buffer)[2]=extApi_endianConversionFloat(eulerAngles[1]);
	((simxFloat*)buffer)[3]=extApi_endianConversionFloat(eulerAngles[2]);
	_exec_int_buffer(simx_cmd_set_object_orientation,operationMode,0,objectHandle,buffer,4*4,&returnValue);
	return(returnValue);
}

EXTAPI_DLLEXPORT simxInt simxSetObjectPosition(simxInt objectHandle,simxInt relativeToObjectHandle,const simxFloat* position,simxInt operationMode)
{
	simxInt returnValue;
	simxChar buffer[4*4];
	if (_communicationThreadRunning==0)
		return(simx_error_initialize_error_flag);
	if (operationMode==simx_opmode_remove)
		return(_removeCommandReply_int(simx_cmd_set_object_position,objectHandle));
	((simxInt*)buffer)[0]=extApi_endianConversionInt(relativeToObjectHandle);
	((simxFloat*)buffer)[1]=extApi_endianConversionFloat(position[0]);
	((simxFloat*)buffer)[2]=extApi_endianConversionFloat(position[1]);
	((simxFloat*)buffer)[3]=extApi_endianConversionFloat(position[2]);
	_exec_int_buffer(simx_cmd_set_object_position,operationMode,0,objectHandle,buffer,4*4,&returnValue);
	return(returnValue);
}

EXTAPI_DLLEXPORT simxInt simxSetObjectParent(simxInt objectHandle,simxInt parentObject,simxChar keepInPlace,simxInt operationMode)
{
	simxInt returnValue;
	simxChar buffer[4+1];
	if (_communicationThreadRunning==0)
		return(simx_error_initialize_error_flag);
	if (operationMode==simx_opmode_remove)
		return(_removeCommandReply_int(simx_cmd_set_object_parent,objectHandle));
	((simxInt*)buffer)[0]=extApi_endianConversionInt(parentObject);
	buffer[4]=keepInPlace;
	_exec_int_buffer(simx_cmd_set_object_parent,operationMode,0,objectHandle,buffer,4+1,&returnValue);
	return(returnValue);
}

EXTAPI_DLLEXPORT simxInt simxSetUIButtonLabel(simxInt uiHandle,simxInt uiButtonID,const simxChar* upStateLabel,const simxChar* downStateLabel,simxInt operationMode)
{
	simxInt returnValue;
	simxInt strL1,strL2,i;
	simxChar* buffer;
	if (_communicationThreadRunning==0)
		return(simx_error_initialize_error_flag);
	if (operationMode==simx_opmode_remove)
		return(_removeCommandReply_intint(simx_cmd_set_ui_button_label,uiHandle,uiButtonID));
	strL1=extApi_getStringLength(upStateLabel);
	strL2=extApi_getStringLength(downStateLabel);
	buffer=extApi_allocateBuffer(strL1+strL2+1+1);
	for (i=0;i<strL1+1;i++)
		buffer[i]=upStateLabel[i];
	for (i=0;i<strL2+1;i++)
		buffer[strL1+1+i]=downStateLabel[i];
	_exec_intint_buffer(simx_cmd_set_ui_button_label,operationMode,0,uiHandle,uiButtonID,buffer,strL1+strL2+1+1,&returnValue);
	extApi_releaseBuffer(buffer);
	return(returnValue);
}

EXTAPI_DLLEXPORT simxInt simxGetLastErrors(simxInt* errorCnt,simxChar** errorStrings,simxInt operationMode)
{
	simxChar* dataPointer;
	simxInt returnValue;
	if (_communicationThreadRunning==0)
		return(simx_error_initialize_error_flag);
	if (operationMode==simx_opmode_remove)
		return(_removeCommandReply_null(simx_cmd_get_last_errors));
	dataPointer=_exec_null(simx_cmd_get_last_errors,operationMode,0,&returnValue);
	if ((dataPointer!=0)&&(returnValue==0))
	{
		errorCnt[0]=_readPureDataInt(dataPointer,0,0);
		errorStrings[0]=dataPointer+SIMX_SUBHEADER_SIZE+4+_getCmdDataSize(dataPointer);
	}
	return(returnValue);
}

EXTAPI_DLLEXPORT simxInt simxGetArrayParameter(simxInt paramIdentifier,simxFloat* paramValues,simxInt operationMode)
{
	simxChar* dataPointer;
	simxInt returnValue,i;
	if (_communicationThreadRunning==0)
		return(simx_error_initialize_error_flag);
	if (operationMode==simx_opmode_remove)
		return(_removeCommandReply_int(simx_cmd_get_array_parameter,paramIdentifier));
	dataPointer=_exec_int(simx_cmd_get_array_parameter,operationMode,0,paramIdentifier,&returnValue);
	if ((dataPointer!=0)&&(returnValue==0))
	{
		for (i=0;i<3;i++)
			paramValues[i]=_readPureDataFloat(dataPointer,0,4*i);
	}
	return(returnValue);
}

EXTAPI_DLLEXPORT simxInt simxSetArrayParameter(simxInt paramIdentifier,const simxFloat* paramValues,simxInt operationMode)
{
	simxInt returnValue;
	if (_communicationThreadRunning==0)
		return(simx_error_initialize_error_flag);
	if (operationMode==simx_opmode_remove)
		return(_removeCommandReply_int(simx_cmd_set_array_parameter,paramIdentifier));
	_exec_int_buffer(simx_cmd_set_array_parameter,operationMode,0,paramIdentifier,(simxChar*)paramValues,3*4,&returnValue);
	return(returnValue);
}

EXTAPI_DLLEXPORT simxInt simxGetBooleanParameter(simxInt paramIdentifier,simxChar* paramValue,simxInt operationMode)
{
	simxChar* dataPointer;
	simxInt returnValue;
	if (_communicationThreadRunning==0)
		return(simx_error_initialize_error_flag);
	if (operationMode==simx_opmode_remove)
		return(_removeCommandReply_int(simx_cmd_get_boolean_parameter,paramIdentifier));
	dataPointer=_exec_int(simx_cmd_get_boolean_parameter,operationMode,0,paramIdentifier,&returnValue);
	if ((dataPointer!=0)&&(returnValue==0))
		paramValue[0]=(simxChar)_readPureDataInt(dataPointer,0,0);
	return(returnValue);
}

EXTAPI_DLLEXPORT simxInt simxSetBooleanParameter(simxInt paramIdentifier,simxChar paramValue,simxInt operationMode)
{
	simxInt returnValue;
	if (_communicationThreadRunning==0)
		return(simx_error_initialize_error_flag);
	if (operationMode==simx_opmode_remove)
		return(_removeCommandReply_int(simx_cmd_set_boolean_parameter,paramIdentifier));
	_exec_int_int(simx_cmd_set_boolean_parameter,operationMode,0,paramIdentifier,(simxInt)paramValue,&returnValue);
	return(returnValue);
}

EXTAPI_DLLEXPORT simxInt simxGetIntegerParameter(simxInt paramIdentifier,simxInt* paramValue,simxInt operationMode)
{
	simxChar* dataPointer;
	simxInt returnValue;
	if (_communicationThreadRunning==0)
		return(simx_error_initialize_error_flag);
	if (operationMode==simx_opmode_remove)
		return(_removeCommandReply_int(simx_cmd_get_integer_parameter,paramIdentifier));
	dataPointer=_exec_int(simx_cmd_get_integer_parameter,operationMode,0,paramIdentifier,&returnValue);
	if ((dataPointer!=0)&&(returnValue==0))
		paramValue[0]=_readPureDataInt(dataPointer,0,0);
	return(returnValue);
}

EXTAPI_DLLEXPORT simxInt simxSetIntegerParameter(simxInt paramIdentifier,simxInt paramValue,simxInt operationMode)
{
	simxInt returnValue;
	if (_communicationThreadRunning==0)
		return(simx_error_initialize_error_flag);
	if (operationMode==simx_opmode_remove)
		return(_removeCommandReply_int(simx_cmd_set_integer_parameter,paramIdentifier));
	_exec_int_int(simx_cmd_set_integer_parameter,operationMode,0,paramIdentifier,paramValue,&returnValue);
	return(returnValue);
}

EXTAPI_DLLEXPORT simxInt simxGetFloatingParameter(simxInt paramIdentifier,simxFloat* paramValue,simxInt operationMode)
{
	simxChar* dataPointer;
	simxInt returnValue;
	if (_communicationThreadRunning==0)
		return(simx_error_initialize_error_flag);
	if (operationMode==simx_opmode_remove)
		return(_removeCommandReply_int(simx_cmd_get_floating_parameter,paramIdentifier));
	dataPointer=_exec_int(simx_cmd_get_floating_parameter,operationMode,0,paramIdentifier,&returnValue);
	if ((dataPointer!=0)&&(returnValue==0))
		paramValue[0]=_readPureDataFloat(dataPointer,0,0);
	return(returnValue);
}

EXTAPI_DLLEXPORT simxInt simxSetFloatingParameter(simxInt paramIdentifier,simxFloat paramValue,simxInt operationMode)
{
	simxInt returnValue;
	if (_communicationThreadRunning==0)
		return(simx_error_initialize_error_flag);
	if (operationMode==simx_opmode_remove)
		return(_removeCommandReply_int(simx_cmd_set_floating_parameter,paramIdentifier));
	_exec_int_float(simx_cmd_set_floating_parameter,operationMode,0,paramIdentifier,paramValue,&returnValue);
	return(returnValue);
}

EXTAPI_DLLEXPORT simxInt simxGetStringParameter(simxInt paramIdentifier,simxChar** paramValue,simxInt operationMode)
{
	simxChar* dataPointer;
	simxInt returnValue;
	if (_communicationThreadRunning==0)
		return(simx_error_initialize_error_flag);
	if (operationMode==simx_opmode_remove)
		return(_removeCommandReply_int(simx_cmd_get_string_parameter,paramIdentifier));
	dataPointer=_exec_int(simx_cmd_get_string_parameter,operationMode,0,paramIdentifier,&returnValue);
	if ((dataPointer!=0)&&(returnValue==0))
		paramValue[0]=dataPointer+SIMX_SUBHEADER_SIZE+_getCmdDataSize(dataPointer);
	return(returnValue);
}

EXTAPI_DLLEXPORT simxInt simxGetCollisionHandle(const simxChar* collisionObjectName,simxInt* handle,simxInt operationMode)
{
	simxChar* dataPointer;
	simxInt returnValue;
	if (_communicationThreadRunning==0)
		return(simx_error_initialize_error_flag);
	if (operationMode==simx_opmode_remove)
		return(_removeCommandReply_string(simx_cmd_get_collision_handle,collisionObjectName));
	dataPointer=_exec_string(simx_cmd_get_collision_handle,operationMode,0,collisionObjectName,&returnValue);
	if ((dataPointer!=0)&&(returnValue==0))
		handle[0]=_readPureDataInt(dataPointer,0,0);
	return(returnValue);
}

EXTAPI_DLLEXPORT simxInt simxGetDistanceHandle(const simxChar* distanceObjectName,simxInt* handle,simxInt operationMode)
{
	simxChar* dataPointer;
	simxInt returnValue;
	if (_communicationThreadRunning==0)
		return(simx_error_initialize_error_flag);
	if (operationMode==simx_opmode_remove)
		return(_removeCommandReply_string(simx_cmd_get_distance_handle,distanceObjectName));
	dataPointer=_exec_string(simx_cmd_get_distance_handle,operationMode,0,distanceObjectName,&returnValue);
	if ((dataPointer!=0)&&(returnValue==0))
		handle[0]=_readPureDataInt(dataPointer,0,0);
	return(returnValue);
}

EXTAPI_DLLEXPORT simxInt simxReadCollision(simxInt collisionObjectHandle,simxChar* collisionState,simxInt operationMode)
{
	simxChar* dataPointer;
	simxInt returnValue;
	if (_communicationThreadRunning==0)
		return(simx_error_initialize_error_flag);
	if (operationMode==simx_opmode_remove)
		return(_removeCommandReply_int(simx_cmd_read_collision,collisionObjectHandle));
	dataPointer=_exec_int(simx_cmd_read_collision,operationMode,0,collisionObjectHandle,&returnValue);
	if ((dataPointer!=0)&&(returnValue==0))
		collisionState[0]=(simxChar)_readPureDataInt(dataPointer,0,0);
	return(returnValue);
}

EXTAPI_DLLEXPORT simxInt simxReadDistance(simxInt distanceObjectHandle,simxFloat* minimumDistance,simxInt operationMode)
{
	simxChar* dataPointer;
	simxInt returnValue;
	if (_communicationThreadRunning==0)
		return(simx_error_initialize_error_flag);
	if (operationMode==simx_opmode_remove)
		return(_removeCommandReply_int(simx_cmd_read_distance,distanceObjectHandle));
	dataPointer=_exec_int(simx_cmd_read_distance,operationMode,0,distanceObjectHandle,&returnValue);
	if ((dataPointer!=0)&&(returnValue==0))
		minimumDistance[0]=_readPureDataFloat(dataPointer,0,0);
	return(returnValue);
}

EXTAPI_DLLEXPORT simxInt simxRemoveObject(simxInt objectHandle,simxInt operationMode)
{
	simxInt returnValue;
	if (_communicationThreadRunning==0)
		return(simx_error_initialize_error_flag);
	if (operationMode==simx_opmode_remove)
		return(_removeCommandReply_int(simx_cmd_remove_object,objectHandle));
	_exec_int(simx_cmd_remove_object,operationMode,0,objectHandle,&returnValue);
	return(returnValue);
}

EXTAPI_DLLEXPORT simxInt simxRemoveUI(simxInt uiHandle,simxInt operationMode)
{
	simxInt returnValue;
	if (_communicationThreadRunning==0)
		return(simx_error_initialize_error_flag);
	if (operationMode==simx_opmode_remove)
		return(_removeCommandReply_int(simx_cmd_remove_ui,uiHandle));
	_exec_int(simx_cmd_remove_ui,operationMode,0,uiHandle,&returnValue);
	return(returnValue);
}

EXTAPI_DLLEXPORT simxInt simxCloseScene(simxInt operationMode)
{
	simxInt returnValue;
	if (_communicationThreadRunning==0)
		return(simx_error_initialize_error_flag);
	if (operationMode==simx_opmode_remove)
		return(_removeCommandReply_null(simx_cmd_close_scene));
	_exec_null(simx_cmd_close_scene,operationMode,0,&returnValue);
	return(returnValue);
}

EXTAPI_DLLEXPORT simxInt simxGetObjects(simxInt objectType,simxInt* objectCount,simxInt** objectHandles,simxInt operationMode)
{
	simxChar* dataPointer;
	simxInt returnValue,off;
#ifdef ENDIAN_TEST
	simxInt i;
#endif
	if (_communicationThreadRunning==0)
		return(simx_error_initialize_error_flag);
	if (operationMode==simx_opmode_remove)
		return(_removeCommandReply_int(simx_cmd_get_objects,objectType));
	dataPointer=_exec_int(simx_cmd_get_objects,operationMode,0,objectType,&returnValue);
	if ((dataPointer!=0)&&(returnValue==0))
	{
		objectCount[0]=_readPureDataInt(dataPointer,0,0);
		off=SIMX_SUBHEADER_SIZE+_getCmdDataSize(dataPointer)+4;
#ifdef ENDIAN_TEST
		for (i=0;i<objectCount[0];i++)
			((simxInt*)(dataPointer+off))[i]=extApi_endianConversionInt(((simxInt*)(dataPointer+off))[i]);
#endif
		objectHandles[0]=((simxInt*)(dataPointer+off));
	}
	return(returnValue);
}

EXTAPI_DLLEXPORT simxInt simxDisplayDialog(const simxChar* titleText,const simxChar* mainText,simxInt dialogType,const simxChar* initialText,simxFloat* titleColors,simxFloat* dialogColors,simxInt* dialogHandle,simxInt* uiHandle,simxInt operationMode)
{
	simxChar* dataPointer;
	simxInt returnValue,str1L,str2L,i,off;
	simxChar* buffer;
	if (_communicationThreadRunning==0)
		return(simx_error_initialize_error_flag);
	if (operationMode==simx_opmode_remove)
		return(_removeCommandReply_string(simx_cmd_display_dialog,titleText));
	str1L=extApi_getStringLength(mainText);
	str2L=extApi_getStringLength(initialText);
	buffer=extApi_allocateBuffer(str1L+1+4+str2L+1+4*6+4*6);
	off=0;
	for (i=0;i<str1L+1;i++)
		buffer[off+i]=mainText[i];
	off+=str1L+1;
	((simxInt*)(buffer+off))[0]=extApi_endianConversionInt(dialogType);
	off+=4;
	for (i=0;i<str2L+1;i++)
		buffer[off+i]=initialText[i];
	off+=str2L+1;
	((simxFloat*)(buffer+off))[0]=extApi_endianConversionFloat(-10.0f);
	if (titleColors!=0)
	{
		for (i=0;i<6;i++)
			((simxFloat*)(buffer+off))[i]=extApi_endianConversionFloat(titleColors[i]);
	}
	off+=4*6;
	((simxFloat*)(buffer+off))[0]=extApi_endianConversionFloat(-10.0f);
	if (dialogColors!=0)
	{
		for (i=0;i<6;i++)
			((simxFloat*)(buffer+off))[i]=extApi_endianConversionFloat(dialogColors[i]);
	}
	dataPointer=_exec_string_buffer(simx_cmd_display_dialog,operationMode,0,titleText,buffer,str1L+1+4+str2L+1+4*6+4*6,&returnValue);
	extApi_releaseBuffer(buffer);
	if ((dataPointer!=0)&&(returnValue==0))
	{
		dialogHandle[0]=_readPureDataInt(dataPointer,0,0);
		if (uiHandle!=NULL)
			uiHandle[0]=_readPureDataInt(dataPointer,0,4);
	}
	return(returnValue);
}

EXTAPI_DLLEXPORT simxInt simxEndDialog(simxInt dialogHandle,simxInt operationMode)
{
	simxInt returnValue;
	if (_communicationThreadRunning==0)
		return(simx_error_initialize_error_flag);
	if (operationMode==simx_opmode_remove)
		return(_removeCommandReply_int(simx_cmd_end_dialog,dialogHandle));
	_exec_int(simx_cmd_end_dialog,operationMode,0,dialogHandle,&returnValue);
	return(returnValue);
}

EXTAPI_DLLEXPORT simxInt simxGetDialogInput(simxInt dialogHandle,simxChar** inputText,simxInt operationMode)
{
	simxChar* dataPointer;
	simxInt returnValue;
	if (_communicationThreadRunning==0)
		return(simx_error_initialize_error_flag);
	if (operationMode==simx_opmode_remove)
		return(_removeCommandReply_int(simx_cmd_get_dialog_input,dialogHandle));
	dataPointer=_exec_int(simx_cmd_get_dialog_input,operationMode,0,dialogHandle,&returnValue);
	if ((dataPointer!=0)&&(returnValue==0))
	{
		inputText[0]=dataPointer+SIMX_SUBHEADER_SIZE+_getCmdDataSize(dataPointer);
	}
	return(returnValue);
}

EXTAPI_DLLEXPORT simxInt simxGetDialogResult(simxInt dialogHandle,simxInt* result,simxInt operationMode)
{
	simxChar* dataPointer;
	simxInt returnValue;
	if (_communicationThreadRunning==0)
		return(simx_error_initialize_error_flag);
	if (operationMode==simx_opmode_remove)
		return(_removeCommandReply_int(simx_cmd_get_dialog_result,dialogHandle));
	dataPointer=_exec_int(simx_cmd_get_dialog_result,operationMode,0,dialogHandle,&returnValue);
	if ((dataPointer!=0)&&(returnValue==0))
	{
		result[0]=_readPureDataInt(dataPointer,0,0);
	}
	return(returnValue);
}

EXTAPI_DLLEXPORT simxInt simxCopyPasteObjects(const simxInt* objectHandles,simxInt objectCount,simxInt** newObjectHandles,simxInt* newObjectCount,simxInt operationMode)
{
	simxChar* dataPointer;
	simxInt returnValue,off;
#ifdef ENDIAN_TEST
	simxInt i;
#endif
	if (_communicationThreadRunning==0)
		return(simx_error_initialize_error_flag);
	if (operationMode==simx_opmode_remove)
		return(_removeCommandReply_int(simx_cmd_copy_paste_objects,0));
	dataPointer=_exec_int_buffer(simx_cmd_copy_paste_objects,operationMode,0,0,(simxChar*)objectHandles,objectCount*4,&returnValue);
	if ((dataPointer!=0)&&(returnValue==0))
	{
		newObjectCount[0]=_readPureDataInt(dataPointer,0,0);
		off=SIMX_SUBHEADER_SIZE+_getCmdDataSize(dataPointer)+4;
#ifdef ENDIAN_TEST
		for (i=0;i<newObjectCount[0];i++)
			((simxInt*)(dataPointer+off))[i]=extApi_endianConversionInt(((simxInt*)(dataPointer+off))[i]);
#endif
		newObjectHandles[0]=((simxInt*)(dataPointer+off));
	}
	return(returnValue);
}

EXTAPI_DLLEXPORT simxInt simxGetObjectSelection(simxInt** objectHandles,simxInt* objectCount,simxInt operationMode)
{
	simxChar* dataPointer;
	simxInt returnValue,off;
#ifdef ENDIAN_TEST
	simxInt i;
#endif
	if (_communicationThreadRunning==0)
		return(simx_error_initialize_error_flag);
	if (operationMode==simx_opmode_remove)
		return(_removeCommandReply_null(simx_cmd_get_object_selection));
	dataPointer=_exec_null(simx_cmd_get_object_selection,operationMode,0,&returnValue);
	if ((dataPointer!=0)&&(returnValue==0))
	{
		objectCount[0]=_readPureDataInt(dataPointer,0,0);
		off=SIMX_SUBHEADER_SIZE+_getCmdDataSize(dataPointer)+4;
#ifdef ENDIAN_TEST
		for (i=0;i<objectCount[0];i++)
			((simxInt*)(dataPointer+off))[i]=extApi_endianConversionInt(((simxInt*)(dataPointer+off))[i]);
#endif
		objectHandles[0]=((simxInt*)(dataPointer+off));
	}
	return(returnValue);
}

EXTAPI_DLLEXPORT simxInt simxSetObjectSelection(const simxInt* objectHandles,simxInt objectCount,simxInt operationMode)
{
	simxInt returnValue;
	if (_communicationThreadRunning==0)
		return(simx_error_initialize_error_flag);
	if (operationMode==simx_opmode_remove)
		return(_removeCommandReply_int(simx_cmd_set_object_selection,0));
	_exec_int_buffer(simx_cmd_set_object_selection,operationMode,0,0,(simxChar*)objectHandles,objectCount*4,&returnValue);
	return(returnValue);
}

EXTAPI_DLLEXPORT simxInt simxClearFloatSignal(const simxChar* signalName,simxInt operationMode)
{
	simxInt returnValue;
	if (_communicationThreadRunning==0)
		return(simx_error_initialize_error_flag);
	if (operationMode==simx_opmode_remove)
		return(_removeCommandReply_string(simx_cmd_clear_float_signal,signalName));
	_exec_string(simx_cmd_clear_float_signal,operationMode,0,signalName,&returnValue);
	return(returnValue);
}

EXTAPI_DLLEXPORT simxInt simxClearIntegerSignal(const simxChar* signalName,simxInt operationMode)
{
	simxInt returnValue;
	if (_communicationThreadRunning==0)
		return(simx_error_initialize_error_flag);
	if (operationMode==simx_opmode_remove)
		return(_removeCommandReply_string(simx_cmd_clear_integer_signal,signalName));
	_exec_string(simx_cmd_clear_integer_signal,operationMode,0,signalName,&returnValue);
	return(returnValue);
}

EXTAPI_DLLEXPORT simxInt simxClearStringSignal(const simxChar* signalName,simxInt operationMode)
{
	simxInt returnValue;
	if (_communicationThreadRunning==0)
		return(simx_error_initialize_error_flag);
	if (operationMode==simx_opmode_remove)
		return(_removeCommandReply_string(simx_cmd_clear_string_signal,signalName));
	_exec_string(simx_cmd_clear_string_signal,operationMode,0,signalName,&returnValue);
	return(returnValue);
}

EXTAPI_DLLEXPORT simxInt simxGetFloatSignal(const simxChar* signalName,simxFloat* signalValue,simxInt operationMode)
{
	simxChar* dataPointer;
	simxInt returnValue;
	if (_communicationThreadRunning==0)
		return(simx_error_initialize_error_flag);
	if (operationMode==simx_opmode_remove)
		return(_removeCommandReply_string(simx_cmd_get_float_signal,signalName));
	dataPointer=_exec_string(simx_cmd_get_float_signal,operationMode,0,signalName,&returnValue);
	if ((dataPointer!=0)&&(returnValue==0))
		signalValue[0]=_readPureDataFloat(dataPointer,0,0);
	return(returnValue);
}

EXTAPI_DLLEXPORT simxInt simxGetIntegerSignal(const simxChar* signalName,simxInt* signalValue,simxInt operationMode)
{
	simxChar* dataPointer;
	simxInt returnValue;
	if (_communicationThreadRunning==0)
		return(simx_error_initialize_error_flag);
	if (operationMode==simx_opmode_remove)
		return(_removeCommandReply_string(simx_cmd_get_integer_signal,signalName));
	dataPointer=_exec_string(simx_cmd_get_integer_signal,operationMode,0,signalName,&returnValue);
	if ((dataPointer!=0)&&(returnValue==0))
		signalValue[0]=_readPureDataInt(dataPointer,0,0);
	return(returnValue);
}

EXTAPI_DLLEXPORT simxInt simxGetStringSignal(const simxChar* signalName,simxChar** signalValue,simxInt* signalLength,simxInt operationMode)
{
	simxChar* dataPointer;
	simxInt returnValue;
	if (_communicationThreadRunning==0)
		return(simx_error_initialize_error_flag);
	if (operationMode==simx_opmode_remove)
		return(_removeCommandReply_string(simx_cmd_get_string_signal,signalName));
	dataPointer=_exec_string(simx_cmd_get_string_signal,operationMode,0,signalName,&returnValue);
	if ((dataPointer!=0)&&(returnValue==0))
	{
		signalValue[0]=dataPointer+SIMX_SUBHEADER_SIZE+_getCmdDataSize(dataPointer);
		signalLength[0]=extApi_endianConversionInt(((simxInt*)(dataPointer+simx_cmdheaderoffset_full_mem_size))[0])-SIMX_SUBHEADER_SIZE-_getCmdDataSize(dataPointer);
	}
	return(returnValue);
}

EXTAPI_DLLEXPORT simxInt simxSetFloatSignal(const simxChar* signalName,simxFloat signalValue,simxInt operationMode)
{
	simxInt returnValue;
	if (_communicationThreadRunning==0)
		return(simx_error_initialize_error_flag);
	if (operationMode==simx_opmode_remove)
		return(_removeCommandReply_string(simx_cmd_set_float_signal,signalName));
	signalValue=extApi_endianConversionFloat(signalValue);
	_exec_string_buffer(simx_cmd_set_float_signal,operationMode,0,signalName,(simxChar*)&signalValue,4,&returnValue);
	return(returnValue);
}

EXTAPI_DLLEXPORT simxInt simxSetIntegerSignal(const simxChar* signalName,simxInt signalValue,simxInt operationMode)
{
	simxInt returnValue;
	if (_communicationThreadRunning==0)
		return(simx_error_initialize_error_flag);
	if (operationMode==simx_opmode_remove)
		return(_removeCommandReply_string(simx_cmd_set_integer_signal,signalName));
	signalValue=extApi_endianConversionInt(signalValue);
	_exec_string_buffer(simx_cmd_set_integer_signal,operationMode,0,signalName,(simxChar*)&signalValue,4,&returnValue);
	return(returnValue);
}

EXTAPI_DLLEXPORT simxInt simxSetStringSignal(const simxChar* signalName,const simxChar* signalValue,simxInt signalLength,simxInt operationMode)
{
	simxInt returnValue;
	if (_communicationThreadRunning==0)
		return(simx_error_initialize_error_flag);
	if (operationMode==simx_opmode_remove)
		return(_removeCommandReply_string(simx_cmd_set_string_signal,signalName));
	_exec_string_buffer(simx_cmd_set_string_signal,operationMode,0,signalName,(simxChar*)signalValue,signalLength,&returnValue);
	return(returnValue);
}

EXTAPI_DLLEXPORT simxInt simxGetObjectFloatParameter(simxInt objectHandle,simxInt parameterID,simxFloat* parameterValue,simxInt operationMode)
{
	simxChar* dataPointer;
	simxInt returnValue;
	if (_communicationThreadRunning==0)
		return(simx_error_initialize_error_flag);
	if (operationMode==simx_opmode_remove)
		return(_removeCommandReply_intint(simx_cmd_get_object_float_parameter,objectHandle,parameterID));
	dataPointer=_exec_intint(simx_cmd_get_object_float_parameter,operationMode,0,objectHandle,parameterID,&returnValue);
	if ((dataPointer!=0)&&(returnValue==0))
		parameterValue[0]=_readPureDataFloat(dataPointer,0,0);
	return(returnValue);
}

EXTAPI_DLLEXPORT simxInt simxSetObjectFloatParameter(simxInt objectHandle,simxInt parameterID,simxFloat parameterValue,simxInt operationMode)
{
	simxInt returnValue;
	if (_communicationThreadRunning==0)
		return(simx_error_initialize_error_flag);
	if (operationMode==simx_opmode_remove)
		return(_removeCommandReply_intint(simx_cmd_set_object_float_parameter,objectHandle,parameterID));
	parameterValue=extApi_endianConversionFloat(parameterValue);
	_exec_intint_buffer(simx_cmd_set_object_float_parameter,operationMode,0,objectHandle,parameterID,(simxChar*)&parameterValue,4,&returnValue);
	return(returnValue);
}

EXTAPI_DLLEXPORT simxInt simxGetObjectIntParameter(simxInt objectHandle,simxInt parameterID,simxInt* parameterValue,simxInt operationMode)
{
	simxChar* dataPointer;
	simxInt returnValue;
	if (_communicationThreadRunning==0)
		return(simx_error_initialize_error_flag);
	if (operationMode==simx_opmode_remove)
		return(_removeCommandReply_intint(simx_cmd_get_object_int_parameter,objectHandle,parameterID));
	dataPointer=_exec_intint(simx_cmd_get_object_int_parameter,operationMode,0,objectHandle,parameterID,&returnValue);
	if ((dataPointer!=0)&&(returnValue==0))
		parameterValue[0]=_readPureDataInt(dataPointer,0,0);
	return(returnValue);
}

EXTAPI_DLLEXPORT simxInt simxSetObjectIntParameter(simxInt objectHandle,simxInt parameterID,simxInt parameterValue,simxInt operationMode)
{
	simxInt returnValue;
	if (_communicationThreadRunning==0)
		return(simx_error_initialize_error_flag);
	if (operationMode==simx_opmode_remove)
		return(_removeCommandReply_intint(simx_cmd_set_object_int_parameter,objectHandle,parameterID));
	parameterValue=extApi_endianConversionInt(parameterValue);
	_exec_intint_buffer(simx_cmd_set_object_int_parameter,operationMode,0,objectHandle,parameterID,(simxChar*)&parameterValue,4,&returnValue);
	return(returnValue);
}

EXTAPI_DLLEXPORT simxInt simxGetModelProperty(simxInt objectHandle,simxInt* prop,simxInt operationMode)
{
	simxChar* dataPointer;
	simxInt returnValue;
	if (_communicationThreadRunning==0)
		return(simx_error_initialize_error_flag);
	if (operationMode==simx_opmode_remove)
		return(_removeCommandReply_int(simx_cmd_get_model_property,objectHandle));
	dataPointer=_exec_int(simx_cmd_get_model_property,operationMode,0,objectHandle,&returnValue);
	if ((dataPointer!=0)&&(returnValue==0))
		prop[0]=_readPureDataInt(dataPointer,0,0);
	return(returnValue);
}

EXTAPI_DLLEXPORT simxInt simxSetModelProperty(simxInt objectHandle,simxInt prop,simxInt operationMode)
{
	simxInt returnValue;
	if (_communicationThreadRunning==0)
		return(simx_error_initialize_error_flag);
	if (operationMode==simx_opmode_remove)
		return(_removeCommandReply_int(simx_cmd_set_model_property,objectHandle));
	_exec_int_int(simx_cmd_set_model_property,operationMode,0,objectHandle,prop,&returnValue);
	return(returnValue);
}

EXTAPI_DLLEXPORT simxInt simxRMLPosition(simxInt dofs,simxDouble timeStep,simxInt flags,const simxDouble* currentPosVelAccel,const simxDouble* maxVelAccelJerk,const simxChar* selection,const simxDouble* targetPosVel,simxInt* rmlState,simxDouble* newPosVelAccel,simxInt operationMode)
{
	simxChar* dataPointer;
	simxInt returnValue,dataBufferSize,off,i;
	simxChar* dataBuffer;
	if (_communicationThreadRunning==0)
		return(simx_error_initialize_error_flag);
	if (operationMode==simx_opmode_remove)
		return(_removeCommandReply_null(simx_cmd_rml_position));

	// First prepare the data buffer to send:
	dataBufferSize=4+8+24*dofs+24*dofs+dofs+16*dofs+4;
	dataBuffer=extApi_allocateBuffer(dataBufferSize);
	off=0;

	// dofs
	((simxInt*)(dataBuffer+off))[0]=extApi_endianConversionInt(dofs);
	off+=4;

	// timeStep
	((simxDouble*)(dataBuffer+off))[0]=extApi_endianConversionDouble(timeStep);
	off+=8;

	// currentPosVelAccel
	for (i=0;i<dofs;i++)
	{
		((simxDouble*)(dataBuffer+off))[0]=extApi_endianConversionDouble(currentPosVelAccel[0+i]);
		off+=8;
	}
	for (i=0;i<dofs;i++)
	{
		((simxDouble*)(dataBuffer+off))[0]=extApi_endianConversionDouble(currentPosVelAccel[dofs+i]);
		off+=8;
	}
	for (i=0;i<dofs;i++)
	{
		((simxDouble*)(dataBuffer+off))[0]=extApi_endianConversionDouble(currentPosVelAccel[2*dofs+i]);
		off+=8;
	}

	// maxVelAccelJerk
	for (i=0;i<dofs;i++)
	{
		((simxDouble*)(dataBuffer+off))[0]=extApi_endianConversionDouble(maxVelAccelJerk[0+i]);
		off+=8;
	}
	for (i=0;i<dofs;i++)
	{
		((simxDouble*)(dataBuffer+off))[0]=extApi_endianConversionDouble(maxVelAccelJerk[dofs+i]);
		off+=8;
	}
	for (i=0;i<dofs;i++)
	{
		((simxDouble*)(dataBuffer+off))[0]=extApi_endianConversionDouble(maxVelAccelJerk[2*dofs+i]);
		off+=8;
	}

	// selection
	for (i=0;i<dofs;i++)
	{
		((simxChar*)(dataBuffer+off))[0]=selection[0+i];
		off++;
	}

	// targetPosVel
	for (i=0;i<dofs;i++)
	{
		((simxDouble*)(dataBuffer+off))[0]=extApi_endianConversionDouble(targetPosVel[0+i]);
		off+=8;
	}
	for (i=0;i<dofs;i++)
	{
		((simxDouble*)(dataBuffer+off))[0]=extApi_endianConversionDouble(targetPosVel[dofs+i]);
		off+=8;
	}

	((simxInt*)(dataBuffer+off))[0]=extApi_endianConversionInt(flags);
	off+=4;


	dataPointer=_exec_int_buffer(simx_cmd_rml_position,operationMode,0,0,dataBuffer,dataBufferSize,&returnValue);
	extApi_releaseBuffer(dataBuffer);

	if ((dataPointer!=0)&&(returnValue==0))
	{
		off=0;
		rmlState[0]=extApi_endianConversionInt(((simxInt*)(dataPointer+off))[0]);
		off+=4;
		for (i=0;i<dofs;i++)
		{
			newPosVelAccel[0+i]=extApi_endianConversionDouble(((simxDouble*)(dataPointer+off))[0]);
			off+=8;
		}
		for (i=0;i<dofs;i++)
		{
			newPosVelAccel[dofs+i]=extApi_endianConversionDouble(((simxDouble*)(dataPointer+off))[0]);
			off+=8;
		}
		for (i=0;i<dofs;i++)
		{
			newPosVelAccel[2*dofs+i]=extApi_endianConversionDouble(((simxDouble*)(dataPointer+off))[0]);
			off+=8;
		}
	}

	return(returnValue);
}

EXTAPI_DLLEXPORT simxInt simxRMLVelocity(simxInt dofs,simxDouble timeStep,simxInt flags,const simxDouble* currentPosVelAccel,const simxDouble* maxAccelJerk,const simxChar* selection,const simxDouble* targetVel,simxInt* rmlState,simxDouble* newPosVelAccel,simxInt operationMode)
{
	simxChar* dataPointer;
	simxInt returnValue,dataBufferSize,off,i;
	simxChar* dataBuffer;
	if (_communicationThreadRunning==0)
		return(simx_error_initialize_error_flag);
	if (operationMode==simx_opmode_remove)
		return(_removeCommandReply_null(simx_cmd_rml_velocity));

	// First prepare the data buffer to send:
	dataBufferSize=4+8+24*dofs+16*dofs+dofs+8*dofs+4;
	dataBuffer=extApi_allocateBuffer(dataBufferSize);
	off=0;

	// dofs
	((simxInt*)(dataBuffer+off))[0]=extApi_endianConversionInt(dofs);
	off+=4;

	// timeStep
	((simxDouble*)(dataBuffer+off))[0]=extApi_endianConversionDouble(timeStep);
	off+=8;

	// currentPosVelAccel
	for (i=0;i<dofs;i++)
	{
		((simxDouble*)(dataBuffer+off))[0]=extApi_endianConversionDouble(currentPosVelAccel[0+i]);
		off+=8;
	}
	for (i=0;i<dofs;i++)
	{
		((simxDouble*)(dataBuffer+off))[0]=extApi_endianConversionDouble(currentPosVelAccel[dofs+i]);
		off+=8;
	}
	for (i=0;i<dofs;i++)
	{
		((simxDouble*)(dataBuffer+off))[0]=extApi_endianConversionDouble(currentPosVelAccel[2*dofs+i]);
		off+=8;
	}

	// maxAccelJerk
	for (i=0;i<dofs;i++)
	{
		((simxDouble*)(dataBuffer+off))[0]=extApi_endianConversionDouble(maxAccelJerk[0+i]);
		off+=8;
	}
	for (i=0;i<dofs;i++)
	{
		((simxDouble*)(dataBuffer+off))[0]=extApi_endianConversionDouble(maxAccelJerk[dofs+i]);
		off+=8;
	}

	// selection
	for (i=0;i<dofs;i++)
	{
		((simxChar*)(dataBuffer+off))[0]=selection[0+i];
		off++;
	}

	// targetVel
	for (i=0;i<dofs;i++)
	{
		((simxDouble*)(dataBuffer+off))[0]=extApi_endianConversionDouble(targetVel[0+i]);
		off+=8;
	}

	((simxInt*)(dataBuffer+off))[0]=extApi_endianConversionInt(flags);
	off+=4;

	dataPointer=_exec_int_buffer(simx_cmd_rml_velocity,operationMode,0,0,dataBuffer,dataBufferSize,&returnValue);
	extApi_releaseBuffer(dataBuffer);

	if ((dataPointer!=0)&&(returnValue==0))
	{
		off=0;
		rmlState[0]=extApi_endianConversionInt(((simxInt*)(dataPointer+off))[0]);
		off+=4;
		for (i=0;i<dofs;i++)
		{
			newPosVelAccel[0+i]=extApi_endianConversionDouble(((simxDouble*)(dataPointer+off))[0]);
			off+=8;
		}
		for (i=0;i<dofs;i++)
		{
			newPosVelAccel[dofs+i]=extApi_endianConversionDouble(((simxDouble*)(dataPointer+off))[0]);
			off+=8;
		}
		for (i=0;i<dofs;i++)
		{
			newPosVelAccel[2*dofs+i]=extApi_endianConversionDouble(((simxDouble*)(dataPointer+off))[0]);
			off+=8;
		}
	}
	return(returnValue);
}


#ifdef _Included_extApiJava

void substr(char *s, char *d, int start, int len)
{
	int i=start;
	while (i < (start+len))
	{
		//if (s[i]=='\0')
		//	d[i-start]='*';
		//else
			d[i-start]=s[i];
		i++;
	}
	d[i-start]='\0';
//	printf("i=%d\n",i);
}

JNIEXPORT jint JNICALL Java_remoteApi_simxStart(JNIEnv * env, jobject obj, jstring connAddr, jint connPort, jboolean waitUntil, jboolean doNotRecon, jint toInMs)
{
	const char *connectionAddress = env->GetStringUTFChars(connAddr, 0);
	simxInt connectionPort = connPort;
	simxChar waitUntilConnected = waitUntil ? 1 : 0;
	simxChar doNotReconnectOnceDisconnected = doNotRecon ? 1 : 0;
	simxInt timeOutInMs = toInMs;

	simxInt retVal = simxStart(connectionAddress, connectionPort, waitUntilConnected, doNotReconnectOnceDisconnected,timeOutInMs);
   	env->ReleaseStringUTFChars( connAddr, connectionAddress);

	return retVal;
}

JNIEXPORT void JNICALL Java_remoteApi_simxFinish  (JNIEnv *env, jobject obj)
{
	simxFinish();
}

JNIEXPORT jint JNICALL Java_remoteApi_simxGetConnectionId(JNIEnv *env, jobject obj)
{
	return simxGetConnectionId();
}


JNIEXPORT jint JNICALL Java_remoteApi_simxGetObjectHandle(JNIEnv *env, jobject obj, jstring objName, jobject hdl, jint opMode)
{
	const char *objectName = env->GetStringUTFChars(objName, 0);
	simxInt objectHandle;
	simxInt operationMode = opMode;
	simxInt retVal;
	retVal = simxGetObjectHandle(objectName, &objectHandle, operationMode);

	jclass cls = env->GetObjectClass(hdl);
	jmethodID mid = env->GetMethodID(cls, "setValue", "(I)V");
	env->CallVoidMethod(hdl, mid, objectHandle);

	env->ReleaseStringUTFChars(objName, objectName);
	
	return retVal;
}

JNIEXPORT jint JNICALL Java_remoteApi_simxGetJointPosition(JNIEnv *env, jobject obj, jint hdl, jobject pos, jint opMode)
{
	simxInt jointHandle = hdl;
	simxFloat position;
	simxInt operationMode = opMode;

	simxInt retVal = simxGetJointPosition(jointHandle, &position, operationMode);

      jclass cls = env->GetObjectClass(pos);
      jmethodID mid = env->GetMethodID(cls, "setValue", "(F)V");
	env->CallVoidMethod(pos, mid, position);

	return retVal;
}

JNIEXPORT jint JNICALL Java_remoteApi_simxSetJointPosition(JNIEnv *env, jobject obj, jint hdl, jfloat pos, jint opMode)
{
	simxInt jointHandle = hdl;
	simxFloat position = pos;
	simxInt operationMode = opMode;
	simxInt retVal = simxSetJointPosition(jointHandle, position, operationMode);
	
	return retVal;
}

JNIEXPORT jint JNICALL Java_remoteApi_simxGetObjectPosition(JNIEnv *env, jobject obj, jint hdl, jint rel, jobject pos, jint opMode)
{
	simxInt objectHandle = hdl;
	simxInt relativeToObjectHandle = rel;
	simxFloat position[3];
	simxInt operationMode = opMode;

	simxInt retVal = simxGetObjectPosition(objectHandle, relativeToObjectHandle, position, operationMode);

	jsize start = 0;
	jsize size = 3;
	jclass cls = env->GetObjectClass(pos);
	jmethodID mid = env->GetMethodID(cls, "getNewArray", "(I)[F");
	jfloatArray posArray = (jfloatArray)env->CallObjectMethod(pos, mid, size);
	env->SetFloatArrayRegion(posArray, start, size, (const jfloat *)position);

	return retVal;
}

JNIEXPORT jint JNICALL Java_remoteApi_simxSetObjectPosition(JNIEnv *env, jobject obj, jint hdl, jint rel, jobject pos, jint opMode)
{
	simxInt objectHandle = hdl;
	simxInt relativeToObjectHandle = rel;
	simxFloat position[3];

	jclass cls = env->GetObjectClass(pos);
	jmethodID mid = env->GetMethodID(cls, "getArray", "()[F");
	jfloatArray posArray = (jfloatArray)env->CallObjectMethod(pos, mid);
	env->GetFloatArrayRegion(posArray, 0, 3, (jfloat *)position);

	simxInt operationMode = opMode;

	simxInt retVal = simxSetObjectPosition(objectHandle, relativeToObjectHandle, position, operationMode);

	return retVal;
}


JNIEXPORT jint JNICALL Java_remoteApi_simxGetVisionSensorImage(JNIEnv *env, jobject obj, jint hdl, jobject res, jobject img, jint opts, jint opMode)
{

	simxInt sensorHandle = hdl;

	simxChar* image;
	simxChar options = (simxChar)opts;
	simxInt operationMode = opMode;
	simxInt resolution[2];

	simxInt retVal = simxGetVisionSensorImage(sensorHandle, resolution, &image, options, operationMode);

	if (retVal==0)
	{
		jclass cls = env->GetObjectClass(res);
		jmethodID mid = env->GetMethodID(cls, "getNewArray", "(I)[I");
		jintArray resArray = (jintArray)env->CallObjectMethod(res, mid, 2);
		env->SetIntArrayRegion(resArray, 0, 2, (jint *)resolution);

		jsize start = 0;
		jsize size = (options&1) ? (resolution[0]*resolution[1]) : (resolution[0]*resolution[1]*3);
		cls = env->GetObjectClass(img);
		mid = env->GetMethodID(cls, "getNewArray", "(I)[C");
		jcharArray imgArray = (jcharArray)env->CallObjectMethod(img, mid, size);
		env->SetCharArrayRegion(imgArray, start, size, (const jchar *)image);
	}

	return retVal;
}

JNIEXPORT jint JNICALL Java_remoteApi_simxSetVisionSensorImage(JNIEnv *env, jobject obj, jint hdl, jobject img, jint bufsize, jint opts, jint opMode)
{
	simxInt sensorHandle = hdl;
	simxInt bufferSize = bufsize;
	simxChar options = (simxChar)opts;
	simxInt operationMode = opMode;

	jchar* imgbuf=new jchar[bufferSize];
	jsize start = 0;
	jsize size = bufsize;	
	jclass cls = env->GetObjectClass(img);
	jmethodID mid = env->GetMethodID(cls, "getArray", "()[C");
	jcharArray imgArray = (jcharArray)env->CallObjectMethod(img, mid);
	env->GetCharArrayRegion(imgArray, start, size, imgbuf);

	simxInt retVal = simxSetVisionSensorImage(sensorHandle,  (simxChar*)imgbuf, bufferSize, options, operationMode);
	delete[] imgbuf; 

	return retVal;
}

JNIEXPORT jint JNICALL Java_remoteApi_simxGetJointMatrix(JNIEnv *env, jobject obj, jint hdl, jobject mtx, jint opMode)
{
	simxInt jointHandle = hdl;
	simxFloat matrix[12];
	simxInt operationMode = opMode;

	simxInt retVal = simxGetJointMatrix(jointHandle, matrix, operationMode);
	
	jsize start = 0;
	jsize size = 12;
	jclass cls = env->GetObjectClass(mtx);
	jmethodID mid = env->GetMethodID(cls, "getNewArray", "(I)[F");
	jfloatArray mtxArray = (jfloatArray)env->CallObjectMethod(mtx, mid, size);
	env->SetFloatArrayRegion(mtxArray, start, size, (const jfloat *)matrix);

	return retVal;
}


JNIEXPORT jint JNICALL Java_remoteApi_simxSetSphericalJointMatrix(JNIEnv *env, jobject obj, jint hdl, jobject mtx, jint opMode)
{
	simxInt jointHandle = hdl;
	simxInt operationMode = opMode;
	simxFloat matrix[12];

	jsize size = 12;
	jclass cls = env->GetObjectClass(mtx);
	jmethodID mid = env->GetMethodID(cls, "getArray", "()[F");
	jfloatArray mtxArray = (jfloatArray)env->CallObjectMethod(mtx, mid);
	env->GetFloatArrayRegion(mtxArray, 0, size, (jfloat *)matrix);
	
	simxInt retVal = simxSetSphericalJointMatrix(jointHandle, matrix, operationMode);

	return retVal;
}

JNIEXPORT jint JNICALL Java_remoteApi_simxSetJointTargetVelocity(JNIEnv *env, jobject obj, jint hdl, jfloat tv, jint opMode)
{
	simxInt jointHandle = hdl;
	simxFloat targetVelocity = tv;
	simxInt operationMode = opMode;

	simxInt retVal = simxSetJointTargetVelocity(jointHandle, targetVelocity, operationMode);
	return retVal;
}

JNIEXPORT jint JNICALL Java_remoteApi_simxSetJointTargetPosition(JNIEnv *env, jobject obj, jint hdl, jfloat tp, jint opMode)
{
	simxInt jointHandle = hdl;
	simxFloat targetPosition = tp;
	simxInt operationMode = opMode;

	simxInt retVal = simxSetJointTargetPosition(jointHandle, targetPosition, operationMode);
	return retVal;
}

JNIEXPORT jint JNICALL Java_remoteApi_simxJointGetForce(JNIEnv *env, jobject obj, jint hdl, jobject frc, jint opMode)
{
	simxInt jointHandle = hdl;
	simxFloat	force;
	simxInt operationMode = opMode;	

	simxInt retVal = simxJointGetForce(jointHandle, &force, operationMode);

	jclass cls = env->GetObjectClass(frc);
	jmethodID mid = env->GetMethodID(cls, "setValue", "(F)V");
	env->CallVoidMethod(frc, mid, force);

	return retVal;
}

JNIEXPORT jint JNICALL Java_remoteApi_simxSetJointForce(JNIEnv *env, jobject obj, jint hdl, jfloat frc, jint opMode)
{
	simxInt jointHandle = hdl;
	simxFloat force = frc;
	simxInt operationMode = opMode;

	simxInt retVal = simxSetJointForce(jointHandle, force, operationMode);

	return retVal;
}

JNIEXPORT jint JNICALL Java_remoteApi_simxReadForceSensor(JNIEnv *env, jobject obj, jint hdl, jobject st, jobject fv, jobject tv, jint opMode) 
{
	simxInt forceSensorHandle = hdl;
	simxInt operationMode = opMode;
	simxChar state;		
	simxFloat forceVector[4];
	simxFloat torqueVector[4];
		
	simxInt retVal = simxReadForceSensor(forceSensorHandle, (st==NULL) ? 0 : &state, (fv==NULL) ? 0 : forceVector, (tv==NULL) ? 0 : torqueVector, operationMode);

	if (st != NULL)
	{
		jclass cls = env->GetObjectClass(st);
		jmethodID mid = env->GetMethodID(cls, "setValue", "(I)V");
		env->CallVoidMethod(st, mid, state);	
	}

	jsize start = 0;
	jsize size = 4;

	if (fv != NULL)
	{
		jclass cls = env->GetObjectClass(fv);
		jmethodID mid = env->GetMethodID(cls, "getNewArray", "(I)[F");
		jfloatArray fvArray = (jfloatArray)env->CallObjectMethod(fv, mid, size);
		env->SetFloatArrayRegion(fvArray, start, size, (const jfloat *)forceVector);
	}

	if (tv != NULL)
	{		
		jclass cls = env->GetObjectClass(tv);
		jmethodID mid = env->GetMethodID(cls, "getNewArray", "(I)[F");
		jfloatArray tvArray = (jfloatArray)env->CallObjectMethod(tv, mid, size);
		env->SetFloatArrayRegion(tvArray, start, size, (const jfloat *)torqueVector);
	}

	return retVal;
}

JNIEXPORT jint JNICALL Java_remoteApi_simxBreakForceSensor(JNIEnv *env, jobject obj, jint hdl, jint opMode)
{
	simxInt forceSensorHandle = hdl;
	simxInt operationMode = opMode;
	
	simxInt retVal = simxBreakForceSensor(forceSensorHandle, operationMode);
	return retVal;
}


JNIEXPORT jint JNICALL Java_remoteApi_simxReadVisionSensor(JNIEnv *env, jobject obj, jint hdl, jobject ds, jobject av, jint opMode)
{
	simxInt sensorHandle = hdl;
	simxInt operationMode = opMode;
	simxChar detectionState;
	simxFloat* auxValues;
	simxInt* auxValuesCount;

	simxInt retVal = simxReadVisionSensor(sensorHandle, (ds == NULL) ? 0 : &detectionState, (av==NULL) ? 0 : &auxValues, (av==NULL) ? 0 : &auxValuesCount, operationMode);

	if (retVal==0)
	{
		if (ds != NULL)
		{
			jclass cls = env->GetObjectClass(ds);
			jmethodID mid = env->GetMethodID(cls, "setValue", "(Z)V");
			env->CallVoidMethod(ds, mid, (detectionState==1));
		}
		
		if (av != NULL && retVal==0)
		{
			jsize size = auxValuesCount[0];
			jclass cls = env->GetObjectClass(av);
			jmethodID mid = env->GetMethodID(cls, "getNewArray", "(I)[LFloatWA;");	
			jobjectArray avArray = (jobjectArray)env->CallObjectMethod(av, mid, size);
			int sizeTotal = 0;
			for (int i=0;i<size;i++)
			{

				jsize size1 = auxValuesCount[i+1];
				jobject o = env->GetObjectArrayElement(avArray, i);

				cls = env->FindClass("FloatWA");
				mid = env->GetMethodID(cls, "getNewArray", "(I)[F");		

				jfloatArray fArray = (jfloatArray)env->CallObjectMethod(o, mid, size1);
				jfloat* f1 = env->GetFloatArrayElements(fArray, 0);
				for (int k=0; k<size1; k++)	
				{
					f1[k] = auxValues[sizeTotal + k];
				}
				env->ReleaseFloatArrayElements(fArray, f1, 0);	
				sizeTotal += size1;
			}
			simxReleaseBuffer((simxChar*)auxValues);
			simxReleaseBuffer((simxChar*)auxValuesCount);
		}
	}

	return retVal;
}

JNIEXPORT jint JNICALL Java_remoteApi_simxGetObjectFloatParameter(JNIEnv *env, jobject obj, jint hdl, jint pi, jobject pv, jint opMode)
{
	simxInt objectHandle = hdl;
	simxInt parameterID = pi;
	simxInt operationMode = opMode;
	simxFloat parameterValue;

	simxInt retVal = simxGetObjectFloatParameter( objectHandle, parameterID, &parameterValue, operationMode);

	jclass cls = env->GetObjectClass(pv);
      jmethodID mid = env->GetMethodID(cls, "setValue", "(F)V");
	env->CallVoidMethod(pv, mid, parameterValue);

	return retVal;
}

JNIEXPORT jint JNICALL Java_remoteApi_simxSetObjectFloatParameter(JNIEnv *env, jobject obj, jint hdl, jint pid, jfloat pv, jint opMode)
{
	simxInt objectHandle = hdl;
	simxInt parameterID = pid;
	simxFloat parameterValue = pv;
	simxInt operationMode = opMode;

	simxInt retVal = simxSetObjectFloatParameter(objectHandle, parameterID, parameterValue, operationMode);
	return retVal;
}


JNIEXPORT jint JNICALL Java_remoteApi_simxGetObjectIntParameter(JNIEnv *env, jobject obj, jint hdl, jint pid, jobject pv, jint opMode)
{
	simxInt objectHandle = hdl;
	simxInt parameterID = pid;
	simxInt operationMode = opMode;
	simxInt parameterValue;

	simxInt retVal = simxGetObjectIntParameter(objectHandle, parameterID, &parameterValue, operationMode);

	jclass cls = env->GetObjectClass(pv);
      jmethodID mid = env->GetMethodID(cls, "setValue", "(I)V");
	env->CallVoidMethod(pv, mid, parameterValue);

	return retVal;
}


JNIEXPORT jint JNICALL Java_remoteApi_simxSetObjectIntParameter(JNIEnv *env, jobject obj, jint hdl, jint pid, jint pv, jint opMode)
{
	simxInt objectHandle = hdl;
	simxInt parameterID = pid;
	simxInt parameterValue = pv;
	simxInt operationMode = opMode;

	simxInt retVal = simxSetObjectIntParameter(objectHandle, parameterID, parameterValue, operationMode);
	return retVal;
}


JNIEXPORT jint JNICALL Java_remoteApi_simxGetModelProperty(JNIEnv *env, jobject obj, jint hdl, jobject prp, jint opMode)
{
	simxInt objectHandle = hdl;
	simxInt operationMode = opMode;
	simxInt prop;

	simxInt retVal = simxGetModelProperty(objectHandle, &prop, operationMode);

	jclass cls = env->GetObjectClass(prp);
	jmethodID mid = env->GetMethodID(cls, "setValue", "(I)V");
	env->CallVoidMethod(prp, mid, prop);

	return retVal;
}


JNIEXPORT jint JNICALL Java_remoteApi_simxSetModelProperty(JNIEnv *env, jobject obj, jint hdl, jint prp, jint opMode)
{
	simxInt objectHandle = hdl;
	simxInt prop = prp;
	simxInt operationMode = opMode;

	simxInt retVal = simxSetModelProperty(objectHandle, prop, operationMode);
	return retVal;
}

JNIEXPORT jint JNICALL Java_remoteApi_simxGetVisionSensorDepthBuffer(JNIEnv *env, jobject obj, jint hdl, jobject res, jobject buf, jint opMode)
{
	simxInt sensorHandle = hdl;
	simxInt operationMode = opMode;
	simxInt resolution[2];
	simxFloat* buffer;

	simxInt retVal = simxGetVisionSensorDepthBuffer(sensorHandle, resolution, &buffer, operationMode);

	if (retVal==0)
	{
		jsize start = 0;
		jsize size = resolution[0]*resolution[1];
		jclass cls = env->GetObjectClass(buf);
		jmethodID mid = env->GetMethodID(cls, "getNewArray", "(I)[F");
		jfloatArray bufArray = (jfloatArray)env->CallObjectMethod(buf, mid, size);	
		env->SetFloatArrayRegion(bufArray, start, size, (const jfloat*)buffer);

		size = 2;
		cls = env->GetObjectClass(res);
		mid = env->GetMethodID(cls, "getNewArray", "(I)[I");
		jintArray resArray = (jintArray)env->CallObjectMethod(res, mid, size);	
		env->SetIntArrayRegion(resArray, start, size, (const jint*)resolution);
	}

	return retVal;	
}

JNIEXPORT jint JNICALL Java_remoteApi_simxGetObjectChild(JNIEnv *env, jobject obj, jint hdl, jint ci, jobject coh, jint opMode)
{
	simxInt parentObjectHandle = hdl;
	simxInt	childIndex = ci;
	simxInt	childObjectHandle;
	simxInt operationMode = opMode;

	simxInt retVal = simxGetObjectChild(parentObjectHandle, childIndex, &childObjectHandle, operationMode);

	jclass cls = env->GetObjectClass(coh);
      jmethodID mid = env->GetMethodID(cls, "setValue", "(I)V");
	env->CallVoidMethod(coh, mid, childObjectHandle);

	return retVal;
}

JNIEXPORT jint JNICALL Java_remoteApi_simxGetObjectParent(JNIEnv *env, jobject obj, jint coh, jobject poh, jint opMode)
{
	simxInt childObjectHandle = coh;
	simxInt	parentObjectHandle;
	simxInt operationMode = opMode;

	simxInt retVal = simxGetObjectParent( childObjectHandle, &parentObjectHandle, operationMode);

	jclass cls = env->GetObjectClass(poh);
	jmethodID mid = env->GetMethodID(cls, "setValue", "(I)V");
	env->CallVoidMethod(poh, mid, parentObjectHandle);

	return retVal;
}


JNIEXPORT jint JNICALL Java_remoteApi_simxStartSimulation(JNIEnv *env, jobject obj, jint opMode)
{
	simxInt operationMode = opMode;

	simxInt retVal = simxStartSimulation(operationMode);
	return retVal;
}

JNIEXPORT jint JNICALL Java_remoteApi_simxPauseSimulation(JNIEnv *env, jobject obj, jint opMode)
{
	simxInt operationMode = opMode;

	simxInt retVal = simxPauseSimulation(operationMode);
	return retVal;
}

JNIEXPORT jint JNICALL Java_remoteApi_simxStopSimulation(JNIEnv *env, jobject obj, jint opMode)
{
	simxInt operationMode = opMode;	
	
	simxInt retVal = simxStopSimulation(operationMode);
	return retVal;
}

JNIEXPORT jint JNICALL Java_remoteApi_simxGetUISlider(JNIEnv *env, jobject obj, jint hdl, jint ubid, jobject pos, jint opMode)
{
	simxInt uiHandle = hdl;
	simxInt uiButtonID = ubid;
	simxInt operationMode = opMode;	
	simxInt position;

	simxInt retVal = simxGetUISlider(uiHandle, uiButtonID, &position, operationMode);

	jclass cls = env->GetObjectClass(pos);
	jmethodID mid = env->GetMethodID(cls, "setValue", "(I)V");
	env->CallVoidMethod(pos, mid, position);

	return retVal;
}

JNIEXPORT jint JNICALL Java_remoteApi_simxSetUISlider(JNIEnv *env, jobject obj, jint hdl, jint ubid, jint pos, jint opMode)
{
	simxInt uiHandle = hdl;
	simxInt uiButtonID = ubid;
	simxInt position = pos;
	simxInt operationMode = opMode;	
	
	simxInt retVal = simxSetUISlider(uiHandle, uiButtonID, position, operationMode);
	return retVal;
}

JNIEXPORT jint JNICALL Java_remoteApi_simxGetUIEventButton(JNIEnv *env, jobject obj, jint hdl, jobject uieb, jobject auxv, jint opMode)
{
	simxInt uiHandle = hdl;
	simxInt uiEventButtonID;
	simxInt auxValues[2];
	simxInt operationMode = opMode;	

	simxInt retVal = simxGetUIEventButton(uiHandle, &uiEventButtonID, auxValues, operationMode);

	jclass cls = env->GetObjectClass(uieb);
	jmethodID mid = env->GetMethodID(cls, "setValue", "(I)V");
	env->CallVoidMethod(uieb, mid, uiEventButtonID);

	jsize start = 0;
	jsize size = 2;
	cls = env->GetObjectClass(auxv);
	mid = env->GetMethodID(cls, "getNewArray", "(I)[I");
	jintArray auxvArray = (jintArray)env->CallObjectMethod(auxv, mid, size);
	env->SetIntArrayRegion(auxvArray, start, size, (const jint*)auxValues);

	return retVal;
}

JNIEXPORT jint JNICALL Java_remoteApi_simxGetUIButtonProperty(JNIEnv *env, jobject obj, jint hdl, jint uib, jobject prp, jint opMode)
{
	simxInt uiHandle = hdl;
	simxInt uiButtonID = uib;
	simxInt prop;
	simxInt operationMode = opMode;	

	simxInt retVal = simxGetUIButtonProperty(uiHandle, uiButtonID, &prop, operationMode);

	jclass cls = env->GetObjectClass(prp);
	jmethodID mid = env->GetMethodID(cls, "setValue", "(I)V");
	env->CallVoidMethod(prp, mid, prop);

	return retVal;
}

JNIEXPORT jint JNICALL Java_remoteApi_simxSetUIButtonProperty(JNIEnv *env, jobject obj, jint hdl, jint uib, jint prp, jint opMode)
{
	simxInt uiHandle = hdl;
	simxInt uiButtonID = uib;
	simxInt prop = prp;
	simxInt operationMode = opMode;

	simxInt retVal = simxSetUIButtonProperty( uiHandle, uiButtonID, prop, operationMode);

	return retVal;
}

JNIEXPORT jint JNICALL Java_remoteApi_simxAuxiliaryConsoleClose(JNIEnv *env, jobject obj, jint hdl, jint opMode)
{
	simxInt consoleHandle = hdl;
	simxInt operationMode = opMode;

	simxInt retVal = simxAuxiliaryConsoleClose(consoleHandle, operationMode);
	return retVal;
}


JNIEXPORT jint JNICALL Java_remoteApi_simxAuxiliaryConsoleShow(JNIEnv *env, jobject obj, jint hdl, jboolean shstate, jint opMode)
{
	simxInt consoleHandle = hdl;
	simxChar showState = shstate ? 1 : 0;
	simxInt operationMode = opMode;

	simxInt retVal = simxAuxiliaryConsoleShow( consoleHandle, showState, operationMode);
	return retVal;
}


JNIEXPORT jint JNICALL Java_remoteApi_simxGetObjectOrientation(JNIEnv *env, jobject obj, jint hdl, jint rtoHdl, jobject euA, jint opMode)
{
	simxInt objectHandle = hdl;
	simxInt relativeToObjectHandle = rtoHdl;
	simxFloat eulerAngles[3];
	simxInt operationMode = opMode;

	simxInt retVal = simxGetObjectOrientation(objectHandle, relativeToObjectHandle, eulerAngles, operationMode);

	jsize start = 0;
	jsize size = 3;
	jclass cls = env->GetObjectClass(euA);
	jmethodID mid = env->GetMethodID(cls, "getNewArray", "(I)[F");
	jfloatArray euArray = (jfloatArray)env->CallObjectMethod(euA, mid, size);
	env->SetFloatArrayRegion(euArray, start, size, eulerAngles);

	return retVal;
}


JNIEXPORT jint JNICALL Java_remoteApi_simxSetObjectParent(JNIEnv *env, jobject obj, jint hdl, jint po, jboolean kip, jint opMode)
{
	simxInt objectHandle = hdl;
	simxInt parentObject = po;
	simxChar keepInPlace = kip ? 1 : 0;
	simxInt operationMode = opMode;

	simxInt retVal = simxSetObjectParent(objectHandle, parentObject, keepInPlace, operationMode);
	return retVal;
}


JNIEXPORT jint JNICALL Java_remoteApi_simxGetArrayParameter(JNIEnv *env, jobject obj, jint pid, jobject pv, jint opMode)
{
	simxInt paramIdentifier = pid;
	simxInt operationMode = opMode;
	simxFloat paramValues[4];

	simxInt retVal = simxGetArrayParameter(paramIdentifier, paramValues, operationMode);

	jsize start = 0;
	jsize size = 4;
	jclass cls = env->GetObjectClass(pv);
	jmethodID mid = env->GetMethodID(cls, "getNewArray", "(I)[F");
	jfloatArray pvArray = (jfloatArray)env->CallObjectMethod(pv, mid, size);
	env->SetFloatArrayRegion(pvArray, start, size, paramValues);
	return retVal;
}


JNIEXPORT jint JNICALL Java_remoteApi_simxSetArrayParameter(JNIEnv *env, jobject obj, jint pid, jobject pv, jint opMode)
{
	simxInt paramIdentifier = pid;
	simxInt operationMode = opMode;

	jclass cls = env->GetObjectClass(pv);
	jmethodID mid = env->GetMethodID(cls, "getArray", "()[F");
	jfloatArray pvArray = (jfloatArray)env->CallObjectMethod(pv, mid);
	mid = env->GetMethodID(cls, "getLength", "()I");
	jint size = env->CallIntMethod(pv, mid);
	
	simxFloat* paramValues = new simxFloat[size];
	env->GetFloatArrayRegion(pvArray, 0, size, (jfloat *)paramValues);

	simxInt retVal = simxSetArrayParameter(paramIdentifier, (const simxFloat*) paramValues, operationMode);

	delete[] paramValues;
	return retVal;
}

JNIEXPORT jint JNICALL Java_remoteApi_simxGetIntegerParameter(JNIEnv *env, jobject obj, jint pi, jobject pv, jint opMode)
{
	simxInt paramIdentifier = pi;
	simxInt operationMode = opMode;
	simxInt paramValue;

	simxInt retVal = simxGetIntegerParameter(paramIdentifier, &paramValue, operationMode);

	jclass cls = env->GetObjectClass(pv);
	jmethodID mid = env->GetMethodID(cls, "setValue", "(I)V");
	env->CallVoidMethod(pv, mid, paramValue);

	return retVal;
}

JNIEXPORT jint JNICALL Java_remoteApi_simxSetIntegerParameter(JNIEnv *env, jobject obj, jint pi, jint pv, jint opMode)
{
	simxInt paramIdentifier = pi;
	simxInt paramValue = pv;
	simxInt operationMode = opMode;

	simxInt retVal = simxSetIntegerParameter(paramIdentifier, paramValue, operationMode);
	return retVal;
}

JNIEXPORT jint JNICALL Java_remoteApi_simxSetBooleanParameter(JNIEnv *env, jobject obj, jint pi, jboolean pv, jint opMode)
{
	simxInt paramIdentifier = pi;
	simxChar paramValue = pv ? 1 : 0;
	simxInt operationMode = opMode;

	simxInt retVal = simxSetBooleanParameter(paramIdentifier, paramValue, operationMode);
	return retVal;
}

JNIEXPORT jint JNICALL Java_remoteApi_simxGetDialogResult(JNIEnv *env, jobject obj, jint hdl, jobject res, jint opMode)
{
	simxInt dialogHandle = hdl;
	simxInt operationMode = opMode;
	simxInt result;

	simxInt retVal = simxGetDialogResult(dialogHandle, &result, operationMode);

	jclass cls = env->GetObjectClass(res);
	jmethodID mid = env->GetMethodID(cls, "setValue", "(I)V");
	env->CallVoidMethod(res, mid, result);

	return retVal;
}

JNIEXPORT jint JNICALL Java_remoteApi_simxSetFloatingParameter(JNIEnv *env, jobject obj, jint pi, jfloat pv, jint opMode)
{
	simxInt paramIdentifier = pi;
	simxFloat paramValue = pv;
	simxInt operationMode = opMode;

	simxInt retVal = simxSetFloatingParameter(paramIdentifier, paramValue, operationMode);
	return retVal;
}


JNIEXPORT jint JNICALL Java_remoteApi_simxRemoveObject(JNIEnv *env, jobject obj, jint hdl, jint opMode)
{
	simxInt objectHandle = hdl;
	simxInt operationMode = opMode;

	simxInt retVal = simxRemoveObject(objectHandle, operationMode);
	return retVal;
}


JNIEXPORT jint JNICALL Java_remoteApi_simxRemoveUI(JNIEnv *env, jobject obj, jint hdl, jint opMode)
{
	simxInt uiHandle = hdl;
	simxInt operationMode = opMode;

	simxInt retVal = simxRemoveUI(uiHandle, operationMode);
	return retVal;
}


JNIEXPORT jint JNICALL Java_remoteApi_simxCloseScene(JNIEnv *env, jobject obj, jint opMode)
{
	simxInt operationMode = opMode;

	simxInt retVal = simxCloseScene(operationMode);
	return retVal;
}

JNIEXPORT jint JNICALL Java_remoteApi_simxEndDialog(JNIEnv *env, jobject obj, jint hdl, jint opMode)
{
	simxInt dialogHandle = hdl;
	simxInt operationMode = opMode;

	simxInt retVal = simxEndDialog(dialogHandle, operationMode);
	return retVal;
}

JNIEXPORT jint JNICALL Java_remoteApi_simxReadDistance(JNIEnv *env, jobject obj, jint hdl, jobject md, jint opMode)
{
	simxInt distanceObjectHandle = hdl;
	simxInt operationMode = opMode;
	simxFloat minimumDistance;

	simxInt retVal = simxReadDistance(distanceObjectHandle, &minimumDistance, operationMode);

	jclass cls = env->GetObjectClass(md);
	jmethodID mid = env->GetMethodID(cls, "setValue", "(F)V");
	env->CallVoidMethod(md, mid, minimumDistance);
	
	return retVal;
}

JNIEXPORT jint JNICALL Java_remoteApi_simxGetFloatingParameter(JNIEnv *env, jobject obj, jint pi, jobject pv, jint opMode)
{
	simxInt paramIdentifier = pi;
	simxInt operationMode = opMode;
	simxFloat paramValue;

	simxInt retVal = simxGetFloatingParameter(paramIdentifier, &paramValue, operationMode);

	jclass cls = env->GetObjectClass(pv);
	jmethodID mid = env->GetMethodID(cls, "setValue", "(F)V");
	env->CallVoidMethod(pv, mid, paramValue);

	return retVal;
}

JNIEXPORT jint JNICALL Java_remoteApi_simxSetObjectOrientation(JNIEnv *env, jobject obj, jint hdl, jint rtoHdl, jobject euAngles, jint opMode)
{
	simxInt objectHandle = hdl;
	simxInt relativeToObjectHandle = rtoHdl;
	simxInt operationMode = opMode;
	simxFloat eulerAngles[3];

	jclass cls = env->GetObjectClass(euAngles);
	jmethodID mid = env->GetMethodID(cls, "getArray", "()[F");
	jfloatArray euArray = (jfloatArray)env->CallObjectMethod(euAngles, mid);
	mid = env->GetMethodID(cls, "getLength", "()I");
	jint size = env->CallIntMethod(euAngles, mid);
	env->GetFloatArrayRegion(euArray, 0, size, (jfloat *)eulerAngles);

	simxInt retVal = simxSetObjectOrientation(objectHandle, relativeToObjectHandle, eulerAngles, operationMode);


	return retVal;
}

JNIEXPORT jint JNICALL Java_remoteApi_simxReadProximitySensor(JNIEnv *env, jobject obj, jint hdl, jobject ds, jobject dp, jobject doh, jobject dsnv, jint opMode)
{
	simxInt sensorHandle = hdl;
	simxInt operationMode = opMode;
	simxChar* detectionState;
	simxFloat* detectedPoint;
	simxInt detectedObjectHandle;
	simxFloat* detectedSurfaceNormalVector;

	if (ds != NULL)
		detectionState = new simxChar[1];
	if (dp != NULL)
		detectedPoint = new simxFloat[3];
	if (dsnv != NULL)
		detectedSurfaceNormalVector = new simxFloat[3];	

	simxInt retVal = simxReadProximitySensor( sensorHandle, (ds==NULL) ? 0 : detectionState, (dp==NULL) ? 0 : detectedPoint, (doh==NULL) ? 0 : &detectedObjectHandle, (dsnv==NULL) ? 0 : detectedSurfaceNormalVector, operationMode);	

	if (ds != NULL)
	{
		jclass cls = env->GetObjectClass(ds);
		jmethodID mid = env->GetMethodID(cls, "setValue", "(Z)V");
		env->CallVoidMethod( ds, mid, (detectionState[0]==1) );
		delete[] detectionState;
	}
	if (dp != NULL)
	{
		jclass cls = env->GetObjectClass(dp);
		jmethodID mid = env->GetMethodID(cls, "getNewArray", "(I)[F");
		jint size = 3;
		jfloatArray dpArray = (jfloatArray)env->CallObjectMethod(dp, mid, size);
		env->SetFloatArrayRegion(dpArray, 0, size, (jfloat *)detectedPoint);
		delete[] detectedPoint;
	}
	if (doh != NULL)
	{
		jclass cls = env->GetObjectClass(doh);
		jmethodID mid = env->GetMethodID(cls, "setValue", "(I)V");
		env->CallVoidMethod( doh, mid, detectedObjectHandle );
	}
	if (dsnv != NULL)
	{
		jclass cls = env->GetObjectClass(dsnv);
		jmethodID mid = env->GetMethodID(cls, "getNewArray", "(I)[F");
		jint size = 3;
		jfloatArray dsnvArray = (jfloatArray)env->CallObjectMethod(dsnv, mid, size);
		env->SetFloatArrayRegion(dsnvArray, 0, size, (jfloat *)detectedSurfaceNormalVector);
		delete[] detectedSurfaceNormalVector;
	}
	
	return retVal;
}


JNIEXPORT jint JNICALL Java_remoteApi_simxLoadModel(JNIEnv *env, jobject obj, jstring mpn, jint opts, jobject hdl, jint opMode)
{
	const simxChar *modelPathAndName = (simxChar*)env->GetStringUTFChars(mpn, 0);
	simxChar options = (simxChar)opts;
	simxInt baseHandle;
	simxInt operationMode = opMode;

	simxInt retVal = simxLoadModel(modelPathAndName, options, &baseHandle, operationMode);

	jclass cls = env->GetObjectClass(hdl);
	jmethodID mid = env->GetMethodID(cls, "setValue", "(I)V");
	env->CallVoidMethod( hdl, mid, baseHandle);
   	env->ReleaseStringUTFChars( mpn, modelPathAndName);
	return retVal;
}


JNIEXPORT jint JNICALL Java_remoteApi_simxLoadUI(JNIEnv *env, jobject obj, jstring uipan, jint opts, jobject uih, jint opMode)
{
	const simxChar *uiPathAndName = (simxChar*)env->GetStringUTFChars(uipan, 0);
	simxChar options = (simxChar)opts;
	simxInt count;
	simxInt** uiHandles = new simxInt*[1];
	simxInt operationMode = opMode;


	simxInt retVal = simxLoadUI(uiPathAndName, options, &count, uiHandles, operationMode);
	
   	env->ReleaseStringUTFChars( uipan, uiPathAndName);

	if (retVal==0)
	{
		jsize start = 0;
		jsize size = count;
		jclass cls = env->GetObjectClass(uih);
		jmethodID mid = env->GetMethodID(cls, "getNewArray", "(I)[I");
		jintArray uihArray = (jintArray)env->CallObjectMethod(uih, mid, size);	
		env->SetIntArrayRegion(uihArray, start, size, (const jint*)uiHandles[0]);
		simxReleaseBuffer((simxChar*)uiHandles[0]);
	}
	delete[] uiHandles;

	return retVal;
}

JNIEXPORT jint JNICALL Java_remoteApi_simxLoadScene(JNIEnv *env, jobject obj, jstring scpan, jint opts, jint opMode)
{
	const simxChar *scenePathAndName = (simxChar*)env->GetStringUTFChars(scpan, 0);
	simxChar options = (simxChar)opts;
	simxInt operationMode = opMode;

	simxInt retVal = simxLoadScene(scenePathAndName, options, operationMode);

	env->ReleaseStringUTFChars( scpan, scenePathAndName );
	return retVal;
}

JNIEXPORT jint JNICALL Java_remoteApi_simxGetUIHandle(JNIEnv *env, jobject obj, jstring uin, jobject hdl, jint opMode)
{
	const simxChar *uiName = (simxChar*)env->GetStringUTFChars(uin, 0);
	simxInt handle;
	simxInt operationMode = opMode;

	simxInt retVal = simxGetUIHandle(uiName, &handle, operationMode);

	jclass cls = env->GetObjectClass(hdl);
	jmethodID mid = env->GetMethodID(cls, "setValue", "(I)V");
	env->CallVoidMethod( hdl, mid, handle);

   	env->ReleaseStringUTFChars( uin, uiName);
	return retVal;
}

JNIEXPORT jint JNICALL Java_remoteApi_simxAddStatusbarMessage(JNIEnv *env, jobject obj, jstring msg, jint opMode)
{
	const simxChar *message = (simxChar*)env->GetStringUTFChars(msg, 0);
	simxInt operationMode = opMode;

	simxInt retVal = simxAddStatusbarMessage(message, operationMode);
   	env->ReleaseStringUTFChars( msg, message);
	return retVal;
}

JNIEXPORT jint JNICALL Java_remoteApi_simxAuxiliaryConsoleOpen(JNIEnv *env, jobject obj, jstring t, jint ml, jint m, jobject pos, jobject sz, jobject tc, jobject bc, jobject ch, jint opMode)
{
	const simxChar *title = (simxChar*)env->GetStringUTFChars(t, 0);
	simxInt maxLines = ml;
	simxInt mode = m;
	simxInt position[2];
	simxInt size[2];
	simxFloat textColor[3];
	simxFloat backgroundColor[3];
	simxInt consoleHandle;
	simxInt operationMode = opMode;

	if (pos != NULL)
	{
		jclass cls = env->GetObjectClass(pos);
		jmethodID mid = env->GetMethodID(cls, "getArray", "()[I");
		jintArray posArray = (jintArray)env->CallObjectMethod(pos, mid);
		env->GetIntArrayRegion(posArray, 0, 2, (jint *)position);
	}

	if (sz != NULL)
	{
		jclass cls = env->GetObjectClass(sz);
		jmethodID mid = env->GetMethodID(cls, "getArray", "()[I");
		jintArray szArray = (jintArray)env->CallObjectMethod(sz, mid);
		env->GetIntArrayRegion(szArray, 0, 2, (jint *)size);
	}

	if (tc != NULL)
	{
		jclass cls = env->GetObjectClass(tc);
		jmethodID mid = env->GetMethodID(cls, "getArray", "()[F");
		jfloatArray tcArray = (jfloatArray)env->CallObjectMethod(tc, mid);
		env->GetFloatArrayRegion(tcArray, 0, 3, (jfloat *)textColor);
	}

	if (bc != NULL)
	{	
		jclass cls = env->GetObjectClass(bc);
		jmethodID mid = env->GetMethodID(cls, "getArray", "()[F");
		jfloatArray bcArray = (jfloatArray)env->CallObjectMethod(bc, mid);
		env->GetFloatArrayRegion(bcArray, 0, 3, (jfloat *)backgroundColor);
	}

	simxInt retVal = simxAuxiliaryConsoleOpen(title, maxLines, mode, (pos==NULL) ? 0 : position, (sz == NULL) ? 0 : size, (tc == NULL) ? 0 : textColor, (bc == NULL) ? 0 : backgroundColor, &consoleHandle, operationMode);

	jclass cls = env->GetObjectClass(ch);
	jmethodID mid = env->GetMethodID(cls, "setValue", "(I)V");
	env->CallVoidMethod( ch, mid, consoleHandle);

   	env->ReleaseStringUTFChars( t, title);
	return retVal;
}

JNIEXPORT jint JNICALL Java_remoteApi_simxAuxiliaryConsolePrint(JNIEnv *env, jobject obj, jint ch, jstring t, jint opMode)
{
	const simxChar *txt = t==NULL ? 0 : (simxChar*)env->GetStringUTFChars(t, 0);
	simxInt consoleHandle = ch;
	simxInt operationMode = opMode;

	simxInt retVal = simxAuxiliaryConsolePrint(consoleHandle, txt, operationMode);
   	if (t != NULL)
		env->ReleaseStringUTFChars( t, txt);
	return retVal;
}

JNIEXPORT jint JNICALL Java_remoteApi_simxSetUIButtonLabel(JNIEnv *env, jobject obj, jint uih, jint uibi, jstring usl, jstring dsl, jint opMode)
{
	simxInt uiHandle = uih;
	simxInt uiButtonID = uibi;
	const simxChar *upStateLabel = (simxChar*)env->GetStringUTFChars(usl, 0);
	const simxChar *downStateLabel = (simxChar*)env->GetStringUTFChars(dsl, 0);
	simxInt operationMode = opMode;

	simxInt retVal = simxSetUIButtonLabel(uiHandle, uiButtonID, upStateLabel, downStateLabel, operationMode);

   	env->ReleaseStringUTFChars( usl, upStateLabel );
   	env->ReleaseStringUTFChars( dsl, downStateLabel );
	return retVal;
}

JNIEXPORT jint JNICALL Java_remoteApi_simxGetLastErrors(JNIEnv *env, jobject obj, jobject es, jint opMode)
{
	simxChar** errorStrings = new simxChar*[1];
	simxInt errorCnt;
	simxInt operationMode = opMode;

	simxInt retVal = simxGetLastErrors(&errorCnt, errorStrings, operationMode);

	if (retVal==0)
	{
		jclass cls = env->GetObjectClass(es);
		jmethodID mid = env->GetMethodID(cls, "getNewArray", "(I)[Ljava/lang/String;");
		jobjectArray esArray = (jobjectArray)env->CallObjectMethod( es, mid, errorCnt);

		int slen = 0;
		for(int i=0;i<errorCnt;i++) {
			jstring s = env->NewStringUTF((const char*)errorStrings[0]+slen);
			env->SetObjectArrayElement(esArray, i, s);
			slen += (env->GetStringLength(s) + 1);
		}
	}

	delete[] errorStrings;	
	return retVal;
}

JNIEXPORT jint JNICALL Java_remoteApi_simxGetBooleanParameter(JNIEnv *env, jobject obj, jint pi, jobject pv, jint opMode)
{
	simxInt paramIdentifier = pi;
	simxChar paramValue;
	simxInt operationMode = opMode;

	simxInt retVal = simxGetBooleanParameter(paramIdentifier, &paramValue, operationMode);

	jclass cls = env->GetObjectClass(pv);
	jmethodID mid = env->GetMethodID(cls, "setValue", "(Z)V");
	env->CallVoidMethod( pv, mid, (paramValue==1));
	
	return retVal;
}

JNIEXPORT jint JNICALL Java_remoteApi_simxGetStringParameter(JNIEnv *env, jobject obj, jint pi, jobject pv, jint opMode)
{
	simxInt paramIdentifier = pi;
	simxChar** paramValue = new simxChar*[1];
	simxInt operationMode = opMode;

	simxInt retVal = simxGetStringParameter(paramIdentifier, paramValue, operationMode);

	if (retVal==0)
	{
		jclass cls = env->GetObjectClass(pv);
		jmethodID mid = env->GetMethodID(cls, "setValue", "(Ljava/lang/String;)V");
		jstring s = env->NewStringUTF((const char*)paramValue[0]);
		env->CallVoidMethod( pv, mid, s);
	}

	delete[] paramValue;

	return retVal;
}

JNIEXPORT jint JNICALL Java_remoteApi_simxGetCollisionHandle(JNIEnv *env, jobject obj, jstring con, jobject hdl, jint opMode)
{
	const simxChar *collisionObjectName = (simxChar*)env->GetStringUTFChars(con, 0);
	simxInt handle;
	simxInt operationMode = opMode;

	simxInt retVal = simxGetCollisionHandle(collisionObjectName, &handle, operationMode);

	env->ReleaseStringUTFChars(con, collisionObjectName);

	jclass cls = env->GetObjectClass(hdl);
	jmethodID mid = env->GetMethodID(cls, "setValue", "(I)V");
	env->CallVoidMethod( hdl, mid, handle);

	return retVal;
}


JNIEXPORT jint JNICALL Java_remoteApi_simxGetDistanceHandle(JNIEnv *env, jobject obj, jstring don, jobject hdl, jint opMode)
{
	const simxChar *distanceObjectName = (simxChar*)env->GetStringUTFChars(don, 0);
	simxInt handle;
	simxInt operationMode = opMode;

	simxInt retVal = simxGetDistanceHandle(distanceObjectName, &handle, operationMode);

	env->ReleaseStringUTFChars(don, distanceObjectName);

	jclass cls = env->GetObjectClass(hdl);
	jmethodID mid = env->GetMethodID(cls, "setValue", "(I)V");
	env->CallVoidMethod( hdl, mid, handle);

	return retVal;
}


JNIEXPORT jint JNICALL Java_remoteApi_simxReadCollision(JNIEnv *env, jobject obj, jint hdl, jobject cs, jint opMode)
{
	simxInt collisionObjectHandle = hdl;
	simxChar collisionState;
	simxInt operationMode = opMode;

	simxInt retVal = simxReadCollision( collisionObjectHandle, &collisionState, operationMode);

	jclass cls = env->GetObjectClass(cs);
	jmethodID mid = env->GetMethodID(cls, "setValue", "(Z)V");
	env->CallVoidMethod( cs, mid, (collisionState==1));

	return retVal;
}


JNIEXPORT jint JNICALL Java_remoteApi_simxGetObjects(JNIEnv *env, jobject obj, jint ot, jobject oh, jint opMode)
{
	simxInt objectType = ot;
	simxInt objectCount;
	simxInt** objectHandles = new simxInt*[1];
	simxInt operationMode = opMode;

	simxInt retVal = simxGetObjects(objectType, &objectCount, objectHandles, operationMode);

	if (retVal==0)
	{
		jsize start = 0;
		jsize size = objectCount;
		jclass cls = env->GetObjectClass(oh);
		jmethodID mid = env->GetMethodID(cls, "getNewArray", "(I)[I");
		jintArray ohArray = (jintArray)env->CallObjectMethod(oh, mid, size);	
		env->SetIntArrayRegion(ohArray, start, size, (const jint*)objectHandles[0]);
	}

	delete[] objectHandles;
	return retVal;
}


JNIEXPORT jint JNICALL Java_remoteApi_simxDisplayDialog(JNIEnv *env, jobject obj, jstring ttxt, jstring mtxt, jint dt, jstring itxt, jobject tc, jobject dc, jobject dh, jobject hdl, jint opMode)
{
	const simxChar *titleText = (simxChar*)env->GetStringUTFChars(ttxt, 0);
	const simxChar *mainText = (simxChar*)env->GetStringUTFChars(mtxt, 0);
	const simxChar *initialText = (simxChar*)env->GetStringUTFChars(itxt, 0);
	simxInt dialogType = dt;

	jsize start = 0;
	jsize size = 6;		
	simxFloat titleColors[6];
	if (tc != NULL)
	{
		jclass cls = env->GetObjectClass(tc);
		jmethodID mid = env->GetMethodID(cls, "getArray", "()[F");
		jfloatArray tcArray = (jfloatArray)env->CallObjectMethod(tc, mid);	
		env->GetFloatArrayRegion(tcArray, start, size, (jfloat*)titleColors);
	}

	simxFloat dialogColors[6];
	if (dc != NULL)
	{
		jclass cls = env->GetObjectClass(dc);
		jmethodID mid = env->GetMethodID(cls, "getArray", "()[F");
		jfloatArray dcArray = (jfloatArray)env->CallObjectMethod(dc, mid);	
		env->GetFloatArrayRegion(dcArray, start, size, (jfloat*)dialogColors);
	}
	
	simxInt dialogHandle;
	simxInt uiHandle;
	simxInt operationMode = opMode;

	simxInt retVal = simxDisplayDialog(titleText, mainText, dialogType, initialText, (tc==NULL) ? 0 : titleColors, (dc==NULL) ? 0 : dialogColors, &dialogHandle, &uiHandle, operationMode);

	env->ReleaseStringUTFChars(ttxt, titleText);
	env->ReleaseStringUTFChars(mtxt, mainText);
	env->ReleaseStringUTFChars(itxt, initialText);

	jclass cls = env->GetObjectClass(dh);
	jmethodID mid = env->GetMethodID(cls, "setValue", "(I)V");
	env->CallVoidMethod( dh, mid, dialogHandle);

	cls = env->GetObjectClass(hdl);
	mid = env->GetMethodID(cls, "setValue", "(I)V");
	env->CallVoidMethod( hdl, mid, uiHandle);

	return retVal;
}

JNIEXPORT jint JNICALL Java_remoteApi_simxGetDialogInput(JNIEnv *env, jobject obj, jint dh, jobject it, jint opMode)
{
	simxInt dialogHandle = dh;
	simxChar **inputText = new simxChar*[1]; 
	simxInt operationMode = opMode;

	simxInt retVal = simxGetDialogInput(dialogHandle, inputText, operationMode);

	if (retVal==0)
	{
		jclass cls = env->GetObjectClass(it);
		jmethodID mid = env->GetMethodID(cls, "setValue", "(Ljava/lang/String;)V");
		jstring s = env->NewStringUTF((const char*)inputText[0]);
		env->CallVoidMethod( it, mid, s );	
	}

	delete[] inputText;
	return retVal;
}

JNIEXPORT jint JNICALL Java_remoteApi_simxCopyPasteObjects(JNIEnv *env, jobject obj, jobject oh, jobject noh, jint opMode)
{
	jclass cls = env->GetObjectClass(oh);
	jmethodID mid = env->GetMethodID(cls, "getLength", "()I");
	jsize start = 0;
	jsize size = env->CallIntMethod( oh, mid );	
	simxInt* objectHandles = new simxInt[size];
	cls = env->GetObjectClass(noh);
	mid = env->GetMethodID(cls, "getArray", "()[I");
	jintArray ohArray = (jintArray)env->CallObjectMethod(oh, mid);	
	env->GetIntArrayRegion(ohArray, start, size, (jint*)objectHandles);

	simxInt objectCount = size;
	simxInt** newObjectHandles = new simxInt*[1];
	simxInt newObjectCount;
	simxInt operationMode = opMode;

	simxInt retVal = simxCopyPasteObjects((const simxInt*)objectHandles, objectCount, newObjectHandles, &newObjectCount, operationMode);

	if (retVal==0)
	{
		cls = env->GetObjectClass(noh);
		mid = env->GetMethodID(cls, "getNewArray", "(I)[I");
		jintArray nohArray = (jintArray)env->CallObjectMethod(noh, mid, newObjectCount);	
		env->SetIntArrayRegion( nohArray, start, newObjectCount, (const jint*)newObjectHandles[0] );
	}

	delete[] objectHandles;
	delete[] newObjectHandles;
	return retVal;
}

JNIEXPORT jint JNICALL Java_remoteApi_simxGetObjectSelection(JNIEnv *env, jobject obj, jobject oh, jint opMode)
{
	simxInt** objectHandles = new simxInt*[1];
	simxInt objectCount;
	simxInt operationMode = opMode;

	simxInt retVal = simxGetObjectSelection( objectHandles, &objectCount, operationMode);

	if (retVal==0)
	{
		jsize start = 0;
		jsize size = (jsize)objectCount;
		jclass cls = env->GetObjectClass(oh);
		jmethodID mid = env->GetMethodID(cls, "getNewArray", "(I)[I");
		jintArray ohArray = (jintArray)env->CallObjectMethod(oh, mid, size);	
		env->SetIntArrayRegion( ohArray, start, size, (const jint*)objectHandles[0] );
	}

	delete[] objectHandles;
	return retVal;
}


JNIEXPORT jint JNICALL Java_remoteApi_simxSetObjectSelection(JNIEnv *env, jobject obj, jobject hdl, jint opMode)
{
	jclass cls = env->GetObjectClass(hdl);
	jmethodID mid = env->GetMethodID(cls, "getLength", "()I");

	jsize start = 0;
	jsize size = env->CallIntMethod( hdl, mid );	

	simxInt* objectHandles = new simxInt[size];
	cls = env->GetObjectClass(hdl);
	mid = env->GetMethodID(cls, "getArray", "()[I");
	jintArray hdlArray = (jintArray)env->CallObjectMethod(hdl, mid);	
	env->GetIntArrayRegion(hdlArray, start, size, (jint*)objectHandles);

	simxInt objectCount = size;
	simxInt operationMode = opMode;

	simxInt retVal = simxSetObjectSelection(objectHandles, objectCount, operationMode);

	delete[] objectHandles;
	return retVal;
}

JNIEXPORT jint JNICALL Java_remoteApi_simxClearFloatSignal(JNIEnv *env, jobject obj, jstring sn, jint opMode)
{
	const simxChar *signalName = (simxChar*)env->GetStringUTFChars(sn, 0);
	simxInt operationMode = opMode;

	simxInt retVal = simxClearFloatSignal(signalName, operationMode);

	env->ReleaseStringUTFChars(sn, signalName);
	return retVal;
}


JNIEXPORT jint JNICALL Java_remoteApi_simxClearStringSignal(JNIEnv *env, jobject obj, jstring sn, jint opMode)
{
	const simxChar *signalName = (simxChar*)env->GetStringUTFChars(sn, 0);
	simxInt operationMode = opMode;

	simxInt retVal = simxClearStringSignal(signalName, operationMode);

	env->ReleaseStringUTFChars( sn, signalName);
	return retVal;
}


JNIEXPORT jint JNICALL Java_remoteApi_simxClearIntegerSignal(JNIEnv *env, jobject obj, jstring sn, jint opMode)
{
	const simxChar *signalName = (simxChar*)env->GetStringUTFChars(sn, 0);
	simxInt operationMode = opMode;

	simxInt retVal = simxClearIntegerSignal(signalName, operationMode);

	env->ReleaseStringUTFChars( sn, signalName);
	return retVal;
}


JNIEXPORT jint JNICALL Java_remoteApi_simxGetFloatSignal(JNIEnv *env, jobject obj, jstring sn, jobject sv, jint opMode)
{
	const simxChar *signalName = (simxChar*)env->GetStringUTFChars(sn, 0);
	simxFloat signalValue[1];
	simxInt operationMode = opMode;	

	simxInt retVal = simxGetFloatSignal(signalName, signalValue, operationMode);

	jclass cls = env->GetObjectClass(sv);
	jmethodID mid = env->GetMethodID(cls, "setValue", "(F)V");
	env->CallVoidMethod( sv, mid, signalValue[0]);

	env->ReleaseStringUTFChars( sn, signalName);
	return retVal;
}


JNIEXPORT jint JNICALL Java_remoteApi_simxGetIntegerSignal(JNIEnv *env, jobject obj, jstring sn, jobject sv, jint opMode)
{
	const simxChar *signalName = (simxChar*)env->GetStringUTFChars(sn, 0);
	simxInt signalValue;
	simxInt operationMode = opMode;

	simxInt retVal = simxGetIntegerSignal( signalName, &signalValue, operationMode);

	jclass cls = env->GetObjectClass(sv);
	jmethodID mid = env->GetMethodID(cls, "setValue", "(I)V");
	env->CallVoidMethod( sv, mid, signalValue);

   	env->ReleaseStringUTFChars( sn, signalName);
	
	return retVal;
}

jstring JNU_NewStringNative(JNIEnv *env, const char *str, int len)
{
	jstring result = NULL;
	jbyteArray bytes = 0;
     	if (env->EnsureLocalCapacity(2) < 0) {
		return NULL; /* out of memory error */
	}
	bytes = env->NewByteArray(len);
	if (bytes != NULL) {
		env->SetByteArrayRegion(bytes, 0, len,(jbyte *)str);
		jclass cls = env->FindClass("java/lang/String");
		jmethodID mid = env->GetMethodID(cls, "<init>", "([B)V");
		result = (jstring)env->NewObject(cls, mid, bytes);
		env->DeleteLocalRef(bytes);
	}

	return result;
}

JNIEXPORT jint JNICALL Java_remoteApi_simxGetStringSignal(JNIEnv *env, jobject obj, jstring sn, jobject sv, jint opMode)
{
	const simxChar *signalName = (simxChar*)env->GetStringUTFChars(sn, 0);
	simxChar* signalValue;
	simxInt signalLength;
	simxInt operationMode = opMode;

	simxInt retVal = simxGetStringSignal(signalName, &signalValue, &signalLength, operationMode);

	if (retVal==0)
	{
		if (signalLength>0)
		{
			jclass cls = env->GetObjectClass(sv);
			jmethodID mid = env->GetMethodID(cls, "setValue", "(Ljava/lang/String;)V");
			simxChar* sigValue = new simxChar[signalLength];
			substr( signalValue, sigValue, 0, signalLength);
			jstring s =  JNU_NewStringNative(env, (const char *)sigValue, signalLength);  //env->NewStringUTF((const char*)sigValue);
			env->CallVoidMethod( sv, mid, s );			
			delete[] sigValue;
		}
	}
	env->ReleaseStringUTFChars( sn, signalName);

	return retVal;
}

JNIEXPORT jint JNICALL Java_remoteApi_simxSetFloatSignal(JNIEnv *env, jobject obj, jstring sn, jfloat sv, jint opMode)
{
	const simxChar *signalName = (simxChar*)env->GetStringUTFChars(sn, 0);
	simxFloat signalValue = sv;
	simxInt operationMode = opMode;

	simxInt retVal = simxSetFloatSignal(signalName, signalValue, operationMode);

	env->ReleaseStringUTFChars( sn, signalName);
	return retVal;
}

JNIEXPORT jint JNICALL Java_remoteApi_simxSetIntegerSignal(JNIEnv *env, jobject obj, jstring sn, jint sv, jint opMode)
{
	const simxChar *signalName = (simxChar*)env->GetStringUTFChars(sn, 0);
	simxInt signalValue = sv;
	simxInt operationMode = opMode;

	simxInt retVal = simxSetIntegerSignal( signalName, signalValue, operationMode);
	env->ReleaseStringUTFChars( sn, signalName);
	return retVal;
}

JNIEXPORT jint JNICALL Java_remoteApi_simxSetStringSignal(JNIEnv *env, jobject obj, jstring sn, jstring sv, jint opMode)
{
	const simxChar *signalName = (simxChar*)env->GetStringUTFChars(sn, 0);
	const simxChar *signalValue = (simxChar*)env->GetStringUTFChars(sv, 0);

	simxInt signalLength = env->GetStringLength(sv);
	simxInt operationMode = opMode;

	simxInt retVal = simxSetStringSignal(signalName, signalValue, signalLength, operationMode);

	env->ReleaseStringUTFChars( sn, signalName);
	env->ReleaseStringUTFChars( sv, signalValue);
	return retVal;
}


JNIEXPORT jint JNICALL Java_remoteApi_simxGetPingTime(JNIEnv *env, jobject obj, jobject pt)
{
	simxInt pingTime;

	simxInt retVal = simxGetPingTime(&pingTime);

	jclass cls = env->GetObjectClass(pt);
	jmethodID mid = env->GetMethodID(cls, "setValue", "(I)V");
	env->CallVoidMethod( pt, mid, pingTime);

	return retVal;
}

JNIEXPORT jint JNICALL Java_remoteApi_simxGetLastCmdTime(JNIEnv *env, jobject obj)
{
	simxInt retVal = simxGetLastCmdTime();
	return retVal;	
}


JNIEXPORT jint JNICALL Java_remoteApi_simxSynchronousTrigger(JNIEnv *env, jobject obj)
{
	simxInt retVal = simxSynchronousTrigger();
	return retVal;	
}

JNIEXPORT jint JNICALL Java_remoteApi_simxSynchronous(JNIEnv *env, jobject obj, jboolean e)
{
	simxChar enable = e ? 1 : 0;
	simxInt retVal = simxSynchronous(enable);
	return retVal;
}

JNIEXPORT jint JNICALL Java_remoteApi_simxPauseCommunication(JNIEnv *env, jobject obj, jboolean e)
{
	simxChar enable = e ? 1 : 0;
	simxInt retVal = simxPauseCommunication(enable);
	return retVal;
}

JNIEXPORT jint JNICALL Java_remoteApi_simxGetInMessageInfo(JNIEnv *env, jobject obj, jint it, jobject i)
{
	simxInt infoType = it;
	simxInt info;
	simxInt retVal = simxGetInMessageInfo(infoType, &info);

	jclass cls = env->GetObjectClass(i);
	jmethodID mid = env->GetMethodID(cls, "setValue", "(I)V");
	env->CallVoidMethod( i, mid, info);
	return retVal;	
}


JNIEXPORT jint JNICALL Java_remoteApi_simxGetOutMessageInfo(JNIEnv *env, jobject obj, jint it, jobject i)
{
	simxInt infoType = it;
	simxInt info;
	simxInt retVal = simxGetOutMessageInfo(infoType, &info);

	jclass cls = env->GetObjectClass(i);
	jmethodID mid = env->GetMethodID(cls, "setValue", "(I)V");
	env->CallVoidMethod( i, mid, info);
	return retVal;
}

JNIEXPORT jint JNICALL Java_remoteApi_simxTransferFile(JNIEnv *env, jobject obj, jstring fpan, jstring fnss, jint to, jint opMode)
{
	const simxChar *filePathAndName = (simxChar*)env->GetStringUTFChars(fpan, 0);
	const simxChar *fileName_serverSide = (simxChar*)env->GetStringUTFChars(fnss, 0);
	simxInt timeOut = to;
	simxInt operationMode = opMode;

	simxInt retVal = simxTransferFile(filePathAndName, fileName_serverSide, timeOut, operationMode);
	
	return retVal;
}

JNIEXPORT jint JNICALL Java_remoteApi_simxEraseFile(JNIEnv *env, jobject obj, jstring fnss, jint opMode)
{
	const simxChar *fileName_serverSide = (simxChar*)env->GetStringUTFChars(fnss, 0);
	simxInt operationMode = opMode;

	simxInt retVal = simxEraseFile(fileName_serverSide, operationMode);
	
	return retVal;

}

// dummy functions that can be deleted later

JNIEXPORT jint JNICALL Java_remoteApi_test(JNIEnv *env, jobject obj, jobject es, jobject t, jint opMode)
{

	simxChar** test = new simxChar*[1];
	test[0]  =  (simxChar*)"hello world\0We are the world\0Born in America\0";
	jclass cls = env->GetObjectClass(es);
	jmethodID mid = env->GetMethodID(cls, "getNewArray", "(I)[Ljava/lang/String;");
	jobjectArray esArray = (jobjectArray)env->CallObjectMethod( es, mid, 3);

	int slen = 0;
	simxChar* sigValue = new simxChar[15];
	substr( test[0], sigValue, 5, 18);
	printf("\nsv = %s", sigValue);	
	jstring s = 	JNU_NewStringNative(env, (const char *)sigValue, 14);
	const simxChar *s1 = (simxChar*)env->GetStringUTFChars(s, 0);
	printf("svnew = %s", s1);
	env->ReleaseStringUTFChars(s, s1);

	for(int i=0;i<3;i++) {
		s = env->NewStringUTF((const char*)test[0]+slen);
		const simxChar *test1 = (simxChar*)env->GetStringUTFChars(s, 0);
		env->ReleaseStringUTFChars(s, test1);
		env->SetObjectArrayElement(esArray, i, env->NewStringUTF((const char*)test[0]+slen));
		slen += env->GetStringLength(s)+1;
	}
	delete[] test;
	cls = env->GetObjectClass(t);
	mid = env->GetMethodID(cls, "setValue", "(Ljava/lang/String;)V");
	s = env->NewStringUTF(sigValue);

	env->CallVoidMethod(t, mid, s);
	delete[] sigValue;

//	float test1[] = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0 };
//	jfloatArray f = new jfloatArray[5];


	return 0;
}


#endif /* _Included_extApiJava */