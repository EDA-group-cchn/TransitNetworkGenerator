#ifndef TRANSIT_ROUTE_H
#define TRANSIT_ROUTE_H

#include <vector>

class Route {
private:
  int firstVertex;
  std::vector<int> edgeList;
public:
  Route(int firstVertex=-1) : firstVertex(firstVertex) { }
  Route(int firstVertex, const std::vector<int> &edgeList) :
      firstVertex(firstVertex), edgeList(edgeList) { }
  int getFirstVertex() const {
    return firstVertex;
  }
  const std::vector<int> &getEdgeList() const {
    return edgeList;
  }
};


#endif //TRANSIT_ROUTE_H
