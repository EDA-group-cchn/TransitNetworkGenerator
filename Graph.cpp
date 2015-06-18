#include "Graph.h"


void Graph::addEdge(int from, int to, float weight) {
  adj.push_back(to);
  prev.push_back(last[from]);
  last[from] = (int)adj.size() - 1;
}

IncidenceEdgeList Graph::getIncidentEdges(int vertex) const {
  return IncidenceEdgeList(vertex, *this);
}
