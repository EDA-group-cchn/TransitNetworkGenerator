#ifndef TRANSIT_GENE_H
#define TRANSIT_GENE_H

#include <bitset>
#include <vector>

#include "SubGraph.h"
#include "Route.h"
#include "TSP.h"
#include "Random.h"


class Gene {
private:
  typedef std::bitset<256> BitSet;
  BitSet verticesMask;
  bool isClosed;
public:
  Gene(bool isClosed) : isClosed(isClosed) { }
  const BitSet &getVerticesMask() const {
    return verticesMask;
  }
  bool getIsClosed() const {
    return isClosed;
  }
  bool operator == (const Gene &other) const {
    return isClosed == other.isClosed && verticesMask == other.verticesMask;
  }
  std::vector<int> getVerticesList() const;
  static Gene generateRandomGene(size_t vertexCount, size_t totalVertexCount,
                                 bool isClosed, Random &random);
  std::pair<Route, Route> calculateBestRoute(const Dijkstra *dijkstra) const;
  Gene randomMutation(size_t vertexCount, Random &random) const;
};

namespace std {
template <> struct hash<Gene> {
  size_t operator()(const Gene &gene) const {
    return hash<std::bitset<256>>()(gene.getVerticesMask()) ^
        hash<bool>()(gene.getIsClosed());
  }
};
}

#endif //TRANSIT_GENE_H
