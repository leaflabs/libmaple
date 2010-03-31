#ifndef _WIRING_MATH_H_
#define _WIRING_MATH_H_

#include <math.h>

void randomSeed(unsigned int);
long random(long);
long random(long, long);
long map(long, long, long, long, long);

#define PI 3.1415926535897932384626433832795
#define HALF_PI 1.5707963267948966192313216916398
#define TWO_PI 6.283185307179586476925286766559
#define DEG_TO_RAD 0.017453292519943295769236907684886
#define RAD_TO_DEG 57.295779513082320876798154814105

#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))
#define constrain(amt,low,high) ((amt)<(low)?(low):((amt)>(high)?(high):(amt)))
#define round(x)     ((x)>=0?(long)((x)+0.5):(long)((x)-0.5))
#define radians(deg) ((deg)*DEG_TO_RAD)
#define degrees(rad) ((rad)*RAD_TO_DEG)
#define sq(x) ((x)*(x))

/* undefine stdlib's abs if encountered */
#ifdef abs
#undef abs
#endif
#define abs(x) (((x) > 0)  ?  (x) : -(unsigned)(x))

#endif

