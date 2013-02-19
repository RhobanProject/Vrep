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

// Make sure to have the server side running in V-REP!
// Start the server from a child script with following command:
// simExtRemoteApiStart(19999) -- starts a remote API server service on port 19999

public class simpleTest
{
	public static void main(String[] args)
	{
		System.out.println("Program started");
		remoteApi vrep = new remoteApi();		
		if (vrep.simxStart("127.0.0.1",19999,true,true,5000)!=-1)
		{
			System.out.println("Connected to remote API server");
			IntWA objectHandles = new IntWA(1);
			int ret=vrep.simxGetObjects(vrep.sim_handle_all,objectHandles,vrep.simx_opmode_oneshot_wait);
			if (ret==vrep.simx_error_noerror)
				System.out.format("Number of objects in the scene: %d\n",objectHandles.getArray().length);
			else
				System.out.format("Remote API function call returned with error code: %d\n",ret);
			vrep.simxFinish();
		}
		else
			System.out.println("Failed connecting to remote API server");
		System.out.println("Program ended");
	}
}
			
