#ifndef TRANSIT_SUBGRAPH_H
#define TRANSIT_SUBGRAPH_H

#include "Dijkstra.h"
#include "Graph.h"
#include "Route.h"
#include <vector>

class SubGraph : public Graph {
private:
  std::vector<int> originalVertexId;
  Dijkstra originalDijkstra;
  const Graph &graph;
public:
  SubGraph(const Graph &graph, std::vector<int> vertices) :
            Graph((int)vertices.size()),
            graph(graph),
            originalVertexId(vertices.size(), -1),
            originalDijkstra(graph) {
              for (int i = 0 ; i < vertices.size(); ++i){
              originalVertexId[i] = vertices[i];
              originalDijkstra.makeDijkstra(vertices[i]);
              for(int j = 0; j < vertices.size(); ++j){
                addEdge(i, j,
                  originalDijkstra.getWeight(vertices[i],vertices[j]));
          }
        }
      }
  int getOriginalVertexId(int vertex) const {
    return originalVertexId[vertex];
  }
  
  Route getOriginalRoute(const Route &r);
};


#endif //TRANSIT_SUBGRAPH_H
