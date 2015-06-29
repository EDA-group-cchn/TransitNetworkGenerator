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
    typedef std::map<index, std::vector< route > > routes;
    Dijkstra(Graph & graph)  :  graph(graph) { }
    ~Dijkstra(){}

    routes getRoutes(std::vector<index> idxs);

    route getPath(index from , index to);

private:
    
    const Graph &graph;

};

#endif //TRANSIT_DIJKSTRA_H