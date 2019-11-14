/**
 * TODO: file header
 *
 * Author:
 */
#include "BitInputStream.hpp"

/* TODO */
void BitInputStream::fill() {
    buf = in.get();
    nbits = 8;
}

/* TODO */
unsigned int BitInputStream::readBit() {
    if (nbits == 0) {
        fill();
        if (!in.good()) return -1;
    }
    if (in.good()) {
        int bit = ((buf & (1 << (nbits - 1))) ? 1 : 0);
        nbits--;
        return bit;
    } else {
        return -1;
    }
}