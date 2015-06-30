#include "Graph.h"


void Graph::addEdge(int from, int to, float weight) {
  adj.push_back(to);
  prev.push_back(last[from]);
  last[from] = (int)adj.size() - 1;
  this->weight.push_back(weight);
}

IncidenceEdgeList Graph::getIncidentEdges(int vertex) const {
  return IncidenceEdgeList(vertex, *this);
}

int Graph::searchEdge(int from, int to) const {
  for(int e : getIncidentEdges(from))
    if(getAdjacentVertex(e) == to)
      return e;

  return -1;
}
