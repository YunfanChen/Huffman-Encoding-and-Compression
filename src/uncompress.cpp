/**
 * Performs pseudo decompression on a given file
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

/* Pseudo decompression with ascii encoding and naive header (checkpoint)
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
    int count;
    string line;
    char cc;

    for (int i = 0; i < freq.size(); i++) {
        filein >> num;
        freq[i] = num;
    }

    HCTree hcTree;
    hcTree.build(freq);

    ofstream fileout;
    fileout.open(outFileName, std::ofstream::out | std::ofstream::trunc);

    char c;
    c = filein.get();
    string code;
    byte temp;
    while (1) {
        c = filein.get();
        if (filein.eof()) break;
        code = code + c;
        istringstream is(code);
        temp = hcTree.decode(is);
        if (map.find(is.str()) != map.end()) {
            fileout << map[is.str()];
            code = "";
        } else if (temp == (byte)-1) {
            continue;
        } else {
            buffer = temp;
            fileout << buffer;
            map[is.str()] = buffer;
            code = "";
        }
    }

    filein.close();
    fileout.close();
}

/* TODO: True decompression with bitwise i/o and small header (final) */
void trueDecompression(string inFileName, string outFileName) {
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

    BitInputStream inputStream(filein);
    for (int i = 0; i < freq.size(); i++) {
        filein >> num;
        freq[i] = num;
    }

    HCTree hcTree;
    hcTree.build(freq);

    ofstream fileout;
    fileout.open(outFileName, std::ofstream::out | std::ofstream::trunc);

    char c;
    c = filein.get();
    string code;
    byte temp;
    // stringstream ss;

    // BitOutputStream outputStream(ss);
    // BitInputStream inputStream(ss);
    while (1) {
        stringstream ss;
        c = filein.get();
        bitset<64> bits;
        for (int i = 0; i < 8; i++) {
            bits[i] = ((c >> i) & 1) + "";
            // cout << bits[i];
        }
        // cout << endl;
        code = (byte)c;

        if (filein.eof()) break;

        // cout << code << endl;
        // string ascii = string(1, stoi(code, nullptr, 2));
        ss.str(code);
        BitInputStream inputStream(ss);
        temp = hcTree.decode(inputStream);
        string bytecode = ss.get() + "";
        if (map.find(bytecode) != map.end()) {
            fileout << map[bytecode];
            code = "";
        } else if (temp == (byte)-1) {
            continue;
        } else {
            buffer = temp;
            fileout << buffer;
            map[bytecode] = buffer;
            code = "";
        }
    }

    filein.close();
    fileout.close();
}

/* Main program that runs the uncompress */
int main(int argc, char* argv[]) {
    cxxopts::Options options("./uncompress",
                             "Uncompresses files using Huffman Encoding");
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
    if (isAsciiOutput) {
        trueDecompression(argv[2], argv[3]);
    } else {
        pseudoDecompression(argv[1], argv[2]);
    }
}
