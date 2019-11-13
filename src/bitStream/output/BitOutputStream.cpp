/**
 * TODO: file header
 *
 * Author:
 */
#include "BitOutputStream.hpp"

/* TODO */
void BitOutputStream::flush() {
    out.put(buf);
    buf = 0;
    nbits = 0;
}

/* TODO */
void BitOutputStream::writeBit(int i) {
    if (out.good()) {
        int num = i << (7 - nbits);
        buf = buf | num;
        nbits++;
        if (nbits == 8) flush();
    } else {
        flush();
    }
}
