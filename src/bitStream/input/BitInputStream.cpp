/**
 * This is a class for BitInputStream.
 *
 * Author: Yunfan Chen
 */
#include "BitInputStream.hpp"

/* Fill the inputstream */
void BitInputStream::fill() {
    buf = in.get();
    nbits = 8;
}

/* read a bit */
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