#include "SubGraph.h"


Route SubGraph::getOriginalRoute(const Route &r)
{
    std::vector<int> edges = r.getEdgeList();
    std::vector<int> edges_result;
    int from = getOriginalVertexId(r.getFirstVertex());
    int tmp_from = from, tmp_to;

    for (int e : edges) {
        tmp_to = getOriginalVertexId(getAdjacentVertex(e));
        Route tmp_route = originalDijkstra.getPath(tmp_from, tmp_to);
        edges_result.insert(edges_result.end(),
                            tmp_route.getEdgeList().begin(),
                            tmp_route.getEdgeList().end()) ;
        tmp_from = tmp_to;
    }

    return Route(from, edges_result);
}