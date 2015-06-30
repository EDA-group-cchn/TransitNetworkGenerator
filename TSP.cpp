#include "TSP.h"

TSP::TSP(Graph graph) {
    nVertices = graph.getVertexCount();

    for(int i=0;i<nVertices;i++) {
        for (int e : graph.getIncidentEdges(i)) {
            int v = graph.getAdjacentVertex(e);
            dist[i][v] = graph.getWeight(e);
        }
    }
}

std::pair<float, std::vector<short> > TSP::run(bool isClosed){
    float weight = tsp(0, 1, isClosed);
    std::vector<short> route;

    long long bitmask = (1 << (nVertices + 1)) - 1;
    for(int i=0;i<nVertices;i++)
    {
        bitmask = parent[bitmask];
        route.push_back(bitmask);
    }
    return std::make_pair(weight, route);
}

float TSP::tsp(int pos, int bitmask, bool isClosed) {
    if (bitmask == (1 << (nVertices + 1)) - 1)
        return (isClosed) ? dist[pos][0] : 0;
    if (memo[pos][bitmask] != -1)
        return memo[pos][bitmask];

    float ans = std::numeric_limits<float>::max();
    float tmp;
    for (int nxt = 0; nxt <= nVertices; nxt++) {
        if (nxt != pos && !(bitmask & (1 << nxt))) {
            tmp =  dist[pos][nxt] + tsp(nxt, bitmask | (1 << nxt), isClosed);
            if(ans < tmp) {
                ans = tmp;
                parent[bitmask] = bitmask | (1 << nxt);
            }
        }
    }

    memo[pos][bitmask] = ans;
    return memo[pos][bitmask];
}