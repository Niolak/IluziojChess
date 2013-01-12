#ifndef BB_H
#define BB_H

#include <stdint.h>

typedef uint64_t bb;

inline bb bbFrom(unsigned int n) {
    return ((bb)0x8000000000000000) >> n;
}

inline unsigned int firstBit(bb b) {
    return __builtin_clzl(b);
}

inline unsigned int lastBit(bb b) {
    return 63-__builtin_ctzl(b);
}

inline unsigned int countBits(bb b) {
    return __builtin_popcountl(b);
}

#endif // BB_H
