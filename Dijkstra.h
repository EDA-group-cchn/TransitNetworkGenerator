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
  weight **dist;
  std::pair<index, edge> **father;
  const Graph *graph;

public:
  Dijkstra(const Graph *graph) : graph(graph) {
    size_t n = graph->getVertexCount();
    dist = new weight* [n];
    father = new std::pair<index, edge>* [n];
    dist[0] = new weight[n * n];
    father[0] = new std::pair<index, edge> [n * n];
    for (size_t i = 1; i < n; ++i) {
      dist[i] = dist[i - 1] + n;
      father[i] = father[i - 1] + n;
    }
  }
  Dijkstra(const Graph *graph, index from) : Dijkstra(graph) {
    makeDijkstra(from);
  }
  ~Dijkstra() {
    delete[] dist[0];
    delete[] father[0];
    delete[] dist;
    delete[] father;
  }

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