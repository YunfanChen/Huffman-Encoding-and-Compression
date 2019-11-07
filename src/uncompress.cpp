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

/* TODO: Pseudo decompression with ascii encoding and naive header (checkpoint)
 */
void pseudoDecompression(string inFileName, string outFileName) {
    unordered_map<string, byte> map;
    ifstream filein;
    filein.open(inFileName);
    if (filein.fail()) {
        cout << "Error: Failed to open input file!" << endl;
        return;
    }
    vector<unsigned int> freq(256);
    byte buffer;
    int num;
    string line;

    for (int i = 0; i < freq.size(); i++) {
        getline(filein, line);
        num = stoi(line);
        freq[i] = num;
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
    string code;
    while (1) {
        c = filein.get();
        if (filein.eof()) break;
        code = code + c;
        istringstream is(code);
        if (map.find(is.str()) != map.end()) {
            fileout << map[is.str()];
            code = "";
        } else if (hcTree.decode(is) == (byte)-1) {
            continue;
        } else {
            buffer = hcTree.decode(is);
            fileout << buffer;
            map[is.str()] = buffer;
            code = "";
        }
    }

    filein.close();
    fileout.close();
}

/* TODO: True decompression with bitwise i/o and small header (final) */
void trueDecompression(string inFileName, string outFileName) {}

/* TODO: Main program that runs the uncompress */
int main(int argc, char* argv[]) {
    pseudoDecompression("data/check1encode.txt", "data/check1decode.txt");
}
