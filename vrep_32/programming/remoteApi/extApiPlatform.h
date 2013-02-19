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

#ifndef _EXTAPIPLATFORM__
#define _EXTAPIPLATFORM__

#ifdef _WIN32
	/* on older win compilers stdint.h can be missing */
	typedef short int16_t;
	typedef unsigned short uint16_t;
	typedef int int32_t;
	typedef unsigned int uint32_t;
#else
	#include <stdint.h>
#endif

#define SOCKET_MAX_PACKET_SIZE 250 /* in bytes */
#define SOCKET_HEADER_LENGTH 6 /* WORD0=1 (to detect endianness), WORD1=packetSize, WORD2=packetsLeftToRead */
#define SOCKET_TIMEOUT_READ 10000 /* in ms */

typedef char simxChar;				/* always 1 byte */
typedef int16_t simxShort;			/* always 2 bytes */
typedef uint16_t simxUShort;		/* always 2 bytes */
typedef int32_t simxInt;			/* always 4 bytes */
typedef uint32_t simxUInt;			/* always 4 bytes */
typedef float simxFloat;			/* always 4 bytes */
typedef double simxDouble;			/* always 8 bytes */
typedef void simxVoid;


#ifdef _WIN32
	#define SIMX_THREAD_RET_TYPE simxVoid
	#define SIMX_THREAD_RET_LINE return
#elif defined (__linux) || defined (__APPLE__)
	#define SIMX_THREAD_RET_TYPE simxVoid*
	#define SIMX_THREAD_RET_LINE return(0)
#endif


/* Following functions only needed for testing endianness robustness */
simxShort extApi_endianConversionShort(simxShort shortValue);
simxUShort extApi_endianConversionUShort(simxUShort shortValue);
simxInt extApi_endianConversionInt(simxInt intValue);
simxFloat extApi_endianConversionFloat(simxFloat floatValue);
simxDouble extApi_endianConversionDouble(simxDouble floatValue);

/* Following functions might be platform specific */
simxChar* extApi_allocateBuffer(simxInt bufferSize);
simxVoid extApi_releaseBuffer(simxChar* buffer);
simxVoid extApi_createMutexes();
simxVoid extApi_deleteMutexes();
simxVoid extApi_lockResources();
simxVoid extApi_unlockResources();
simxVoid extApi_lockSendStart();
simxVoid extApi_unlockSendStart();
simxInt extApi_getTimeInMs();
simxInt extApi_getTimeDiffInMs(simxInt lastTime);
simxVoid extApi_initRand();
simxFloat extApi_rand();
simxVoid extApi_sleepMs(simxInt ms);
simxVoid extApi_switchThread();
simxChar extApi_areStringsSame(const simxChar* str1,const simxChar* str2);
simxInt extApi_getStringLength(const simxChar* str);
simxChar* extApi_readFile(const simxChar* fileName,simxInt* len);
simxChar extApi_launchThread(SIMX_THREAD_RET_TYPE (*startAddress)(simxVoid*));
simxChar extApi_connectToServer_socket(const simxChar* theConnectionAddress,simxInt theConnectionPort);
simxVoid extApi_cleanUp_socket();
simxInt extApi_send_socket(const simxChar* data,simxInt dataLength);
simxInt extApi_recv_socket(simxChar* data,simxInt maxDataLength);

#endif /* _EXTAPIPLATFORM__	*/			
