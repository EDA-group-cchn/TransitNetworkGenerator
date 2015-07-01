#include "Gene.h"

std::vector<int> Gene::getVerticesList() const {
  std::vector<int> vertices;
  for(int i=0; i<verticesMask.size(); ++i)
    if(verticesMask[i])
      vertices.push_back(i);

  return vertices;
}

Gene Gene::generateRandomGene(int vertexCount, bool isClosed) {
  BitSet set;

  for(int i=0; i<20; ++i) {
    short tmp = Random::uniformInt(0,255);

    if(set[tmp])
      --i;

    set[tmp] = true;
  }

  Gene gene(isClosed);
  gene.verticesMask = set;
  return gene;
}

Route Gene::calculateBestRoute(const Graph &graph) const {
  SubGraph subGraph(graph, getVerticesList());
  TSP tsp(subGraph);
  Route route = tsp.run(isClosed);
  return subGraph.getOriginalRoute(route);
}

Gene Gene::randomMutation() const {
  return Gene(false);
}
