#include <iostream>
#include <vector>

#include "Graph.h"
#include "GeneticSolver.h"
#include "Dijkstra.h"

using namespace std;

int main() {
  /*int n, m, p;
  cin >> n >> m >> p;
  Graph graph(n, m);
  int u, v;
  float w1, w2;
  cout<<"Graph Edges"<<endl;
  for (int i = 0; i < m; ++i) {
    cin >> u >> v >> w1;
    graph.addEdge(u, v, w1);
  }

  cout<<"Passenger"<<endl;
  vector<Passenger> passengers(p);
  for (int i = 0; i < p; ++i) {
    cin >> u >> v >> w1 >> w2;
    passengers[i] = Passenger(u, v, w1, w2);
  }

  GeneticSolver solver(graph, passengers);
  Graph solution = solver.solve(0).generateSolutionGraph(graph);

  cout << solution.getVertexCount() << ' ' << solution.getEdgeCount();
  for (u = 0; u < solution.getVertexCount(); ++u) {
    cout << u << ':';
    for (int e : solution.getIncidentEdges(u))
      cout << ' ' << solution.getAdjacentVertex(e);
    cout << endl;
  }*/

  Graph graph(5);
  graph.addEdge(0, 1, 1);
  graph.addEdge(0, 2, 2);
  graph.addEdge(1, 2, 3);
  graph.addEdge(1, 3, 3);
  graph.addEdge(2, 4, 1);
  graph.addEdge(3, 2, 2);
  graph.addEdge(3, 4, 1);

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
  typename Dijkstra::route r = d.getPath(0, 4);
  for (typename Dijkstra::route::iterator i = r.begin(); i != r.end(); ++i)
  {
    cout<< i->first<< "-->"<<i->second.first << " accumulative weight = "<< i->second.second << endl;
  }
  /* Esta parte de codigo imprime:
    0-->2 weight = 2 -->1 weight = 1 
    1-->3 weight = 3  -->2 weight = 3 
    2-->4 weight = 1  
    3-->4 weight = 1  -->2 weight = 2 
    4
    0-->2 accumulative weight = 2
    2-->4 accumulative weight = 3


  */

  return 0;
}
