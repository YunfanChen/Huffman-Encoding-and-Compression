/**
 * HCTree class
 *
 * Author: Yunfan Chen
 */
#include "HCTree.hpp"

priority_queue<HCNode*, vector<HCNode*>, HCNodePtrComp> pq;

/* delete the tree */
HCTree::~HCTree() { deleteAll(root); }

/* Build the HCTree from the given frequency vector. */
void HCTree::build(const vector<unsigned int>& freqs) {
    for (int i = 0; i < freqs.size(); i++) {
        if (freqs[i] != 0) {
            HCNode* node = new HCNode(freqs[i], i);
            leaves[i] = node;
            pq.push(node);
        }
    }
    if (pq.size() == 0) {
        root = new HCNode(0, 0);
        return;
    }
    if (pq.size() == 1) {
        HCNode* node = new HCNode(0, 0);
        pq.push(node);
    }
    while (pq.size() > 1) {
        HCNode* father = new HCNode(0, 0);

        HCNode* left = pq.top();
        father->c0 = left;
        // cout << "c0 is :" << left->symbol << endl;
        left->p = father;
        pq.pop();

        HCNode* right = pq.top();
        father->c1 = right;
        // cout << "c1 is :" << right->symbol << endl;
        right->p = father;
        pq.pop();

        father->count = father->count + left->count + right->count;

        pq.push(father);
    }
    root = pq.top();
    pq.pop();
}

/* TODO */
void HCTree::encode(byte symbol, BitOutputStream& out) const {
    HCNode* node = leaves[symbol];
    stack<char> s;
    while (node != root) {
        if (node->p->c0 == node) {  // node is left child
            s.push('0');
            node = node->p;
        } else if (node->p->c1 == node) {  // node is right child
            s.push('1');
            node = node->p;
        }
    }
    while (!s.empty()) {
        out.writeBit(s.top());
        s.pop();
    }
    out.flush();
}

/* Write the encoding bits of given symbol to ostream.  */
void HCTree::encode(byte symbol, ostream& out) const {
    HCNode* node = leaves[symbol];
    stack<char> s;
    while (node != root) {
        if (node->p->c0 == node) {  // node is left child
            s.push('0');
            node = node->p;
        } else if (node->p->c1 == node) {  // node is right child
            s.push('1');
            node = node->p;
        }
    }
    while (!s.empty()) {
        out << (s.top());
        s.pop();
    }
}

/* TODO */
byte HCTree::decode(BitInputStream& in) const {
    HCNode* node = root;
    int curBit;

    while (node->c0 || node->c1) {
        curBit = in.readBit();
        if (curBit == 1) {
            if (node->c1 == nullptr) return -1;
            node = node->c1;
        } else if (curBit == 0) {
            if (node->c0 == nullptr) return -1;
            node = node->c0;
        } else {
            return -1;
        }
    }
    if (node->c0 == nullptr && node->c1 == nullptr) return node->symbol;
    return -1;
}

/* Decode the sequence of bits (represented as char of either ‘0’ or ‘1’)
 * from istream to return the coded symbol. */
byte HCTree::decode(istream& in) const {
    char c;
    HCNode* node = root;
    while (1) {
        in.get(c);
        if (in.eof()) break;
        if (c == '0') {
            if (node->c0 == nullptr) return -1;
            node = node->c0;
        } else if (c == '1') {
            if (node->c1 == nullptr) return -1;
            node = node->c1;
        } else {
            return -1;
        }
    }
    if (node->c0 == nullptr && node->c1 == nullptr) return node->symbol;
    return -1;
}

/** Delete all nodes in the tree*/
void HCTree::deleteAll(HCNode* node) {
    if (node) {
        deleteAll(node->c1);
        deleteAll(node->c0);
    }
    delete node;
}
