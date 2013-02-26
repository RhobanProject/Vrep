#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <signal.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include "primitive.h"
#include "VREPClient.hpp"
#include <ga/ga.h>

/**
 * VREPClient instance
 * Globale variable
 */
static VREPClient VREP;

using namespace std;

static void exiting(bool success = true)
{
    //Close server connection
    VREP.stop();
    VREP.disconnect();
    if (success) {
        exit(EXIT_SUCCESS);
    } else {
        exit(EXIT_FAILURE);
    }
}

static void signal_handler(int sig, siginfo_t *siginfo, void *context)
{
    cout << endl << "Exiting..." << endl;
    exiting();
}

static void attachSignalHandler()
{
    struct sigaction action;
    bzero(&action, sizeof(action));
    action.sa_sigaction = &signal_handler;
    action.sa_flags = SA_SIGINFO;
    if (sigaction(SIGINT, &action, NULL) < 0) {
        cerr << "Unable to register signal handler" << endl;
        exit(EXIT_FAILURE);
    }
}

double score()
{
    double x1, y1, z1;
    double x2, y2, z2;
    // Initializing primitive
    primitive_init(VREP);
    //Main Loop
    cout << "Starting simulation" << endl;
    VREP.start();
    x1 = VREP.readPositionTrackerX();
    y1 = VREP.readPositionTrackerY();
    z1 = VREP.readPositionTrackerZ();
    for (double t=0; t<30.0; t+=0.02) {
        //Display state
        //Do next step
        VREP.nextStep();

        //Compute motors move
        primitive_tick(VREP);
    }
    x2 = VREP.readPositionTrackerX();
    y2 = VREP.readPositionTrackerY();
    z2 = VREP.readPositionTrackerZ();
    //End simulation
    cout << "Stopping simulation" << endl;
    VREP.stop();

    return sqrt(pow(x1-x2,2)+pow(y1-y2,2)+pow(z1-z2,2));
}

int main(int argc, char* argv[])
{
    //Network parameters
    int port = 0;
    char* ip = NULL;

    GARandomSeed();
    
    //Parse input arguments
    if (argc != 3) {
        cerr << "Bad usage. Usage: ./command [ip address] [port number]" << endl;
        cerr << "Provide network parameters to connect to V-REP server" << endl;
        return EXIT_FAILURE;
    } else {
        ip = argv[1];
        port = atoi(argv[2]);
    }

    //Signal attaching
    attachSignalHandler();

    try {
        //Connection to V-REP
        cout << "Connecting to V-REP server " << ip << ":" << port << endl;
        VREP.connect(ip, port);

        cout << "Running score evaluation" << endl;
        cout << "Score: " << score() << endl;
    } catch (string str) {
        cerr << "Exception error: " << str << endl;
        exiting(false);
    }

    exiting();
}

