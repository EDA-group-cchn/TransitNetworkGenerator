#ifndef TRANSIT_RANDOM_H
#define TRANSIT_RANDOM_H

#include <random>
#include <algorithm>
#include <set>


class Random {
private:
  std::mt19937 generator;
public:
  template <typename T>
  T uniformInt(T minimum, T maximum);

  template <typename T, typename D>
  T customDistributionInt(const std::vector<D> &accumulatedWeights,
                                 T start = 0);

  template <typename T>
  std::vector<T> manyInts(T minimum, T maximum, size_t quantity);

  bool boolean() {
    return (bool)uniformInt(0, 1);
  }

  template <typename T>
  T uniformFloat(T minimum, T maximum);
};

template <typename T>
T Random::uniformInt(T minimum, T maximum) {
  std::uniform_int_distribution<T> distribution(minimum, maximum);
  return distribution(generator);
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
std::vector<T> Random::manyInts(T minimum, T maximum, size_t quantity) {
  std::set<T> used;
  T x;
  for (size_t i = 0; i < quantity; ++i) {
    do {
      x = uniformInt(minimum, maximum);
    } while (used.find(x) != used.end());
    used.insert(x);
  }
  return std::vector<T> (used.begin(), used.end());
}

template <typename T>
T Random::uniformFloat(T minimum, T maximum) {
  std::uniform_real_distribution<T> distribution(minimum, maximum);
  return distribution(generator);
}

#endif //TRANSIT_RANDOM_H
