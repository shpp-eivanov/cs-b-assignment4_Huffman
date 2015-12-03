/**********************************************************
 * File: Huffman.cpp
 * ----------------------
 * v.1 2015/11/10
 * Program makes Huffman principle compression and
 * decompression for user .txt file.
 **********************************************************/
#include <iostream>
#include "simpio.h"
#include "console.h"
#include "bstream.h"
#include "HuffmanEncoding.h"
#include "HuffmanDecoding.h"
#include "HuffmanTypes.h"

using namespace std;

int main() {
   /* Huffman text file compression-decompression process
    * --------------------------------------------------------
    * Input file is coded due to Huffman compression rules
    * into cypherFile. After then cypher file is decompressed
    * into outFile.
    *
    * Input files are saved into res project folder, or you could
    * use fileInput function for console input
    * Output files will be saved into project build folder
    *
    * After decompression this programm is done.
    *
    * Suposed, it will be simple .txt file.
    * Any other file types weren't tesetd.
    */

   //string inputFile = fileInput("Enter file name: ");
   string inputFile = "tomSawyer.txt";
   string cypherFile = "Cyphered_" + inputFile;
   string outFile = "Decoded_" + inputFile;

   cout << "PROCESSING..." << endl;
   cout << "==========================================================" << endl;
   /* Huffman compression process */
   cout << "    - WAIT, FILE \"" << inputFile << "\" IS BEING CODED..." << endl;
   /* Prepare input stream object   */
   ifbstream infile;
   infile.open(inputFile.c_str());
   ofbstream outfile;
   outfile.open(cypherFile.c_str());
   /* Input file compression */
   compress(infile, outfile);
   infile.close();
   outfile.close();
   cout << "    - FILE'S CODING COMPLETE!" << endl;

   /* Huffman decompression process */
   cout << "    - WAIT, CYPHER FILE \"" << cypherFile << "\" IS BEING DECODED..." << endl;
   ifbstream ibStream;
   ibStream.open(cypherFile.c_str());
   ibStream.rewind();
   ofbstream outstr2;
   outstr2.open(outFile.c_str());
   /* Cypher file decompression */
   decompress(ibStream,outstr2);
   ibStream.close();
   outstr2.close();
   cout << "    - CYPHER FILE DECODING COMPLETE TO FILE: \"" << outFile << "\"" <<  endl;
   cout << "=================================================" << endl;
   cout << "ALL FILES ARE SAVED INTO PROJECT BUILD FOLDER!" << endl;

   return 0;
}
