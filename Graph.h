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
  Graph(std::size_t vertexCount, std::size_t edgeCount=0) :
      last(vertexCount, -1) {
    if (edgeCount > 0) {
      adj.reserve(edgeCount);
      prev.reserve(edgeCount);
    }
  }
  std::size_t getVertexCount() const {
    return last.size();
  }
  std::size_t getEdgeCount() const {
    return adj.size();
  }
  int getAdjacentVertex(int edge) const {
    return adj[edge];
  }
  int searchEdge(int from, int to) const;
  float getWeight(int edge) const {
    return weight[edge];
  }
  void addEdge(int from, int to, float weight);

  IncidenceEdgeList getIncidentEdges(int vertex) const;

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
