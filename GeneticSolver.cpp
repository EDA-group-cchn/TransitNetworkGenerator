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
    #pragma omp for schedule(static)
    for (size_t i = 0; i < graph->getVertexCount(); ++i)
      dijkstra.makeDijkstra((int) i);
    Random random;
    generateInitialPopulation(numRoutes, generationSize, random);
    for (int it = 0; it < numIterations; ++it)
      generateNextPopulation(generationSize, random);
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
                                              size_t generationSize,
                                              Random &random) {
  #pragma omp for schedule(static)
  for (int i = 0; i < generationSize; ++i) {
    Chromosome *chromosome = new Chromosome;
    for (int j = 0; j < numRoutes; ++j) {
      size_t numStops = random.uniformInt(12ul, 16ul);
      bool closedRoute = random.boolean();
      chromosome->addGene(
          Gene::generateRandomGene(numStops, graph->getVertexCount(),
                                   closedRoute, random));
    }
    generation[i] = chromosome;
    costs[i] = chromosome->calculateCost(&dijkstra, passengers, routesCache);
  }
}

void GeneticSolver::generateNextPopulation(size_t generationSize,
                                           Random &random) {
  #pragma omp master
  {
    bestId = getBestSolutionId();
    generateAccumulatedDistribution();
    size_t worstId = 0;
    double total = 0;
    for (size_t i = 0; i < generationSize; ++i) {
      total += costs[i];
      if (costs[i] > costs[worstId])
        worstId = i;
    }
    std::cerr << "mean: " << total / generationSize << "\tbest: " <<
        costs[bestId] << "\tworst: " << costs[worstId] << std::endl;
  }
  #pragma omp barrier
  #pragma omp for schedule(dynamic)
  for (size_t i = 0; i < generationSize; ++i) {
    if (i == bestId) {  // conserving the best
      if (random.uniformInt(0, 99) < 2) {  // 2% chance of mutation
        nextGeneration[i] = doMutation(i, random);
        nextCosts[i] = nextGeneration[i]->calculateCost(&dijkstra, passengers,
                                                        routesCache);
      } else {
        nextGeneration[bestId] = new Chromosome(*generation[bestId]);
        nextCosts[bestId] = costs[bestId];
      }
    } else {
      if (random.uniformInt(0, 9) < 2) {  // 20% chance of mutation
        nextGeneration[i] = doMutation(i, random);
      } else {
        size_t j;
        do {
          j = random.customDistributionInt<size_t>(distribution);
        } while (j == i);
        nextGeneration[i] = doCrossOver(i, j, random);
      }
      nextCosts[i] = nextGeneration[i]->calculateCost(&dijkstra, passengers,
                                                      routesCache);
    }
  }
  #pragma omp master
  {
    for (Chromosome *chromosome : generation)
      delete chromosome;
    std::copy(nextGeneration.begin(), nextGeneration.end(), generation.begin());
    std::copy(nextCosts.begin(), nextCosts.end(), costs.begin());
  }
}

Chromosome * GeneticSolver::doMutation(size_t id, Random &random) {
  Chromosome *original = generation[id];
  Chromosome *chromosome = new Chromosome;
  for (size_t i = 0; i < original->size(); ++i) {
    if (random.uniformInt(0, 9) < 4)  // 40% chance to mutate a gene
      chromosome->addGene(original->getGene(i)
                              .randomMutation(graph->getVertexCount(),
                                              random));
    else
      chromosome->addGene(original->getGene(i));
  }
  return chromosome;
}

Chromosome * GeneticSolver::doCrossOver(size_t id1, size_t id2,
                                        Random &random) {
  Chromosome *c1 = generation[id1], *c2 = generation[id2];
  size_t q1 = random.uniformInt((c1->size() + 5) / 2, c1->size() - 1),
      q2 = c1->size() - q1;
  if (costs[id1] > costs[id2])
    std::swap(q1, q2);
  Chromosome *chromosome = new Chromosome;
  for (size_t x : random.manyInts(0ul, c1->size() - 1, q1))
    chromosome->addGene(c1->getGene(x));
  for (size_t x : random.manyInts(0ul, c2->size() - 1, q2))
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
