/**
 * TODO: file header
 *
 * Author:
 */
#include "HCTree.hpp"

priority_queue<HCNode*, vector<HCNode*>, HCNodePtrComp> pq;

/* TODO */
HCTree::~HCTree() { delete root; }

/* TODO */
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
void HCTree::encode(byte symbol, BitOutputStream& out) const {}

/* TODO */
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
byte HCTree::decode(BitInputStream& in) const { return ' '; }

/* TODO */
byte HCTree::decode(istream& in) const {
    char c;
    HCNode* node = root;
    while (node->c0 != nullptr || node->c1 != nullptr) {
        in.get(c);
        // cout << "debug get: " << c << endl;
        if (c == '0') {
            node = node->c0;
        } else if (c == '1') {
            node = node->c1;
        } else {
            return -1;
        }
    }
    // cout << "my decode symbol is: " << node->symbol << endl;
    return node->symbol;
}
