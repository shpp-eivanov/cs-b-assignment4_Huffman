/*******************************************************
 * File: HuffmanEncoding.h
 * --------------------------
 * v.2 2015/12/23
 * - compress() is changed
 *
 * Definitions for the functions necessary to build a
 * Huffman encoding system.
 *******************************************************/

#ifndef HuffmanEncoding_Included
#define HuffmanEncoding_Included

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
#include "HuffmanEncoding.h"
#include "HuffmanTypes.h"


/* Function: fileInput
 * -------------------
 * Defines if this file exist in project directory
 */
string fileInput(string promptText);

/* Function: getFrequencyTable
 * Usage: Map<ext_char, int> freq = getFrequencyTable(file);
 * --------------------------------------------------------
 * Given an input stream containing text, calculates the
 * frequencies of each character within that text and stores
 * the result as a Map from ext_chars to the number of times
 * that the character appears.
 */
Map<ext_char, int> getFrequencyTable(ibstream &infile);

/* Function: buildNodesVector
 * Usage: buildNodesVector(vector, frequencyTable);
 * --------------------------------------------------------
 * Creates symbols Nodes from table and adds them to Nodes* vector
 */
void buildNodesVector(Vector<Node*>& nodesVector, Map<ext_char, int> &fileFrequenciesTable);

/* Function: buildEncodingTree
 * Usage: Node* tree = buildEncodingTree(nodesVector);
 * --------------------------------------------------------
 * Given a nodesVector of frequencies,
 * constructs a Huffman encoding tree from those frequencies
 * and returns a pointer to the root.
 *
 * This function can assume that there is always at least one
 * entry in the map, since the EOF character will always
 * be present
 */
Node* buildEncodingTree(Vector<Node*> &nodesVector);

/* Function: deleteTree
 * Usage: deleteTree(encodingTree);
 * --------------------------------
 * Deallocates all memory allocated for a given encoding
 * tree.
 */
void deleteTree(Node* &node);

/* Function: encodeTreeToFileHeader
 * --------------------------------
 * Encodes tree shape into cypherFile.
 * Makes depth traversing of coding tree, and writes:
 *
 * - 0 - if it's knot at this traverse, without symbols
 *
 * - 1 - if it's leaf at this traverse, without childs.
 *   It is followed by char byte code.
 */
void encodeTreeToFileHeader(Node* node, obstream &outstr);

/* Function: encodeMainTextToFile
 * Usage: encodeMainTextToFile(sourceFile, encodingTree, cypheredFile);
 * --------------------------------------------------------
 * Encodes the given file using the encoding specified by the
 * given encoding tree, then writes the result one bit at a
 * time to the specified output file.
 *
 * This function can assume the following:
 *
 *   - The encoding tree was constructed from the given file,
 *     so every character appears somewhere in the encoding
 *     tree.
 *
 *   - The output file already has the encoding table written
 *     to it, and the file cursor is at the end of the file.
 *     This means that you should just start writing the bits
 *     without seeking the file anywhere.
 */
void encodeMainTextToFile(ibstream &infile, Node* encodingTree, obstream &outfile);

/* Function: compress
 * Usage: compress(inputFile, cypherFile);
 * --------------------------------------------------------
 * Main entry point for the Huffman compressor.  Compresses
 * the inputFile, then writes the result to cypherFile.
 */
void compress(string inputFile, string cypherFile);

#endif
