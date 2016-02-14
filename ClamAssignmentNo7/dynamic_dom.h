/**
 @author Cullin Lam clam@cs.uml.edu 
 * @file dynamic_dom.h 
 * This file declares functions used to build and manipulate the Xercesc Dom Object 
 * Created 2015-12-03 
 * 
 * 
 * 
 * Last Updated 
 *       2015-12-03
 *          
 */

#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/dom/DOM.hpp>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <string>
#include <xercesc/dom/DOMDocumentTraversal.hpp>
#include <xercesc/dom/DOMTreeWalker.hpp>
#include <xercesc/dom/DOMNode.hpp>
#include <xercesc/dom/DOMNodeIterator.hpp>
#include <xercesc/util/OutOfMemoryException.hpp>
#include <xercesc/framework/StdOutFormatTarget.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>
#ifndef DYNAMIC_DOM_H
#define	DYNAMIC_DOM_H

XERCES_CPP_NAMESPACE_USE
using namespace std; 

class XStr {
/**
 * This class provides functions to transcode between XMLCh* and Char*
 * @source: Jesse Heines Handouts
*/
public:
    /**
     * This function converts an XMLCh* to a Char* (c-string)
     * @param toTranscode XMLCh* to transcode to a c string
     * @return converted c-style string
     */
    XStr(const char* const toTranscode) {
        // Call the private transcoding method
        fUnicodeForm = XMLString::transcode(toTranscode);
    }
    /**
     * destructor method
     */
    ~XStr() {
        XMLString::release(&fUnicodeForm);
    }
    /**
     * converts to unicode form (XMLCh*) from the XStr object
     * @return unicode form (XMLCh*) of the XStr object
     */
    const XMLCh* unicodeForm() const {
        return fUnicodeForm;
    }

private:
    /**
     * Unicode form of the XStr object
     */
    XMLCh* fUnicodeForm;
};
/**
 * X converts a c-string to an XMLCh*
 */
#define X(str) XStr(str).unicodeForm()
/**
 * x converts a XMLCh*  to a c string
 */
#define x(str) XMLString::transcode(str) //to convert between XMLCh* and char*

/**
 * This class allows the user to create a Dom Document dynamically
 */
class DomBuilder
{
    /**
     * The Xerces Dom document used for building the DOM 
     */
    DOMDocument* doc; 
    /**
     * Xerces serializer object used for outputting xml 
     */
    DOMLSSerializer *theSerializer; 
    /**
     * Xerces Output object used for setting output destination 
     */
     DOMLSOutput *theOutputDesc;
    /**
     * Xerces Tree Walker Object used for traversing DOM
     * will be initialized after root node is created
     */
    DOMTreeWalker *walker = NULL;
    /**
     * If root has been created has_root will be true otherwise
     * if root has not yet been created or has been deleted it will be false
     */
     bool has_root = false;
public:
     /**
      * Default constructor that sets up Dom serializer and output 
      */
     DomBuilder(); 
     /**
      * Destructor method used to free resources 
      */
     ~DomBuilder(); 
     /**
      * Add root element to DOM
      * @param name name of new root element
      */
    void add_root(string name);
     /**
      * Outputs the Dom to std_out; 
      */
     void output_dom(); 
     /**
      * Add element to the Dom tree 
      * @param elem_name name of element to be created and added 
      * @param parent name of parent elem 
      * @param value of element 
      */
     void add_element(string elem_name, string parent, string value);
     /**
      * Add attribute name to an element 
      * @param attr_name name of attr to add
      * @param attr_val value of attr to add 
      * @param elem_name name of element to add attr to 
      */
     void add_attribute(string attr_name, string attr_val, string elem_name);
    /**
     * removes a node and all it's children from the DOM
     * @param elem_name name of element to remove 
     */
    void remove_child(string elem_name);
    /**
     * @return true if root exists false otherwise 
     */
    bool check_root()
    {
        return has_root; 
    }
    /**
     *  removes root element, resets DOM
     */
    void remove_root();
    /**
     * removes attribute
     * @param name of element 
     * @param attr_name name of attribute to remove from element  
     */
    void remove_attribute(string elem_name,string attr_name);
    /**
     * outputs DOM nodes alphabetically by element name
     */
    void output_alpha();

    
};


#endif	/* DYNAMIC_DOM_H */

