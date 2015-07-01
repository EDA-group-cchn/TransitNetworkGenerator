#include "Gene.h"

std::vector<int> Gene::getVerticesList() const {
  std::vector<int> vertices;
  for(int i=0; i<verticesMask.size(); ++i)
    if(verticesMask[i])
      vertices.push_back(i);

  return vertices;
}

Gene Gene::generateRandomGene(int vertexCount, int verticesNumber,  bool isClosed) {
  BitSet set;

  int tmp;
  for(int i=0; i<vertexCount; ++i) {
    tmp = Random::uniformInt(0, verticesNumber - 1);

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
