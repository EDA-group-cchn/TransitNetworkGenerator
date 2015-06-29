#include "Dijkstra.h"
#include <iostream>
#include <vector>
#include <queue>

#define INF 999999

struct comparator{
    bool operator() ( std::pair<int, int> i, std::pair <int, int> j ){
        return i.first > j.first;
        }
};

typename Dijkstra::route Dijkstra::getPath(index from, index to)
{
    route final_route;
    std::priority_queue< std::pair<int, int>, 
                        std::vector<std::pair<int, int> >,
                        comparator > route_queue;
    
    vertexArray dist;
    vertexArray father;
    for (int i = 0 ;i < graph.getVertexCount(); ++i)
    {
        dist.push_back(INF);
        father.push_back(-1);
    }

    dist[from]  = 0;
    route_queue.push(std::make_pair(from, 0));
    int last = INF;
    while (route_queue.top().first != to and route_queue.size() != 0)
    {
        int u  = route_queue.top().first;
    
        for (int e: graph.getIncidentEdges(u))
        {
            int v = graph.getAdjacentVertex(e);
            if (dist[v] > (dist[u] + graph.getWeight(e)))
            {
                
                dist[v] = dist[u] + graph.getWeight(e);
                father[v] = u;
                route_queue.push(std::make_pair(v, dist[v]));
            }
        }
        route_queue.pop();
    }

    index temp = to;
    while (temp != from)
    {
        if (father[temp] == -1) 
        {
            return route();
        }
        final_route[father[temp]] = std::make_pair(temp, dist[temp]);
        temp = father[temp];
    }

    return final_route;

}

typename Dijkstra::routes Dijkstra::getRoutes(std::vector<index> idxs)
{
    routes routes_map;
    for(int i = 0; i < idxs.size(); ++i)
    {
        for (int j = 0; j < idxs.size(); ++j)
        {
                
            route temp;                
            temp = getPath(idxs[i], idxs[j]);
            routes_map[idxs[i]].push_back(temp);
                
        }
    }
    
    return routes_map;
}

