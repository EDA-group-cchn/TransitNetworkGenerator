#include "Dijkstra.h"
#include <vector>
#include <queue>
#include <algorithm>
#include <limits>

#define INF 999999

struct comparator{
    bool operator() ( std::pair<int, float> i, std::pair <int, float> j ){
        return i.second > j.second;
        }
};

void Dijkstra::makeDijkstra(index from)
{
    std::priority_queue< std::pair<int, float>, 
                        std::vector<std::pair<int, float> >,
                        comparator > route_queue;

    for (int i = 0; i < graph.getVertexCount(); ++i)
    {
        dist[from][i] = std::numeric_limits<float>::max();;
        father[from][i] = std::make_pair(-1,-1);
    }

    dist[from][from]  = 0;
    route_queue.push(std::make_pair(from, 0));
    int last = INF;

    while (route_queue.size() != 0){
    
        int u  = route_queue.top().first;
    
        for (int e: graph.getIncidentEdges(u)){
            
            int v = graph.getAdjacentVertex(e);
            if (dist[from][v] > (dist[from][u] + graph.getWeight(e))){
                
                dist[from][v] = dist[from][u] + graph.getWeight(e);
                father[from][v] = std::make_pair(u, e);

                route_queue.push(std::make_pair(v, dist[from][v]));
            }
        }

        route_queue.pop();
    }
}

Route Dijkstra::getPath(index from, index to)
{
    index temp = to;
    std::vector<int> edges;
    while(temp != from)
    {
        edges.push_back(father[from][temp].second);
        temp = father[from][temp].first;
    }

    std::reverse(edges.begin(), edges.end());

    return Route(from, edges);
}