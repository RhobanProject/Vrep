extern "C" {
    #include "extApi.h"
}
#include "Object.hpp"
#include "VREPClient.hpp"

Object::Object(simxInt handle) :
    _handle(handle),
    _name()
{
}

simxInt Object::getHandle() const
{
    return _handle;
}
        
std::string Object::getName() const
{
    return _name;
}

void Object::load(VREPClient& VREP)
{
    //Get joint name
    _name = VREP.getNameFromHandle(_handle);
}

