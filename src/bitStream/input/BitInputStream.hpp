/**
 * TODO: file header
 *
 * Author:
 */
#ifndef BITINPUTSTREAM_HPP
#define BITINPUTSTREAM_HPP

#include <iostream>

typedef unsigned char byte;

using namespace std;

/** TODO: class header */
class BitInputStream {
  private:
    char buf;     // one byte buffer of bits
    int nbits;    // number of bits have been writen to buf
    istream& in;  // reference to the input stream to use

  public:
    /* TODO: add function header and implement */
    explicit BitInputStream(istream& is) : in(is){};

    /* TODO: add function header */
    void fill();

    /* TODO: add function header */
    unsigned int readBit();
};

#endif