#ifndef VREPCLIENT_HPP
#define VREPCLIENT_HPP

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "Object.hpp"
#include "Motor.hpp"
#include "ForceSensor.hpp"

/**
 * Handle V-REP Server communication with the
 * remote API
 */
class VREPClient
{
    public:

        /**
         * Connection timeout and communication speed (miliseconds)
         */
        static const simxInt CONNECTION_TIMEOUT = 2000;
        static const simxInt CONNECTION_CYCLE = 5;

        /**
         * Initialization
         */
        VREPClient();

        /**
         * Connect with the given network parameters
         * to the V-REP Server
         */
        void connect(const char* ip, int port);

        /**
         * Close connection to the server
         */
        void disconnect() const;

        /**
         * Return the number of motors
         */
        size_t countMotors() const;

        /**
         * Return the number of force sensors
         */
        size_t countForceSensors() const;

        /**
         * Return a motor by its index
         */
        const Motor& getMotor(size_t index) const;
        Motor& getMotor(size_t index);

        /**
         * Return a motor by its name
         */
        Motor& getMotor(const std::string& name);

        /**
         * Return a force sensor by its index
         */
        const ForceSensor& getForceSensor(size_t index) const;
        ForceSensor& getForceSensor(size_t index);

        /**
         * Return accelerometer value
         */
        double readAccelerometerX() const;
        double readAccelerometerY() const;
        double readAccelerometerZ() const;

        /**
         * Return position tracker value
         */
        double readPositionTrackerX() const;
        double readPositionTrackerY() const;
        double readPositionTrackerZ() const;

        /**
         * Start/Stop the V-REP simulation
         */
        void start();
        void stop();

        /**
         * Apply a simulation step
         * Send writen joint target position
         * Fetch current joint position
         */
        void nextStep();

    private:

        /**
         * Vrep client ID
         */
        simxInt _id;

        /**
         * Retrieve all joints handle
         */
        void scanMotors();
        
        /**
         * Retrieve all force sensors handle
         */
        void scanForceSensors();
        
        /**
         * Retrieve the identifier name of the given
         * V-REP handle
         */
        std::string getNameFromHandle(simxInt handle) const;

        /**
         * Retrive the type of the given joint
         */
        simxInt getMotorType(simxInt handle) const;

        /**
         * Retrive interval configuration of
         * the given joint
         */
        void getMotorInterval
            (simxInt handle, bool& cyclic, double& min, double& max) const;

        /**
         * Return true if dynamic is enabled
         * for the given joint
         */
        bool getMotorDynamic(simxInt handle) const;

        /**
         * Return true if position control is enabled
         * for the given joint
         */
        bool getMotorPositionControl(simxInt handle) const;

        /**
         * Send a target position to the given joint
         */
        void writeMotorPosition(simxInt handle, simxFloat pos) const;

        /**
         * Send the maximum force torque to apply to 
         * a joint
         */
        void writeMotorTorqueMax(simxInt handle, simxFloat force) const;

        /**
         * Read current joint position
         */
        double readMotorPosition(simxInt handle) const;

        /**
         * Read current joint torque
         */
        double readMotorTorque(simxInt handle) const;

        /**
         * Read force sensor value
         */
        void readForceSensor(simxInt handle, 
            double& forceX, double& forceY, double& forceZ,
            double& torqueX, double& torqueY, double& torqueZ) const;

        /**
         * Read fom V-REP server accelerometer sensor
         */
        void readAccelerometer();

        /**
         * Read from V-REP server dummy object position
         * tracker
         */
        void readPositionTracker();

        /**
         * Is the value streaming has to be initialized
         */
        bool _initStreaming;

        /**
         * Motor container
         */
        std::vector<Motor> _motors;

        /**
         * Motors, mapped by name
         */
        std::map<std::string, Motor*> _motorsByName;

        /**
         * Force sensor container
         */
        std::vector<ForceSensor> _forceSensors;

        /**
         * Accelerometer value
         */
        double _accelerometerXRead;
        double _accelerometerYRead;
        double _accelerometerZRead;

        /**
         * Position object tracked
         */
        double _positionTrackerXRead;
        double _positionTrackerYRead;
        double _positionTrackerZRead;

        /**
         * Object can access to private methods
         * for V-REP communication
         */
        friend class Object;
        friend class Motor;
        friend class ForceSensor;
};

#endif

