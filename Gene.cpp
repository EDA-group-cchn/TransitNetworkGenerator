#include "Gene.h"

std::vector<int> Gene::getVerticesList() const {
  std::vector<int> vertices;
  for (size_t i = 0; i < verticesMask.size(); ++i)
    if (verticesMask.test(i))
      vertices.push_back((int) i);

  return vertices;
}

Gene Gene::generateRandomGene(int vertexCount, int verticesNumber,
                              bool isClosed) {
  Gene gene(isClosed);

  for (int i = 0; i < vertexCount; ++i) {
    size_t tmp = (size_t) Random::uniformInt(0, verticesNumber - 1);
    if (gene.verticesMask.test(tmp))
      --i;
    else
      gene.verticesMask.set(tmp);
  }

  return gene;
}

Route Gene::calculateBestRoute(const Graph *graph) const {
  SubGraph subGraph(graph, getVerticesList());
  TSP tsp(&subGraph);
  Route route = tsp.run(isClosed);
  return subGraph.getOriginalRoute(route);
}

Gene Gene::randomMutation() const {
  return Gene(false);
}
