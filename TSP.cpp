#include "TSP.h"

TSP::TSP(const Graph *graph) : graph(graph) {
  std::size_t n = graph->getVertexCount();
  memo = new float*[n];
  child = new int*[n];
  memo[0] = new float[n * (1 << n)];
  child[0] = new int[n * (1 << n)];
  for (std::size_t i = 1; i < n; ++i) {
    memo[i] = memo[i - 1] + (1 << n);
    child[i] = child[i - 1] + (1 << n);
  }
  std::fill(memo[0], memo[0] + n * (1 << n), -1);
}

std::vector<int> TSP::run(bool isClosed) {
  int vertex = startingVertex = 0;
  tsp(0, 1, isClosed);
  if (not isClosed) {  // we need to obtain the best starting point
    for (startingVertex = 1; startingVertex < graph->getVertexCount();
         ++startingVertex)
      if (tsp(startingVertex, 1 << startingVertex, isClosed) <
          memo[vertex][1 << vertex])
        vertex = startingVertex;
  }

  std::vector<int> route{vertex};
  int mask = 1 << vertex;
  for (int i = 1; i < graph->getVertexCount() + isClosed; ++i) {
    route.push_back(child[vertex][mask]);
    vertex = child[vertex][mask];
    mask |= 1 << vertex;
  }

  return route;
}

float TSP::tsp(int pos, int bitMask, bool isClosed) {
  if (memo[pos][bitMask] >= 0)
    return memo[pos][bitMask];

  if (bitMask == (1 << graph->getVertexCount()) - 1) {
    if (isClosed) {
      int e = graph->searchEdge(pos, startingVertex);
      child[pos][bitMask] = startingVertex;
      memo[pos][bitMask] = graph->getWeight(e);
    } else {
      memo[pos][bitMask] = 0;
    }
    return memo[pos][bitMask];
  }

  float ans = std::numeric_limits<float>::max(), tmp;
  for (int e : graph->getIncidentEdges(pos)) {
    int nxt = graph->getAdjacentVertex(e);
    if (nxt != pos && !(bitMask & (1 << nxt))) {
      tmp = graph->getWeight(e) + tsp(nxt, bitMask | (1 << nxt), isClosed);
      if (ans > tmp) {
        ans = tmp;
        child[pos][bitMask] = nxt;
      }
    }
  }

  return memo[pos][bitMask] = ans;
}

TSP::~TSP() {
  delete[] memo[0];
  delete[] child[0];
  delete[] memo;
  delete[] child;
}
