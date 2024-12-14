/*
 *  TheHash.cpp
 *  Ariella Mann and Ben Rowland
 *  4/21/23
 *
 *  COMP 15 Proj 4
 *
 *  This file holds the implementation of the functions in TheHash 
    class. An instance of TheHash is created with every instance
    of the Gerp class. 
 *
 */

#include "TheHash.h"
#include <cassert>


using namespace std;

/*
 * name:      TheHash constructor
 * purpose:   sets all variables of the hash 
 */
TheHash::TheHash() {
    loadFactor = 0;
    numElements = 0;
    tableSize = 10631;
    hashTable = new hashNode *[tableSize];
    for (int i = 0; i < tableSize; i++) {
        hashTable[i] = nullptr;
    }
}

/*
 * name:      TheHash destructor
 * purpose:   deletes all manually allocated memory 
 */
TheHash::~TheHash() {
    for(int i = 0; i < tableSize; i++) {
        hashNode *currNode = hashTable[i];
        while (currNode != nullptr) {
            hashNode *temp = currNode;
            currNode = currNode->nextNode;
            delete temp;
        }
    }
    delete [] hashTable;
}

/*
 * name:      resizeTable
 * purpose:   allocates more space for the hash
 */
void TheHash::resizeTable() {
    int oldTableSize = tableSize;
    tableSize = tableSize * 2 + 1;
    hashNode **oldHashTable = hashTable;
    hashTable = new hashNode *[tableSize];
    for (int i = 0; i < tableSize; i++) {
        hashTable[i] = nullptr;
    }
    hashNode *currNode = nullptr;
    hashNode *temp = currNode;
    for (int i = 0; i < oldTableSize; i++) {
        currNode = oldHashTable[i];
        while (currNode != nullptr) {
            addWord(currNode->name, currNode->line, currNode->path);
            temp = currNode;
            currNode = currNode->nextNode;
            delete temp;
        }
    }
    delete [] oldHashTable;
}


/*
 * name:      addWord
 * purpose:   adds word to the hash
 * arguments: word to be added, the index of where the path
              that file is stored and the index of where that
              line is stored (both in vectors)
 * returns:   none
 */
void TheHash::addWord(string word, int line, int path) {
    loadFactor = (float)numElements/tableSize;
    if (loadFactor > 0.7) {
        resizeTable();
    }
    string lowerCase = makeLowerCase(word);
    size_t index = hash<string>{}(lowerCase);
    index = index % tableSize;
    hashNode *currNode = hashTable[index];
    while (currNode != nullptr and line == currNode->line) {
        if (word.compare(currNode->name) == 0) {
            return;
        }
        currNode = currNode->nextNode;
    }
    hashNode *newNode = new hashNode();
    newNode->line = line;
    newNode->path = path;
    newNode->name = word;
    newNode->nextNode = hashTable[index];
    hashTable[index] = newNode;
    numElements++;
}

/*
 * name:      addPath
 * purpose:   stores the path in vector in hash
 * arguments: string with the path to be added
 * returns:   none
 */
int TheHash::addPath(string &path) {
    int nextIndex = paths.size();
    paths.push_back(path);
    return nextIndex;
}

/*
 * name:      addLine
 * purpose:   stores the line in vector in hash
 * arguments: string with the line to be added
 * returns:   none
 */
int TheHash::addLine(string &line) {
    int nextIndex = lines.size();
    lines.push_back(line);
    return nextIndex;
}

/*
 * name:      getPath
 * purpose:   path getter
 * arguments: int of index of path wanted
 * returns:   string of path
 */
string TheHash::getPath(int i) {
    return paths[i];
}

/*
 * name:      getLine
 * purpose:   line getter
 * arguments: int of index of line wanted
 * returns:   string of line
 */
string TheHash::getLine(int i) {
    return lines[i];
}

/*
 * name:      printInsensitive
 * purpose:   prints path, line number, and line to an output file
              when it contains the word the user searches for 
 * arguments: word to search for and stream of where to print   
              the final lines where the word is found
 * returns:   none
 */
void TheHash::printInsensitive(string word, ostream &output) {
    if (word != "") {
        string lowerCase = makeLowerCase(word);
        size_t index = hash<string>{}(lowerCase);
        index = index % tableSize;
        hashNode *currNode = hashTable[index];
        if (currNode == nullptr) {
            output << word << " Not Found.\n"; 
        }
        int lastLine = -1;
        while(currNode != nullptr) {
            if (currNode->line != lastLine) {
                output << paths[currNode->path] 
                       << lines[currNode->line] << endl;
                lastLine = currNode->line;
            }
            currNode = currNode->nextNode;
        }
    }
    else {
        output << word << " Not Found.\n"; 
    } 
}

/*
 * name:      printSensitive
 * purpose:   prints path, line number, and line to an output file
              when it contains the word the user searches for 
 * arguments: word to search for and stream of where to print   
              the final lines where the word is found
 * returns:   none
 */
void TheHash::printSensitive(string word, ostream &output) {
    bool foundWord = false;
    if (word != "") {
        string lowerCase = makeLowerCase(word);
        size_t index = hash<string>{}(lowerCase);
        index = index % tableSize;
        hashNode *currNode = hashTable[index];
        while(currNode != nullptr) {
            if (word.compare(currNode->name) == 0) {
                output << paths[currNode->path] 
                       << lines[currNode->line] << endl;
                foundWord = true;
            }
            currNode = currNode->nextNode;
        }
    }
    if ((not foundWord) or (word == "")) {
        output << word << " Not Found. Try with @insensitive or @i.\n";
    }
}

/*
 * name:      makeLowerCase
 * purpose:   turns a string into all lowercase chars
 * arguments: string of word to be made lowercase  
 * returns:   fully lowercase string
 */
string TheHash::makeLowerCase(string word) {
    int length = word.length();
    for (int i = 0; i < length; i++) {
        word[i] = tolower(word[i]);
    }
    return word;
}
