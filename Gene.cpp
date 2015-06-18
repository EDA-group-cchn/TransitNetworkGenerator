#include "Gene.h"

std::vector<int> Gene::getVerticesList() const {
  return std::vector<int>();
}

Gene Gene::generateRandomGene(int vertexCount, bool isClosed) {
  return Gene(isClosed);
}

Route Gene::calculateBestRoute(const Graph &graph) {
  return Route(0);
}
