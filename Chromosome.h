#ifndef TRANSIT_CHROMOSOME_H
#define TRANSIT_CHROMOSOME_H

#include <vector>

#include "Gene.h"
#include "Passenger.h"


class Chromosome {
private:
  std::vector<Gene> genes;
public:
  Chromosome() { };
  const Gene &getGene(int id) const {
    return genes[id];
  }
  Graph generateSolutionGraph(const Graph &original) const;
  float calculateCost(const std::vector<Passenger> &passengers) const;
};


#endif //TRANSIT_CHROMOSOME_H
