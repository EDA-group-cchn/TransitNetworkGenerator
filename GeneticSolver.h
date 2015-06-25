#ifndef TRANSIT_GENETICSOLVER_H
#define TRANSIT_GENETICSOLVER_H

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
  std::vector<Chromosome> generation;
  std::vector<double> costs;
  const Graph &graph;
  const std::vector<Passenger> &passengers;
  void generateInitialPopulation(int numRoutes, int generationSize);
public:
  GeneticSolver(const Graph &graph, const std::vector<Passenger> &passengers) :
      graph(graph), passengers(passengers) { }
  Graph solve(int numRoutes, int numIterations, int generationSize);
};


#endif //TRANSIT_GENETICSOLVER_H
