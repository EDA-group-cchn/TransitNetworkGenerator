#include "SubGraph.h"


Route SubGraph::getOriginalRoute(const Route &r)
{
    std::vector<int> edges = r.getEdgeList();
    std::vector<int> edges_result;
    int from = getOriginalVertexId(r.getFirstVertex());
    int tmp_from = from;
    int tmp_to;
    
    for (int i = 0 ; i < edges.size(); ++i){
        tmp_to = getOriginalVertexId(graph.getAdjacentVertex(edges[i]));
        Route tmp_route = originalDijkstra.getPath(tmp_from, tmp_to);
        std::vector<int> tmp_ed = tmp_route.getEdgeList();
        edges_result.insert(edges_result.end(), 
                            tmp_route.getEdgeList().begin(),
                            tmp_route.getEdgeList().end()) ;
        tmp_from = tmp_to;
    }

    return Route(from, edges_result);


}