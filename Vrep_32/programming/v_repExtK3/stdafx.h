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

#ifdef _WIN32 
	#define WIN32_LEAN_AND_MEAN // Exclude rarely-used stuff from Windows headers
	#include <afxwin.h>         // MFC core and standard components
#endif // _WIN32

#include <stdio.h>

#define piValue 3.1415926535f

// Never change following data, data is serialized together with a scene!
// Keep following data same across all K-Team plugins to V-REP
#define DEVELOPER_DATA_HEADER 1		// Keep always same for all plugins created by K-Team!!!

#define	K3_BASE						0
#define	K3_LEFTMOTOR				1
#define	K3_RIGHTMOTOR				2
#define	K3_IRSENSOR1				3
#define	K3_IRSENSOR2				4
#define	K3_IRSENSOR3				5
#define	K3_IRSENSOR4				6
#define	K3_IRSENSOR5				7
#define	K3_IRSENSOR6				8
#define	K3_IRSENSOR7				9
#define	K3_IRSENSOR8				10
#define	K3_IRSENSOR9				11
#define	K3_USSENSOR1				12
#define	K3_USSENSOR2				13
#define	K3_USSENSOR3				14
#define	K3_USSENSOR4				15
#define	K3_USSENSOR5				16
#define K3_MAXVELOCITY				17 // data tag
#define K3_MODELVERSION				18 // data tag
#define	K3_COLORSENSORLEFT			19
#define	K3_COLORSENSORRIGHT			20
#define K3_MAXACCELERATION			21 // data tag
#define K3_GRIPPER_ARMMAXACCELERATION			22 // data tag


#define	K3_GRIPPER_ARMMOTOR1		40
#define	K3_GRIPPER_ARMMOTOR2		41
#define	K3_GRIPPER_ARMMOTOR3		42
#define	K3_GRIPPER_ARMMOTOR4		43
#define	K3_GRIPPER_ARMMOTOR5		44
#define	K3_GRIPPER_ARMMOTOR6		45
#define	K3_GRIPPER_GRIPPERMOTOR1	46
#define	K3_GRIPPER_GRIPPERMOTOR2	47
#define	K3_GRIPPER_GRIPPERMOTOR3	48
#define	K3_GRIPPER_LEFTDISTSENSOR	49
#define	K3_GRIPPER_RIGHTDISTSENSOR	50
#define	K3_GRIPPER_LEFTCOLSENSOR	51
#define	K3_GRIPPER_RIGHTCOLSENSOR	52

