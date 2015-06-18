#ifndef TRANSIT_GRAPH_H
#define TRANSIT_GRAPH_H

#include <vector>


class IncidenceEdgeList;


class Graph {
protected:
  std::vector<int> adj, prev, last;
  std::vector<float> weight;
public:
  friend class IncidenceEdgeList;
  Graph() { }
  Graph(int vertexCount, int edgeCount=0) : last((std::size_t)vertexCount, -1) {
    if (edgeCount > 0) {
      adj.reserve((std::size_t)edgeCount);
      prev.reserve((std::size_t)edgeCount);
    }
  }
  int getVertexCount() const {
    return (int)last.size();
  }
  int getEdgeCount() const {
    return (int)adj.size();
  }
  int getAdjacentVertex(int edge) const {
    return adj[edge];
  }
  float getWeight(int edge) const {
    return weight[edge];
  }
  void addVertex() {
    last.push_back(-1);
  }
  void addEdge(int from, int to, float weight);

  IncidenceEdgeList getIncidentEdges(int vertex) const;

  template <typename Operation>
  void forEachIncidentEdge(int vertex, Operation &&f) {
    for (int edge = last[vertex]; edge != -1; edge = prev[edge])
      f(edge);
  }
};


class IncidenceEdgeList {
private:
  int vertex;
  const Graph &graph;
public:
  IncidenceEdgeList(int vertex, const Graph &graph) : vertex(vertex),
                                                      graph(graph) { }
  class iterator {
  private:
    int edge;
    const Graph &graph;
  public:
    iterator(int edge, const Graph &graph) : edge(edge), graph(graph) { }
    bool operator != (const iterator &other) {
      return edge != other.edge;
    }
    iterator &operator ++() {
      edge = graph.prev[edge];
      return *this;
    }
    iterator operator ++(int) {
      return iterator(graph.prev[edge], graph);
    }
    int operator *() const {
      return edge;
    }
  };
  iterator begin() {
    return iterator(graph.last[vertex], graph);
  }
  iterator end() {
    return iterator(-1, graph);
  }
};

#endif //TRANSIT_GRAPH_H
