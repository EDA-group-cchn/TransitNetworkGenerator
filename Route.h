#ifndef TRANSIT_ROUTE_H
#define TRANSIT_ROUTE_H

#include <vector>

class Route {
private:
  using std::vector;
  int firstVertex;
  vector<int> edgeList;
public:
  Route(int firstVertex) : firstVertex(firstVertex) { }
  Route(int firstVertex, const vector<int> &edgeList) : Route(firstVertex),
                                                        edgeList(edgeList) { }
  int getFirstVertex() const {
    return firstVertex;
  }
  const vector<int> &getEdgeList() const {
    return edgeList;
  }
};


#endif //TRANSIT_ROUTE_H
