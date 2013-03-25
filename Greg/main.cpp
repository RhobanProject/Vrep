#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <signal.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <VREPClient.hpp>
#include <ga/ga.h>

#include "genetic.h"

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

/**
 * Runs the genetic experience
 */
void runExperience(VREPClient &vrep)
{
    GeneticExperience experience(vrep);
    experience.run();
}

/**
 * Create the VREP instance and run the genetic experience
 */
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

        for (int motor=0; motor<VREP.countMotors(); motor++) {
            cout << "Motor #" << motor << ": " << VREP.getMotor(motor).getName() << endl;
        }

        runExperience(VREP);
    } catch (string str) {
        cerr << "Exception error: " << str << endl;
        exiting(false);
    }

    exiting();
}

