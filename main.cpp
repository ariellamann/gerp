/*
 *  main.cpp
 *  Ariella Mann and Ben Rowland
 *  4/24/23
 *
 * CS 15 - Project 4 - gerp
 *  
 * This file is the driver function for the gerp program. 
   The gerp program searches through a given directory for 
   word given by the user and prints out all instances of that
   word in the directory to a given output file. 
   This program is helping for searching a large directory for 
   a specific word because also tells the user the exact file 
   and line where they can find that word. 
 *
 */

#include "Gerp.h"
#include "TheHash.h"
#include "DirNode.h"
#include "FSTree.h"


using namespace std;

/* Name:       main
 * Purpose:    Main function for the gerp program. Reads
               in from the command line and calls to readIn 
               from the given directory and run which runs 
               the program
 * Parameters: number of command line arguments and an 
               array of things on the command line
 * Returns:    zero
 */
int main(int argc, char *argv[]){
    if (argc != 3) {
        cerr << "Usage: ./gerp inputDirectory outputFile\n";
        exit(EXIT_FAILURE);
    }

    Gerp gerp_program;
    gerp_program.readIn(argv[1]);
    gerp_program.run(argv[2]);

    return 0;
}
