#include <iostream>
#include "primitive.h"
#include "spline.h"
#include <ga/ga.h>

#define AMPLITUDE 30

double t = 0;

/**
 * Initializes the primitive
 */
void primitive_init(VREPClient &vrep)
{
    vrep.getMotor("FL1")->setRevert(true);
    vrep.getMotor("BL1")->setRevert(true);
    
    vrep.getMotor("BL2")->setRevert(true);
    vrep.getMotor("BR2")->setRevert(true);
    vrep.getMotor("FL2")->setRevert(true);
    vrep.getMotor("FR2")->setRevert(true);
}

/**
 * Tick the primitive
 */
void primitive_step(VREPClient &vrep, Spline *splines)
{
    int motor;
    t += 0.02;

    if (t > 1.0) t -= 1.0;
    if (t < 0.0) t += 1.0;

    for (int motor=0; motor<vrep.countMotors(); motor++) {
        vrep.getMotor(motor).writePosDeg(AMPLITUDE*splines[motor].get(t));
    }
}

