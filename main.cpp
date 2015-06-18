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
  for (int i = 0; i < m; ++i) {
    cin >> u >> v >> w1;
    graph.addEdge(u, v, w1);
  }
  vector<Passenger> passengers(p);
  for (int i = 0; i < p; ++i) {
    cin >> u >> v >> w1 >> w2;
    passengers[i] = Passenger(u, v, w1, w2);
  }
  GeneticSolver solver(graph, passengers);
  Graph solution = solver.solve(0).generateSolutionGraph(graph);
  cout << solution.getVertexCount() << ' ' << solution.getEdgeCount();
  for (u = 0; u < solution.getVertexCount(); ++u) {
    // TODO: iterator needed
    cout << endl;
  }
  return 0;
}
