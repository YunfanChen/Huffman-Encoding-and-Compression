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
    // unordered_map<string, byte> map;
    // ifstream filein;
    // filein.open(inFileName);
    // if (filein.fail()) {
    //     cout << "Error: Failed to open input file!" << endl;
    //     return;
    // }
    // vector<unsigned int> freq(256);

    // byte buffer;
    // int num;
    // string line;

    // for (int i = 0; i < freq.size(); i++) {
    //     getline(filein, line);
    //     num = stoi(line);
    //     freq[i] = num;
    // }

    // HCTree hcTree;
    // hcTree.build(freq);

    // ofstream fileout;
    // fileout.open(outFileName, std::ofstream::out | std::ofstream::trunc);

    // char c;
    // string code;
    // byte temp;
    // BitInputStream inputStream(filein);
    // while (1) {
    //     c = filein.get();
    //     if (filein.eof()) break;

    //     buffer = hcTree.decode(inputStream);
    //     if (buffer == (byte)-1) break;
    //     fileout.put(buffer);
    // }

    // filein.close();
    // fileout.close();
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

    BitInputStream inputStream(filein);
    for (int i = 0; i < freq.size(); i++) {
        getline(filein, line);
        num = stoi(line);
        freq[i] = num;
    }

    HCTree hcTree;
    hcTree.build(freq);

    ofstream fileout;
    fileout.open(outFileName, std::ofstream::out | std::ofstream::trunc);

    char c;
    string code;
    byte temp;
    BitOutputStream outputStream(fileout);
    while (1) {
        // c = filein.get();
        if (filein.eof()) break;
        // code = code + c;
        // istringstream is(code);
        temp = hcTree.decode(inputStream);
        if (temp == (byte)-1) break;
        // if (map.find(temp) != map.end()) {
        //     fileout << map[is.str()];
        //     code = "";
        // } else if (temp == (byte)-1) {
        //     continue;
        // } else {
        // buffer = temp;
        // fileout << buffer;
        fileout.put(temp);
        //     map[is.str()] = buffer;
        //     code = "";
        // }
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
    // pseudoDecompression(argv[1], argv[2]);
}
