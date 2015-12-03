/*******************************************************
 * File: HuffmanEncoding.h
 *
 * Definitions for the functions necessary to build a
 * Huffman encoding system.
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
 * Reads header of cyphered file and reconstructs huffman tree
 * --------------------------------------------------------
 * Reads header of cyphered file and reconstructs huffman tree
 * for this cypher file
 */
void readFileHeader(ibstream& infile, Node* root);

/* Main cypher text decoding process */
void decodeFileToFile(ibstream &infile, Node* root, obstream &outfile);

/* Function: decompress
 * Usage: decompress(infile, outfile);
 * --------------------------------------------------------
 * Main entry point for the Huffman decompressor.
 * Decompresses the file whose contents are specified by the
 * input ibstream, then writes the decompressed version of
 * the file to the stream specified by outfile.
 */
void decompress(ibstream& infile, obstream &outfile);

#endif
