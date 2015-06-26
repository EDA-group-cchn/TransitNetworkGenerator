#ifndef TRANSIT_RANDOM_H
#define TRANSIT_RANDOM_H

#include "omp.h"
#include <random>
#include <algorithm>


class Random {
private:
  static omp_lock_t lock;
  static std::mt19937 generator;
  class Initializer {
  public:
    Initializer() {
      omp_init_lock(&Random::lock);
    }
    ~Initializer() {
      omp_destroy_lock(&Random::lock);
    }
  };
  friend class Initializer;
  static Initializer initializer;

public:
  template <typename T>
  static T uniformInt(T minimum, T maximum);

  template <typename T, typename D>
  static T customDistributionInt(const std::vector<D> &accumulatedWeights,
                                 T start = 0);

  static bool boolean() {
    return (bool)uniformInt(0, 1);
  }

  template <typename T>
  static T uniformFloat(T minimum, T maximum);
};

template <typename T>
T Random::uniformInt(T minimum, T maximum) {
  std::uniform_int_distribution<T> distribution(minimum, maximum);
  omp_set_lock(&lock);
  T num = distribution(generator);
  omp_unset_lock(&lock);
  return num;
}

template <typename T, typename D>
T Random::customDistributionInt(const std::vector<D> &accumulatedWeights,
                                T start) {
  T num = std::lower_bound(accumulatedWeights.begin(),
                           accumulatedWeights.end(),
                           uniformFloat(0., accumulatedWeights.back()))
          - accumulatedWeights.begin();
  return start + num;
}

template <typename T>
T Random::uniformFloat(T minimum, T maximum) {
  std::uniform_real_distribution<T> distribution(minimum, maximum);
  omp_set_lock(&lock);
  T num = distribution(generator);
  omp_unset_lock(&lock);
  return num;
}

#endif //TRANSIT_RANDOM_H
