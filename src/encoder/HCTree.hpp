/**
 * This is class for HCTree
 *
 * Author: Yunfan Chen
 */
#ifndef HCTREE_HPP
#define HCTREE_HPP

#include <fstream>
#include <queue>
#include <stack>
#include <vector>
#include "BitInputStream.hpp"
#include "BitOutputStream.hpp"
#include "HCNode.hpp"

using namespace std;

/** HCTree class */
class HCTree {
  private:
    HCNode* root;            // the root of HCTree
    vector<HCNode*> leaves;  // a vector storing pointers to all leaf HCNodes

    /* delete all node in HCTree */
    void deleteAll(HCNode*);

  public:
    /* Initializes a new empty HCTree. */
    explicit HCTree() : root(0) { leaves = vector<HCNode*>(256, (HCNode*)0); }

    /* delete the tree */
    ~HCTree();

    /* Build the HCTree from the given frequency vector. */
    void build(const vector<unsigned int>& freqs);

    /* Write the encoding bits of given symbol to ostream.  */
    void encode(byte symbol, BitOutputStream& out) const;

    /*  add function header */
    void encode(byte symbol, ostream& out) const;

    /*  add function header */
    byte decode(BitInputStream& in) const;

    /* Decode the sequence of bits (represented as char of either ‘0’ or ‘1’)
     * from istream to return the coded symbol. */
    byte decode(istream& in) const;
};

#endif  // HCTREE_HPP
