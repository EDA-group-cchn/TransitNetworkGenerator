#ifndef TRANSIT_DIJKSTRA_H
#define TRANSIT_DIJKSTRA_H

#include "Graph.h"
#include "Route.h"
#include <vector>
#include <queue>
#include <algorithm>
#include <limits>


class Dijkstra {
private:
  typedef float weight;
  typedef int index;
  typedef int edge;
  std::vector<std::vector<weight> > dist;
  std::vector<std::vector< std::pair <index, edge > > > father;
  const Graph *graph;

public:
  Dijkstra(const Graph *graph) : graph(graph) {
    size_t n = graph->getVertexCount();
    dist.resize(n);
    father.resize(n);
    for (size_t i = 0; i < n; ++i) {
      father[i].resize(n);
      dist[i].resize(n);
    }
  }
  Dijkstra(const Graph *graph, index from) : Dijkstra(graph) {
    makeDijkstra(from);
  }
  ~Dijkstra(){}

  void makeDijkstra(index from);

  weight getWeight(index from, index to) const {
    return dist[from][to];
  }

  Route getPath(index from, index to) const;

  const Graph * getGraph() const {
    return graph;
  }

};

#endif //TRANSIT_DIJKSTRA_H