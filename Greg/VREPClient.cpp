#include <iostream>
#include "VREPClient.hpp"

VREPClient::VREPClient() :
    _motors(),
    _forceSensors(),
    _accelerometerXRead(0),
    _accelerometerYRead(0),
    _accelerometerZRead(0)
{
}

void VREPClient::connect(const char* ip, int port)
{
    //Connection to server
    if (simxStart(ip, port, true, true, VREPClient::CONNECTION_TIMEOUT) == -1) {
        throw std::string("Unable to connect to V-REP Server");
    }
    //Enabling synchonous mode
    if (simxSynchronous(true) != simx_error_noerror) {
        throw std::string("Unable to enable synchronous mode");
    }
    //Retrieve joints
    scanMotors();
    //Retrieve force sensors
    scanForceSensors();
}

void VREPClient::disconnect() const
{
    simxFinish();
}
        
size_t VREPClient::countMotors() const
{
    return _motors.size();
}

size_t VREPClient::countForceSensors() const
{
    return _forceSensors.size();
}

const Motor& VREPClient::getMotor(size_t index) const
{
    if (index >= _motors.size()) {
        throw std::string("Invalid motor index");
    } else {
        return _motors[index];
    }
}

Motor *VREPClient::getMotor(std::string name)
{
    if (_motorsByName.find(name) != _motorsByName.end()) {
        return _motorsByName[name];
    }

    return NULL;
}

Motor& VREPClient::getMotor(size_t index)
{
    if (index >= _motors.size()) {
        throw std::string("Invalid motor index");
    } else {
        return _motors[index];
    }
}

const ForceSensor& VREPClient::getForceSensor(size_t index) const
{
    if (index >= _forceSensors.size()) {
        throw std::string("Invalid force sensor index");
    } else {
        return _forceSensors[index];
    }
}
ForceSensor& VREPClient::getForceSensor(size_t index)
{
    if (index >= _forceSensors.size()) {
        throw std::string("Invalid force sensor index");
    } else {
        return _forceSensors[index];
    }
}

double VREPClient::readAccelerometerX() const
{
    return _accelerometerXRead;
}
double VREPClient::readAccelerometerY() const
{
    return _accelerometerYRead;
}
double VREPClient::readAccelerometerZ() const
{
    return _accelerometerZRead;
}

void VREPClient::start()
{
    //Start simulation
    simxInt error = simxStartSimulation(simx_opmode_oneshot_wait);
    if (error != simx_error_noerror) {
        throw std::string("Unable to start the simulation");
    }
    //Start joint data streaming
    for (size_t i=0;i<_motors.size();i++) {
        //Position
        simxFloat pos;
        simxInt error = simxGetJointPosition(_motors[i].getHandle(), &pos, 
            simx_opmode_streaming);
        if (error != simx_error_noerror && error != simx_error_novalue_flag) {
            throw std::string("Unable to set up joint position streaming");
        }
        //Torque
        simxFloat torque;
        error = simxJointGetForce(_motors[i].getHandle(), &torque, 
            simx_opmode_streaming);
        if (error != simx_error_noerror && error != simx_error_novalue_flag) {
            throw std::string("Unable to set up joint torque streaming");
        }
    }
    //Start force sensor data streaming
    for (size_t i=0;i<_forceSensors.size();i++) {
        simxInt error = simxReadForceSensor(_forceSensors[i].getHandle(), 
            NULL, NULL, NULL, simx_opmode_streaming);
        if (error != simx_error_noerror && error != simx_error_novalue_flag) {
            throw std::string("Unable to set up force sensor streaming");
        }
    }
    //Start accelerometer data streaming
    simxFloat accelero;
    error = simxGetFloatSignal("accelerometerX", &accelero, simx_opmode_streaming);
    if (error != simx_error_noerror && error != simx_error_novalue_flag) {
        throw std::string("Unable to set up accelerometer X streaming");
    }
    error = simxGetFloatSignal("accelerometerY", &accelero, simx_opmode_streaming);
    if (error != simx_error_noerror && error != simx_error_novalue_flag) {
        throw std::string("Unable to set up accelerometer Y streaming");
    }
    error = simxGetFloatSignal("accelerometerZ", &accelero, simx_opmode_streaming);
    if (error != simx_error_noerror && error != simx_error_novalue_flag) {
        throw std::string("Unable to set up accelerometer Z streaming");
    }
    //Simulation step to initialize communication (streaming/buffer)
    error = simxSynchronousTrigger();
    error = simxSynchronousTrigger();
    error = simxSynchronousTrigger();
    if (error != simx_error_noerror) {
        throw std::string("Unable to step the simulation");
    }
    //Pause communication
    if (simxPauseCommunication(1) != 0) {
        throw std::string("Unable to pause communication");
    }
}
void VREPClient::stop()
{
    //Resume communication
    if (simxPauseCommunication(0) != 0) {
        throw std::string("Unable to resume communication");
    }
    //Stop simulation
    simxInt error = simxStopSimulation(simx_opmode_oneshot_wait);
    if (error != simx_error_noerror) {
        throw std::string("Unable to stop the simulation");
    }
}

void VREPClient::nextStep()
{
    //Update motor data
    for (size_t i=0;i<_motors.size();i++) {
        _motors[i].update(*this);
    }
    //Update force sensors data
    for (size_t i=0;i<_forceSensors.size();i++) {
        _forceSensors[i].update(*this);
    }
    //Update accelerometer sensor
    readAccelerometer();
    
    //Resume communication
    if (simxPauseCommunication(0) != 0) {
        throw std::string("Unable to resume communication");
    }
    //Simulation step
    simxInt error = simxSynchronousTrigger();
    if (error != simx_error_noerror) {
        throw std::string("Unable to step the simulation");
    }
    //Pause communication
    if (simxPauseCommunication(1) != 0) {
        throw std::string("Unable to pause communication");
    }
}

void VREPClient::scanMotors()
{
    simxInt motorCount = 0;
    simxInt* motorArray = NULL;
    //Get joints
    if (
        simxGetObjects(sim_object_joint_type, &motorCount, &motorArray, 
        simx_opmode_oneshot_wait) != simx_error_noerror
    ) {
        throw std::string("Unable to retrieve motor handles");
    }
    //Save joints
    _motors.clear();
    _motorsByName.clear();
    for (int i=0;i<motorCount;i++) {
        _motors.push_back(motorArray[i]);
    }
    //Load joints data
    for (int i=0;i<motorCount;i++) {
        Motor *m = &_motors[i];
        m->load(*this);
        _motorsByName[m->getName()] = m;
    }
}
 
void VREPClient::scanForceSensors()
{
    simxInt sensorCount = 0;
    simxInt* sensorArray = NULL;
    //Get force sensor
    if (
        simxGetObjects(sim_object_forcesensor_type, &sensorCount, &sensorArray, 
        simx_opmode_oneshot_wait) != simx_error_noerror
    ) {
        throw std::string("Unable to retrieve force sensor handles");
    }
    //Save force sensor
    _forceSensors.clear();
    for (int i=0;i<sensorCount;i++) {
        _forceSensors.push_back(sensorArray[i]);
    }
    //Load force sensor data
    for (int i=0;i<sensorCount;i++) {
        _forceSensors[i].load(*this);
    }
}

std::string VREPClient::getNameFromHandle(simxInt handle) const
{
    simxChar* name = NULL;
    simxInt error = 0;
    error = simxCustomGetObjectName(handle, &name, simx_opmode_oneshot_wait);
    if (error == simx_error_noerror) {
        return std::string(name);
    } else {
        throw std::string("Unable to fetch object name from handle");
    }
}

simxInt VREPClient::getMotorType(simxInt handle) const
{
    simxInt type = -1;
    simxInt error = 0;
    error = simxCustomGetJointType(handle, &type, simx_opmode_oneshot_wait);
    if (error == simx_error_noerror) {
        return type;
    } else {
        throw std::string("Unable to fetch joint type");
    }
}

void VREPClient::getMotorInterval
    (simxInt handle, bool& cyclic, double& min, double& max) const
{
    simxChar cyclicChar;
    simxFloat interval[2];
    simxInt error = 0;

    error = simxCustomGetJointInterval(handle, &cyclicChar, 
        (simxFloat*)interval, simx_opmode_oneshot_wait);
    if (error == simx_error_noerror) {
        cyclic = (bool)cyclicChar;
        min = (double)interval[0];
        max = (double)interval[1];
        return;
    } else {
        throw std::string("Unable to fetch joint type");
    }
}

bool VREPClient::getMotorDynamic(simxInt handle) const
{
    simxInt value;
    simxInt error = 0;

    error = simxGetObjectIntParameter(handle, 2000, &value, 
        simx_opmode_oneshot_wait);
    if (error == simx_error_noerror) {
        return (bool)value;
    } else {
        throw std::string("Unable to fetch joint dynamic");
    }
}

bool VREPClient::getMotorPositionControl(simxInt handle) const
{
    simxInt value;
    simxInt error = 0;

    error = simxGetObjectIntParameter(handle, 2001, &value, 
        simx_opmode_oneshot_wait);
    if (error == simx_error_noerror) {
        return (bool)value;
    } else {
        throw std::string("Unable to fetch joint position control");
    }
}

void VREPClient::writeMotorPosition(simxInt handle, simxFloat pos)
{
    simxInt error = simxSetJointTargetPosition(handle, pos, simx_opmode_oneshot);
    if (error != simx_error_noerror && error != simx_error_novalue_flag) {
        throw std::string("Unable to send joint target position");
    }
}

double VREPClient::readMotorPosition(simxInt handle)
{
    simxFloat pos;
    simxInt error = simxGetJointPosition(handle, &pos, simx_opmode_buffer);
    if (error != simx_error_noerror) {
        throw std::string("Unable to read joint current position");
    } 

    return pos;
}

double VREPClient::readMotorTorque(simxInt handle)
{
    simxFloat torque;
    simxInt error = simxJointGetForce(handle, &torque, simx_opmode_buffer);
    if (error != simx_error_noerror) {
        throw std::string("Unable to read joint current torque");
    } 

    return torque;
}

void VREPClient::readForceSensor(simxInt handle,
    double& forceX, double& forceY, double& forceZ,
    double& torqueX, double& torqueY, double& torqueZ) const
{
    simxFloat force[3];
    simxFloat torque[3];
    simxChar state;
    simxInt error = simxReadForceSensor(handle, &state, force, 
        torque, simx_opmode_buffer);
    if (error != simx_error_noerror) {
        throw std::string("Unable to read force sensor");
    } else if (state == 0x01) {
        forceX = force[0];
        forceY = force[1];
        forceZ = force[2];
        torqueX = torque[0];
        torqueY = torque[1];
        torqueZ = torque[2];
    }
}

void VREPClient::readAccelerometer()
{
    simxInt error;
    simxFloat accX, accY, accZ;
    error = simxGetFloatSignal("accelerometerX", &accX, 
        simx_opmode_buffer);
    if (error != simx_error_noerror) {
        accX = 0.0;
        //throw std::string("Unable to read accelerometer X sensor");
    }
    error = simxGetFloatSignal("accelerometerY", &accY, 
        simx_opmode_buffer);
    if (error != simx_error_noerror) {
        accY = 0.0;
        //throw std::string("Unable to read accelerometer Y sensor");
    }
    error = simxGetFloatSignal("accelerometerZ", &accZ, 
        simx_opmode_buffer);
    if (error != simx_error_noerror) {
        accZ = 0.0;
        //throw std::string("Unable to read accelerometer Z sensor");
    }

    _accelerometerXRead = accX;
    _accelerometerYRead = accY;
    _accelerometerZRead = accZ;
}

