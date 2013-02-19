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
#include "simxSocket.h"

class CSimxConnections
{
public:
	CSimxConnections();
	virtual ~CSimxConnections();

	void addSocketConnection(CSimxSocket* conn);
	CSimxSocket* getSynchronousSimulationTriggerConnection();
	void setSynchronousSimulationTriggerConnection(CSimxSocket* conn);
	void removeSocketConnection(CSimxSocket* conn);

	CSimxSocket* getConnectionAtIndex(int index);
	CSimxSocket* getConnectionFromPort(int portNb);


	bool mainScriptAboutToBeCalled();
	void simulationEnded();
	void instancePass();

	void removeAllConnections();

protected:
	std::vector<CSimxSocket*> _allSocketConnections;
	CSimxSocket* _synchronousSimulationTriggerConnection;
};
