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
  short used = 0;
  for(int i=0; i<set.size(); ++i) {

    set[i] = false;

    if(vertexCount > used)
      if(Random::boolean())
        set[i] = true;
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
