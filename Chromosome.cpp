#include <limits>
#include "Chromosome.h"

Graph Chromosome::generateSolutionGraph(const Graph &original,
                                         RoutesCache &routesCache) const {
  
  Graph new_graph(original.getVertexCount());
  for (const Gene &g : genes) {
    Route r;
    if (routesCache.check(g)) {
      r = routesCache.get(g);
    } else{
      r = g.calculateBestRoute(original);
      routesCache.add(g, r);
    }
    int from = r.getFirstVertex();
    std::vector<int> edges = r.getEdgeList();
    for(int e : edges) {
      new_graph.addEdge(from, original.getAdjacentVertex(e),
                        original.getWeight(e));
    }
  }
  return new_graph;
}

float Chromosome::calculateCost(const Graph &original,
                                const std::vector<Passenger> &passengers,
                                RoutesCache &routesCache) const {
  Graph solutionGraph = generateSolutionGraph(original, routesCache);
  Dijkstra dijkstra(solutionGraph);
  for (int i = 0; i < original.getVertexCount(); ++i)
    dijkstra.makeDijkstra(i);
  float meanCost = 0;
  for (int i = 0; i < passengers.size(); ++i) {
    const Passenger &passenger = passengers[i];
    float cost = dijkstra.getWeight(passenger.getBusStopStartId(),
                                        passenger.getBusStopEndId());
    if (cost < std::numeric_limits<float>::max())
      cost += passenger.getBusStopStartDistance() +
          passenger.getBusStopEndDistance();
    else
      cost += meanCost + 100; // a penalty for not serving this passenger
    meanCost = (meanCost * i + cost) / (i + 1);
  }
  return meanCost;
}
