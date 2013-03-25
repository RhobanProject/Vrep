#ifndef FORCESENSOR_HPP
#define FORCESENSOR_HPP

#include <iostream>
#include "Object.hpp"
class VREPClient;

/**
 * Represent V-REP Force Sensor Object
 */
class ForceSensor : public Object
{
    public:

        /**
         * Initialize the force sensor with the given V-REP
         * handle
         */
        ForceSensor(simxInt handle);
        
        /**
         * Read sensor values from V-REP server
         * Automaticaly called by VREPClient
         */
        void update(VREPClient& VREP);

        /**
         * Return force norm
         */
        double readForceNorm() const;

        /**
         * Return torque norm
         */
        double readTorqueNorm() const;

    private:

        /**
         * Force sensor values
         */
        double _forceXRead;
        double _forceYRead;
        double _forceZRead;
        
        /**
         * Torque sensor values
         */
        double _torqueXRead;
        double _torqueYRead;
        double _torqueZRead;
};

#endif

