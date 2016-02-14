/* 
 * File:   XMLParser.h
 * Author: Cullin cullin_lam@student.uml.edu 
 *
 * Created on 2015-09-02 3:28 PM
 * Updated on 2015-09-08
 *  -Updated documentation to uppercase XML
 * 
 * This file contains class declarations for XMLParser and XMLElement  
 */

#include <vector>
#include <string>

#ifndef XMLPARSER_H
#define	XMLPARSER_H

using namespace std;

class XMLElement {
    /*
     Represents an XML element 
     */
private:
    // line number where XML element was found 
    int line_num;
    // the name of the XML element 
    string element_name;
public:
    //default constructor 
    XMLElement();
    // constructor with two arguments: line number and line of XML 
    XMLElement(int line_found, string XML_line);
    // return line_num 
    int get_line_num();
    // return element_name 
    string get_element_name();
    // set line_num 
    void set_line_num(int line);
    //set element name 
    void set_element_name(string tag);
};

class XMLParser {
    /*
        Object that provides methods to parse XML files 
     */
private:
    // container to hold XMLElements 
    vector<XMLElement> element_vector;
public:
    // outputs line number and line for each line in the XML file 
    void read_XML(const string file_name);
    // stores XML elements found in the XML file in vector container 
    void read_XML_elements(const string file_name);
    // outputs XML elements in vector container: element_vector 
    void output_elements();
};


#endif	/* XMLPARSER_H */
