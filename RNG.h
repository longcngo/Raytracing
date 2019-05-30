#ifndef RNGH
#define RNGH

#include <stdint.h>
#include <ctime>

/*
    RNG class based on xoroshiro128
*/

static double float_norm = (1.0f/(1 << 24));

static uint64_t state[2];

static inline uint64_t seed_state(uint64_t x)
{
    uint64_t z = (x += 0x9e3779b97f4a7c15);
	z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9;
	z = (z ^ (z >> 27)) * 0x94d049bb133111eb;
	return z ^ (z >> 31);
}

inline void xorseed()
{
    state[0] = seed_state(time(NULL));
    state[1] = seed_state(time(NULL));
}

static inline uint64_t rotl(const uint64_t x, int k)
{
    return (x << k) | (x >> (64-k));
}

inline uint64_t xorand()
{
    const uint64_t s0 = state[0];
    uint64_t s1 = state[1];
    const uint64_t result = s0 + s1;

    // magic numbers: a=24, b=16, c=37
    s1 ^= s0;
    state[0] = rotl(s0, 24) ^ s1 ^ (s1<<16);
    state[1] = rotl(s1, 37);
    return result;
}

inline float xorandf()
{
    return (xorand() >> 40) * float_norm;
}

#endif
