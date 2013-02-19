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

#include "stdafx.h"
#include "simxConnections.h"

CSimxConnections::CSimxConnections()
{
	_synchronousSimulationTriggerConnection=NULL;
}

CSimxConnections::~CSimxConnections()
{
	removeAllConnections();
}

void CSimxConnections::removeAllConnections()
{
	for (unsigned int i=0;i<_allSocketConnections.size();i++)
		delete _allSocketConnections[i];
	_allSocketConnections.clear();
}

void CSimxConnections::addSocketConnection(CSimxSocket* conn)
{
	_allSocketConnections.push_back(conn);
}

CSimxSocket* CSimxConnections::getSynchronousSimulationTriggerConnection()
{
	return(_synchronousSimulationTriggerConnection);
}

void CSimxConnections::setSynchronousSimulationTriggerConnection(CSimxSocket* conn)
{
	_synchronousSimulationTriggerConnection=conn;
}

void CSimxConnections::removeSocketConnection(CSimxSocket* conn)
{
	for (unsigned int i=0;i<_allSocketConnections.size();i++)
	{
		if (_allSocketConnections[i]==conn)
		{
			delete conn;
			_allSocketConnections.erase(_allSocketConnections.begin()+i);
			break;
		}
	}
}

CSimxSocket* CSimxConnections::getConnectionAtIndex(int index)
{
	if ((index>=0)&&(index<int(_allSocketConnections.size())))
		return(_allSocketConnections[index]);
	return(NULL);
}

CSimxSocket* CSimxConnections::getConnectionFromPort(int portNb)
{
	for (unsigned int i=0;i<_allSocketConnections.size();i++)
	{
		if (_allSocketConnections[i]->getPortNb()==portNb)
			return(_allSocketConnections[i]);
	}
	return(NULL);
}

bool CSimxConnections::mainScriptAboutToBeCalled()
{ // return value true means: do not execute the main script!
	bool retVal=false;
	for (unsigned int i=0;i<_allSocketConnections.size();i++)
	{
		_allSocketConnections[i]->mainScriptAboutToBeCalled();
		if (_synchronousSimulationTriggerConnection==_allSocketConnections[i])
		{ // this socket has to generate the trigger (if enabled)
			if (_allSocketConnections[i]->getWaitForTrigger())
			{ // trigger not yet received
				retVal=(_allSocketConnections[i]->getStatus()==3); // wait only if the comm thread is running and the client is still connected!
			}
			else
				_allSocketConnections[i]->setWaitForTrigger(true); // trigger received. Reactivate it for next time!
		}
	}
	return(retVal);
}

void CSimxConnections::simulationEnded()
{
	for (unsigned int i=0;i<_allSocketConnections.size();i++)
	{
		if (_allSocketConnections[i]->getActiveOnlyDuringSimulation())
		{
			removeSocketConnection(_allSocketConnections[i]);
			i=-1; // make sure to start the loop from the beginning (ordering has changed)
		}
	}
}

void CSimxConnections::instancePass()
{
	for (unsigned int i=0;i<_allSocketConnections.size();i++)
		_allSocketConnections[i]->instancePass();
}
