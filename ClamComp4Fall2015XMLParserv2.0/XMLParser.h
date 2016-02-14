/* 
 * File:   XMLParser.h
 * Author: Cullin cullin_lam@student.uml.edu 
 *
 * Created on 2015-09-02 3:28 PM
 * Last Updated on 2015-09-26 :
 *      2015-09-26 
 *          - added get_root function 
 *      2015-09-26  
 *          - Moved XMLElement class to new file XMLElement.h    
 *          - XMLParser member element_vector now stores Element* 
 *          - Added ParserState enum type source ~ Jesse Heines 
 *          - Added ShowState function to XMLParser source ~ Jesse Heines 
 *          - Added global var curr_state which stores current Parser State 
 *          - Added root member to XMLParser 
 *          - Added str_content and children members to XMLElement 
 * 
 *      2015-09-08
 *          -Updated documentation to uppercase XML
 * 
 * This file contains class declarations for XMLParser  
 */

#include <vector>
#include <stack> 
#include <string>
#include "XMLElement.h"

#ifndef XMLPARSER_H
#define	XMLPARSER_H

using namespace std;
// enum type that describes various parser states 
typedef enum ParserState {UNKNOWN, STARTING_DOCUMENT, DIRECTIVE,ELEMENT_NAME_AND_CONTENT, 
    ELEMENT_OPENING_TAG, ELEMENT_CONTENT,ELEMENT_CLOSING_TAG, SELF_CLOSING_TAG,
    STARTING_COMMENT, IN_COMMENT, ENDING_COMMENT, ONE_LINE_COMMENT,
    ERROR} ParserState;

class XMLParser {
    /*
        Object that provides methods to parse XML files 
     */
private:
    //Current parser state
    ParserState curr_state = STARTING_DOCUMENT; 
    // Pointer to Root Element 
    XMLElement* root = NULL; 
    // container to hold XMLElements 
    vector<XMLElement*> element_vector;
    // Unclosed Elements stack implemented with a vector  
    stack<XMLElement*> unclosed_element_stack; 
    
public:
    // outputs line number and line for each line in the XML file 
    void read_XML(const string file_name);
    // stores XML elements found in the XML file in vector container 
    void read_XML_elements(const string file_name);
    // outputs XML elements in vector container: element_vector 
    void output_elements();
    // This function is used during debugging to display the parser state source ~ Jesse Heines 
    void ShowState(ParserState state); 
    // Parses the file for XML Elements and checks for well formedness 
    void parse_XML(const string file_name); 
    // Deprecated in this version 
    void parse_XML_elements(const string file_name); 
    // Return reference to root element 
    XMLElement* get_root(); 
    //Get XMLData and return Parser State 
ParserState GetXMLData(string line,string& element_name,string& str_content)                       
;};


#endif	/* XMLPARSER_H */
