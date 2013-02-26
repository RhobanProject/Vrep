#include <iostream>
#include <ga/ga.h>

using namespace std;

float Objective(GAGenome&);

void Initializer(GAGenome &g)
{
    GA2DArrayGenome<float> &genome = (GA2DArrayGenome<float>&)g;
    for (int x=0; x<genome.width(); x++) {
        for (int y=0; y<genome.height(); y++) {
            genome.gene(x, y, GARandomFloat(-1, 1));
        }
    }
}

int Mutator(GAGenome &g, float pmut)
{
    GA2DArrayGenome<float> &genome = (GA2DArrayGenome<float>&)g;
    int mut = 0;
    while (GAFlipCoin(pmut)) {
        int geneX = GARandomInt(0, genome.width()-1);
        int geneY = GARandomInt(0, genome.height()-1);
        mut = 1;
        genome.gene(geneX, geneY, genome.gene(geneX, geneY)+GAGaussianFloat(1));
    }
    return mut;
}

main(){
    GA2DArrayGenome<float> genome(10, 8, Objective);     // create a genome
    genome.initializer(::Initializer);
    genome.mutator(::Mutator);

    GASimpleGA ga(genome);                            // create the GA
    ga.populationSize(100);
    ga.nGenerations(500);
    ga.pMutation(0.2);

    while (!ga.done()) {
        ga.evolve();                                      // evolve the GA
        cout << ga.statistics() << endl;                   // print out the results
        cout << ga.statistics().bestIndividual() << endl;                   // print out the results
        usleep(100000);
    }
}

    float
Objective(GAGenome & g)
{
    GA2DArrayGenome<float> &genome = (GA2DArrayGenome<float>&)g;
    float score=1000.0;
    for (int x=0; x<genome.width(); x++) {
        for (int y=0; y<genome.height(); y++) {
            if (x == 0 || y == 0) {
                score += genome.gene(x, y);
            } else {
                score -= genome.gene(x, y);
            }
        }
    }
    return score;
}
