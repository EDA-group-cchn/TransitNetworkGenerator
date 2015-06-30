#ifndef TRANSIT_DIJKSTRA_H
#define TRANSIT_DIJKSTRA_H

#include "Graph.h"
#include "Route.h"
#include <vector>
#include <queue>
#include <algorithm>
#include <limits>


class Dijkstra
{
public:
  typedef float weight;
  typedef int index;
  typedef int edge;
  Dijkstra(const Graph & graph)  :  graph(graph) {
    int n = graph.getVertexCount();
    dist.resize((std::size_t)n);
    father.resize((std::size_t)n);
    for (int i = 0; i < n; ++i)
    {
      father[i].resize((std::size_t)n);
      dist[i].resize((std::size_t)n);
    }
  }
  Dijkstra(const Graph & graph, index from) : Dijkstra(graph)
  {
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