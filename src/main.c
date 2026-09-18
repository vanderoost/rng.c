#include "plt/plt.h"
#include "rng/rng.h"
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SAMPLE_COUNT (1 << 20)

int main(void) {
  rng_seed(time(NULL), 1);

  float buffer[SAMPLE_COUNT];
  float mean = 0.0f;
  for (size_t i = 0; i < SAMPLE_COUNT; ++i) {
    buffer[i] = rng_norm();

    mean += buffer[i];
  }
  mean /= SAMPLE_COUNT;
  printf("mean: %.3f\n", mean);

  float var = 0.0f;
  for (size_t i = 0; i < SAMPLE_COUNT; ++i) {
    float dev = (buffer[i] - mean);
    var += dev * dev;
  }
  var /= SAMPLE_COUNT;
  float std = sqrtf(var);
  printf("var: %.3f\n", var);
  printf("std: %.3f\n", std);

  plt_hist(buffer, SAMPLE_COUNT, 16, 72);

  return 0;
}
