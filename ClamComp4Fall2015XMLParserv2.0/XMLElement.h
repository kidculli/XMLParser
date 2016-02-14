/* 
 * File:   XMLElement.h
 * Author: Cullin Lam cullin_lam@student.uml.edu 
 *
 * Created on September 26, 2015, 10:34 PM
 * 
 * This File contains class declaration for XMLElement 
 */
#include <string>
#include <vector>
#ifndef XMLELEMENT_H
#define	XMLELEMENT_H
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
    /** the textual content of the element */
    string str_content;
    /** vector of children */
    vector<XMLElement*> children ;
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
    //setter for str_content 
    void set_str_content(string content); 
    // add child element to children vector;  
    void add_child(XMLElement* child);
    // return str_content 
    string get_str_content();
    // return children of the element 
    vector<XMLElement*> get_children();  
    
};

#endif	/* XMLELEMENT_H */

