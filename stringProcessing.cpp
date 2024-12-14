/*
 *  stringProcessing.cpp
 *  Ariella Mann {amann04} and Ben Rowland {browla01}
 *  4/17/23
 *
 *  CS 15 - Project 4 - gerp
 *
 * File that holds a function that trips the ends of a string 
   of trailing non alphanumeric characters.  
 */

#include <cassert>
#include <iostream>
#include "stringProcessing.h"

using namespace std;

//testing main
// int main () {
//     std::string test1 = "#%@&*^$Hello!!!!";
//     std::string return1 = stripNonAlphaNum(test1);
//     std::cerr << return1 << endl;
//     assert(return1 == "Hello");

//     std::string test2 = "##54Hi#78&&";
//     std::string return2 = stripNonAlphaNum(test2);
//     std::cerr << return2 << endl;
//     assert(return2 == "54Hi#78");

//     std::string test3 = "423894723849";
//     std::string return3 = stripNonAlphaNum(test3);
//     std::cerr << return3 << endl;
//     assert(return3 == test3);

//     std::string test4 = "$#$%*^%*&$%@%@#%@";
//     std::string return4 = stripNonAlphaNum(test4);
//     std::cerr << return4 << endl;
//     assert(return4 == "");

//     std::string test5 = "";
//     std::string return5 = stripNonAlphaNum(test5);
//     std::cerr << return5 << endl;
//     assert(return5 == "");
//     return 0;
// }

/*
 * name:      stripNonAlphaNum
 * purpose:   gets rid of trailing non letter or number characters
 * arguments: original string to strip
 * returns:   stripped version of the string: only alphanumerical chars
 */
std::string stripNonAlphaNum(std::string input) {
    int start = 0;
    int end = 0;
    int length = input.length();
    int i = 0;
    bool notDone = true;
    while (notDone and i < length) {
        char temp = input[i];
        if ((temp >= 97 and temp <= 122) or
            (temp >= 65 and temp <= 90) or
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
        if ((temp >= 97 and temp <= 122) or
            (temp >= 65 and temp <= 90) or
            (temp >= 48 and temp <= 57)) {
            end = i;
            notDone = false;
        }
        i--;
    }
    return input.substr(start, end - start + 1);
}
