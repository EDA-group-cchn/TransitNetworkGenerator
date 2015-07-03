#ifndef TRANSIT_SUBGRAPH_H
#define TRANSIT_SUBGRAPH_H

#include "Dijkstra.h"
#include "Graph.h"
#include "Route.h"
#include <vector>

class SubGraph : public Graph {
private:
  std::vector<int> originalVertexId;
  const Dijkstra *dijkstra;
public:
  SubGraph(const Dijkstra *dijkstra, std::vector<int> vertices) :
      Graph(vertices.size()), dijkstra(dijkstra),
      originalVertexId(vertices.size(), -1) {
    for (int i = 0; i < vertices.size(); ++i) {
      originalVertexId[i] = vertices[i];
      for (int j = 0; j < vertices.size(); ++j)
        addEdge(i, j, dijkstra->getWeight(vertices[i], vertices[j]));
    }
  }
  int getOriginalVertexId(int vertex) const {
    return originalVertexId[vertex];
  }
  
  Route getOriginalRoute(const Route &r);
};


#endif //TRANSIT_SUBGRAPH_H
