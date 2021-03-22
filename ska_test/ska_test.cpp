// ska_test.cpp : Defines the entry point for the application.
//

#include "ska_test.h"
#define ANKERL_NANOBENCH_IMPLEMENT
#include "nanobench.h"

#include "ska_sort.h"
#include <algorithm>
#include <chrono>
#include <vector>

typedef struct {
  uint64_t state;
  uint64_t inc;
} pcg32_random_t;

uint32_t pcg32_random_r(pcg32_random_t *rng) {
  uint64_t oldstate = rng->state;
  // Advance internal state
  rng->state = oldstate * 6364136223846793005ULL + (rng->inc | 1);
  // Calculate output function (XSH RR), uses old state for max ILP
  uint32_t xorshifted = ((oldstate >> 18u) ^ oldstate) >> 27u;
  uint32_t rot = oldstate >> 59u;
  return (xorshifted >> rot) | (xorshifted << ((-rot) & 31));
}

int main() {
  std::chrono::high_resolution_clock clk;

  pcg32_random_t rng;
  rng.inc = std::chrono::duration_cast<std::chrono::nanoseconds>(
                clk.now().time_since_epoch())
                .count();

  ankerl::nanobench::Bench benchmark;
  benchmark.epochs(1024);
  benchmark.minEpochIterations(128);
  benchmark.minEpochTime(std::chrono::nanoseconds{4000});
  benchmark.warmup(4);
  // for metrics
  // benchmark.unit("sorts");
  benchmark.performanceCounters(true);
  benchmark.relative(true);

  size_t bench_size = 1024;
  std::vector<uint32_t> data;

  data.reserve(bench_size);
  //flip the bits since the patterns probably similar to inc
  rng.state =
      ~(std::chrono::duration_cast<std::chrono::nanoseconds>(clk.now().time_since_epoch())
          .count());

  while (bench_size < 100000) {
    while (data.size() < bench_size) {
      data.emplace_back();
    }
    for (size_t i = 0; i < data.size(); i++) {
      data[i] = pcg32_random_r(&rng);
    }

    std::string bench_num = std::to_string(bench_size);
    std::string title = std::string{"std::sort ("} + bench_num + ")";
    benchmark.run(title, [&]() {
      std::sort(data.begin(), data.end());
      for (size_t i = 0; i < data.size(); i++) {
        data[i] = pcg32_random_r(&rng);
      }
    });

    title = std::string{"ska_sort ("} + bench_num + ")";
    benchmark.run(title, [&]() {
      ska_sort(data.begin(), data.end());
      for (size_t i = 0; i < data.size(); i++) {
        data[i] = pcg32_random_r(&rng);
      }
    });

    bench_size *= 2;
  }
}
