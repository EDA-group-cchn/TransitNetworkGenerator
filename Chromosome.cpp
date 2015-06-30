#include "Chromosome.h"

Graph Chromosome::generateSolutionGraph(const Graph &original,
                                         RoutesCache &routesCache) const {
  
  Graph new_graph(original.getVertexCount());
  for (Gene g : genes)
  {
    Route r;
    if (routesCache.check(g)){
        r = routesCache.get(g);
    }
    else{
        r = g.calculateBestRoute(original);
    }
    int from = r.getFirstVertex();
    std::vector<int> edges = r.getEdgeList();
    for(int e : edges)
    {
        new_graph.addEdge(from, original.getAdjacentVertex(e),
                          original.getWeight(e));
    }

  }
  return new_graph;
}

float Chromosome::calculateCost(const Graph &original,
                                const std::vector<Passenger> &passengers,
                                RoutesCache &routesCache) const {
  return 0;
}
