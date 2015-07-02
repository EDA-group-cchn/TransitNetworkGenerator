#ifndef TRANSIT_ROUTESCACHE_H
#define TRANSIT_ROUTESCACHE_H

#include <unordered_map>
#include <omp.h>

#include "Gene.h"
#include "Route.h"


class RoutesCache {
private:
  omp_lock_t lock;
  std::unordered_map<Gene, Route> cache;
public:
  RoutesCache() {
    omp_init_lock(&lock);
  }
  bool check(const Gene &gene) {
    omp_set_lock(&lock);
    bool found = cache.find(gene) != cache.end();
    omp_unset_lock(&lock);
    return found;
  }
  void add(const Gene &gene, const Route &route) {
    omp_set_lock(&lock);
    cache[gene] = route;
    omp_unset_lock(&lock);
  }
  Route get(const Gene &gene) {
    omp_set_lock(&lock);
    Route route = cache[gene];
    omp_unset_lock(&lock);
    return route;
  }
  ~RoutesCache() {
    omp_destroy_lock(&lock);
  }
};


#endif //TRANSIT_ROUTESCACHE_H
