# Copyright 2006-2013 Dr. Marc Andreas Freese. All rights reserved. 
# marc@coppeliarobotics.com
# www.coppeliarobotics.com
# 
# -------------------------------------------------------------------
# This file is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
# 
# You are free to use/modify/distribute this file for whatever purpose!
# -------------------------------------------------------------------
#
# This file was automatically created for V-REP release V3.0.1 on January 20th 2013

# Make sure to have the server side running in V-REP!
# Start the server from a child script with following command:
# simExtRemoteApiStart(19999) -- starts a remote API server service on port 19999

import vrep

print 'Program started'
if vrep.simxStart('127.0.0.1',19999,True,True,5000)!=-1:
    print 'Connected to remote API server'
    res,objs=vrep.simxGetObjects(vrep.sim_handle_all,vrep.simx_opmode_oneshot_wait)
    if res==vrep.simx_error_noerror:
        print 'Number of objects in the scene: ',len(objs)
    else:
        print 'Remote API function call returned with error code: ',res
    vrep.simxFinish()
else:
    print 'Failed connecting to remote API server'
print 'Program ended'
