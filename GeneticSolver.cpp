#include "GeneticSolver.h"

Graph GeneticSolver::solve(int numRoutes, int numIterations,
                           int generationSize) {
  generateInitialPopulation(numRoutes, generationSize);
  return Graph();
}

void GeneticSolver::generateInitialPopulation(int numRoutes,
                                              int generationSize) {
  generation.resize((std::size_t)generationSize);
  costs.resize((std::size_t)generationSize);
  #pragma omp parallel for
  for (int i = 0; i < generationSize; ++i) {
    Chromosome &chromosome = generation[i];
    for (int j = 0; j < numRoutes; ++j) {
      int numStops = Random::uniformInt(10, 20);
      bool closedRoute = Random::boolean();
      chromosome.addGene(Gene::generateRandomGene(numStops, closedRoute));
    }
    costs[i] = chromosome.calculateCost(graph, passengers, routesCache);
  }
}
