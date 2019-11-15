/**
 * This is a class for BitInputStream
 *
 * Author:Yunfan Chen
 */
#ifndef BITINPUTSTREAM_HPP
#define BITINPUTSTREAM_HPP

#include <iostream>

typedef unsigned char byte;

using namespace std;

/** class header */
class BitInputStream {
  private:
    char buf;     // one byte buffer of bits
    int nbits;    // number of bits have been writen to buf
    istream& in;  // reference to the input stream to use

  public:
    /* initialize variables */
    explicit BitInputStream(istream& is) : in(is) {
        nbits = 0;
        buf = 0;
    };

    /* Fill the inputstream */
    void fill();

    /* read a bit */
    unsigned int readBit();
};

#endif