#ifndef _GENETIC_H
#define _GENETIC_H

#include <VREPClient.hpp>
#include <ga/ga.h>

#include "spline.h"

#define SPLINE_NB_POINTS 10
#define POPULATION_SIZE 50
#define NB_GENERATIONS 500
#define P_MUTATION 0.2
#define SIMULATION_TIME 20

typedef GA2DArrayGenome<float> SplinesGenome;

class GeneticExperience
{
    public:
        GeneticExperience(VREPClient &vrep_);
        ~GeneticExperience();

        Spline *getSplines();
        void updateSplines(GAGenome &genome);
        VREPClient &getVrep();

        void run();

    protected:
        VREPClient &vrep;
        SplinesGenome genome;
        Spline *splines;
};

#endif
