// This file is part of the COLLADA PLUGIN for V-REP
// 
// Copyright 2006-2013 Dr. Marc Andreas Freese. All rights reserved. 
// marc@coppeliarobotics.com
// www.coppeliarobotics.com
// 
// The COLLADA PLUGIN is licensed under the terms of GNU GPL:
// 
// -------------------------------------------------------------------
// The COLLADA PLUGIN is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// The COLLADA PLUGIN is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with the COLLADA PLUGIN.  If not, see <http://www.gnu.org/licenses/>.
// -------------------------------------------------------------------
//
// This file was automatically created for V-REP release V3.0.1 on January 20th 2013

// Written by Alex Doumanoglou on behalf of Dr. Marc Freese

#pragma once
#include <vector>
#include <string>
#include <sstream>
#include "vec3.h"
#include "mat4.h"

class StringHelper
{
private:
	StringHelper() { };

	static std::vector<std::string> split(const std::string &str, const std::vector<char>& delim);
	static bool contains_char(const std::vector<char>& v,char c);
public:
	//static std::vector<float> ConvertStringToFloatArray(const std::string& string);
	template <class T> 
/*	static std::vector<T> ConvertStringToTArray(const std::string& string)
	{
		std::vector<char> delims;
		delims.push_back(' ');
		delims.push_back('\n');
		delims.push_back('\r');
		std::vector<std::string> sarray = split(string,delims);
		std::vector<T> tarray;
		for(std::vector<std::string>::iterator it = sarray.begin();it != sarray.end(); it++) {
			if((*it).length() > 0) {
				T f;
				if(from_string<T>(f,*it)) {
					tarray.push_back(f);
				}
				else
					throw 1;
			}
		}
		return tarray;
	}*/

	static std::vector<T> ConvertStringToTArray(const std::string& string)
	{
		std::vector<char> delims;
		delims.push_back(' ');
		delims.push_back('\n');
		delims.push_back('\r');
		std::vector<T> tarray;
		std::string str="";
		int slen = string.length();
		for(int i=0;i<slen;i++) {
			char c = string[i];
			if(contains_char(delims,c)) {
				if(str.length()>0) {
					T f;
					if(from_string<T>(f,str)) {
						tarray.push_back(f);
						str = "";
					}
					else
						throw 1;
				}
			}
			else
				str += c;
		}
		if(str.length()>0) {
			T f;
			if(from_string<T>(f,str)) {
				tarray.push_back(f);
				str = "";
			}
			else
				throw 1;
		}

		return tarray;
	}


	template <class T>
	static bool from_string(T& t, 
						const std::string& s)
	{
		std::istringstream iss(s);
		return !(iss >> std::dec >> t).fail();
	}

	template <class T> 
		static std::string to_string(const T& t) {
		std::ostringstream os; os<<t; return os.str(); 
	}

	static std::string ConvertVec3ArrayToString(const std::vector<vec3>& values);
	static std::string ConvertVec3ToString(const vec3& vec);
	static std::string ConvertMat4ToString(const mat4& mat);
};
