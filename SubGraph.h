#ifndef TRANSIT_SUBGRAPH_H
#define TRANSIT_SUBGRAPH_H


#include "Graph.h"

class SubGraph : public Graph {
private:
  std::vector<int> originalVertexId;
  std::vector<int> originalEdgeId;
public:
  SubGraph() : Graph() { }
  SubGraph(int vertexCount, int edgeCount=0) :
      Graph(vertexCount, edgeCount),
      originalVertexId((std::size_t)vertexCount, -1),
      originalEdgeId((std::size_t)edgeCount, -1) { }
  int getOriginalVertexId(int vertex) const {
    return originalVertexId[vertex];
  }
  int getOriginalEdgeId(int edge) const {
    return originalEdgeId[edge];
  }
  static SubGraph generateSubGraph(const Graph &g, std::vector<int> vertices);
};


#endif //TRANSIT_SUBGRAPH_H
