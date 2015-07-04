#include "SubGraph.h"


Route SubGraph::getOriginalRoute(const std::vector<int> &r)
{
  std::vector<int> edges_result;
  int from = getOriginalVertexId(r[0]);

  for (size_t i = 1; i < r.size(); ++i) {
    Route tmp_route = dijkstra->getPath(getOriginalVertexId(r[i-1]),
                                        getOriginalVertexId(r[i]));
    edges_result.insert(edges_result.end(),
                        tmp_route.getEdgeList().begin(),
                        tmp_route.getEdgeList().end()) ;
  }

  return Route(from, edges_result);
}