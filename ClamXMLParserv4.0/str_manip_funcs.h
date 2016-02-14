/*File: str_manip_funcs.cpp
* Author: Cullin Lam cullin_lam@student.uml.edu
* created: 2015-10-11
* last updated: 2015-10-12
 *
 * 2015-10-12
 *      - trim pass by value instead of reference
 *
 *  2015-10-11
 *      - added strip, split, trim
*
 * This file declares all functions that will be implemented in str_manip_funcs.cpp.
 * These functions perform string manipulations that may be useful to the XMLParser
*/
#include <string>
#include <vector>
#ifndef STR_MANIP_FUNCS_H
#define STR_MANIP_FUNCS_H
using namespace std;
/**
 * @file str_manip_funcs.h This file declares all functions that will be implemented in str_manip_funcs.cpp. These functions perform string manipulations that may be useful to the XMLParser
 * @author Cullin Lam  
 */
/**
 * Trim leading and trailing white space (spaces and tabs) from the
 *    string passed as an argument and return the trimmed string.
 * @param str string to trim
 * @return trimmed string
 */
string trim(string str);
/**
 * Strips string of specified char
 * @param str string that will be stripped 
 * @param z char that will be removed from string 
 * @return stripped string 
 */ 
string strip( string& str, char z);
// The following functions allow for a string to be split by a delimiter character, the results are returned in a vector
/**
 * Returns a vector of strings that have been split by a delimiter character 
 * helper function for overloaded version 
 * source http://stackoverflow.com/questions/236129/split-a-string-in-c
 * @param s string to be split
 * @param delim delimitting char 
 * @param elems vector to store split strings 
 * @return vector of strings split by delimiter 
 */ 
vector<string> &split(const string &s, char delim, vector<string> &elems);
/**
 * Returns a vector of strings that have been split by a delimiter character 
 * helper function for overloaded version 
 * source http://stackoverflow.com/questions/236129/split-a-string-in-c
 * @param s string to be split
 * @param delim delimitting char 
 * @return vector of strings split by delimiter 
 */ 
vector<string> split(const string &s, char delim);
#endif //STR_MANIP_FUNCS_H
