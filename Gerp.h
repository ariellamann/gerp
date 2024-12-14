/*
 *  Gerp.h
 *  Ariella Mann {amann04} and Ben Rowland {browla01}
 *  4/21/23
 *
 *  CS 15 - Project 4 - gerp
 *
 *   This file holds the declaration of the Gerp class.
 *   This class is the core of the gerp program. The Gerp
 *   class reads in all of the information from the given
 *   directory and stores it in the hash table held in 
 *   TheHash class. This class also holds the query loop
 *   which prompts the user for queries (ex. words to search
 *   the directory for - which is stored in TheHAsh). 
 *   Every new instance of the Gerp class creates a new instance
 *   of TheHash class. The two public functions, run and readIn,
 *   are called in the driver function to begin the program. 
 */

#ifndef __GERP_H__
#define __GERP_H__

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include "DirNode.h"
#include "FSTree.h"
#include "TheHash.h"

using namespace std;

class Gerp {
    public:
    Gerp();
    ~Gerp();
    void run(string outputFile);
    void readIn(string directory);

    private:
    void command_loop(string &outputFile);
    string stripNonAlphaNum(string input);
    void open_output(ofstream &output, string &filename);
    void treeTraversal(DirNode *currNode);
    void treeTraversal(DirNode *currNode, string &path, string &filePath); 
    void readFile(string &path, int &pathIndex);
    

    TheHash *hash;
};

#endif
