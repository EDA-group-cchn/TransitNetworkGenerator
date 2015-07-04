#include <iostream>
#include <vector>

#include "Graph.h"
#include "GeneticSolver.h"


using namespace std;

int main() {
  int n, m, p;
  cin >> n >> m >> p;
  Graph graph((size_t) n, (size_t) m);
  int u, v;
  float w1, w2;
  for (int i = 0; i < m; ++i) {
    cin >> u >> v >> w1;
    graph.addEdge(u, v, w1);
  }

  vector<Passenger> passengers((size_t) p);
  for (int i = 0; i < p; ++i) {
    cin >> u >> v >> w1 >> w2;
    passengers[i] = Passenger(u, v, w1, w2);
  }

  GeneticSolver solver(&graph, passengers);
  vector<Route> solution = solver.solve(10, 200, 100);

  for (const Route &route : solution) {
    v = route.getFirstVertex();
    cout << v;
    for (int e : route.getEdgeList()) {
      v = graph.getAdjacentVertex(e);
      cout << ' ' << v;
    }
    cout << endl;
  }

  return 0;
}
