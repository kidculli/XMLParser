/**
 * @file dynamic_dom.cpp
 * @author: Cullin Lam clam@cs.uml.edu
 * This file utilizes Xercesc library to create an interface for users to dynamically
 * create a Dom object in memory 
 *
 * Created on 2015-12-07
 * 
 * Last Updated 2015-12-08
 *        -added add_root method
 *        -implemented constructor
 *        - implemented required functions
 *        - removed createDocument with root
 *        - added has_root member
 *        - added output_alpha function
 *        - reset tree walker position before use 
 *         - added destructor method 
 */

#include "dynamic_dom.h"
#include <iostream>
using namespace std;
/**
 * This function is used to compare two strings alphabetically; used for sorting
 * @param first    first item to be compared
 * @param second   second item to be compared
 * @return         true if first comes before second alphabetically false otherwise
 */

bool compare_elem_alpha(DOMNode* first, DOMNode* second) {
    if (strcmp(x(first->getNodeName()), x(second->getNodeName())) < 0) {
        return true;
    } else {
        return false;
    }
}
DomBuilder::DomBuilder()
{
    // Initialize the XML4C2 system.
    try {
        XMLPlatformUtils::Initialize();
    } catch (const XMLException& toCatch) {
        char *pMsg = XMLString::transcode(toCatch.getMessage());
        //XERCES_STD_QUALIFIER cerr << "Error during Xerces-c Initialization.\n" << "  Exception message:" << pMsg;
        XMLString::release(&pMsg);
        //return 1;
    }

    //Create doc 
    
    // first create Dom imp object 
    DOMImplementation* impl = DOMImplementationRegistry::getDOMImplementation(X("Core"));
    // create Doc
     doc = impl->createDocument();
     // create Dom Serializer instance 
     theSerializer = ((DOMImplementationLS*) impl)->createLSSerializer();
     // Configure Serializer 
     // Make the output more human readable by inserting line feeds.
            if (theSerializer->getDomConfig()->canSetParameter(XMLUni::fgDOMWRTFormatPrettyPrint, true))
                theSerializer->getDomConfig()->setParameter(XMLUni::fgDOMWRTFormatPrettyPrint, true);

            // The end-of-line sequence of characters to be used in the XML being written out.
            theSerializer->setNewLine(XMLString::transcode("\r\n"));
     // Set output to std out 
     // create output instance
    theOutputDesc = ((DOMImplementationLS*) impl)->createLSOutput();

    // referenced the following http://stackoverflow.com/questions/2897317/writing-xml-with-xerces-3-0-1-and-c-on-windows
    // set output from serializer to stdout
    XMLFormatTarget *myFormTarget;
    myFormTarget = new StdOutFormatTarget();
    theOutputDesc->setByteStream(myFormTarget);


}
void DomBuilder::add_root(string name) {
    if(has_root)
    {
        cout<<"root element currently exists please use 'remove root' before adding a new root"<<endl;
        return;
    }
    DOMElement* root = doc->createElement(X(name.c_str()));
    doc->appendChild(root);
    // We can iniialize tree walker after root node is created
    walker = doc->createTreeWalker(root,
                                   DOMNodeFilter::SHOW_ELEMENT,
                                   NULL,
                                   true);
    //set root status
    has_root = true;
}
void DomBuilder::output_dom() {
    // output the DOM
    theSerializer->write(doc, theOutputDesc);
}
void DomBuilder::add_element(string elem_name, string parent, string value) {

    // reset Walker position 
    walker->setCurrentNode(walker->getRoot()); 
    // traverse tree using walker
    for (DOMNode* current = doc->getDocumentElement(); current != 0; current = walker->nextNode()) {
        string curr_node_name (x(walker->getCurrentNode()->getNodeName()));
        if(parent == curr_node_name)
        {
            // create elem
            DOMNode* elem_node = doc->createElement(X(elem_name.c_str()));
            if(value!="") {
                // create value node
                DOMText *val = doc->createTextNode(X(value.c_str()));
                // append text node to elem node
                elem_node->appendChild(val);
            }
            current->appendChild(elem_node);
            return;
        }
    }

    // parent not found
    cout << "Element '"<<elem_name<<"' not added, parent element '"<<parent<<"' not found.";
}

void DomBuilder::add_attribute(string attr_name, string attr_val, string elem_name) {
    // reset Walker position 
    walker->setCurrentNode(walker->getRoot()); 
    // traverse tree using walker
    for (DOMNode* current = doc->getDocumentElement(); current != 0; current = walker->nextNode()) {
        string curr_node_name (x(walker->getCurrentNode()->getNodeName()));
        if(elem_name == curr_node_name)
        {
            DOMAttr* attr = doc->createAttribute(X(attr_name.c_str()));
            attr->setValue(X(attr_val.c_str()));
            //cast DOMNode to DOMElement source - http://stackoverflow.com/questions/4746631/passing-from-a-domnode-to-a-domelement-in-xerces-c
            DOMElement* the_elem = dynamic_cast<DOMElement*>(current);
            the_elem->setAttributeNode(attr);
            return;
        }
    }

    // parent not found
    cout << "Attribute '"<<attr_name<<"' not added, element '"<<elem_name<<"' not found."<<endl;
}
void DomBuilder::remove_child(string elem_name) {
    // reset Walker position 
    walker->setCurrentNode(walker->getRoot()); 
    // traverse tree using walker
    for (DOMNode* current = doc->getDocumentElement(); current != 0; current = walker->nextNode()) {
        string curr_node_name(x(walker->getCurrentNode()->getNodeName()));
        if (elem_name == curr_node_name) {
            // Get parent Node
            DOMNode *parent = current->getParentNode();
            // Remove child from parent and release it's resources
            parent->removeChild(current)->release();
            return;
        }
    }
        // elem not found
        cout << "Element '" << elem_name << "' not found."<<endl;
}
void DomBuilder::remove_root() {
    DOMNode* root = doc->getDocumentElement();
    if(root !=NULL)
    {
        // remove root node
        doc->removeChild(root);
        //release resources
        root->release();
        // set root status
        has_root = false;
    }
    else {
        cout << "Unable to remove root, no root element found"<<endl;
    }
}
void DomBuilder::remove_attribute(string elem_name, string attr_name) {
     // reset Walker position 
    walker->setCurrentNode(walker->getRoot()); 
    // traverse tree using walker
    for (DOMNode* current = doc->getDocumentElement(); current != 0; current = walker->nextNode()) {
        string curr_node_name(x(walker->getCurrentNode()->getNodeName()));
        if (elem_name == curr_node_name) {
            DOMElement* the_elem = dynamic_cast<DOMElement*>(current);
            DOMNode* attr_node = the_elem->getAttributes()->getNamedItem(X(attr_name.c_str()));
            if (attr_node!= NULL) {
                the_elem->removeAttribute(X(attr_name.c_str()));
                return;
            }
            else {
                cout << "Unable to remove attribute, '"<<attr_name<<"' not found."<<endl;
                return;
            }
        }
    }
    // elem not found
    cout << "Element '" << elem_name << "' not found."<<endl;
}

void DomBuilder::output_alpha() {
    if(!has_root)
    {
        cout<<"No root element exists, cannot output element nodes"<<endl;
        return;
    }
    // create vector to hold Dom nodes
    vector<DOMNode*> elem_vec;
    // reset Walker position 
    walker->setCurrentNode(walker->getRoot()); 
    for (DOMNode* current = walker->getRoot(); current != 0; current = walker->nextNode()) {
        // store nodes into vector
        elem_vec.push_back(current);
    }
    // sort function - alphabetically elements
    std::sort(elem_vec.begin(), elem_vec.end(), compare_elem_alpha);

    // iterate through sorted nodes
    for (auto i : elem_vec) {
        int x;
        string text = string(x(i->getTextContent()));
        cout << "Node Name: " << x(i->getNodeName()) << ((text != "") ? " |Text Content: " + text : "") << endl;

        //get attr map
        if (i->hasAttributes()) {
            DOMNamedNodeMap *attr_map = i->getAttributes();
            // get each node in the map
            for (x = 0; x < attr_map->getLength(); x++) {
                DOMNode *temp = attr_map->item(x);
                cout << setw(5) << "" << "Attribute" << x + 1 << ": " << x(temp->getNodeName()) << " = "
                << x(temp->getNodeValue()) << endl;
            }
        }
    }
}
DomBuilder::~DomBuilder()
{
    // release Xerces resources
    theOutputDesc->release(); 
    theSerializer->release(); 
    walker->release(); 
    doc->release(); 
}