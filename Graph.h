#ifndef TRANSIT_GRAPH_H
#define TRANSIT_GRAPH_H

#include <vector>

class Graph {
protected:
  using std::vector;
  using std::size_t;
  vector<int> adj, prev, last;
  vector<float> weight;
public:
  Graph() { }
  Graph(int vertexCount) : last((size_t)vertexCount, -1) { }
  Graph(int vertexCount, int edgeCount) : Graph(vertexCount),
                                          adj(vertexCount, -1),
                                          prev(vertexCount, -1) { }
  size_t getVertexCount() const {
    return last.size();
  }
  size_t getEdgeCount() const {
    return adj.size();
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
