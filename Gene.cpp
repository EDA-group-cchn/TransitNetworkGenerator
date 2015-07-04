#include "Gene.h"

std::vector<int> Gene::getVerticesList() const {
  std::vector<int> vertices;
  for (size_t i = 0; i < verticesMask.size(); ++i)
    if (verticesMask.test(i))
      vertices.push_back((int) i);

  return vertices;
}

Gene Gene::generateRandomGene(size_t vertexCount, size_t totalVertexCount,
                              bool isClosed, Random &random) {
  Gene gene(isClosed);

  for (size_t i = 0; i < vertexCount; ++i) {
    size_t tmp = random.uniformInt(0ul, totalVertexCount - 1);
    if (gene.verticesMask.test(tmp))
      --i;
    else
      gene.verticesMask.set(tmp);
  }

  return gene;
}

Route Gene::calculateBestRoute(const Dijkstra *dijkstra) const {
  SubGraph subGraph(dijkstra, getVerticesList());
  TSP tsp(&subGraph);
  std::vector<int> route = tsp.run(isClosed);
  return subGraph.getOriginalRoute(route);
}

Gene Gene::randomMutation(size_t vertexCount, Random &random) const {
  Gene gene = *this;
  if (random.uniformInt(0, 9) < 9) {  // 90% chance of moving
    size_t i, j;
    do {
      i = random.uniformInt(0ul, vertexCount - 1);
    } while (not verticesMask.test(i));
    do {
      j = random.uniformInt(0ul, vertexCount - 1);
    } while (verticesMask.test(j));
    gene.verticesMask.reset(i);
    gene.verticesMask.set(j);
  } else {
    gene.isClosed = not isClosed;
  }
  return gene;
}
