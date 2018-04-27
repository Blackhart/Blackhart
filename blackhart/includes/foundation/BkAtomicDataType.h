#ifndef __BK_ATOMIC_DATA_TYPES_H__
#define __BK_ATOMIC_DATA_TYPES_H__

// Standard headers.
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

typedef int8_t      int8;
typedef int16_t     int16;
typedef int32_t     int32;
typedef int64_t     int64;

typedef uint8_t     uint8;
typedef uint16_t    uint16;
typedef uint32_t    uint32;
typedef uint64_t    uint64;

#ifdef __BK_DOUBLE_PRECISION_FLOATING_POINT
    typedef double  real;
#else
    typedef float   real;
#endif

#define BK_REAL(x)	(real)(x)

#endif