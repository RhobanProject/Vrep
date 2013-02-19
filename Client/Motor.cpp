#include <iostream>
#include <assert.h>
#include "Motor.hpp"
#include "VREPClient.hpp"

Motor::Motor(simxInt handle) :
    Object(handle),
    _min(0),
    _max(0),
    _positionRead(0),
    _torqueRead(0),
    _positionWrite(0),
    _positionDirty(false)
{
}
        
double Motor::getMinPos() const
{
    return _min;
}
double Motor::getMaxPos() const
{
    return _max;
}
        
double Motor::readPos() const
{
    return _positionRead;
}
        
double Motor::readTorque() const
{
    return _torqueRead;
}
        
void Motor::writePos(double pos)
{
    _positionWrite = pos;
    _positionDirty = true;
}

void Motor::load(VREPClient& VREP)
{
    Object::load(VREP);
    //Get joint type
    if (VREP.getMotorType(_handle) != sim_joint_revolute_subtype) {
        throw std::string("Joint type is not revolute: ") + _name;
    }
    //Get joint interval
    bool cyclic;
    VREP.getMotorInterval(_handle, cyclic, _min, _max);
    if (cyclic == true) {
        throw std::string("Joint position is cyclic: ") + _name;
    }
    //Get joint dynamic
    if (VREP.getMotorDynamic(_handle) == false) {
        throw std::string("Joint dynamic is disabled: ") + _name;
    }
    //Get joint position control
    if (VREP.getMotorPositionControl(_handle) == false) {
        throw std::string("Joint position control is disabled: ") + _name;
    }
}

void Motor::update(VREPClient& VREP)
{
    if (_positionDirty) {
        VREP.writeMotorPosition(_handle, _positionWrite);
        _positionDirty = false;
    }
    _positionRead = VREP.readMotorPosition(_handle);
    _torqueRead = VREP.readMotorTorque(_handle);
}

