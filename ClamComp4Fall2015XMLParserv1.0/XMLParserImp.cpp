/*
 * File: XMLParserImp.cpp 
 * Author: Cullin Lam cullin_lam@student.uml.edu 
 * created: 2015-09-02
 * last updated: 2015-09-19
 * 
 * 2015-09-19
 *      - Removed fprintf statement to check for <,> brackets 
 * 
 * 2015-09-11 
 *      - Modified XMLElement constructor to output warning if line is missing 
 *      '<' or '>' brackets 
 * 2015-09-08
 *      - Updated documentation to uppercase XML
 *      - Modified XMLParser::read_xml_elements to omit tag attributes 
 * 
 * This file implements all functions declared in XMLParser.h. It contains the 
 * core functionality of the XMLParser and XMLElement classes. 
 */

#include "XMLParser.h"
#include <iostream>
#include <fstream>
#include <cctype>

using namespace std;

void XMLParser::read_XML(const string file_name) {
    // open the file for reading 
    ifstream xml_file;
    xml_file.open(file_name);
    string curr_line;
    int line_num = 1;

    // store line from XML file into curr_line while EOF not reached 
    while (getline(xml_file, curr_line)) {
        // output line number and XML line to stdout 
        cout << line_num << " " << curr_line << endl;
        line_num++;
    }
    cout << endl << endl;
    xml_file.close();
}

void XMLParser::read_XML_elements(const string file_name) {
    //open file for reading 
    ifstream XML_file;
    XML_file.open(file_name);
    string curr_line;
    int line_num = 1;

    // store line from XML file into curr_line while EOF not reached 
    while (getline(XML_file, curr_line)) {
        // instantiate an XMLELement with the line number and line from XML file
        XMLElement tag = XMLElement(line_num, curr_line);
        // check if a valid XMLElement was created 
        if (tag.get_element_name() != "") {
            // insert into vector 
            element_vector.push_back(tag);
        }
        line_num++;
    }
    XML_file.close();
}

void XMLParser::output_elements() {
    for (auto i : element_vector) {
        cout << i.get_line_num() << " " << i.get_element_name() << endl;
    }
}

XMLElement::XMLElement() {
    line_num = -1;
    element_name = "";
}

XMLElement::XMLElement(int line_found, string XML_line) {
    /*
     * Constructor that parses XML_line for elements 
     * 
        args:
     *      line_found(int): line number of the XML file 
     *      XML_line(string): line of text from XML file 
     * return:
     *      XMLElement, if invalid input XML.element_name is set to ""
     */

    // get the index of the closing angle bracket of the element tag 
    size_t endpos = XML_line.find('>');
    // if not found skip line 
    if (endpos == string::npos) {
        line_num = line_found;
        element_name = "";
        return;

    }
    // get the substring up until the endpos where '>' was found 
    string token = XML_line.substr(0, endpos);
    // find beginning position of element tag 
    size_t beginpos = token.find('<');
    // get the text within the angle brackets 
    string element_str = token.substr(beginpos + 1, string::npos);
    // check if there is a white space character 
    size_t space_pos = element_str.find(' ');
    if (space_pos != string::npos) {
        // get text until the whitespace char 
        element_str = element_str.substr(0, space_pos);
    }
    // do not store if tag begins with a punct character i.e. !,?,/
    if (ispunct(element_str[0])) {
        line_num = line_found;
        element_name = "";
        return;

    }
    line_num = line_found;
    element_name = element_str;
}

int XMLElement::get_line_num() {
    return line_num;
}

string XMLElement::get_element_name() {
    return element_name;
}

void XMLElement::set_line_num(int line) {
    line_num = line;
}

void XMLElement::set_element_name(string tag) {
    element_name = tag;
}
