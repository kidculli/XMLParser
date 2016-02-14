/*
 * File:   XMLElement.h
 * Author: Cullin Lam cullin_lam@student.uml.edu
 *
 * Created on September 26, 2015, 10:34 PM
 * Last Updated on 10-12-15
 *    10-12-15
 *      - Added javadoc comments 
 *    10-11-15 
 *      - Added extract_attr function
 *      - added map attributes
 * This File contains class declaration for XMLElement
 */

#ifndef XMLELEMENT_H
#define XMLELEMENT_H

#include <string>
#include <vector>
#include <map>

using namespace std;
class XMLElement {
    /**
      Object that stores information about an XML element
     * @author Cullin Lam 
     * @version 4.0
     */
private:
    /** line number where XML element was found*/ 
    int line_num;
    /**the name of the XML element*/
    string element_name;
    /**the textual content of the element */
    string str_content = "{EMPTY}";
    /**vector of children */
    vector<XMLElement*> children;
    /**dictionary for element attributes*/
    map<string,string> attributes;
    /** Method that extracts attributes from an xml string.
     * @param line      line of an xml file 
     * @return          returns an STL Map<string,string> class
     */
    map<string,string> extract_attr(string line);
public:
    /**default constructor*/
    XMLElement();
    /**constructor with two arguments: line number and line of XML. Will initialize 
     * properties: line_num, element_name, and attributes.
     *
     * @param line_found    line number where element is found 
     * @param XML_line      line of text from XML_file
     * @return  XMLElement object
     */
    XMLElement(int line_found, string XML_line);
    /**
     * getter function for line_num
     * @return line_number where XMLElement was found 
     */
    int get_line_num();
    /**
     * getter function for element_name
     * @return name of the XML element 
     */ 
    string get_element_name();
    /**
     * sets line_num
     * @param line_num  line number of XML element.  
     */ 
    void set_line_num(int line);
    /**
     * sets element name
     * @param tag  name of the XML element 
     */ 
    void set_element_name(string tag);
    /**
     * setter for str_content
     * @param content content of XML element   
     */ 
    void set_str_content(string content);
    /**
     * adds child element to children vector
     * @param child pointer to an XMLElement object 
     */ 
    void add_child(XMLElement* child);
    /**
     * returns str_content
     * @return content of XML element 
     */ 
    string get_str_content();
    /**
     * return children of the element
     * @return vector of XMLElement pointers 
     */
    vector<XMLElement*> get_children();
    /**
     * Getter function for attributes
     * @return map object that holds attribute,value pairs of the Xml element.  
     */  
    const map<string, string> &getAttributes() const {
        return attributes;
    }

};

#endif //XMLELEMENT_H


