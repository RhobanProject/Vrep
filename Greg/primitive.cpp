#include <iostream>
#include "primitive.h"
#include "spline.h"

#define AMPLITUDE 30

Spline s1;
Spline s2;

volatile double t = 0.0;
volatile double leftGain = 1.0;
volatile double rightGain = 1.0;
volatile double timeGain = 1.8;
volatile double amplitudeGain = 1.0;
volatile double altitudeGain = 1.0;
volatile double backGain = 0.4;
volatile double balance = 1.0;
volatile double frontBalance = 1.0;
volatile double backBalance = 1.0;
volatile double leftOffset = 0.0;
volatile double rightOffset = 0.0;
volatile double frontOffset = 2.0;
volatile double backOffset = 0.0;
volatile double open = 10.0;
volatile double phase = 0.25;

using namespace std;

void primitive_init(VREPClient &vrep)
{
    // First spline: /\_________
    s1.addPoint(0.0, 0.0);
    s1.addPoint(0.1, 1.0);
    s1.addPoint(0.2, 0.0);
    s1.addPoint(1.0, 0.0);

    // Second spline: _/`--------.._
    s2.addPoint(0.0, 0.0);
    s2.addPoint(0.05, 0.0);
    s2.addPoint(0.15, 1.0);
    s2.addPoint(1.0, 0.0);

    vrep.getMotor("FL1")->setRevert(true);
    vrep.getMotor("BL1")->setRevert(true);
    
    vrep.getMotor("BL2")->setRevert(true);
    vrep.getMotor("BR2")->setRevert(true);
    vrep.getMotor("FL2")->setRevert(true);
    vrep.getMotor("FR2")->setRevert(true);
}

void primitive_step(VREPClient &vrep)
{
    t += timeGain*0.02;

    if (t > 1.0) t -= 1.0;
    if (t < 0.0) t += 1.0;

    double s = 1.0;
    if (amplitudeGain < 0) {
        s = -1.0;
    }
    
    for (int i=0; i<vrep.countMotors(); i++)
        vrep.getMotor(i).writePos(0);
 
    vrep.getMotor("FR2")->writePosDeg(frontOffset+rightOffset+s*s1.getMod(t)*altitudeGain*AMPLITUDE*amplitudeGain);
    vrep.getMotor("BL2")->writePosDeg(backOffset+leftOffset+s*s1.getMod(t+phase)*altitudeGain*AMPLITUDE*amplitudeGain);
    vrep.getMotor("BR2")->writePosDeg(backOffset+rightOffset+s*s1.getMod(t+2*phase)*altitudeGain*AMPLITUDE*amplitudeGain);
    vrep.getMotor("FL2")->writePosDeg(frontOffset+leftOffset+s*s1.getMod(t+3*phase)*altitudeGain*AMPLITUDE*amplitudeGain);

    vrep.getMotor("FR1")->writePosDeg(rightGain*s2.getMod(t)*AMPLITUDE*amplitudeGain+open);
    vrep.getMotor("BL1")->writePosDeg(leftGain*s2.getMod(t+phase)*AMPLITUDE*amplitudeGain-open);
    vrep.getMotor("BR1")->writePosDeg(rightGain*s2.getMod(t+2*phase)*AMPLITUDE*amplitudeGain-open);
    vrep.getMotor("FL1")->writePosDeg(leftGain*s2.getMod(t+3*phase)*AMPLITUDE*amplitudeGain+open);

}

void primitive_tick(VREPClient &vrep)
{
    primitive_step(vrep);
    //primitive_step(vrep);
}

