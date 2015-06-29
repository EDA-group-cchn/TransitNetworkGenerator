#include "GeneticSolver.h"

Graph GeneticSolver::solve(size_t numRoutes, size_t numIterations,
                           size_t generationSize) {
  generateInitialPopulation(numRoutes, generationSize);
  for (int it = 0; it < numIterations; ++it)
    generateNextPopulation(generationSize);
  return generation[getBestSolutionId()].generateSolutionGraph(graph,
                                                               routesCache);
}

void GeneticSolver::generateInitialPopulation(size_t numRoutes,
                                              size_t generationSize) {
  generation.resize(generationSize);
  costs.resize(generationSize);
  #pragma omp parallel for
  for (int i = 0; i < generationSize; ++i) {
    Chromosome &chromosome = generation[i];
    for (int j = 0; j < numRoutes; ++j) {
      int numStops = Random::uniformInt(10, 20);
      bool closedRoute = Random::boolean();
      chromosome.addGene(Gene::generateRandomGene(numStops, closedRoute));
    }
    costs[i] = chromosome.calculateCost(graph, passengers, routesCache);
  }
}

void GeneticSolver::generateNextPopulation(size_t generationSize) {
  std::vector<Chromosome> nextGeneration(generationSize);
  std::vector<double> nextCosts(generationSize);
  std::vector<double> distribution = generateAccumulatedDistribution();
  size_t bestId = getBestSolutionId();
  #pragma omp parallel for
  for (size_t i = 0; i < generationSize; ++i)
    if (i == bestId) {  // conserving the best
      nextGeneration[bestId] = generation[bestId];
      nextCosts[bestId] = costs[bestId];
    } else {
      if (Random::uniformInt(0, 9) < 4) {  // 40% chance of mutation
        nextGeneration[i] = doMutation(i);
      } else {
        size_t j;
        do {
          j = Random::customDistributionInt<size_t>(distribution);
        } while (j == i);
        nextGeneration[i] = doCrossOver(i, j);
      }
      nextCosts[i] = nextGeneration[i].calculateCost(graph, passengers,
                                                     routesCache);
    }
  generation = nextGeneration;
  costs = nextCosts;
}

Chromosome GeneticSolver::doMutation(size_t id) {
  Chromosome &original = generation[id];
  Chromosome chromosome;
  for (size_t i = 0; i < original.size(); ++i) {
    if (Random::uniformInt(0, 9) < 3)  // 30% chance to mutate a gene
      chromosome.addGene(original.getGene(i).randomMutation());
    else
      chromosome.addGene(original.getGene(i));
  }
  return Chromosome();
}

Chromosome GeneticSolver::doCrossOver(size_t id1, size_t id2) {
  Chromosome &c1 = generation[id1], &c2 = generation[id2];
  size_t q1 = Random::uniformInt((c1.size() + 1) / 2, c1.size() - 1),
      q2 = c1.size() - q1;
  if (costs[id1] > costs[id2])
    std::swap(q1, q2);
  Chromosome chromosome;
  for (size_t x : Random::manyInts<size_t>(0, c1.size(), q1))
    chromosome.addGene(c1.getGene(x));
  for (size_t x : Random::manyInts<size_t>(0, c2.size(), q2))
    chromosome.addGene(c2.getGene(x));
  return chromosome;
}

std::vector<double> GeneticSolver::generateAccumulatedDistribution() {
  std::vector<double> distribution(costs.size());
  double acc = 0;
  for (size_t i = 0; i < costs.size(); ++i) {
    acc += 1 / costs[i];
    distribution[i] = acc;
  }
  return distribution;
}

size_t GeneticSolver::getBestSolutionId() {
  size_t bestId = 0;
  for (size_t i = 1; i < costs.size(); ++i)
    if (costs[bestId] > costs[i])
      bestId = i;
  return bestId;
}
