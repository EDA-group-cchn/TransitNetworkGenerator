#include "Random.h"

omp_lock_t Random::lock;
std::mt19937 Random::generator;
typename Random::Initializer Random::initializer;
