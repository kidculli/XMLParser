/*
 * File:   XMLParser.h
 * Author: Cullin cullin_lam@student.uml.edu
 * 
 * Created on 2015-09-02 3:28 PM
 * Last Updated on 2015-10-25 :
 *      2015-10-25
 *          - added declaration of method write_json
 *          - changed parse_xml to return int value 
 *      2015-10-24
 *          - added declaraton of method to_json
 *      2015-10-12
 *          - added javadoc comments 
 *      2015-10-11
 *          - added print_stack function
 *          - updated traverse_element_tree definition and declaration
 *      2015-10-01
 *          - added traverse_element_tree
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

#ifndef XMLPARSER_H
#define XMLPARSER_H
#include <vector>
#include <stack>
#include <string>
#include <map>
#include "XMLElement.h"
#include <fstream>

using namespace std;
/**enum type that describes various parser states*/
typedef enum ParserState {UNKNOWN, STARTING_DOCUMENT, DIRECTIVE,ELEMENT_NAME_AND_CONTENT,
    ELEMENT_OPENING_TAG, ELEMENT_CONTENT,ELEMENT_CLOSING_TAG, SELF_CLOSING_TAG,
    STARTING_COMMENT, IN_COMMENT, ENDING_COMMENT, ONE_LINE_COMMENT,
    ERROR} ParserState;
/**
 Object that provides methods to parse XML files
 * @author Cullin Lam 
 * @version 5.0 
 */
class XMLParser {

private:
    /**Current parser state*/
    ParserState curr_state = STARTING_DOCUMENT;
    /**Pointer to Root Element*/
    XMLElement* root = NULL;
    /**container to hold all found XMLElements*/ 
    vector<XMLElement*> element_vector;
    /**Unclosed Elements stack*/
    stack<XMLElement*> unclosed_element_stack;
    /**
     * outputs stack contents leaving contents in place 
     * source - http://stackoverflow.com/questions/4523178/how-to-print-out-all-elements-in-a-stdstack-or-stdqueue-conveniently
     * @param s a stack of XMLElement pointers, passed by reference 
     */
    void print_stack(stack<XMLElement*> &s);
    /**
     * Recursively travels to each node in element tree and outputs data to a json file
     * @param out file stream object for output 
     * @param curr pointer to current XMLElement in the tree 
     * @param lvl current tree depth  
     */
    void write_json(ofstream& out,XMLElement* curr, unsigned level);


public:
    /**
     * outputs line number and line for each line in the XML file
     * @param file_name path of XML file to be parsed 
     */
    void read_XML(const string file_name);
    /**
     * stores XML elements found in the XML file in vector container
     * @param file_name path of XML file to be parsed 
     */
    void read_XML_elements(const string file_name);
    /**
     * outputs XML elements in vector container: element_vector
     */
    void output_elements();
    /**
     * This function is used during debugging to display the parser state source - Jesse Heines
     * @param state state of the parser 
     */
    void ShowState(ParserState state);
    /**
     * Parses the file for XML Elements and checks for well-formedness also
     * builds a tree of XML Elements and outputs their data 
     * @param file_name path of XML file to be parsed 
     * @return integer indicating either EXIT_SUCCESS or EXIT_FAILURE
     */
    int parse_XML(const string file_name);
    /**
     * Finds XML elements in the xml document 
     * Deprecated in this version
     * @param file_name path of XML file to be parsed 
     * @return EXIT_SUCCESS or EXIT_FAILURE
     */
    void parse_XML_elements(const string file_name);
    /**
     * Recursively travels to each element in the tree and outputs its information and tree level
     * Helper function for parse_XML_elements
     * @param curr pointer to current XMLElement 
     * @param level current tree level depth 
     */
    void traverse_element_tree(XMLElement* curr, unsigned level);
    /**
     * Converts an  xml file into a new json file 
     * @param in_file_name path of the xml file to be converted 
     * @param out_file_name path of the json file to be created 
     * @return EXIT_SUCCESS or EXIT_FAILURE
     */
    int to_json(const string in_file_name, const string out_file_name); 
    /**
     * returns root element
     * @return pointer to root element 
     */
    
    XMLElement* get_root();
    /**
     * Gets XML data and returns and sets Parser State
     * @param line line of xml file text 
     * @param element_name string that will be assigned XML element name 
     * @param str_content string that will be assigned content of XML element 
     */
    ParserState GetXMLData(string line,string& element_name,string& str_content);
};

#endif //XMLPARSER_H
