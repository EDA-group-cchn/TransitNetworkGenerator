#ifndef TRANSIT_SUBGRAPH_H
#define TRANSIT_SUBGRAPH_H


#include "Graph.h"
#include "Route.h"

class SubGraph : public Graph {
private:
  std::vector<int> originalVertexId;
public:
  SubGraph() : Graph() { }
  SubGraph(int vertexCount) :
      Graph(vertexCount),
      originalVertexId((std::size_t)vertexCount, -1) { }
  int getOriginalVertexId(int vertex) const {
    return originalVertexId[vertex];
  }
  static SubGraph generateSubGraph(const Graph &g, std::vector<int> vertices);
  Route getOriginalRoute(const Graph &g, const Route &r);
};


#endif //TRANSIT_SUBGRAPH_H
