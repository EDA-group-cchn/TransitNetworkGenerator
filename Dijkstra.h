#ifndef TRANSIT_DIJKSTRA_H
#define TRANSIT_DIJKSTRA_H

#include "Graph.h"
#include "Route.h"
#include <map>
#include <vector>
#include <queue>
#include <iostream>

class Dijkstra
{
public:
    typedef float weight;
    typedef int index;
    typedef int edge;
    Dijkstra(Graph & graph)  :  graph(graph){
        int n = graph.getVertexCount();
        dist.reserve(n);
        father.reserve(n);
        for (int i = 0; i < n; ++i)
        {
            father[i].reserve(n);
            dist[i].reserve(n);
        }
    }
    Dijkstra(Graph & graph, index from) : graph(graph)
    {
        int n = graph.getVertexCount();
        dist.reserve(n);
        father.reserve(n);
        for (int i = 0; i < n; ++i)
        {
            father[i].reserve(n);
            dist[i].reserve(n);
        }
        makeDijkstra(from);

    }  
    ~Dijkstra(){}


    void makeDijkstra(index from);

    weight getWeight(index from, index to){
        return dist[from][to];
    }

    Route getPath(index from, index to);


private:
    std::vector<std::vector<weight> > dist;
    std::vector<std::vector< std::pair <index, edge > > > father;
    const Graph &graph;

};

#endif //TRANSIT_DIJKSTRA_H