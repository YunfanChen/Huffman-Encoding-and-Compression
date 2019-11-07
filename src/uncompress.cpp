/**
 * TODO: file header
 *
 * Author:
 */
#include <fstream>
#include <iostream>
#include <sstream>

#include "FileUtils.hpp"
#include "HCNode.hpp"
#include "HCTree.hpp"

/* TODO: Pseudo decompression with ascii encoding and naive header (checkpoint)
 */
void pseudoDecompression(string inFileName, string outFileName) {
    ifstream filein;
    filein.open(inFileName);
    if (filein.fail()) {
        cout << "Error: Failed to open input file!" << endl;
        return;
    }
    vector<unsigned int> freq(256);
    byte buffer;
    int num;
    int count;
    string line;

    for (int i = 0; i < freq.size(); i++) {
        getline(filein, line);
        num = stoi(line);
        freq[i] = num;
        count = count + num;
    }

    HCTree hcTree;
    hcTree.build(freq);

    ofstream fileout;
    fileout.open(outFileName, std::ofstream::out | std::ofstream::trunc);
    if (fileout.fail()) {
        cout << "Error: Failed to open output file!" << endl;
        return;
    }

    char c;
    for (int i = 0; i < count; i++) {
        c = filein.get();
        istringstream is(c + "");
        buffer = hcTree.decode(is);
        if (buffer == (byte)-1) break;
        fileout << buffer;
    }

    filein.close();
    fileout.close();
}

/* TODO: True decompression with bitwise i/o and small header (final) */
void trueDecompression(string inFileName, string outFileName) {}

/* TODO: Main program that runs the uncompress */
int main(int argc, char* argv[]) { return 0; }
