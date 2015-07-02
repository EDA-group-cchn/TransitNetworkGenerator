#ifndef TRANSIT_GENETICSOLVER_H
#define TRANSIT_GENETICSOLVER_H

#include <iostream>
#include <vector>
#include <unordered_map>

#include "Random.h"
#include "RoutesCache.h"
#include "Graph.h"
#include "Chromosome.h"
#include "Passenger.h"


class GeneticSolver {
private:
  RoutesCache routesCache;
  std::vector<Chromosome *> generation, nextGeneration;
  std::vector<double> costs, nextCosts, distribution;
  const Graph *graph;
  const std::vector<Passenger> &passengers;
  size_t bestId;
  void generateInitialPopulation(size_t numRoutes,
                                                size_t generationSize,
                                                Random &random);
  void generateNextPopulation(size_t generationSize,
                                             Random &random);
  void generateAccumulatedDistribution();
  size_t getBestSolutionId();
public:
  GeneticSolver(const Graph *graph, const std::vector<Passenger> &passengers) :
      graph(graph), passengers(passengers) { }
  std::vector<Route> solve(size_t numRoutes, size_t numIterations,
                           size_t generationSize);
  Chromosome *doMutation(size_t id, Random &random);
  Chromosome *doCrossOver(size_t id1, size_t id2, Random &random);
};


#endif //TRANSIT_GENETICSOLVER_H
