/**********************************************************
* File: HuffmanDecoding.cpp
* --------------------------
* v.2 2015/12/23
* - decompress() is changed
* - "HuffmanEncoding.h" to import deleteTree is added
*
* Implementation of the functions from HuffmanEncoding.h.
*
**********************************************************/

#include "HuffmanDecoding.h"
#include "HuffmanEncoding.h" //To import deleteTree
#include "HuffmanTypes.h"

using namespace std;


/* Function: readFileHeader
 * Reads header of cyphered file and reconstructs huffman tree
 * --------------------------------------------------------
 * Reads header of cyphered file and reconstructs huffman tree
 * for this cypher file
 */
void readFileHeader(ibstream& infile, Node* root) {
    /* Recursive header decoding */
    int bit = 0;
    if ((bit = infile.readBit()) > -1) {
        if (bit == 1) {//It's a tree leaf
            /* We write followed symbol into leaf node */
            ext_char nodeSymb = infile.get();
            root->symbol = nodeSymb;
        }else if (bit == 0) {//It's a tree knot
            /* We have to create children for it */
            root->symbol = NOT_A_CHAR;
            Node* leftChild = new Node;
            Node* rightChild = new Node;
            root->leftChild = leftChild;
            root->rightChild = rightChild;
            /* Move to children */
            readFileHeader(infile, leftChild);
            readFileHeader(infile, rightChild);
        }
    }
}

/* Function: decodeFileToFile
 * --------------------------
 * Main cyphered text decoding process.
 */
void decodeFileToFile(ibstream& infile, Node* root, obstream& outfile) {
    int bit;
    Node* currentNode = root;
    /* Runs through every cypher bit and, at the same time, move
     * through tree to symbols leafs */
    while ((bit = infile.readBit()) > -1) {
        if (bit == 0) {
            currentNode = currentNode->leftChild;
        }else{
            currentNode = currentNode->rightChild;
        }
        if ((currentNode->symbol) < NOT_A_CHAR) {
            if (((char)currentNode->symbol) == EOF) {
                break;
            }else{
                outfile.put((char)(currentNode->symbol));
            }
            currentNode = root;
        }
    }
}

/* Function: decompress
 * Usage: decompress(infile, outfile);
 * --------------------------------------------------------
 * Main entry point for the Huffman decompressor.
 * Decompresses the file whose contents are specified by the
 * input ibstream, then writes the decompressed version of
 * the file to the stream specified by outfile.
 */
void decompress(string cypherFile, string outFile) {
    cout << "    - WAIT, CYPHER FILE \"" << cypherFile << "\" IS BEING DECODED..." << endl;
    ifbstream ibStream;
    ibStream.open(cypherFile.c_str());
    //ibStream.rewind();
    ofbstream obStream;
    obStream.open(outFile.c_str());

    Node* huffmanTreeRoot = new Node;
    /* Gets Huffman tree from the header */
    readFileHeader(ibStream, huffmanTreeRoot);

    ibStream.get();//get some redundant charr

    /* Main decoding process */
    decodeFileToFile(ibStream, huffmanTreeRoot, obStream);

    deleteTree(huffmanTreeRoot);

    ibStream.close();
    obStream.close();
    cout << "    - CYPHER FILE DECODING COMPLETE TO FILE: \"" << outFile << "\"" << endl;
    cout << "==========================================================" << endl;
    cout << "ALL FILES ARE SAVED INTO PROJECT BUILD FOLDER!" << endl;
}
