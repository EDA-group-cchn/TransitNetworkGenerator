#include <iostream>
#include <vector>

#include "Graph.h"
#include "GeneticSolver.h"
#include "Dijkstra.h"
#include "Route.h"

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

  Dijkstra d(graph);
  d.makeDijkstra(1);
  cout<<"\n\n"<<d.getWeight(1, 4)<<endl;

  Route r = d.getPath(1, 4);
  cout<<"Route\n";
  vector<int>  ed = r.getEdgeList();
  for (std::vector<int>::iterator i = ed.begin(); i != ed.end(); ++i)
  {
    cout<< graph.getAdjacentVertex(*i) <<endl;
    
  }
/*
  vector<int> a;
  
  a.push_back(1);
  a.push_back(2);
  a.push_back(4);

  cout<<"Getting Routes\n";
  typename Dijkstra::routes rs = d.getRoutes(a);

  cout<<"\n\n\nShow\n";
  for (typename Dijkstra::routes::iterator i = rs.begin(); i != rs.end(); ++i)
  {
    std::cout<<"from" << i->first<<"\n";
    for (typename Dijkstra::route j : i->second)
    {
      for (std::pair<int, std::pair<int, int> > k : j)
      {

        cout<< k.first<<" "<<k.second.first<< " "<<k.second.second<<"\n";

      }
      cout<<"\n\n";
    }
    cout<<"\n";

  }
*/

/* 0-->2 weight = 2 -->1 weight = 1 
1-->0 weight = 1  -->3 weight = 3 -->2 weight = 3 
2-->1 weight = 2  -->3 weight = 1 -->4 weight = 1 
3-->4 weight = 1  -->2 weight = 2 
4
1-->2 accumulative weight = 3
2-->4 accumulative weight = 4
Getting Routes



Show
from1


1 2 3


1 2 3
2 4 4



from2
2 1 2




2 4 1



from4




*/

  return 0;
}
