#include "GeneticSolver.h"

std::vector<Route> GeneticSolver::solve(size_t numRoutes, size_t numIterations,
                                        size_t generationSize) {
  generation.resize(generationSize);
  nextGeneration.resize(generationSize);
  costs.resize(generationSize);
  nextCosts.resize(generationSize);
  distribution.resize(generationSize);
  #pragma omp parallel
  {
    generateInitialPopulation(numRoutes, generationSize);
    for (int it = 0; it < numIterations; ++it)
      generateNextPopulation(generationSize);
  }
  Chromosome *solutionChromosome = generation[getBestSolutionId()];
  std::vector<Route> solution(numRoutes);
  for (size_t i = 0; i < numRoutes; ++i)
    solution[i] = routesCache.get(solutionChromosome->getGene(i));
  for (size_t i = 0; i < generationSize; ++i)
    delete generation[i];
  return solution;
}

void GeneticSolver::generateInitialPopulation(size_t numRoutes,
                                              size_t generationSize) {
  #pragma omp for schedule(dynamic)
  for (int i = 0; i < generationSize; ++i) {
    Chromosome *chromosome = generation[i] = new Chromosome;
    for (int j = 0; j < numRoutes; ++j) {
      int numStops = Random::uniformInt(10, 20);
      bool closedRoute = Random::boolean();
      chromosome->addGene(Gene::generateRandomGene(numStops,
                                                   graph.getVertexCount(),
                                                   closedRoute));
    }
    costs[i] = chromosome->calculateCost(graph, passengers, routesCache);
  }
}

void GeneticSolver::generateNextPopulation(size_t generationSize) {
  size_t bestId = getBestSolutionId();
  #pragma omp master
  generateAccumulatedDistribution();
  #pragma omp barrier
  #pragma omp for schedule(dynamic)
  for (size_t i = 0; i < generationSize; ++i) {
    if (i == bestId) {  // conserving the best
      nextGeneration[bestId] = new Chromosome(*generation[bestId]);
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
      nextCosts[i] = nextGeneration[i]->calculateCost(graph, passengers,
                                                      routesCache);
    }
  }
  #pragma omp master
  {
    for (Chromosome *chromosome : generation)
      delete chromosome;
    std::copy(generation.begin(), nextGeneration.begin(), nextGeneration.end());
    std::copy(costs.begin(), nextCosts.begin(), nextCosts.end());
  }
}

Chromosome * GeneticSolver::doMutation(size_t id) {
  Chromosome *original = generation[id];
  Chromosome *chromosome = new Chromosome;
  for (size_t i = 0; i < original->size(); ++i) {
    if (Random::uniformInt(0, 9) < 3)  // 30% chance to mutate a gene
      chromosome->addGene(original->getGene(i).randomMutation());
    else
      chromosome->addGene(original->getGene(i));
  }
  return chromosome;
}

Chromosome * GeneticSolver::doCrossOver(size_t id1, size_t id2) {
  Chromosome *c1 = generation[id1], *c2 = generation[id2];
  size_t q1 = Random::uniformInt((c1->size() + 1) / 2, c1->size() - 1),
      q2 = c1->size() - q1;
  if (costs[id1] > costs[id2])
    std::swap(q1, q2);
  Chromosome *chromosome = new Chromosome;
  for (size_t x : Random::manyInts<size_t>(0, c1->size(), q1))
    chromosome->addGene(c1->getGene(x));
  for (size_t x : Random::manyInts<size_t>(0, c2->size(), q2))
    chromosome->addGene(c2->getGene(x));
  return chromosome;
}

void GeneticSolver::generateAccumulatedDistribution() {
  double acc = 0;
  for (size_t i = 0; i < costs.size(); ++i) {
    acc += 1 / costs[i];
    distribution[i] = acc;
  }
}

size_t GeneticSolver::getBestSolutionId() {
  size_t bestId = 0;
  for (size_t i = 1; i < costs.size(); ++i)
    if (costs[bestId] > costs[i])
      bestId = i;
  return bestId;
}
