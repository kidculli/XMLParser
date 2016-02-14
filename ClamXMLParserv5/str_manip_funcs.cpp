/*File: str_manip_funcs.cpp
* Author: Cullin Lam cullin_lam@student.uml.edu
* created: 2015-10-11
* last updated: 2015-10-12
*
 * 2015-10-12
 *      - trim function now str value is passed by value instead of reference to avoid lvalue error
 * 2015-10-11
 *      - added strip, split, trim
 *
 * This file implements all functions declared in str_manip_funcs.h.
 * These functions perform string manipulations that may be useful to the XMLParser
*/

#include "str_manip_funcs.h"
#include <sstream>

/**
 * Trim leading and trailing white space (spaces and tabs) from the
 *    string passed as an argument and return the trimmed string.
 * @param str string to trim
 * @return trimmed string
 * source: Jesse Heines
 */
string trim(string str) {
    // cout << "Trimming |" << str << "|" << endl ;  // for debugging
    while ( str[0] == ' ' || str[0] == '\t' ) {
        str.erase( str.begin() ) ;  // must use an iterator
    }
    while ( str[str.length()-1] == ' ' || str[str.length()-1] == '\t' ) {
        str.erase( str.end()-1 ) ;  // must use an iterator
    }
    return str ;
}

// The following functions allow for a string to be split by a delimiter character, the results are returned in a vector
// source http://stackoverflow.com/questions/236129/split-a-string-in-c
vector<string> &split(const string &s, char delim, vector<string> &elems) {
    stringstream ss(s);
    string item;
    while (getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}


vector<string> split(const string &s, char delim) {
    vector<string> elems;
    split(s, delim, elems);
    return elems;
}
// This function removes all occurrences of the specified character from the inputted string
string strip( string& str, char z)
{
    while (str.find(z,0) != string::npos)
    {
        str.erase(str.begin() + str.find(z,0));
    }

    return str;
}
