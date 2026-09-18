# plt.c

C library for generating pseudo random numbers. Using the principles from
[pcg-random.org](https://pcg-random.org).

## Example usage

Seeding:

```c
uint32_t roll = rng_u();
```

Generating a random 32-bit integer:

```c
uint32_t roll = rng_u();
```

## Blog article

Read about how I created this library from scratch:
[*TODO*](https://vanderoost.com/articles/)

## Screencast

Walkthrough where I'm cooking this up from scratch:

*TODO*

## License

MIT — see [LICENSE](LICENSE).

The PCG32 generator in `src/rng/` is derived from
[imneme/pcg-c](https://github.com/imneme/pcg-c) by Melissa O'Neill and the PCG
Project contributors, which is offered under `Apache-2.0 OR MIT`. It is used
here under the MIT option, so this library is MIT throughout.
