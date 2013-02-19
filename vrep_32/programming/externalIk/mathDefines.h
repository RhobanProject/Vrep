
#pragma once
#include <math.h>
#include <limits>
#include <float.h>
#include <cstdlib>
#define piVal 3.14159265359f
#define zd9868840d1 6.28318530718f
#define zdf5f975397 57.2957795130785499f
#define zae8adfe92e 0.017453292519944444f
#define z80bf311ca0 (0.01f*FLT_MAX) 
#define z8a29dc95a7 (0.01f*DBL_MAX) 
#define zbdcaeb8dad INT_MAX
#define z7b6672f671 (rand()/(float)RAND_MAX)

#ifdef za11fdc8cf2
#define VREP_IS_NAN(x) (_isnan(x))
#define VREP_IS_FINITE(x) (_finite(x))
#else
#ifdef z9b4cc679b0
#define VREP_IS_NAN(x) (_isnan(x))
#define VREP_IS_FINITE(x) (_finite(x))
#endif
#ifdef z26f0ce5fea
#define VREP_IS_NAN(x) ((zb91c101d5b::z3e914555f7::isnan)(x))
#define VREP_IS_FINITE(x) (z9d13fdffbf(x))
#endif
#ifdef z17293392e9
#define VREP_IS_NAN(x) (isnan(x))
#define VREP_IS_FINITE(x)                         \
			(sizeof (x) == sizeof (float)             \
			? z0dc7bb1a6c (x)                           \
			: sizeof (x) == sizeof (double)           \
			? za167c985ef (x) : z441e180d4d (x))
#endif
#endif

