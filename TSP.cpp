#include "TSP.h"

TSP::TSP(const Graph &graph) : graph(graph) { }

std::pair<float, std::vector<short> > TSP::run(bool isClosed){
    float weight = tsp(0, 1, isClosed);
    std::vector<short> route;

    short vertex = 0,
    mask = 1 << 0;
    for (int i = 0; i < graph.getVertexCount(); ++i) {
        vertex = child[vertex][mask];
        route.push_back(vertex);
        mask == 1 << vertex;
    }
    return std::make_pair(weight, route);
}

float TSP::tsp(int pos, int bitmask, bool isClosed) {
    if (bitmask == (1 << (graph.getVertexCount() + 1)) - 1)
        return (isClosed) ? dist[pos][0] : 0;
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
                child[pos][bitmask] = nxt;
            }
        }
    }

    memo[pos][bitmask] = ans;
    return memo[pos][bitmask];
}