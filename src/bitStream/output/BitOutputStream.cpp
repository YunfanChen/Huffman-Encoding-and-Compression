/**
 * a class for BitOutputStream
 *
 * Author: Yunfan Chen
 */
#include "BitOutputStream.hpp"

/* write 8 bits to out */
void BitOutputStream::flush() {
    out.put(buf);
    buf = 0;
    nbits = 0;
}

/* write one bit */
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
