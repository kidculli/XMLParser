/**
 * @file main.cpp
 * @author: Cullin Lam clam@cs.uml.edu
 * This file utilizes Xercesc library to create a DOM object in memory and then 
 * prints out the resultant structure to stdout 
 *
 * Created on November 18, 2015, 1:21 PM
 * 
 * Last Updated November 19, 2015
 *      - added calls to Serializer and TreeWalker 
 */


#include <cstdlib>

using namespace std;
// ---------------------------------------------------------------------------
//  Includes
// ---------------------------------------------------------------------------
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/dom/DOM.hpp>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <string.h>
#include <xercesc/dom/DOMDocumentTraversal.hpp>
#include <xercesc/dom/DOMTreeWalker.hpp>
#include <xercesc/dom/DOMNode.hpp>
#include <xercesc/dom/DOMNodeIterator.hpp>
#include <xercesc/util/OutOfMemoryException.hpp>
#include <xercesc/framework/StdOutFormatTarget.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>
#if defined(XERCES_NEW_IOSTREAMS)
#include <iostream>
#else
#include <iostream.h>
#endif

XERCES_CPP_NAMESPACE_USE

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
/**
 * Main routine that utilizes Xercesc module to create a DOM object in memory 
 * and prints out the resultant DOM structure 
 * @param argC    number of command line args 
 * @param argV    name of command line args 
 * @return        0 if no errors occurred 
 */
int main(int argC, char*argv[]) {
    // Initialize the XML4C2 system.
    try {
        XMLPlatformUtils::Initialize();
} catch (const XMLException& toCatch) {
    char *pMsg = XMLString::transcode(toCatch.getMessage());
    XERCES_STD_QUALIFIER cerr << "Error during Xerces-c Initialization.\n" << "  Exception message:" << pMsg;
    XMLString::release(&pMsg);
    return 1;
}

    // Watch for special case help request
    int errorCode = 0;
    if (argC > 1) {
        XERCES_STD_QUALIFIER
        cout << "\nUsage:\n"
                "    CreateDOMDocument\n\n"
                "This program creates a new DOM document from scratch in memory.\n"
                "It then prints the count of elements in the tree.\n" << XERCES_STD_QUALIFIER
                endl;
        errorCode = 1;
    }
    if (errorCode) {
        XMLPlatformUtils::Terminate();
        return errorCode;
    }


    DOMImplementation* impl = DOMImplementationRegistry::getDOMImplementation(X("Core"));

    if (impl != NULL) {
        try {
            // create a DomDocument instance
            DOMDocument* doc = impl->createDocument(
                    0, // root element namespace URI.
                    X("TheHood"), // root element name
                    0); // document type object (DTD).

            // create root attribute nodes
            DOMAttr* woop_atr = doc->createAttribute(X("WOOP"));
            woop_atr->setValue(X("DANG"));
            DOMAttr* fiyah_atr = doc->createAttribute(X("FIYAH"));
            fiyah_atr->setValue(X("hot"));
            DOMAttr* hungry_atr = doc->createAttribute(X("hungry"));
            hungry_atr->setValue(X("starving"));

            // create root element
            DOMElement* rootElem = doc->getDocumentElement();
            // set root attrs
            rootElem->setAttributeNode(woop_atr);
            rootElem->setAttributeNode(fiyah_atr);
            rootElem->setAttributeNode(hungry_atr);

            //create root child elements
            DOMElement* gangElem = doc->createElement(X("gang"));
            rootElem->appendChild(gangElem);
            DOMText* gangDataVal = doc->createTextNode(X("YoungThugz"));
            gangElem->appendChild(gangDataVal);
            gangElem->setAttribute(X("hardness"), X("rock"));

            //create gang attr nodes
            DOMAttr* members_atr = doc->createAttribute(X("members"));
            members_atr->setValue(X("500"));
            DOMAttr* color_atr = doc->createAttribute(X("color"));
            color_atr->setValue(X("magenta"));
            // set gang attr
            gangElem->setAttributeNode(members_atr);
            gangElem->setAttributeNode(color_atr);
            // create gang elem children
            DOMElement* piruElem = doc->createElement(X("piru"));
            piruElem->setNodeValue(X("w"));
            DOMElement* cripElem = doc->createElement(X("crip"));
            cripElem->setNodeValue(X("t"));
            DOMElement* trgElem = doc->createElement(X("trg"));
            trgElem->setNodeValue(X("o"));
            // append gang elem children
            gangElem->appendChild(piruElem);
            gangElem->appendChild(cripElem);
            gangElem->appendChild(trgElem);

            DOMElement* turfElem = doc->createElement(X("turf"));
            rootElem->appendChild(turfElem);
            turfElem->setAttribute(X("idea"), X("great"));
            DOMText* turfDataVal = doc->createTextNode(X("West Side Projects"));
            turfElem->appendChild(turfDataVal);

            DOMElement* cliqueElem = doc->createElement(X("clique"));
            rootElem->appendChild(cliqueElem);
            DOMText* cliqueDataVal = doc->createTextNode(X("Balla$"));
            cliqueElem->appendChild(cliqueDataVal);
            cliqueElem->setAttribute(X("Comradery"), X("tight"));

            DOMElement* sideElem = doc->createElement(X("side"));
            rootElem->appendChild(sideElem);
            DOMText* sideDataVal = doc->createTextNode(X("North North"));
            sideElem->appendChild(sideDataVal);
            // create side elem children
            DOMElement* tempElem = doc->createElement(X("temperature"));
            tempElem->setNodeValue(X("100 C"));
            DOMElement* med_incomeElem = doc->createElement(X("medianIncome"));
            med_incomeElem->setNodeValue(X("$20,000"));
            DOMElement* schoolsElem = doc->createElement(X("schools"));
            schoolsElem->setNodeValue(X("Regional"));
            // append side elem children
            sideElem->appendChild(tempElem);
            sideElem->appendChild(med_incomeElem);
            sideElem->appendChild(schoolsElem);

            DOMElement* gatElem = doc->createElement(X("gat"));
            rootElem->appendChild(gatElem);
            DOMText* gatDataVal = doc->createTextNode(X("Glock"));
            gatElem->appendChild(gatDataVal);
            //set gat attr
            gatElem->setAttribute(X("caliber"), X(".50"));
            // create gat elem children
            DOMElement* rifleElem = doc->createElement(X("rifle"));
            DOMElement* meleeElem = doc->createElement(X("melee"));
            DOMElement* pieceElem = doc->createElement(X("piece"));
            // append gat elem children
            gatElem->appendChild(rifleElem);
            gatElem->appendChild(meleeElem);
            gatElem->appendChild(pieceElem);

            DOMElement* contraElem = doc->createElement(X("contra"));
            rootElem->appendChild(contraElem);
            DOMText* contraDataVal = doc->createTextNode(X("Cocoa"));
            contraElem->appendChild(contraDataVal);
            contraElem->setAttribute(X("rareness"), X("extreme"));
            // create contra elem children
            DOMElement* methElem = doc->createElement(X("meth"));
            DOMElement* ganjaElem = doc->createElement(X("ganja"));
            DOMElement* ethElem = doc->createElement(X("ethanol"));
            // append contra elem children
            contraElem->appendChild(methElem);
            contraElem->appendChild(ganjaElem);
            contraElem->appendChild(ethElem);
            //create contra attr nodes
            DOMAttr* price_atr = doc->createAttribute(X("price"));
            price_atr->setValue(X("$25"));
            DOMAttr* source_atr = doc->createAttribute(X("source"));
            source_atr->setValue(X("Columbia"));
            // set contra attr
            contraElem->setAttributeNode(price_atr);
            contraElem->setAttributeNode(source_atr);

            DOMElement* rivalsElem = doc->createElement(X("rivals"));
            rootElem->appendChild(rivalsElem);
            DOMText* rivalsDataVal = doc->createTextNode(X("Warrriors"));
            rivalsElem->appendChild(rivalsDataVal);

            DOMElement* policeElem = doc->createElement(X("police"));
            rootElem->appendChild(policeElem);
            DOMText* policeDataVal = doc->createTextNode(X("popo"));
            policeElem->appendChild(policeDataVal);

            DOMElement* drugsElem = doc->createElement(X("drugs"));
            rootElem->appendChild(drugsElem);
            DOMText* drugsDataVal = doc->createTextNode(X("codiene"));
            drugsElem->appendChild(drugsDataVal);
            // create drugs elem children
            DOMElement* mixElem = doc->createElement(X("mix"));
            DOMElement* spriteElem = doc->createElement(X("sprite"));
            DOMElement* leanElem = doc->createElement(X("lean"));
            // append drugs elem children
            drugsElem->appendChild(mixElem);
            drugsElem->appendChild(spriteElem);
            drugsElem->appendChild(leanElem);

            DOMElement* crimeElem = doc->createElement(X("crime"));
            rootElem->appendChild(crimeElem);
            DOMText* crimeDataVal = doc->createTextNode(X("187"));
            crimeElem->appendChild(crimeDataVal);

            //
            // Now count the number of elements in the above DOM tree.
            //

            const XMLSize_t elementCount = doc->getElementsByTagName(X("*"))->getLength();
            XERCES_STD_QUALIFIER cout << "The tree just created contains: " << elementCount
                    << " elements." << XERCES_STD_QUALIFIER endl;

            // create serializer instance
            DOMLSSerializer *theSerializer = ((DOMImplementationLS*) impl)->createLSSerializer();
            // create output instance
            DOMLSOutput *theOutputDesc = ((DOMImplementationLS*) impl)->createLSOutput();

            // referenced the following http://stackoverflow.com/questions/2897317/writing-xml-with-xerces-3-0-1-and-c-on-windows
            // set output from serializer to stdout
            XMLFormatTarget *myFormTarget;
            myFormTarget = new StdOutFormatTarget();
            theOutputDesc->setByteStream(myFormTarget);

            // Make the output more human readable by inserting line feeds.
            if (theSerializer->getDomConfig()->canSetParameter(XMLUni::fgDOMWRTFormatPrettyPrint, true))
                theSerializer->getDomConfig()->setParameter(XMLUni::fgDOMWRTFormatPrettyPrint, true);

            // The end-of-line sequence of characters to be used in the XML being written out.
            theSerializer->setNewLine(XMLString::transcode("\r\n"));

            // output the DOM
            theSerializer->write(doc, theOutputDesc);

            cout << endl << endl << "*****************************************" << endl;

            // Using DOMTreeWalker class to traverse tree
            // create tree walker
            DOMTreeWalker* walker = doc->createTreeWalker(rootElem,
                    DOMNodeFilter::SHOW_ELEMENT,
                    NULL,
                    true);
            // create vector to hold Dom nodes
            vector<DOMNode*> elem_vec;
            // traverse tree using walker
            for (DOMNode* current = walker->nextNode(); current != 0; current = walker->nextNode()) {
                // store nodes int vector
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
            // release doc resources
            doc->release();
        } catch (const OutOfMemoryException&) {
            XERCES_STD_QUALIFIER cerr << "OutOfMemoryException" << XERCES_STD_QUALIFIER endl;
            errorCode = 5;
        } catch (const DOMException& e) {
            XERCES_STD_QUALIFIER cerr << "DOMException code is:  " << e.code << XERCES_STD_QUALIFIER endl;
            errorCode = 2;
        } catch (...) {
            XERCES_STD_QUALIFIER cerr << "An error occurred creating the document" << XERCES_STD_QUALIFIER endl;
            errorCode = 3;
        }
    }// (impl != NULL)
    else {
        XERCES_STD_QUALIFIER cerr << "Requested implementation is not supported" << XERCES_STD_QUALIFIER endl;
        errorCode = 4;
    }


}
