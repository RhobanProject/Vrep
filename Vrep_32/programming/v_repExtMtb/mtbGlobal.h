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

#define piValue 3.1415926535f

// Never change following data, data is serialized together with a scene!
// Keep following data same across all of your plugins to V-REP
#define DEVELOPER_DATA_HEADER 0		// Keep always same for all plugins created by you or your company!!!
									// This number identifies data you might save together with scene objects
									// If several developers or companies are using the same number, then
									// data attached to scene objects might not be interpreted correctly.
									// Best is to use the serial number of your first copy of V-REP and
									// always stick to it.

// Following section defines data tags. You can attach custom data to any object in a scene.
// That custom data is saved and loaded together with the scene object.
// Refer to the plugin tutorial in the V-REP manual for more details.

#define	MTB_BASE					210 // identifies the base object of an "mtb"-robot
#define MTB_PROGRAM					211 // TAG under which the robot language program is saved. MTB_PROGRAM is attached to the base of the MTB robot model
#define MTB_OPTIONS					214 // indicates options (bit1=automatic execution. MTB_OPTIONS is attached to the base of the MTB robot model

// You can add more tags here. But make sure that all tags under the same DEVELOPER_DATA_HEADER
// do not collide (also across other plugins)
