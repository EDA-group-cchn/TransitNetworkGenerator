#ifndef TRANSIT_DIJKSTRA_H
#define TRANSIT_DIJKSTRA_H

#include "Graph.h"
#include <map>
#include <vector>
#include <queue>

class Dijkstra
{
public:
    typedef std::vector<int> vertexArray;
    typedef int weight;
    typedef int index;
    typedef std::map<index, std::pair <index, weight> > route;

    Dijkstra(Graph & graph)  :  graph(graph) { }
    ~Dijkstra(){}

    std::map<index, route> &getRoutes() {
        return routes;
    }
    route getPath(index from , index to);

private:
    std::map<index, route> routes;
    const Graph &graph;

};

#endif //TRANSIT_DIJKSTRA_H