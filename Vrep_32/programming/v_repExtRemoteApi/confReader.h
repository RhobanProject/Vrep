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
#include <string>

class CConfReader
{
public:
	CConfReader();
	virtual ~CConfReader();

	bool readConfiguration(const char* filename);

	bool getString(const char* variableName,std::string& variable);
	bool getInteger(const char* variableName,int& variable);
	bool getFloat(const char* variableName,float& variable);
	bool getBoolean(const char* variableName,bool& variable);

private:
	void _removeComments(std::string& line);
	bool _removeFrontAndBackSpacesAndTabs(std::string& line);
	int _getVariableIndex(const char* variableName);
	std::vector<std::string> _variables;
	std::vector<std::string> _values;
};
