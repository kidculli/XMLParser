/*
 * File:   main.cpp
 * Author: Cullin Lam cullin_lam@student.uml.edu
 * Created on 2015-09-02 3:26 PM
 * Last Updated on 2015-10-11
 *
 * 2015-10-11
 *      - Removed test code from main
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
#include "str_manip_funcs.h"
using namespace std;

int main(int argc, char** argv) {
    /**
     This function executes the main program which parses an XML file supplied
     via command line and outputs it's tags with the line number where it was
     found. Command line arg supplied is -song.xml which is found under Resource
     files.

     args:
        @param argc   number of command line args
        @param argv   array of command line args

     return:
        @return 0 on success
     */
    
     //initialize XMLParser instance
     XMLParser my_parser = XMLParser();
    // test file hierarchy
    my_parser.parse_XML(argv[1]);
    cout << "\n\nOutputting root children...\n";
    for (auto i: my_parser.get_root()->get_children())
    {
        cout << "L "<<i->get_line_num() <<" Child: " << i->get_element_name() <<endl;
    }

    my_parser.traverse_element_tree(my_parser.get_root(),0);


    return 0;
}

