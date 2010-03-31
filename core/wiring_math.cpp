#include <stdlib.h>
#include "math.h"

/* from newlib:
 *
 * rand returns the next pseudo-random integer in sequence; it is a number 
 *      between 0 and RAND_MAX (inclusive).
 *
 * srand does not return a result. */


/* The rest copied from WMath.cpp  */
void randomSeed(unsigned int seed) {
  if (seed != 0) {
    srand(seed);
  }
}

long random(long howbig) {
  if (howbig == 0) {
    return 0;
  }
  return rand() % howbig;
}

long random(long howsmall, long howbig) {
  if (howsmall >= howbig) {
    return howsmall;
  }
  long diff = howbig - howsmall;
  return random(diff) + howsmall;
}

long map(long x, long in_min, long in_max, long out_min, long out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}


