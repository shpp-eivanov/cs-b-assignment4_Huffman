/*******************************************************
 * File: HuffmanDecoding.h
 * --------------------------
 * v.2 2015/12/23
 * - decompress() is changed
 *
 * Definitions for the functions necessary to build a
 * Huffman encoding system.
 *
 *******************************************************/

#ifndef HuffmanDecoding_Included
#define HuffmanDecoding_Included

#include <fstream>
#include <iostream>
#include <iomanip>
#include "filelib.h"
#include <string>
#include "simpio.h"
#include "map.h"
#include <stdlib.h>
#include "console.h"
#include "strlib.h"
#include "vector.h"
#include "bstream.h"
#include "HuffmanDecoding.h"
#include "HuffmanTypes.h"


/* Function: readFileHeader
 * --------------------------------------------------------
 * Reads header of cyphered file and reconstructs huffman tree
 * for this cypher file
 */
void readFileHeader(ibstream& infile, Node* root);

/* Function: decodeFileToFile
 * --------------------------
 * Main cyphered text decoding process.
 */
void decodeFileToFile(ibstream &infile, Node* root, obstream &outfile);

/* Function: decompress
 * Usage: decompress(cypherFile, outFile);
 * --------------------------------------------------------
 * Main entry point for the Huffman decompressor.
 * Decompresses the cypherFile, then writes the decompressed version
 * to outFile.
 */
void decompress(string cypherFile, string outFile);

#endif
