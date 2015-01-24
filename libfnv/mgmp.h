#ifndef __MGMP_H
#define __MGMP_H

#include <sys/types.h>
#include <stdint.h>

uint64_t fnv_mpn_mul (uint64_t *, const uint64_t *, uint32_t, const uint64_t *, uint32_t);

#endif

