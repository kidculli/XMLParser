/*!\mainpage DomBuilder v1
 *\section Features
 * Extra commands: 
 * - add element parent_name element_name element_text(optional)
 * - add root root_name
 * - remove root
 * - remove child element_name
 * - remove attribute element_name attribute_name
 * - print alpha(optional)
 * @file main.cpp
 * @author Cullin Lam, clam@cs.uml.edu
 *
 * Created on December 7, 2015, 10:23 AM
 * 
 * This file contains the main function that process user commands and  
 * translates commands to DomBuilder calls 
 * 
 * starter code provided by Jesse Heines 
 * 
 * 
 */

#include <iostream>  // for cout and friends
#include <sstream>   // for string streams
#include <string>    // for the STL string class
#include <regex>     // for regular expressions
#include <cstdlib>
#include "dynamic_dom.h"


using namespace std;
/**
 * global DomBuilder object
 */
DomBuilder my;

// forward references
void ParseCommandString( string strUserEntry ) ;
void ProcessAddCommand( string strUserEntry ) ;
void ProcessAddRootCommand( string strUserEntry);
void ProcessAddElementCommand( string strUserEntry ) ;
void ProcessAddAttributeCommand( string strUserEntry ) ;
void ProcessPrintCommand( string strUserEntry ) ;
void ProcessRemoveCommand( string strUserEntry);
void ProcessRemoveChildCommand(string strUserEntry);
void ProcessRemoveAttrCommand(string strUserEntry);



/**
 * The standard C++ main function.
 * @param argc number of command line arguments
 * @param argv array of command line arguments
 * @return 
 */
int main(int argc, char** argv) {
  
  // display program title
  cout << "=============================" << endl ;
  cout << "       DOMBuilder v1         " << endl ;
  cout << "=============================" << endl ;
    
  // string entered by the user in response to the command prompt
  string strUserEntry = "" ;
  
//  // prompt the user to enter a command string
//  // version 1 without using a regular expression
//  while ( ! jmhUtilities::caseInsCompare( jmhUtilities::trim( strUserEntry ), "quit" ) ) {
//    cout << "\nYour command: " ;
//    getline( cin, strUserEntry ) ;
//  }
  
  // prompt the user to enter a command string
  // version 2 using a regular expression
  regex reQuit( "\\s*quit\\s*", regex::icase ) ;
  while( ! regex_match( strUserEntry, reQuit ) ) {
    cout << "\nYour command: " ;
    getline( cin, strUserEntry ) ;
    
    // if the user didn't enter 'quit', go parse the command string
    if ( ! regex_match( strUserEntry, reQuit ) ) {
      ParseCommandString( strUserEntry ) ;
    }
  }

  return EXIT_SUCCESS ;
}


/**
 * Check for a valid basic command.
 * @param strUserEntry command string entered by the user
 */
void ParseCommandString( string strUserEntry ) {
  // regular expressions for basic commands
  regex reBasicAddCommand( "\\s*add.*", regex::icase ) ;
  regex reBasicPrintCommand( "\\s*print.*", regex::icase ) ;
  regex reBasicHelpCommand( "\\s*help.*", regex::icase ) ;
  regex reBasicRemoveCommand( "\\s*remove.*", regex::icase ) ;

  // test for each basic command in turn
  if ( regex_match( strUserEntry, reBasicAddCommand ) ) {
    ProcessAddCommand( strUserEntry ) ;
  } else if ( regex_match( strUserEntry, reBasicPrintCommand ) ) {
    ProcessPrintCommand( strUserEntry ) ;
  }
    else if(regex_match( strUserEntry, reBasicRemoveCommand ))
  {
    ProcessRemoveCommand(strUserEntry);
  }
  else if ( regex_match( strUserEntry, reBasicHelpCommand ) ) {
    cout << "  Commands are:" << endl ;
    cout << "    add element parent_name element_name element_text(optional)" << endl ;
    cout << "    add attribute parent_name attribute_name attribute_value" << endl ;
    cout << "    add root root_name"<<endl;
    cout << "    remove root"<<endl;
    cout << "    remove child element_name"<<endl;
    cout << "    remove attribute element_name attribute_name"<<endl;
    cout << "    print alpha(optional)" << endl ;
    cout << "    help (this command)" << endl ;
    cout << "    quit" << endl ;
  } else {
    cout << "  Invalid command.  Acceptable commands are 'add', 'print', 'help', and 'quit'." << endl ;
  }
}


/**
 * Handle an add command entered by the user
 * @param strUserEntry command string entered by the user
 */
void ProcessAddCommand( string strUserEntry ) {
  // regular expressions for the second parameter in the add command
  regex reAddElementCommand( "\\s*add\\s+element.*", regex::icase ) ;
  regex reAddAttributeCommand( "\\s*add\\s+attribute.*", regex::icase ) ;
  regex reAddRootCommand( "\\s*add\\s+root.*", regex::icase ) ;
  // test for each possible second parameter in turn
  if ( regex_match( strUserEntry, reAddElementCommand ) ) {
    ProcessAddElementCommand( strUserEntry ) ;
  } else if ( regex_match( strUserEntry, reAddAttributeCommand ) ) {
    ProcessAddAttributeCommand(strUserEntry);
  }
    else if ( regex_match( strUserEntry, reAddRootCommand ) ) {
      ProcessAddRootCommand( strUserEntry ) ;
  } else {
    cout << "  Invalid add command: 2nd parameter must be 'element' or 'attribute' or 'root'." << endl ;
  }
}
/**
 * Handle an remove command entered by the user
 * @param strUserEntry command string entered by the user
 */
void ProcessRemoveCommand( string strUserEntry)
{
  // regular expressions for the second parameter in the remove command
  regex reRemoveChildCommand( "\\s*remove\\s+child.*", regex::icase ) ;
  regex reRemoveRootCommand( "\\s*remove\\s+root.*", regex::icase ) ;
  regex reRemoveAttributeCommand("\\s*remove\\s+attribute.*", regex::icase);
  if ( regex_match( strUserEntry, reRemoveChildCommand ) ) {
    ProcessRemoveChildCommand(strUserEntry);
  }
    else if(regex_match( strUserEntry, reRemoveRootCommand )) {
    my.remove_root();
  }
    else if (regex_match( strUserEntry, reRemoveAttributeCommand ))
  {
    ProcessRemoveAttrCommand(strUserEntry);
  }
    else
    {
      cout<<"  Invalid remove command: 2nd parameter must be 'child' or 'attribute' or 'root'." << endl ;
    }
}
/**
 * Handle an remove child command entered by the user
 * @param strUserEntry command string entered by the user
 */
void ProcessRemoveChildCommand(string strUserEntry)
{
  // the what variable is actually an array that will be populated by the regex_match function
  //    when matched groups are found
  cmatch what;
  // what[0] contains the entire matched string
  // what[1] contains the first matched group
  // what[2] contains the second matched group
  // what[3] etc.

  // regular expression to pick out the name of the child to remove
  regex reRemoveChildCmd( "^\\s*remove\\s*child\\s(\\w+)(.*)$", regex::icase ) ;

  // note that the following variant of the regex_match command requires a C string, not an STL string
  if ( regex_match( strUserEntry.c_str(), what, reRemoveChildCmd ) ) {
    cout << "  You have specified that you want to remove an element named '" << what[1] <<"'"<<endl;
    my.remove_child(what[1].str());
  }
  else {
    cout << "  Invalid 'remove child' command." << endl ;
    cout << "    'remove child' must be followed by one more parameter:" << endl ;
    cout << "      (1) the name of the element to be removed" << endl ;

  }
}
/**
 *Handle an add root command entered by user
 *@param strUserEntry command string entered by the user
 */
void ProcessAddRootCommand(string strUserEntry)
{
// the what variable is actually an array that will be populated by the regex_match function
  //    when matched groups are found
  cmatch what;
  // what[0] contains the entire matched string
  // what[1] contains the first matched group
  // what[2] contains the second matched group
  // what[3] etc.

  // regex to pick out add root command and element name 
  regex reAddRootCmd( "^\\s*add\\s*root\\s(\\w+)(.*)$", regex::icase ) ;

  // note that the following variant of the regex_match command requires a C string, not an STL string
  if ( regex_match( strUserEntry.c_str(), what, reAddRootCmd ) ) {
    cout << "  You have specified that you want to add a root element named '" << what[1]<<"'"<<endl ;
    my.add_root(what[1].str());
  }
  else {
    cout << "  Invalid 'add root' command." << endl ;
    cout << "    'add root' must be followed by one more parameter:" << endl ;
    cout << "     (1) the name of the root element to be added to the DOM"<< endl ;
  }
}
/**
 * Handle an add element command entered by the user, 
 * if last argument is supplied element text will also be created 
 * @param strUserEntry command string entered by the user
 */
void ProcessAddElementCommand( string strUserEntry ) {
  //check too see if there is a root elem
  if (!my.check_root())
  {
    cout << " No root element has been created, please use 'add root' command first"<<endl;
    return;
  }
  // the what variable is actually an array that will be populated by the regex_match function
  //    when matched groups are found
  cmatch what;
  // what[0] contains the entire matched string
  // what[1] contains the first matched group
  // what[2] contains the second matched group
  // what[3] etc.
  
  // regular expression to pick out the name of the parent to which the new element is to be added 
  //    and the name of the new element itself
  regex reAddElementCmd( "^\\s*add\\s*element\\s(\\w+)\\s(\\w+)\\s*(\\w*)(.*)$", regex::icase ) ;
  
  // note that the following variant of the regex_match command requires a C string, not an STL string
  if ( regex_match( strUserEntry.c_str(), what, reAddElementCmd ) ) {
    cout << "  You have specified that you want to add a new element named '" << what[2]
         << "' to parent element '" << what[1]<<"' ";
      if(what[3].str()!="") {
        cout << "with element text '" << what[3] << "'." << endl;
      }
    my.add_element(what[2].str(),what[1].str(),what[3].str());

  }
  else {
    cout << "  Invalid 'add element' command." << endl ;
    cout << "    'add element' must be followed by two more parameters:" << endl ;
    cout << "      (1) the name of the parent to which the new element is to be added, and" << endl ;
    cout << "      (2) the name of the new element itself, and" << endl ;
    cout << "      (3) optionally element text" << endl;

  }
}


/**
 * Handle an add attribute command entered by the user
 * @param strUserEntry command string entered by the user
 */
void ProcessAddAttributeCommand( string strUserEntry ) {
  // the what variable is actually an array that will be populated by the regex_match function
  //    when matched groups are found
  cmatch what;
  // what[0] contains the entire matched string
  // what[1] contains the first matched group
  // what[2] contains the second matched group
  // what[3] etc.
  
  // regular expression to pick out the name of the element to which the new attribute is to be added,
  //    the name of the new attribute, and the value of that attribute
  regex reAddAttributeCmd( "^\\s*add\\s*attribute\\s(\\w+)\\s(\\w+)\\s(\\w+)(.*)$", regex::icase ) ;
  
  // note that the following variant of the regex_match command requires a C string, not an STL string
  if ( regex_match( strUserEntry.c_str(), what, reAddAttributeCmd ) ) {
    cout << "  You have specified that you want to add a new attribute named '" << what[2] 
         << "' with a value of '" << what[3] << "' to element '"  << what[1] << "'." << endl ;
    my.add_attribute(what[2].str(),what[3].str(),what[1].str());
  } else {
    cout << "  Invalid 'add attribute' command." << endl ;
    cout << "    'add attribute' must be followed by three more parameters:" << endl ;
    cout << "      (1) the name of the element to which the new attribute to be added," << endl ;
    cout << "      (2) the name of the new attribute to be added, and " << endl ;
    cout << "      (3) the value of the new attribute to be added." << endl ;
  }
}


/**
 * Handle a print command entered by the user
 * if alpha argument supplied Dom nodes will be outputted alphabetically
 * @param strUserEntry command string entered by the user
 */
void ProcessPrintCommand( string strUserEntry ) {
  // the what variable is actually an array that will be populated by the regex_match function
  //    when matched groups are found
  cmatch what;
  // what[0] contains the entire matched string
  // what[1] contains the first matched group
  // what[2] contains the second matched group
  // what[3] etc.
  cout <<what[0];
  // regular expression to pick out the name of the element to which the  attribute is to be removed,
  regex rePrintCommand( "^\\s*print\\s*(\\w*)(.*)$", regex::icase ) ;
  regex reAlphaPrintCommand("^\\s*print\\s*alpha(.*)$", regex::icase);
  // note that the following variant of the regex_match command requires a C string, not an STL string
  if ( regex_match( strUserEntry.c_str(), what, reAlphaPrintCommand ) ) {
    my.output_alpha();

  }
    else if(regex_match( strUserEntry.c_str(), what, rePrintCommand ))
  {
    my.output_dom();
  }
  else {
    cout << "  Invalid 'print' command." << endl ;
    cout << "    'remove attribute' may be followed by 0 or 1 more parameter:" << endl ;
    cout << "      (0) basic print" << endl ;
    cout << "      (2) alphabetical print of DOM elements" << endl ;

  }
}
/**
 * Handles remove attribute command 
 * @param strUserEntry
 */
void ProcessRemoveAttrCommand(string strUserEntry){
  // the what variable is actually an array that will be populated by the regex_match function
  //    when matched groups are found
  cmatch what;
  // what[0] contains the entire matched string
  // what[1] contains the first matched group
  // what[2] contains the second matched group
  // what[3] etc.
  cout <<what[0];
  // regular expression to pick out the name of the element to which the  attribute is to be removed,
  regex reRemoveAttributeCmd( "^\\s*remove\\s*attribute\\s(\\w+)\\s(\\w+)(.*)$", regex::icase ) ;

  // note that the following variant of the regex_match command requires a C string, not an STL string
  if ( regex_match( strUserEntry.c_str(), what, reRemoveAttributeCmd ) ) {
    cout << "  You have specified that you want to remove an attribute named '" << what[2]
    << "' from element '"  << what[1] << "'." << endl ;
   my.remove_attribute(what[1].str(),what[2].str());
  } else {
    cout << "  Invalid 'remove attribute' command." << endl ;
    cout << "    'remove attribute' must be followed by 2 more parameters:" << endl ;
    cout << "      (1) the name of the element from which the attribute is to be removed," << endl ;
    cout << "      (2) the name of the  attribute to be removed" << endl ;

  }
}
