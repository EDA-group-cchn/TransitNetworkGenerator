#ifndef TRANSIT_TSP_H
#define TRANSIT_TSP_H

#include "Graph.h"
#include "Route.h"
#include <limits>
#include <vector>

class TSP {
private:
  int **child;
  float **memo;
  const Graph *graph;

  float tsp(int pos, int bitMask, bool isClosed);
public:
  TSP(const Graph *graph);
  ~TSP();

  std::vector<int> run(bool isClosed);
};


#endif //TRANSIT_TSP_H
