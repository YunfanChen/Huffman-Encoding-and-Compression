/**
 * Performs pseudo compression on a given file
 *
 * Author: Yunfan Chen
 */
#include <fstream>
#include <iostream>
#include <sstream>
#include <unordered_map>

#include "FileUtils.hpp"
#include "HCNode.hpp"
#include "HCTree.hpp"
#include "cxxopts.hpp"

using namespace std;

/* Add pseudo compression with ascii encoding and naive header
 * (checkpoint) */
void pseudoCompression(string inFileName, string outFileName) {
    unordered_map<byte, string> map;
    ifstream filein;
    filein.open(inFileName);
    if (filein.fail()) {
        cout << inFileName << endl;
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
    fileout.open(outFileName, std::ofstream::out | std::ofstream::trunc);

    for (int i = 0; i < freq.size(); i++) {
        fileout << freq.at(i) << "\n";
    }

    filein.open(inFileName);
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

/* Main program that runs the compress */
int main(int argc, char* argv[]) {
    cxxopts::Options options("./compress",
                             "Compresses files using Huffman Encoding");
    options.positional_help("./path_to_input_file ./path_to_output_file");

    bool isAsciiOutput = false;
    string inFileName, outFileName;
    options.allow_unrecognised_options().add_options()(
        "ascii", "Write output in ascii mode instead of bit stream",
        cxxopts::value<bool>(isAsciiOutput))(
        "input", "", cxxopts::value<string>(inFileName))(
        "output", "", cxxopts::value<string>(outFileName))(
        "h,help", "Print help and exit");

    options.parse_positional({"input", "output"});
    auto userOptions = options.parse(argc, argv);

    if (userOptions.count("help") || !FileUtils::isValidFile(inFileName) ||
        outFileName.empty()) {
        cout << options.help({""}) << std::endl;
        exit(0);
    }
    pseudoCompression(argv[2], argv[3]);
}