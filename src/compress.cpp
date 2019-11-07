/**
 * TODO: file header
 *
 * Author:
 */
#include <fstream>
#include <iostream>
#include <sstream>
#include <unordered_map>

#include "FileUtils.hpp"
#include "HCNode.hpp"
#include "HCTree.hpp"

using namespace std;

/* TODO: add pseudo compression with ascii encoding and naive header
 * (checkpoint) */
void pseudoCompression(string inFileName, string outFileName) {
    unordered_map<byte, string> map;
    ifstream filein;
    filein.open(inFileName, ios::binary);
    // filein.open(inFileName);
    if (filein.fail()) {
        cout << "Error: Failed to open input file!" << endl;
        return;
    }
    vector<unsigned int> freq(256, 0);
    byte buffer;
    int index;

    while (1) {
        buffer = filein.get();
        index = (int)buffer;
        if (filein.eof()) break;
        freq[index]++;
    }
    filein.close();

    HCTree hcTree;
    hcTree.build(freq);

    ofstream fileout;
    // fileout.open(outFileName, std::ofstream::out | std::ofstream::trunc);
    fileout.open(outFileName, ios::binary);
    if (fileout.fail()) {
        cout << "Error: Failed to open output file!" << endl;
        return;
    }

    for (int i = 0; i < freq.size(); i++) {
        fileout << freq.at(i) << "\n";
    }

    // filein.open(inFileName);
    filein.open(inFileName, ios::binary);
    while (1) {
        ostringstream os;
        char c = filein.get();
        buffer = (byte)c;
        if (filein.eof()) break;
        if (map.find(buffer) != map.end()) {
            fileout << map[buffer];
        } else {
            hcTree.encode(buffer, os);
            map[buffer] = os.str();
            fileout << os.str();
        }
    }

    filein.close();
    fileout.close();

    return;
}

/* TODO: True compression with bitwise i/o and small header (final) */
void trueCompression(string inFileName, string outFileName) {}

/* TODO: Main program that runs the compress */
int main(int argc, char* argv[]) {
    // pseudoCompression("data/check1.txt", "data/check1encode.txt");
}