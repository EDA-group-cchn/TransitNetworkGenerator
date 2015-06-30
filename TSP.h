#ifndef TRANSIT_TSP_H
#define TRANSIT_TSP_H

#include "Graph.h"
#include "Route.h"
#include <limits>
#include <vector>

class TSP {
private:
    int child[20][1 << 20];
    float memo[20][1 << 20];
    const Graph graph;

    float tsp(int pos, int bitmask, bool isClosed);
public:
    TSP(const Graph &graph);

    Route run(bool isClosed);
};


#endif //TRANSIT_TSP_H
