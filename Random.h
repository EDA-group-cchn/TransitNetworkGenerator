#ifndef TRANSIT_RANDOM_H
#define TRANSIT_RANDOM_H

#include "omp.h"
#include <random>


class Random {
private:
  static omp_lock_t lock;
  static std::mt19937 generator;
  class Initializer {
  public:
    Initializer() {
      omp_init_lock(&Random::lock);
    }
  };
  friend class Initializer;
  static Initializer initializer;

public:
  static int uniformInt(int a, int b) {
    omp_set_lock(&lock);
    std::uniform_int_distribution<int> distribution(a, b);
    int ans = distribution(generator);
    omp_unset_lock(&lock);
    return ans;
  }
  static bool boolean() {
    return (bool)uniformInt(0, 1);
  }
};

#endif //TRANSIT_RANDOM_H
