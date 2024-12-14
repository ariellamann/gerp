/*
 *  stringProcessing.cpp
 *  Ariella Mann {amann04} and Ben Rowland {browla01}
 *  4/17/23
 *
 *  CS 15 - Project 4 - gerp
 *
 * Defines a tree traversal function that prints the paths 
   to each file in a given directory. 
 */

#include <string>
#include <iostream>
#include "DirNode.h"
#include "FSTree.h"

using namespace std;

void treeTraversal(DirNode *currNode);
void treeTraversal(DirNode *currNode, string path);

/*
 * name:      main
 * purpose:  reads in commands 
 * arguments: number of command line arguments and an array
              of the arguments
 * returns:  zero
 */
int main(int argc, char *argv[]) {
    if (argc != 2) {
        cerr << "Error: directory\n";
        exit(EXIT_FAILURE);
    }

    FSTree directory(argv[1]);
    DirNode *root = directory.getRoot();
    treeTraversal(root);

    return 0;
}

/*
 * name:      treeTraversal
 * purpose:   wrapper function for treeTraversal
 * arguments: pointer to the root directory
 * returns:   nothing
 */
void treeTraversal(DirNode *currNode) {
    treeTraversal(currNode, "");
}

/*
 * name:      treeTraversal
 * purpose:   prints out the path to ever file accessible from a given
              directory
 * arguments: pointer to the root directory, string of previous path
 * returns:   nothing
 */
void treeTraversal(DirNode *currNode, string path) {
    for (int i = 0; i < currNode->numFiles(); i++) {
        cout << path + currNode->getName() + "/" + currNode->getFile(i) << endl;
    }
    for (int i = 0; i < currNode->numSubDirs(); i++) {
        treeTraversal(currNode->getSubDir(i), path + currNode->getName() + "/");
    }
}
