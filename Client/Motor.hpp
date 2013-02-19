#ifndef MOTOR_HPP
#define MOTOR_HPP

#include <iostream>
extern "C" {
    #include "extApi.h"
}
#include "Object.hpp"
class VREPClient;

/**
 * Represent V-REP Joint Object
 */
class Motor : public Object
{
    public:

        /**
         * Initialize the motor with the given V-REP
         * handle
         */
        Motor(simxInt handle);

        /**
         * Return minimum and maximum
         * position (radian)
         */
        double getMinPos() const;
        double getMaxPos() const;

        /**
         * Return the current position
         * of the join (radian)
         */
        double readPos() const;

        /**
         * Return the current force/torque
         * of the join
         */
        double readTorque() const;

        /**
         * The target position to be sent
         * to the join
         */
        void writePos(double pos);

        /**
         * Initialization of motors data
         * from V-REP
         * Automaticaly called by VREPClient
         */
        void load(VREPClient& VREP);

        /**
         * Write and read values to V-REP server
         * Automaticaly called by VREPClient
         */
        void update(VREPClient& VREP);

    private:

        /**
         * Minimum position in radian
         */
        double _min;

        /**
         * Maximum position in radian
         */
        double _max;

        /**
         * Current position of the join
         * from V-REP sensor (radian)
         */
        double _positionRead;

        /**
         * Current force/torque of the join
         * from V-REP sensor
         */
        double _torqueRead;

        /**
         * Target position to be sent to
         * the join
         */
        double _positionWrite;

        /**
         * True if positionWrite has
         * been modified
         */
        bool _positionDirty;
};

#endif

