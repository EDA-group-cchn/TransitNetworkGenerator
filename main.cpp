#include <iostream>
#include <vector>

#include "Graph.h"
#include "GeneticSolver.h"
#include "Dijkstra.h"

using namespace std;

int main() {
  int n, m, p;
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
  }

  return 0;
}
