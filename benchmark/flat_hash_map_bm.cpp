#include <benchmark/benchmark.h>

#include "flat_hash_map.hpp"

static void BM_Test(benchmark::State& state) {
  SKTL::Containers::FlatHashMap m;
  for (auto _ : state) {
    m.insert(0);
  }
}

BENCHMARK(BM_Test);

BENCHMARK_MAIN();
