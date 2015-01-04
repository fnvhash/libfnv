/* Fast FNV64-1a implementation in optimized x64 assembly for gas / gcc
 * Donated with compliments into the public domain by
 *
 * http://fnvhash.com
 *
 * Based on earlier work by M.S.Schulte
 *
 * Benchmarked to perform about 25% faster than gcc pure C reference
 * implementation hash_64a.c.
 *
 * Call with:
 *
 * #include <inttypes.h>
 *
 * #define FNV64_1A_INIT 0xcbf29ce484222325ULL
 *
 * uint64_t fnv64a(unsigned char *buf, uint64_t len, uint64_t hval);
 *
 * uint64_t result = fnv64a(buf, BUFSIZE, FNV64_1A_INIT);
 */

        .globl  fnv64a

        .text
fnv64a:
        mov     %rdx, %rax
        mov     %rsi, %rcx
        movq    $0x100000001b3, %rsi
        xor     %rdx, %rdx
nexta:
        movb (%rdi), %dl
        xorb    %dl, %al
        mul     %rsi
        inc     %rdi
        dec     %rcx
        jnz nexta
        ret
