#ifndef TRANSIT_TSP_H
#define TRANSIT_TSP_H

#include "Graph.h"
#include <limits>
#include <vector>

class TSP {
private:
    short nVertices;
    float dist[20][20];
    long long parent[1 << 20];
    float memo[20][1 << 20];

    float tsp(int pos, long long bitmask, bool isClosed);
public:
    TSP(Graph graph);

    std::pair<float, std::vector<short> > run(bool isClosed);
};


#endif //TRANSIT_TSP_H
