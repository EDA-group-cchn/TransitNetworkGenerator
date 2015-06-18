#ifndef TRANSIT_GRAPH_H
#define TRANSIT_GRAPH_H

#include <vector>

class Graph {
protected:
  using std::vector;
  using std::size_t;
  vector<int> adj, prev, last;
  vector<float> weight;
  int edgeCount;
public:
  Graph() { }
  Graph(int vertexCount) : last((size_t)vertexCount, -1), edgeCount(0) { }
  Graph(int vertexCount, int edgeCount) : Graph(vertexCount),
                                          adj((size_t)edgeCount, -1),
                                          prev((size_t)edgeCount, -1) { }
  int getVertexCount() const {
    return (int)last.size();
  }
  int getEdgeCount() const {
    return edgeCount;
  }
  int getAdjVertex(int edge) const {
    return adj[edge];
  }
  float getWeight(int edge) const {
    return weight[edge];
  }
  void addVertex() {
    last.push_back(-1);
  }
  void addEdge(int from, int to, float weight);
};


#endif //TRANSIT_GRAPH_H
