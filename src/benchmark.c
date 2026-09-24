#include "rng/rng.h"
#include <float.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define CALLS 100000000
#define RUNS 5

typedef uint32_t (*bench_fn)(size_t n);

static uint64_t now_ns(void) {
  struct timespec ts;
  clock_gettime(CLOCK_MONOTONIC, &ts);
  return (uint64_t)ts.tv_sec * 1000000000ULL + ts.tv_nsec;
}

// Each loop folds its results into a returned value so the compiler can't eliminate the
// calls as dead code.
static uint32_t bench_rng_u(size_t n) {
  uint32_t sink = 0;
  for (size_t i = 0; i < n; ++i) {
    sink ^= rng_u();
  }
  return sink;
}

static uint32_t bench_rand(size_t n) {
  uint32_t sink = 0;
  for (size_t i = 0; i < n; ++i) {
    sink ^= (uint32_t)rand();
  }
  return sink;
}

static void bench(const char *name, bench_fn fn) {
  uint32_t sink = fn(CALLS / 10); // warm up caches and branch predictors

  double best = DBL_MAX;
  for (size_t run = 0; run < RUNS; ++run) {
    uint64_t start = now_ns();
    sink ^= fn(CALLS);
    (void)sink;

    double ns_per_call = (double)(now_ns() - start) / CALLS;
    if (ns_per_call < best) {
      best = ns_per_call;
    }
  }

  printf("%-6s %6.3f ns/call\n", name, best);
}

int main(void) {
  rng_seed(42, 1);
  srand(42);

  bench("rng_u", bench_rng_u);
  bench("rand", bench_rand);

  return 0;
}
