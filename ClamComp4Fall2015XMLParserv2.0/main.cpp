/* 
 * File:   main.cpp
 * Author: Cullin Lam cullin_lam@student.uml.edu 
 * Created on 2015-09-02 3:26 PM
 * Last Updated on 2015-09-30  
 * 
 * 2015-09-30 
 *      - Outputs root children 
 * 2015-09-08
 *      -Updated documentation uppercased XML (2015-09-08)
 * 
 * 
 * Main Program that creates an XMLParser instance and processes an XML file 
 * supplied via the command line
 */

#include "XMLParser.h"
#include <iostream>
using namespace std;

int main(int argc, char** argv) {
    /*
     This function executes the main program which parses an XML file supplied 
     via command line and outputs it's tags with the line number where it was 
     found. Command line arg supplied is -song.xml which is found under Resource 
     files. 
        
     args:
        argc(int): number of command line args 
        argv(char**): array of command line args  
     
     return: 
        0 on success
     */

//    // initialize XMLParser instance 
    XMLParser my_parser = XMLParser();
    my_parser.parse_XML(argv[1]); 
    cout << "\n\nOutputting root children...\n"; 
    for (auto i: my_parser.get_root()->get_children())
    {
        cout << "L "<<i->get_line_num() <<" Child: " << i->get_element_name() <<endl; 
    }
//    // output the XML file with line number 
//    my_parser.read_XML(argv[1]);
//    // process XML elements  
//    my_parser.read_XML_elements(argv[1]);
//    // output to stdout found elements 
//    my_parser.output_elements();
//
//    XMLElement my = XMLElement(2, "<alfhafa/>");
//    cout<<my.get_element_name()<<endl; 
//    
//      XMLElement test = XMLElement(); 
//      my_parser.unclosed_element_stack.push_back(&test); 
//      my_parser.check_closed("</foo>"); 
//    string name = "FOO"; 
//    string content = "LALALAL"; 
//    int endpos = 0 ; 
//    //cout<< "START STATE: "<<start<<endl; 
//    ParserState curr = my_parser.GetXMLData("<SWAG>",name,content); 
//    //cout << curr << endl; 
//    my_parser.ShowState(curr); 
//    cout << "Content: " << content<<endl; 

    return 0;
}

