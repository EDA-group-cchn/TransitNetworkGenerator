#ifndef TRANSIT_TSP_H
#define TRANSIT_TSP_H

#include "Graph.h"
#include <limits>
#include <vector>

class TSP {
private:
    float dist[20][20];
    long long parent[20][1 << 20];
    float memo[20][1 << 20];
    Graph * graph;

    float tsp(int pos, int bitmask, bool isClosed);
public:
    TSP(Graph *graph);

    std::pair<float, std::vector<short> > run(bool isClosed);
};


#endif //TRANSIT_TSP_H
