#include <iostream>
#include <vector>

#include "Graph.h"
#include "GeneticSolver.h"


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
  vector<Route> solution = solver.solve(10, 20, 16);

  for (const Route &route : solution) {
    v = route.getFirstVertex();
    cout << v;
    for (int e : route.getEdgeList()) {
      v= graph.getAdjacentVertex(e);
      cout << ' ' << v;
    }
    cout << endl;
  }

  return 0;
}
