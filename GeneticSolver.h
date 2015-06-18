#ifndef TRANSIT_GENETICSOLVER_H
#define TRANSIT_GENETICSOLVER_H

#include <vector>
#include <unordered_map>

#include "Graph.h"
#include "Chromosome.h"
#include "Passenger.h"


class GeneticSolver {
private:
  typedef std::unordered_map<Gene, Route> Cache;
  Cache routesCache;
  std::vector<Chromosome> generation;
  const Graph &graph;
  const std::vector<Passenger> &passengers;
public:
  GeneticSolver(const Graph &graph, const std::vector<Passenger> &passengers) :
      graph(graph), passengers(passengers) { }
  Chromosome solve(int numIterations);
};


#endif //TRANSIT_GENETICSOLVER_H
