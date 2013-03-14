#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <iostream>
class VREPClient;
typedef int simxInt;
typedef float simxFloat;

/**
 * Base class
 * Represent V-REP dynamic object
 */
class Object
{
    public:

        /**
         * Initialize the object with the given V-REP
         * handle
         */
        Object(simxInt handle);

        /**
         * Return V-REP motor handle
         */
        simxInt getHandle() const;

        /**
         * Return motor identifier name
         */
        std::string getName() const;
        
        /**
         * Initialization of object name
         * from V-REP
         */
        virtual void load(VREPClient& VREP);
        
        /**
         * Write and/or read data from V-REP server
         */
        virtual void update(VREPClient& VREP) = 0;

    protected:

        /**
         * V-REP object handle
         */
        simxInt _handle;

        /**
         * V-REP object identifier name
         */
        std::string _name;
};

#endif

