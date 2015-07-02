#include <iostream>
#include <vector>

#include "Graph.h"
#include "Dijkstra.h"
#include "SubGraph.h"

using namespace std;

int main() {

  Graph graph(5);
  graph.addEdge(0, 1, 0.1);
  graph.addEdge(0, 2, 1.9);
  graph.addEdge(1, 2, 3);
  graph.addEdge(1, 3, 3);
  graph.addEdge(2, 4, 1);
  graph.addEdge(2, 3, 1);
  graph.addEdge(3, 2, 2);
  graph.addEdge(3, 4, 1);
  graph.addEdge(2, 1, 2);
  graph.addEdge(1, 0, 1);
  for (int i = 0 ; i< graph.getVertexCount();i++)
  {
    cout<<i;
    for (int e: graph.getIncidentEdges(i))
    {
      cout<<"-->"<<graph.getAdjacentVertex(e)<<" weight = "<< graph.getWeight(e)<<"\t";
    }
    cout<<endl;
  }

  Dijkstra d(&graph);
  d.makeDijkstra(1);
  cout<<"\n\n"<<d.getWeight(1, 4)<<endl;

  Route r = d.getPath(1, 4);
  cout<<"Route\n";
  vector<int>  ed = r.getEdgeList();
  for (std::vector<int>::iterator i = ed.begin(); i != ed.end(); ++i)
  {
    cout<< graph.getAdjacentVertex(*i) <<endl;
    
  }

  vector<int> idx;
  idx.push_back(0);
  idx.push_back(1);
  idx.push_back(4);
  idx.push_back(3);
  cout<<"----------\nSubgraph\n----------\n";
  SubGraph sg(&graph, idx);
  Dijkstra ds(&sg);
  
  
  for(int i = 0; i< sg.getVertexCount();i++)
  {
    cout<<sg.getOriginalVertexId(i);
  }
cout<<"\n\n\n";
  ds.makeDijkstra(1);
  Route sroute = ds.getPath(1, 2);
  Route orig_route = sg.getOriginalRoute(sroute);
  vector<int> orig_ed = orig_route.getEdgeList();
  for (std::vector<int>::iterator i = orig_ed.begin(); i != orig_ed.end(); ++i)
  {
    cout<< graph.getAdjacentVertex(*i) <<endl;
    
  }


  return 0;
}
