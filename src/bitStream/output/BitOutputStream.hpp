/**
 * This is a class for BitOutputStream
 *
 * Author: Yunfan Chen
 */
#ifndef BITOUTPUTSTREAM_HPP
#define BITOUTPUTSTREAM_HPP

#include <iostream>

typedef unsigned char byte;

using namespace std;

/** class header */
class BitOutputStream {
  private:
    char buf;      // one byte buffer of bits
    int nbits;     // number of bits have been writen to buf
    ostream& out;  // reference to the output stream to use

  public:
    /* initialize the variables */
    explicit BitOutputStream(ostream& os) : out(os) {
        buf = 0;
        nbits = 0;
    };

    /* write 8 bit to out */
    void flush();

    /* write one bit */
    void writeBit(int i);
};

#endif
