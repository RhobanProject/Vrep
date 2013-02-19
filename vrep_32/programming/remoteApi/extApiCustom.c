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

#include "extApiCustom.h"
#include "extApi.h"
#include "extApiInternal.h"
#include "extApiCustomConst.h"

/* Your custom remote API functions. Following are examples: */

EXTAPI_DLLEXPORT simxInt simxCustomGetObjectCount(simxInt* objectCount,simxInt operationMode)
{
	simxChar* dataPointer;
	simxInt returnValue; /* every "regular" remote API function returns a same error code */

	/* First catch a possible error: */
	if (_communicationThreadRunning==0)
		return(simx_error_initialize_error_flag);

	/* Then take care of the "remove" operation mode: */
	if (operationMode==simx_opmode_remove)
		return(_removeCommandReply_null(simx_customcmd_get_object_count)); /* _null indicates that the command is identified only by the command ID */

	/* Now "execute" the command (i.e. place the into the outbox, and retrieve a command reply from the inbox) */
	dataPointer=_exec_null(simx_customcmd_get_object_count,operationMode,0,&returnValue); /* _null indicates that the command is identified only by the command ID */

	/* Now extract the desired data: */
	if ((dataPointer!=0)&&(returnValue==0))
		objectCount[0]=_readPureDataInt(dataPointer,0,0); /* pure data is the data that is not used to identify a command */

	/* return the error code */
	return(returnValue);
}

EXTAPI_DLLEXPORT simxInt simxCustomGetObjectType(simxInt objectHandle,simxInt* objectType,simxInt operationMode)
{
	simxChar* dataPointer;
	simxInt returnValue;

	/* First catch a possible error: */
	if (_communicationThreadRunning==0)
		return(simx_error_initialize_error_flag);

	/* Then take care of the "remove" operation mode: */
	if (operationMode==simx_opmode_remove)
		return(_removeCommandReply_int(simx_customcmd_get_object_type,objectHandle)); /* _int indicates that the command is identified by the command ID AND an integer value */

	/* Now "execute" the command (i.e. place the command (with its associated command data) into the outbox, and retrieve a command reply from the inbox) */
	dataPointer=_exec_int(simx_customcmd_get_object_type,operationMode,0,objectHandle,&returnValue); /* _int indicates that the command is identified by the command ID AND an integer value*/

	/* Now extract the desired data: */
	if ((dataPointer!=0)&&(returnValue==0))
		objectType[0]=_readPureDataInt(dataPointer,0,0); /* pure data is the data that is not used to identify a command */

	/* return the error code */
	return(returnValue);
}

EXTAPI_DLLEXPORT simxInt simxCustomSetObjectName(simxInt objectHandle,const simxChar* objectName,simxInt operationMode)
{
	simxInt returnValue;

	/* First catch a possible error: */
	if (_communicationThreadRunning==0)
		return(simx_error_initialize_error_flag);

	/* Then take care of the "remove" operation mode: */
	if (operationMode==simx_opmode_remove)
		return(_removeCommandReply_int(simx_customcmd_set_object_name,objectHandle)); /* _int indicates that the command is identified by the command ID AND an integer value */

	/* Now "execute" the command (i.e. place the command (with its associated command data (i.e. the object handle) and pure data (i.e. the new name)) into the outbox) */
	_exec_int_buffer(simx_customcmd_set_object_name,operationMode,0,objectHandle,(simxChar*)objectName,extApi_getStringLength(objectName)+1,&returnValue);

	/* return the error code */
	return(returnValue);
}

EXTAPI_DLLEXPORT simxInt simxCustomGetUIButtonLabel(simxInt uiHandle,simxInt buttonID,simxChar** label,simxInt operationMode)
{
	simxChar* dataPointer;
	simxInt returnValue;

	/* First catch a possible error: */
	if (_communicationThreadRunning==0)
		return(simx_error_initialize_error_flag);

	/* Then take care of the "remove" operation mode: */
	if (operationMode==simx_opmode_remove)
		return(_removeCommandReply_intint(simx_customcmd_get_ui_button_label,uiHandle,buttonID)); /* _intint indicates that the command is identified by the command ID AND 2 integer values */

	/* Now "execute" the command (i.e. place the command (with its associated command data) into the outbox, and retrieve a command reply from the inbox) */
	dataPointer=_exec_intint(simx_customcmd_get_ui_button_label,operationMode,0,uiHandle,buttonID,&returnValue);

	/* Now extract the desired data: */
	if ((dataPointer!=0)&&(returnValue==0))
		label[0]=dataPointer+SIMX_SUBHEADER_SIZE+_getCmdDataSize(dataPointer); /* we point on the pure data start. The pointer stays valid until next remote API call (i.e. the command reply was copied from the inbox to another buffer) */

	/* return the error code */
	return(returnValue);
}

EXTAPI_DLLEXPORT simxInt simxCustomGetScriptHandle(const simxChar* objectName,simxInt* scriptHandle,simxInt operationMode)
{
	simxChar* dataPointer;
	simxInt returnValue;

	/* First catch a possible error: */
	if (_communicationThreadRunning==0)
		return(simx_error_initialize_error_flag);

	/* Then take care of the "remove" operation mode: */
	if (operationMode==simx_opmode_remove)
		return(_removeCommandReply_string(simx_customcmd_get_script_handle,objectName));

	/* Now "execute" the command (i.e. place the command (with its associated command data) into the outbox, and retrieve a command reply from the inbox) */
	dataPointer=_exec_string(simx_customcmd_get_script_handle,operationMode,0,objectName,&returnValue);

	/* Now extract the desired data: */
	if ((dataPointer!=0)&&(returnValue==0))
		scriptHandle[0]=_readPureDataInt(dataPointer,0,0); /* pure data is the data that is not used to identify a command */

	/* return the error code */
	return(returnValue);
}
