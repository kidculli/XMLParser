/*
 * File:   XMLElement.cpp
 * Author: Cullin Lam cullin_lam@student.uml.edu
 *
 * Created on September 26, 2015, 10:34 PM
 * Updated:
 *      2015-10-12
 *          - added call to trim when setting str_content
 *          - fixed extract_attr logic
 *      2015-10-11
 *          - Added extract_attr function
 *      2015-09-26
 *          - added str_content and children members
 * This File contains method implementations for XMLElement
 */

#include "XMLElement.h"
#include <iostream>
#include "str_manip_funcs.h"

using namespace std;

XMLElement::XMLElement() {
    line_num = -1;
    element_name = "foo";
    // if tag contains text in between its opening and closing tags
    string str_content;
    // vector of children of the XMLElement
    vector<XMLElement*> children;
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
        //get text after whitespace char
        string attribute_str = element_str.substr(space_pos,string::npos);
        // set attribute map
        attributes = extract_attr(attribute_str);
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
void XMLElement::set_str_content(string content) {
    str_content = trim(content);
}
void XMLElement::add_child(XMLElement* child) {
    children.push_back(child);
}
vector<XMLElement*> XMLElement::get_children()
{
    return children;
}
string XMLElement::get_str_content() {
    return str_content;
}
map<string,string> XMLElement::extract_attr(string line) {
    vector<string> attr_vec;
    // split xml line by =
    vector<string> token_vec = split(line,'=');
    // iterate through tokens
    for (int i = 0;i < token_vec.size();i++)
    {
        // trim whitespace
        string token = trim(token_vec[i]);
        // first and last index will contain just a key or value token respectively so just add them to the attr_vector
        if(i==0 || i== token_vec.size() - 1)
        {
            attr_vec.push_back(token);
        }
        // string will contain both a key and value, need to split them and add to attr vec
        else {
            // find index of closing quote
            size_t close_quote_index = token.find('"', 1);
            // push value into vector
            attr_vec.push_back(token.substr(1, close_quote_index - 1));
            // if there are more than 2 elements get the next key
            if (token_vec.size() > 2) {
                // substring the rest of the string after closing quote
                string temp = token.substr(close_quote_index + 1, string::npos);
                attr_vec.push_back(temp);
            }
        }
    }
    // initialize return map
    map<string,string> ret_map;
    // iterate through attribute vector, keys are odd indices while values are even
    for (int i = 0;i < attr_vec.size();i+=2)
    {
        //debug
        //cout << attr_vec[i] <<endl;
        // set key val pair
        ret_map[trim(attr_vec[i])] = trim(strip(attr_vec[i+1],'"'));
    }

    return ret_map;

}

