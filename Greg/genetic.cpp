#include <math.h>
#include <iostream>
#include <ga/ga.h>
#include "genetic.h"
#include "primitive.h"

using namespace std;

float Objective(GAGenome&);

/**
 * Genome initializer, uses random numbers
 */
void RandomInitializer(GAGenome &g)
{
    SplinesGenome &genome = (SplinesGenome&)g;
    for (int x=0; x<genome.width(); x++) {
        for (int y=0; y<genome.height(); y++) {
            genome.gene(x, y, GARandomFloat(-1, 1));
        }
    }
}

/**
 * Do a mutation
 */
int Mutator(GAGenome &g, float pmut)
{
    SplinesGenome &genome = (SplinesGenome&)g;
    int mut = 0;
    while (GAFlipCoin(pmut)) {
        int geneX = GARandomInt(0, genome.width()-1);
        int geneY = GARandomInt(0, genome.height()-1);
        mut = 1;
        genome.gene(geneX, geneY, genome.gene(geneX, geneY)+GAGaussianFloat(1));
    }
    return mut;
}

/**
 * The objective is the distance
 */
float Objective(GAGenome & g)
{
    double x1, y1, z1;
    double x2, y2, z2;
    GeneticExperience *experience = (GeneticExperience *)g.userData();

    if (experience == NULL) {
        cout << "Score: unable to find the experience" << endl;
        return 0;
    }

    cout << "Scoring... " << flush;

    experience->updateSplines(g);
    VREPClient &vrep = experience->getVrep();

    //Main Loop
    vrep.start();
    x1 = vrep.readPositionTrackerX();
    y1 = vrep.readPositionTrackerY();
    z1 = vrep.readPositionTrackerZ();
    for (double t=0; t<SIMULATION_TIME; t+=0.02) {
        //Display state
        //Do next step
        vrep.nextStep();

        //Compute motors move
        primitive_step(vrep, experience->getSplines());
    }
    x2 = vrep.readPositionTrackerX();
    y2 = vrep.readPositionTrackerY();
    z2 = vrep.readPositionTrackerZ();
    //End simulation
    vrep.stop();

    double score = sqrt(pow(x1-x2,2)+pow(y1-y2,2)+pow(z1-z2,2));
    cout << score << endl;
    return score;
}


GeneticExperience::GeneticExperience(VREPClient &vrep_)
    : genome(SPLINE_NB_POINTS, vrep_.countMotors(), Objective, (void *)this),
    splines(NULL),
    vrep(vrep_)
{
    genome.initializer(::RandomInitializer);
    genome.mutator(::Mutator);
    splines = new Spline[vrep.countMotors()];
}

GeneticExperience::~GeneticExperience()
{
    if (splines != NULL) {
        delete splines;
    }
}

void GeneticExperience::run()
{
    cout << "Running the genetic experience" << endl;
    GASimpleGA ga(genome);
    ga.populationSize(POPULATION_SIZE);
    ga.nGenerations(NB_GENERATIONS);
    ga.pMutation(P_MUTATION);
    primitive_init(vrep);

    ga.initialize();

    while (!ga.done()) {
        ga.step();  
        cout << ga.statistics() << endl;                   
        cout << ga.statistics().bestIndividual() << endl;
    }
}
        
/**
 * Gets the splines
 */
Spline *GeneticExperience::getSplines()
{
    return splines;
}

VREPClient &GeneticExperience::getVrep()
{
    return vrep;
}

/**
 * Update the splines according to a genome
 */
void GeneticExperience::updateSplines(GAGenome &g)
{
    SplinesGenome &genome = (SplinesGenome&)g;
    int motor, index;

    for (motor=0; motor<genome.height(); motor++) {
        Spline &spline = splines[motor];
        spline.clear();

        for (index=0; index<SPLINE_NB_POINTS; index++) {
            spline.addPoint(index*1.0/SPLINE_NB_POINTS, genome.gene(index, motor));
            //cout << index << "," << motor << ": " << genome.gene(index, motor) << endl;
        }
        //spline.print();
    }
}

