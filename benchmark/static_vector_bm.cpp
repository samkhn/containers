#include "benchmark/benchmark.h"
#include "static_vector.hpp"

static void BM_StaticVectorPushBack(benchmark::State& state) {
  SKTL::Containers::StaticVector<int, 11> v;
  for (auto _ : state) {
    v.PushBack(10);
    benchmark::DoNotOptimize(v.Data());
  }
}

// TODO: generate a bunch of random integers as Args to pushback to Vector
BENCHMARK(BM_StaticVectorPushBack);

BENCHMARK_MAIN();
