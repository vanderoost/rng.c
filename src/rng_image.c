#include "rng/rng.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RNG_FUN rng_u()

#define SAMPLE_COUNT (1 << 26)

#define WIDTH 960
#define HEIGHT 540
#define DEPTH 3 // RGB

#define BUF_LEN (WIDTH * HEIGHT * DEPTH)

int main(void) {
  uint8_t pix_buffer[BUF_LEN] = {};

  // Generate random pixels
  double rand_max_inv = 1.0 / (UINT32_MAX + 1.0);
  for (size_t i = 0; i < SAMPLE_COUNT; ++i) {
    uint32_t roll_a = RNG_FUN << 1;
    uint32_t roll_b = RNG_FUN << 1;

    size_t pixel_ix = roll_a * rand_max_inv * WIDTH * HEIGHT;
    uint8_t *pixel = &pix_buffer[pixel_ix * DEPTH];

    double pixel_val = roll_b * rand_max_inv * 1.2 - 0.1;
    uint32_t pixel_col = pixel_val * (1 << 24);

    memcpy(pixel, &pixel_col, DEPTH);
  }

  // Write a PPM image
  FILE *fp = fopen("image.ppm", "wb");
  if (fp == NULL) {
    fprintf(stderr, "shit hit the fan :/");
    return 1;
  }
  fprintf(fp, "P6\n");
  fprintf(fp, "%d %d\n", WIDTH, HEIGHT);
  fprintf(fp, "255\n");
  size_t pixels_written = fwrite(pix_buffer, DEPTH, WIDTH * HEIGHT, fp);
  printf("Wrote %zu pixels\n", pixels_written);
  fclose(fp);

  return 0;
}
