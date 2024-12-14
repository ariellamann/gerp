/*
 *  TheHash.h
 *  Ariella Mann and Ben Rowland
 *  4/21/23
 *
 *  COMP 15 Proj 4
 *
 *  This hold the decleration of the Hash class. This class utilizes 
    a hash function, hash table, and two vectors to store information. 
    The class holds all functions dealing with, storing and getting info 
    in the Hash table which is used to hold every word in the given
    directory. Storing this information in this Hash class is helpful 
    because it allows for faster retrieval. Every decleration of a 
    TheHash holds a hash table and vectors to store lines, words, 
    and paths from directories and files. 
 *
 */

#ifndef THE_HASH_H
#define THE_HASH_H
#include <vector>
#include <string>
#include <functional>
#include <utility>
#include <iostream>
#include <locale>

using namespace std;

class TheHash {
    public:
    TheHash();
    ~TheHash();
    void addWord(string word, int line, int path);
    string getPath(int i);
    string getLine(int i);
    int addLine(string &line);
    int addPath(string &path);
    void printSensitive(string word, ostream &output);
    void printInsensitive(string word, ostream &output);
    

    private:
    string makeLowerCase(string word);
    void resizeTable();
    vector<string> lines;
    vector<string> paths;
    struct hashNode {
        string name;
        int line;
        int path;
        hashNode *nextNode;
    };
    hashNode **hashTable;
    float loadFactor;
    int tableSize;
    int numElements;

};

#endif
