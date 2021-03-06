/*
 * File: XMLParser.cpp
 * Author: Cullin Lam cullin_lam@student.uml.edu
 * created: 2015-09-02
 * last updated: 2015-10-13
 * 2015-10-13
 *      - fixed output for first part 
 * 2015-10-12
 *      - Added conditional outputting for traverse_element_tree
 *      - Self closing elements now added to parent element's child vector
 * 2015-10-11
 *      - Added print_stack function
 *      - Modified output with new lines to make more readable
 *      - use trim function to trim curr_line in parse_XML
 *
 * 2015-10-01
 *      - Added new function traverse_element_tree;
 *
 * 2015-09-30
 *      - STARTING_COMMENT & END_COMMENT set str_content now
 *      - defined get_root
 *      - Removed handling of ELEMENT_CONTENT case
 *      - Updated Documentation
 *      - ELEMENT_CLOSING_TAG case of GetXMLData sets curr_element_name
 *      - Added error checking to see if closed element matches top of stack
 *      - Added error checking when opening file
 *
 * 2015-09-27
 *      - Completed GetXMLData function and moved it inside XMLParser
 *      - Uses private member curr_state to determine parser state instead of
 *        being passed in.
 *      - removed start_pos and end_pos parameters to GetXMLData because they are
 *        not needed.
 *      - removed line_num parameter for GetXMLData because it is not needed
 *
 * 2015-09-26
 *      - Moved all XMLElement methods to a new file
 *      - Renamed file to XMLParser.cpp
 *      - Updated XMLParser to allocate memory for Elements dynamically using new
 *      - Updated all tag references to use -> operator
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
 * core functionality of the XMLParser.
 *
 * Notes
 *
 *      - Need to implement pointer to current element
 *      - Check to see if root closed prematurely
 *      - Should create helper function for GetXMLData
 */

#include "XMLParser.h"
#include "XMLElement.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include "str_manip_funcs.h"
#include <iomanip>
// Used for formatted output in traverse_element_tree set width value
#define OUTWIDTH 25
// Used for formatted output in traverse_element_tree set fill char
#define FILLCHAR '-'

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
        XMLElement* tag = new XMLElement(line_num, curr_line);
        // check if a valid XMLElement was created
        if (tag->get_element_name() != "") {
            // insert into vector
            element_vector.push_back(tag);
        }
        line_num++;
    }
    XML_file.close();
}

void XMLParser::parse_XML_elements(const string file_name)
{
    //open file for reading
    ifstream XML_file;
    XML_file.open(file_name);
    string curr_line;
    int line_num = 1;

    // store line from XML file into curr_line while EOF not reached
    while (getline(XML_file, curr_line)) {
        // instantiate an XMLELement with the line number and line from XML file
        XMLElement* tag = new XMLElement(line_num, curr_line);
        // check if a valid XMLElement was created
        if (tag->get_element_name() != "") {
            // insert into vector
            element_vector.push_back(tag);
        }
            // No open tag was found must be another case
        else {

        }
        line_num++;
    }
    XML_file.close();
}

void XMLParser::parse_XML(const string file_name)
{
    //open file for reading
    ifstream XML_file;
    XML_file.open(file_name);
    // check if opening the file was successful
    if ( ( XML_file.rdstate() & std::ifstream::failbit ) != 0 ) {
        // note the single & in the above Boolean statement, not &&
        std::cerr << "Error opening '" << file_name << "'\n" ;
        std::exit(EXIT_FAILURE);
    }
    // current line being parsed
    string curr_line;
    // current line number
    int line_num = 1;

    // store line from XML file into curr_line while EOF not reached
    while (getline(XML_file, curr_line)) {
        // Stores the current element name if found
        string curr_element_name;
        // Stores the current element content if found
        string curr_element_content ="{EMPTY}";
        // temporary pointer to constructed XMLElement
        XMLElement* temp;
        // Remove whitspace from the xml file line
        trim(curr_line);
        // Retrieve line information
        GetXMLData(curr_line,curr_element_name,curr_element_content);
        // string that specifies parser state 
        string ps_str; 
        // output ps and element name and content if applicable 
        cout << right <<"L " << line_num << " " << trim(curr_line) << endl;
        switch(curr_state)
        {
            case UNKNOWN :
                cout << right  << setw(4) <<""<< "UNKNOWN" <<endl ;
                cout << right  << setw(4) <<""<< "content: " << curr_element_content<<endl<<endl;
                break ;
            case STARTING_DOCUMENT : cout << right << "STARTING_DOCUMENT" << endl << endl ; break ;
            case DIRECTIVE :
                cout << right  << setw(4) <<""<< "DIRECTIVE" << endl ;
                cout << right  << setw(4) <<""<< "content: " << curr_element_content<<endl<<endl;
                break ;
            case ELEMENT_OPENING_TAG :
                cout << right  << setw(4) <<""<< "ELEMENT_OPENING_TAG" << endl ;
                cout << right  << setw(4) <<""<< "Element name: " << curr_element_name <<endl;
                // If root has not been set this is the root element
                if (root == NULL)
                {
                    // construct root
                    root = new XMLElement(line_num,curr_line);
                    // add to vector and stack
                    element_vector.push_back(root);
                    unclosed_element_stack.push(root);
                    cout << right << setw(4) <<""<< "Pushed " << root->get_element_name() << " onto element stack" <<endl;
                    print_stack(unclosed_element_stack);
                    cout <<endl;
                }
                else
                {
                    // construct the element
                    temp = new XMLElement(line_num,curr_line);
                    // add new Element as child of previous tag
                    unclosed_element_stack.top()->add_child(temp);
                    // add to vector and stack
                    element_vector.push_back(temp);
                    unclosed_element_stack.push(temp);
                    cout << right << setw(4) <<""<< "Pushed " << temp->get_element_name() << " onto element stack" <<endl;
                    print_stack(unclosed_element_stack);
                    cout <<endl;
                }
                break ;
            case ELEMENT_NAME_AND_CONTENT :
                cout << right << setw(4) <<"" << "ELEMENT_NAME_AND_CONTENT\n" ;
                cout << right << setw(4) <<"" << "Element name: " << curr_element_name<<endl;
                cout << right << setw(4) <<"" << "content: " << curr_element_content<<endl;
                cout << right << setw(4) <<"" << "Stack unchanged\n\n";
                // construct the element
                temp = new XMLElement(line_num,curr_line);
                temp->set_str_content(curr_element_content);
                // add as child to top element
                unclosed_element_stack.top()->add_child(temp);
                // add to vector
                element_vector.push_back(temp);
                break ;
            case ELEMENT_CLOSING_TAG :
            {
                cout << right << setw(4) <<"" << "ELEMENT_CLOSING_TAG\n" ;
                // keep reference to closed element
                temp = unclosed_element_stack.top();
                // If we find a closing tag that doesn't match the last opened
                // tag throw an error and exit program.
                if (temp->get_element_name() != curr_element_name)
                {
                    cerr << right << setw(4) <<"" <<  "Error processing element closing tag: " << curr_element_name\
                    << " cannot find element opening tag."<<endl;
                    std::exit(EXIT_FAILURE);
                }
                cout << right << setw(4) <<"" << "Closed element: " << temp->get_element_name() <<endl;
                // remove closed element from stack
                unclosed_element_stack.pop();
                if (unclosed_element_stack.empty())
                {
                    cout << right << setw(4) <<"" << "Stack is empty"<<endl;
                    break;
                }
                cout << right << setw(4) <<"" << "Top of stack: " << unclosed_element_stack.top()->get_element_name() << endl;
                print_stack(unclosed_element_stack);
                cout <<endl;
                break ;
            }
            case SELF_CLOSING_TAG :
            {
                cout << right << setw(4) <<"" << "SELF_CLOSING_TAG\n" ;
                temp = new XMLElement(line_num,curr_line);
                // remove the "/" from name
                temp->set_element_name(temp->get_element_name().substr(0,string::npos-1));
                cout << right << setw(4) <<"" << "Element name: " << temp->get_element_name() <<endl<<endl;
                // add to vector
                element_vector.push_back(temp);
                //add to parent
                unclosed_element_stack.top()->add_child(temp);
                break ;
            }
            case STARTING_COMMENT :
            {
                cout << right << setw(4) <<"" << "STARTING_COMMENT\n" ;
                cout << right << setw(4) <<"" << "content: " << trim(curr_element_content)<<endl<<endl;
                break ;
            }
            case IN_COMMENT :
            {
                cout << right << setw(4) <<"" << "IN_COMMENT\n" ;
                cout << right << setw(4) <<"" << "content: " << trim(curr_element_content)<<endl<<endl;
                break ;
            }
            case ENDING_COMMENT :
            {
                cout << right << setw(4) <<"" << "ENDING_COMMENT\n" ;
                cout << right << setw(4) <<"" << "content: " << trim(curr_element_content)<<endl<<endl;
                break ;
            }
            case ONE_LINE_COMMENT :
            {
                cout << right << setw(4) <<"" << "ONE_LINE_COMMENT\n" ;
                cout << right << setw(4) <<"" << "content: " << trim(curr_element_content) <<endl<<endl;
                break ;
            }
            case ERROR : cout << right << setw(4) <<"" << "ERROR\n\n" ; break ;

            default : cout << right << setw(4) <<"" << "UNKNOWN\n\n" ; break ;
        }
        line_num++;
    }
    XML_file.close();
}

ParserState XMLParser::GetXMLData(string line,string& element_name,string& str_content)
{
    /**
    * This function is used during debugging to display the parser state.
    * Args:
    *      @param current_state(ParserState): the current parser state
    *      @param line(string): line of the XML file being parsed
     *     @param element_name(string&): name of XMLElement passed by reference
     *     @param str_content(string&): Content of the XMLElement passed by reference
    */

    // Find the first opening and closing brackets in the line
    size_t open_bracket_1 = line.find('<');
    size_t close_bracket_1 = line.find('>');
    // No closing bracket was found, determine the current state
    if(close_bracket_1 == string::npos)
    {
        if (curr_state == STARTING_COMMENT || curr_state == IN_COMMENT)
        {
            str_content =  line;
            curr_state = IN_COMMENT;
            return IN_COMMENT;
        }
        if(line.find("<!--")!= string::npos)
        {
            // set string content to text after <!--
            str_content = line.substr(open_bracket_1 + 4,string::npos);
            curr_state = STARTING_COMMENT;
            return STARTING_COMMENT;
        }
        else
        {
            str_content = line;
            curr_state = UNKNOWN;
            return UNKNOWN;
        }
    }
        // No opening bracket was found and --> was found
    else if(open_bracket_1 == string::npos && line.find("-->")!= string::npos)
    {
        // set string content to text before -->
        str_content = line.substr(0,close_bracket_1 - 3);
        curr_state = ENDING_COMMENT;
        return ENDING_COMMENT;
    }
        // Directive was found <?
    else if(line.find("<?")!=string::npos)
    {
        // set start position to be 2 indices after < position
        size_t start = open_bracket_1 + 2;
        // set end position to be 3 indices before > position
        size_t end = close_bracket_1 - 3;
        // collect content between opening and closing directive brackets
        str_content = line.substr(start,end);
        curr_state = DIRECTIVE;
        return DIRECTIVE;
    }
        // Opening comment was found
    else if(line.find("<!--")!=string::npos)
    {
        // set start position to be 4 indices after < position
        size_t start = open_bracket_1 + 4;
        // set end position to be 6 indices before > position
        size_t end = close_bracket_1 - 6;
        // collect content between opening and closing comment brackets
        str_content = line.substr(start,end);
        curr_state = ONE_LINE_COMMENT;
        return ONE_LINE_COMMENT;
    }
        // Closing tag was found </, checks to see if character after < is '/'
    else if(line.at(open_bracket_1 + 1) == '/')
    {
        element_name = line.substr(open_bracket_1 + 2, close_bracket_1-(open_bracket_1 + 2));
        curr_state = ELEMENT_CLOSING_TAG;
        return ELEMENT_CLOSING_TAG;
    }
        // Final case opening tag was found
    else
    {
        // Use XMLElement constructor to get element_name
        XMLElement element = XMLElement(0,line);
        string name = element.get_element_name();
        if (name == "")
        {
            // This case should have been addressed above i.e. punct char after
            // < return error if this is reached
            curr_state = ERROR;
            return ERROR;
        }
        //check if tag is closed on this line
        size_t end_index = line.find("</" + name);
        if(end_index!=string::npos)
        {
            // Get content between open and closing tags
            str_content = line.substr(close_bracket_1+1,end_index - (close_bracket_1+1));
            element_name = name;
            curr_state = ELEMENT_NAME_AND_CONTENT;
            return ELEMENT_NAME_AND_CONTENT;
        }
            // check if self closing tag
        else if(line.find("/>")!=string::npos)
        {
            str_content = "{EMPTY}";
            //XMLElement constructor leaves '/' at the end of name of self closing tags
            element_name = name.substr(0,string::npos - 1);
            curr_state = SELF_CLOSING_TAG;
            return SELF_CLOSING_TAG;
        }
        // If above cases not reached then an Element was opened
        element_name = name;
        curr_state = ELEMENT_OPENING_TAG;
        return ELEMENT_OPENING_TAG;

    }
    curr_state = ERROR;
    return ERROR;
}
// This function recursively prints out the element stack and returns with original structure
// source - http://stackoverflow.com/questions/4523178/how-to-print-out-all-elements-in-a-stdstack-or-stdqueue-conveniently
void XMLParser::print_stack(stack<XMLElement*> &s)
{
    if(s.empty())
    {
        cout << endl;
        return;
    }
    XMLElement* x= s.top();
    s.pop();
    print_stack(s);
    s.push(x);
    cout<< "Stack contains: " << x->get_element_name() <<endl;
}
XMLElement* XMLParser::get_root() {
    return root;
}

void XMLParser::output_elements() {
    for (auto i : element_vector) {
        cout << i->get_line_num() << " " << i->get_element_name() << endl;
    }
}

void XMLParser::traverse_element_tree(XMLElement* curr, unsigned level)
{
    // temp vector to hold child vector of current element
    vector<XMLElement*> child_vec = curr->get_children();
    // output element details
    cout <<endl<< right << setfill(FILLCHAR)<<setw(OUTWIDTH) << (level ? "Child tag name : " : "Root tag name : ");
    cout << left << curr->get_element_name() <<endl;
    cout << right << setfill(FILLCHAR) <<setw(OUTWIDTH) << (level ? "Child line # : " : "Root line # : ") << left << curr->get_line_num() << endl;
    cout << right << setfill(FILLCHAR) << setw(OUTWIDTH) <<  (level ? "Child lvl : " : "Root lvl : ") << left << level << endl;
    cout << right << setfill(FILLCHAR) << setw(OUTWIDTH) << (level ? "Child content: " : "Root content: ")<< left << curr->get_str_content() << endl;
    cout << right << setfill(FILLCHAR) << setw(OUTWIDTH) << "Direct children : " << left << child_vec.size() << endl;
    cout << right << setfill(FILLCHAR) << setw(OUTWIDTH) << "Number of attributes: " << left << curr -> getAttributes().size() << endl;
    if (!curr->getAttributes().empty()) {
        cout <<right<<setfill(FILLCHAR)<<setw(OUTWIDTH) << "Attributes: " << endl;
        for (const auto &p : curr->getAttributes()) {
            cout << right << setfill(FILLCHAR) << setw(OUTWIDTH + 10) << "Attribute:" << left << setfill(FILLCHAR) << setw(14)<< p.first << " Value:" << p.second << endl;
        }
    }

    if(child_vec.empty())
    {
        return;
    }
    else
    {
        for (auto i: child_vec)
        {
            traverse_element_tree(i, level + 1);
        }

    }
}

/**
 * This function is used during debugging to display the parser state.
 * @param ps the parser state
 */
void XMLParser::ShowState(ParserState state) {
    cout << "ParserState = " ;
    switch (state) {
        case UNKNOWN : cout << "UNKNOWN" ; break ;
        case STARTING_DOCUMENT : cout << "STARTING_DOCUMENT" ; break ;
        case DIRECTIVE : cout << "DIRECTIVE" ; break ;
        case ELEMENT_OPENING_TAG : cout << "ELEMENT_OPENING_TAG" ; break ;
        case ELEMENT_CONTENT : cout << "ELEMENT_CONTENT" ; break ;
        case ELEMENT_NAME_AND_CONTENT : cout << "ELEMENT_NAME_AND_CONTENT" ; break ;
        case ELEMENT_CLOSING_TAG : cout << "ELEMENT_CLOSING_TAG" ; break ;
        case SELF_CLOSING_TAG : cout << "SELF_CLOSING_TAG" ; break ;
        case STARTING_COMMENT : cout << "STARTING_COMMENT" ; break ;
        case IN_COMMENT : cout << "IN_COMMENT" ; break ;
        case ENDING_COMMENT : cout << "ENDING_COMMENT" ; break ;
        case ONE_LINE_COMMENT : cout << "ONE_LINE_COMMENT" ; break ;
        case ERROR : cout << "ERROR" ; break ;
        default : cout << "UNKNOWN" ; break ;
    }
    cout << endl ;
}




