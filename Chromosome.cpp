#include "Chromosome.h"

std::pair<Graph, double> Chromosome::generateSolution(
    const Dijkstra *dijkstra,
    RoutesCache &routesCache) const {
  const Graph *original = dijkstra->getGraph();
  Graph newGraph(original->getVertexCount());
  double maxRouteLength = 0;
  for (const Gene &g : genes) {
    std::pair<Route, Route> r;
    if (routesCache.check(g)) {
      r = routesCache.get(g);
    } else{
      r = g.calculateBestRoute(dijkstra);
      routesCache.add(g, r);
    }
    double routeLength1 = addRouteToGraph(original, &newGraph, r.first),
           routeLength2 = addRouteToGraph(original, &newGraph, r.second);
    maxRouteLength = std::max(maxRouteLength,
                              std::max(routeLength1, routeLength2));
  }
  return std::make_pair(newGraph, maxRouteLength);
}

double Chromosome::calculateCost(const Dijkstra *originalDijkstra,
                                 const std::vector<Passenger> &passengers,
                                 RoutesCache &routesCache) const {
  auto solution = generateSolution(originalDijkstra, routesCache);
  Graph &solutionGraph = solution.first;
  double &maxRouteLength = solution.second;

  Dijkstra dijkstra(&solutionGraph);
  for (int i = 0; i < solutionGraph.getVertexCount(); ++i)
    dijkstra.makeDijkstra(i);
  double meanCost = 0;
  for (int i = 0; i < passengers.size(); ++i) {
    const Passenger &passenger = passengers[i];
    double cost = dijkstra.getWeight(passenger.getBusStopStartId(),
                                     passenger.getBusStopEndId());
    if (cost < std::numeric_limits<float>::max())
      cost += passenger.getBusStopStartDistance() +
          passenger.getBusStopEndDistance();
    else
      cost = meanCost + 30; // a penalty for not serving this passenger
    meanCost = (meanCost * i + cost) / (i + 1);
  }

  return meanCost * 0.35 + maxRouteLength * 0.65;
}

double Chromosome::addRouteToGraph(const Graph *original, Graph *newGraph,
                                   const Route &route) {
  int from = route.getFirstVertex();
  std::vector<int> edges = route.getEdgeList();
  double routeLength = 0;
  for (int e : edges) {
    routeLength += original->getWeight(e);
    int to = original->getAdjacentVertex(e);
    newGraph->addEdge(from, to, original->getWeight(e));
    from = to;
  }
  return routeLength;
}
