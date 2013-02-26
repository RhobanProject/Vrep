#include <math.h>
#include "ForceSensor.hpp"
#include "VREPClient.hpp"

ForceSensor::ForceSensor(simxInt handle) :
    Object(handle),
    _forceXRead(0),
    _forceYRead(0),
    _forceZRead(0)
{
}

void ForceSensor::update(VREPClient& VREP)
{
    VREP.readForceSensor(_handle, 
        _forceXRead, _forceYRead, _forceZRead,
        _torqueXRead, _torqueYRead, _torqueZRead);
}

double ForceSensor::readForceNorm() const
{
    return sqrt(
        _forceXRead*_forceXRead + 
        _forceYRead*_forceYRead + 
        _forceZRead*_forceZRead);
}

double ForceSensor::readTorqueNorm() const
{
    return sqrt(
        _torqueXRead*_torqueXRead + 
        _torqueYRead*_torqueYRead + 
        _torqueZRead*_torqueZRead);
}

