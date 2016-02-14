/*
 * File: XMLParser.cpp 
 * Author: Cullin Lam cullin_lam@student.uml.edu 
 * created: 2015-09-02
 * last updated: 2015-09-30
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
        // Retrieve line information 
        GetXMLData(curr_line,curr_element_name,curr_element_content); 
        cout << "L " << line_num << " "; 
        switch(curr_state)
        {
            case UNKNOWN : 
                cout << "UNKNOWN\n" ; 
                cout << "content: " << curr_element_content<<endl; 
                break ;
            case STARTING_DOCUMENT : cout << "STARTING_DOCUMENT\n" ; break ;
            case DIRECTIVE :
                cout << "DIRECTIVE\n" ; 
                cout << "content: " << curr_element_content<<endl; 
                break ;
            case ELEMENT_OPENING_TAG : 
                cout << "ELEMENT_OPENING_TAG\n" ; 
                cout << "Element name: " << curr_element_name <<endl; 
                // If root has not been set this is the root element 
                if (root == NULL)
                {
                    // construct root
                    root = new XMLElement(line_num,curr_line); 
                    // add to vector and stack 
                    element_vector.push_back(root); 
                    unclosed_element_stack.push(root); 
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
                }
                break ;
            case ELEMENT_NAME_AND_CONTENT : 
                cout << "ELEMENT_NAME_AND_CONTENT\n" ; 
                cout << "Element name: " << curr_element_name<<endl;
                cout << "content: " << curr_element_content<<endl; 
                // construct the element 
                temp = new XMLElement(line_num,curr_line); 
                temp->set_str_content(curr_element_content); 
                // add to vector
                element_vector.push_back(temp); 
                break ;
            case ELEMENT_CLOSING_TAG : 
            {
                cout << "ELEMENT_CLOSING_TAG\n" ; 
                // keep reference to closed element 
                temp = unclosed_element_stack.top(); 
                // If we find a closing tag that doesn't match the last opened
                // tag throw an error and exit program. 
                if (temp->get_element_name() != curr_element_name)
                {
                    cerr << "Error processing element closing tag: " << curr_element_name\
                    << " cannot find element opening tag."<<endl; 
                    std::exit(EXIT_FAILURE); 
                }
                //cout << "curr element : " << curr_element_name <<endl; 
                cout << "Closed element: " << temp->get_element_name() <<endl; 
                // remove closed element from stack 
                unclosed_element_stack.pop();
                break ;
            }
            case SELF_CLOSING_TAG : 
            {
                cout << "SELF_CLOSING_TAG\n" ; 
                temp = new XMLElement(line_num,curr_line);
                // remove the "/" from name 
                temp->set_element_name(temp->get_element_name().substr(0,string::npos-1));
                cout << "Element name: " << temp->get_element_name() <<endl; 
                // add to vector
                element_vector.push_back(temp);
                break ;
            }
            case STARTING_COMMENT : 
            {
                cout << "STARTING_COMMENT\n" ; 
                cout << "content: " << curr_element_content<<endl; 
                break ;
            }
            case IN_COMMENT :
            {
                cout << "IN_COMMENT\n" ; 
                cout << "content: " << curr_element_content<<endl; 
                break ;    
            }
            case ENDING_COMMENT : 
            {
                cout << "ENDING_COMMENT\n" ;
                cout << "content: " << curr_element_content<<endl; 
                break ;
            }
            case ONE_LINE_COMMENT :
            {
                cout << "ONE_LINE_COMMENT\n" ;
                cout << "content: " << curr_element_content <<endl; 
                break ;
            }
            case ERROR : cout << "ERROR\n" ; break ;

            default : cout << "UNKNOWN\n" ; break ;
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

XMLElement* XMLParser::get_root() {
    return root; 
}

void XMLParser::output_elements() {
    for (auto i : element_vector) {
        cout << i->get_line_num() << " " << i->get_element_name() << endl;
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

