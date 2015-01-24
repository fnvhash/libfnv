#include "mgmp.h"

typedef uint64_t mp_limb_t;
typedef const uint64_t *mp_srcptr;
typedef uint64_t *mp_ptr;
typedef size_t mp_size_t;


#define GMP_LIMB_BITS (sizeof(mp_limb_t) * 8)

#define GMP_LIMB_MAX (~ (mp_limb_t) 0)
#define GMP_LIMB_HIGHBIT ((mp_limb_t) 1 << (GMP_LIMB_BITS - 1))

#define GMP_HLIMB_BIT ((mp_limb_t) 1 << (GMP_LIMB_BITS / 2))
#define GMP_LLIMB_MASK (GMP_HLIMB_BIT - 1)

#define gmp_umul_ppmm(w1, w0, u, v)         \
  do {                  \
    mp_limb_t __x0, __x1, __x2, __x3;         \
    unsigned __ul, __vl, __uh, __vh;          \
    mp_limb_t __u = (u), __v = (v);         \
                  \
    __ul = __u & GMP_LLIMB_MASK;          \
    __uh = __u >> (GMP_LIMB_BITS / 2);          \
    __vl = __v & GMP_LLIMB_MASK;          \
    __vh = __v >> (GMP_LIMB_BITS / 2);          \
                  \
    __x0 = (mp_limb_t) __ul * __vl;         \
    __x1 = (mp_limb_t) __ul * __vh;         \
    __x2 = (mp_limb_t) __uh * __vl;         \
    __x3 = (mp_limb_t) __uh * __vh;         \
                  \
    __x1 += __x0 >> (GMP_LIMB_BITS / 2); \
    __x1 += __x2;                        \
    if (__x1 < __x2)                     \
      __x3 += GMP_HLIMB_BIT;             \
                  \
    (w1) = __x3 + (__x1 >> (GMP_LIMB_BITS / 2));      \
    (w0) = (__x1 << (GMP_LIMB_BITS / 2)) + (__x0 & GMP_LLIMB_MASK); \
  } while (0)

static mp_limb_t
mpn_addmul_1 (mp_ptr rp, mp_srcptr up, mp_size_t n, mp_limb_t vl) {
  mp_limb_t ul, cl, hpl, lpl, rl;

  cl = 0;
  do
    {
      ul = *up++;
      gmp_umul_ppmm (hpl, lpl, ul, vl);

      lpl += cl;
      cl = (lpl < cl) + hpl;

      rl = *rp;
      lpl = rl + lpl;
      cl += lpl < rl;
      *rp++ = lpl;
    }
  while (--n != 0);

  return cl;
}

static mp_limb_t
mpn_mul_1 (mp_ptr rp, mp_srcptr up, mp_size_t n, mp_limb_t vl) {
  mp_limb_t ul, cl, hpl, lpl;

  cl = 0;
  do
    {
      ul = *up++;
      gmp_umul_ppmm (hpl, lpl, ul, vl);

      lpl += cl;
      cl = (lpl < cl) + hpl;

      *rp++ = lpl;
    }
  while (--n != 0);

  return cl;
}


uint64_t fnv_mpn_mul (uint64_t *rp, const uint64_t *up, uint32_t un, const uint64_t *vp, uint32_t vn)
{

  /* We first multiply by the low order limb. This result can be
     stored, not added, to rp. We also avoid a loop for zeroing this
     way. */

  rp[un] = mpn_mul_1 (rp, up, un, vp[0]);
  rp += 1, vp += 1, vn -= 1;

  /* Now accumulate the product of up[] and the next higher limb from
     vp[]. */

  while (vn >= 1)
    {
      rp[un] = mpn_addmul_1 (rp, up, un, vp[0]);
      rp += 1, vp += 1, vn -= 1;
    }
  return rp[un - 1];
}

