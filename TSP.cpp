#include "TSP.h"

TSP::TSP(const Graph &graph) : graph(graph) {
    std::fill(memo[0], memo[0] + sizeof memo, -1);
}

Route TSP::run(bool isClosed){
    tsp(0, 1, isClosed);
    std::vector<int> route;

    int vertex = 0,
    mask = 1 << 0;
    for (int i = 0; i < graph.getVertexCount(); ++i) {
        vertex = graph.getAdjacentVertex(child[vertex][mask]);
        route.push_back(child[vertex][mask]);
        mask == 1 << vertex;
    }
    return Route(0, route);
}

float TSP::tsp(int pos, int bitmask, bool isClosed) {
    if (bitmask == (1 << graph.getVertexCount()) - 1)
        return (isClosed) ? graph.getWeight(graph.searchEdge(pos, 0)) : 0;
    if (memo[pos][bitmask] != -1)
        return memo[pos][bitmask];

    float ans = std::numeric_limits<float>::max();
    float tmp;

    for (int e : graph.getIncidentEdges(pos)) {
        int nxt = graph.getAdjacentVertex(e);
        if (nxt != pos && !(bitmask & (1 << nxt))) {
            tmp = graph.getWeight(e) + tsp(nxt, bitmask | (1 << nxt), isClosed);
            if(ans < tmp) {
                ans = tmp;
                child[pos][bitmask] = e;
            }
        }
    }

    memo[pos][bitmask] = ans;
    return memo[pos][bitmask];
}