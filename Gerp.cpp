/*
 *  Gerp.cpp
 *  Ariella Mann {amann04} and Ben Rowland {browla01}
 *  4/21/23
 *
 *  CS 15 - Project 4 - gerp
 *
 *   This file holds the implementation of the Gerp class.
 *   To best use this class, simply declare an instance of 
 *   the Gerp class and call the two public functions on that
 *   instance, readIn and then run. ReadIN will read from the
 *   given directory and store all of the information in TheHash
 *   class to make accessing and query responses quick. The run
 *   function prompts the user and deals with all queries, it 
 *   runs the program. 
 *
 */

#include <iostream>
#include "Gerp.h"
#include <cassert>

using namespace std;

/*
 * name:      constuctor 
 * purpose:   constucts an instance of Gerp
 */
Gerp::Gerp() {
    hash = new TheHash();
}

/*
 * name:      destructor
 * purpose:   deletes any manually allocated memory
 */
Gerp::~Gerp() {
    delete hash;
}

/*
 * name:      run
 * purpose:   public function called to run program
 *            which calls command loop
 */
void Gerp::run(string outputFile) {
    command_loop(outputFile);
}

/*
 * name:      command_loop
 * purpose:   reads in commands from user and calls 
 *            respective function to implement query
 * arguments: output file to store printed lines later
 * returns:   none
 */
void Gerp::command_loop(string &outputFile) {
    ofstream outstream;
    open_output(outstream, outputFile);
    bool finish = false;
    string prompt;
    cout << "Query? ";
    while (not finish and (cin >> prompt)) {
        if (prompt == "@quit" or prompt == "@q") {
            finish = true;
        }
        else if (prompt == "@insensitive" or prompt == "@i") {
            cin >> prompt;
            prompt = stripNonAlphaNum(prompt);
            hash->printInsensitive(prompt, outstream);
        }
        else if (prompt == "@f") {
            outstream.close();
            cin >> prompt;
            open_output(outstream, prompt);
        }
        else {
            prompt = stripNonAlphaNum(prompt);
            hash->printSensitive(prompt, outstream);
        }
        if (not finish) {
            cout << "Query? ";
        }
    }
    outstream.close();
    std::cout << "Goodbye! Thank you and have a nice day." << endl;
}

/*
 * name:      stripNonAlphaNum
 * purpose:   gets rid of trailing non letter or number characters
 * arguments: original string to strip
 * returns:   stripped version of the string: only alphanumerical chars
 */
string Gerp::stripNonAlphaNum(string input) {
    int start, end, i;
    start = end = i = 0;
    int length = input.length();
    bool notDone = true;
    while (notDone and i < length) {
        char temp = input[i];
        if ((temp >= 97 and temp <= 122) or (temp >= 65 and temp <= 90) or
            (temp >= 48 and temp <= 57)) {
            start = i;
            notDone = false;
        }
        i++;
    }
    if (notDone == true) { 
        return "";
    }
    i = length;
    notDone = true;
    while (notDone and i > start) {
        char temp = input[i];
        if ((temp >= 97 and temp <= 122) or (temp >= 65 and temp <= 90) or
            (temp >= 48 and temp <= 57)) {
            end = i;
            notDone = false;
        }
        i--;
    }
    return input.substr(start, end - start + 1);
}

/*
 * name:      open_output
 * purpose:   opens an output stream
 * arguments: output stream and a string of the file name
 * returns:   none
 */
void Gerp::open_output(ofstream &stream, string &filename) {
    stream.open(filename);
    if (not stream.is_open()) {
        std::cerr << "Error: could not open file " << filename << std::endl;
        exit(EXIT_FAILURE);
    }
}

/*
 * name:      readIn
 * purpose:   builds FSTree, calls to traverse it and read in
              and store all the information
 * arguments: string of the given directory
 * returns:   none
 */
void Gerp::readIn(string directory) {
    FSTree theTree(directory);
    DirNode *root = theTree.getRoot();
    treeTraversal(root);
}

/*
 * name:      treeTraversal
 * purpose:   wrapper function for treeTraversal
 * arguments: pointer to the root directory
 * returns:   nothing
 */
void Gerp::treeTraversal(DirNode *currNode) {
    string empty = "";
    treeTraversal(currNode, empty, empty);
}

/*
 * name:      treeTraversal (recursive)
 * purpose:   traverses the FSTree and reads every file
 * arguments: pointer to the root of the FSTree, a string with the path
              up until this point, and the file path to be opened 
 * returns:   none
 */
void Gerp::treeTraversal(DirNode *currNode, string &path, string &filePath) {
    for (int i = 0; i < currNode->numFiles(); i++) {
        string pathPlus = path + currNode->getName()+ "/" + 
                          currNode->getFile(i);
        string filePathPlus = filePath + currNode->getName()+ "//" + 
                              currNode->getFile(i);
        int pathIndex = hash->addPath(pathPlus);
        readFile(filePathPlus, pathIndex);
    }
    for (int i = 0; i < currNode->numSubDirs(); i++) {
        string newPath = path + currNode->getName() + "/";
        string newFilePath = filePath + currNode->getName() + "//";
        treeTraversal(currNode->getSubDir(i), newPath, newFilePath);
    }
}

/*
 * name:      readFile
 * purpose:   reads a file and stores information into the hash
 * arguments: string of the file to be opened
 * returns:   none
 */
void Gerp::readFile(string &fileName, int &pathIndex) {
    ifstream infile(fileName);
    if (not infile.is_open()) {
        std::cerr << "Error: could not open file " << fileName << std::endl;
        exit(EXIT_FAILURE);
    }
    string line;
    int lineNum = 1;
    while (not infile.eof()) {
        getline(infile, line);
        string fullLine = ":" + to_string(lineNum) + ": "+line;
        int lineIndex = hash->addLine(fullLine);
        int index = min(line.find(" "), line.find("\t"));
        
        while (index != -1) {
            string word = stripNonAlphaNum(line.substr(0,index));
            line = line.substr(index + 1);
            hash->addWord(word, lineIndex, pathIndex);
            index = min(line.find(" "), line.find("\t"));
        }
        string toAdd = line.substr(index+1);
        hash->addWord(toAdd, lineIndex, pathIndex);
        hash->addWord(stripNonAlphaNum(line.substr(index+1)), 
                     lineIndex, pathIndex);
        lineNum++;
    }
    infile.close();
}
