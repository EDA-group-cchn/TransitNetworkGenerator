#include "SubGraph.h"
#include "Dijkstra.h"
#include <iostream>

SubGraph SubGraph::generateSubGraph(const Graph &g, std::vector<int> vertices) {
  
  SubGraph subg(vertices.size());
  Dijkstra d (g);

  for (int i = 0 ; i < vertices.size(); ++i){
    subg.originalVertexId[i] = vertices[i];
    d.makeDijkstra(vertices[i]);
    for(int j = 0; j < vertices.size(); ++j){
        subg.addEdge(i, j, d.getWeight(vertices[i], vertices[j]));
    }
  }

  return subg;
}


Route SubGraph::getOriginalRoute(const Graph &g, const Route &r)
{
    Dijkstra d (g, r.getFirstVertex());
    std::vector<int> edges = r.getEdgeList();
    std::vector<int> edges_result;
    int from = getOriginalVertexId(r.getFirstVertex());
    int tmp_from = from;
    int tmp_to;
    d.makeDijkstra(from);

    for (int i = 0 ; i < edges.size(); ++i){
        tmp_to = getOriginalVertexId(g.getAdjacentVertex(edges[i]));
        Route tmp_route = d.getPath(tmp_from, tmp_to);
        std::vector<int> tmp_ed = tmp_route.getEdgeList();
   
        edges_result.insert(edges_result.end(), 
                            tmp_route.getEdgeList().begin(),
                            tmp_route.getEdgeList().end()) ;
        tmp_from = tmp_to;
    }

    return Route(from, edges_result);




}