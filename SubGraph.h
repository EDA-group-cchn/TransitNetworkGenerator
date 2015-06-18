#ifndef TRANSIT_SUBGRAPH_H
#define TRANSIT_SUBGRAPH_H


#include "Graph.h"

class SubGraph : public Graph {
private:
  vector<int> originalVertexId;
  vector<int> originalEdgeId;
public:
  SubGraph() : Graph() { }
  SubGraph(int vertexCount) : Graph(vertexCount),
                              originalVertexId((size_t)vertexCount, -1) { }
  SubGraph(int vertexCount, int edgeCount) : Graph(vertexCount, edgeCount),
                                             originalVertexId(
                                                 (size_t)vertexCount, -1),
                                             originalEdgeId(
                                                 (size_t)edgeCount, -1) { }
  int getOriginalVertexId(int vertex) const {
    return originalVertexId[vertex];
  }
  int getOriginalEdgeId(int edge) const {
    return originalEdgeId[edge];
  }
  static SubGraph generateSubGraph(const Graph &g, vector<int> vertices);
};


#endif //TRANSIT_SUBGRAPH_H
