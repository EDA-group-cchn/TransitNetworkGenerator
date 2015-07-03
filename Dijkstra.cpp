#include "Dijkstra.h"


struct comparator{
  bool operator() ( std::pair<int, float> i, std::pair <int, float> j ){
    return i.second > j.second;
  }
};

void Dijkstra::makeDijkstra(index from)
{
  std::priority_queue< std::pair<int, float>,
      std::vector<std::pair<int, float>>, comparator> route_queue;

  std::vector<bool> seen(graph->getVertexCount());

  std::fill(dist[from], dist[from] + graph->getVertexCount(),
            std::numeric_limits<float>::max());

  dist[from][from]  = 0;
  route_queue.push(std::make_pair(from, 0));

  while (route_queue.size() != 0) {
    int u  = route_queue.top().first;
    route_queue.pop();
    if (seen[u])
      continue;
    seen[u] = true;

    for (int e : graph->getIncidentEdges(u)) {

      int v = graph->getAdjacentVertex(e);
      if (dist[from][v] > (dist[from][u] + graph->getWeight(e))) {

        dist[from][v] = dist[from][u] + graph->getWeight(e);
        father[from][v] = std::make_pair(u, e);

        route_queue.push(std::make_pair(v, dist[from][v]));
      }
    }
  }
}

Route Dijkstra::getPath(index from, index to) const {
  index temp = to;
  std::vector<int> edges;
  while (temp != from) {
    edges.push_back(father[from][temp].second);
    temp = father[from][temp].first;
  }

  std::reverse(edges.begin(), edges.end());

  return Route(from, edges);
}