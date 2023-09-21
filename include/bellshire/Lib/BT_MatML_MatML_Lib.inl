#pragma once

#include <memory>   // std::unique_ptr
#include <string>
#include <fstream>
#include <typeinfo>
#include <iostream>

#include <xercesc/dom/DOM.hpp>
#include <xercesc/util/PlatformUtils.hpp>

#include <xsd/cxx/xml/string.hxx>

#include "bellshire/lib/dom-parse.hxx"
#include "bellshire/Lib/dom-serialize.hxx"
#include "xsd/cxx/tree/element-map.hxx"

#include "bellshire/Lib/matml31_lib.hxx"

#include "bellshire/Lib/BT_MatML_MatML_Lib.h"

namespace bellshire::Lib
{

    template <class MatML_Class>
    bool MatML_Lib::Get(const std::string& filename, std::unique_ptr<MatML_Class>& element)
    {
        // We need to initialize the Xerces-C++ runtime because we
        // are doing the XML-to-DOM parsing ourselves.
        // Note: Source of memory leak xerces_3.2
        // https://xerces.apache.org/xerces-c/faq-parse-3.html#faq-7
        ::xercesc::XMLPlatformUtils::Initialize();

        bool r(true);

        try
        {

            std::ifstream ifs;
            ifs.exceptions(std::ifstream::badbit | std::ifstream::failbit);
            ifs.open(filename);

            // Parse the XML request to a DOM document using the parse()
            // function from dom-parse.hxx.
            xml_schema::dom::unique_ptr<xercesc::DOMDocument> doc(parse(ifs, filename, true));

            xercesc::DOMElement& root(*doc->getDocumentElement());

            std::unique_ptr<xml_schema::element_type> req= std::move(xml_schema::element_map::parse(root)) ;

            // We can test which request we've got either using RTTI.
            // dynamic cast if we're unsure that it is cast able
            if (dynamic_cast<MatML_Class*>(req.get())) {
                element.reset(static_cast<MatML_Class*>(req.release()));

                r = true;
            }

        }
        catch (const xml_schema::no_element_info& e)
        {
            // This exception indicates that we tried to parse or serialize
            // an unknown element.
            //
            std::cerr << "unknown request: " << e.element_namespace() << "#" <<
                e.element_name() << std::endl;
            r = false;
        }
        catch (const xml_schema::exception& e)
        {
            std::cerr << e << std::endl;
            r = false;
        }
        catch (const std::ios_base::failure&)
        {
            std::cerr << filename << ": unable to open or read failure" << std::endl;
            r = false;
        }

        ::xercesc::XMLPlatformUtils::Terminate();
        return r;
    }

    template <class MatML_Class>
    bool MatML_Lib::Set(const std::string& filename, std::unique_ptr<MatML_Class>& element)
    {
        if (!element) return false;

        // We need to initialize the Xerces-C++ runtime because we
        // are doing the XML-to-DOM parsing ourselves.
        // Note: Source of memory leak ( KB) xerces_3.2
        // https://xerces.apache.org/xerces-c/faq-parse-3.html#faq-7
        ::xercesc::XMLPlatformUtils::Initialize();

        bool r(true);

        try
        {
            std::ofstream ofs;
            ofs.exceptions(std::ofstream::badbit | std::ofstream::failbit);
            ofs.open(filename);

            //std::unique_ptr<xml_schema::element_type> res(element->_clone());
            std::unique_ptr<xml_schema::element_type>& res(element);

            // Serialize the response to a DOM document.
           //
            namespace xml = xsd::cxx::xml;

            const XMLCh ls_id[] = { xercesc::chLatin_L, xercesc::chLatin_S, xercesc::chNull };

            ::xercesc::DOMImplementation* impl(
                ::xercesc::DOMImplementationRegistry::getDOMImplementation(ls_id));

            const std::string& name(res->_name());
            const std::string& ns(res->_namespace());

            xml_schema::dom::unique_ptr<::xercesc::DOMDocument> doc(
                impl->createDocument(
                    xml::string(ns).c_str(),
                    xml::string("" + name).c_str(),
                    0));

            ::xercesc::DOMElement* root(doc->getDocumentElement());

            root->setAttributeNS(
                xml::string("http://www.w3.org/2000/xmlns/").c_str(),
                xml::string("xmlns:xsi").c_str(),
                xml::string("http://www.w3.org/2001/XMLSchema-instance").c_str());

            root->setAttributeNS(
                xml::string("http://www.w3.org/2000/xmlns/").c_str(),
                xml::string("xmlns:xsd").c_str(),
                xml::string("http://www.w3.org/2001/XMLSchema").c_str());

            root->setAttributeNS(
                xml::string("http://www.w3.org/2001/XMLSchema-instance").c_str(),
                xml::string("xsi:noNamespaceSchemaLocation").c_str(),
                xml::string("matml31_lib.xsd").c_str());

            xml_schema::element_map::serialize(*doc->getDocumentElement(), *res);

            // Serialize the DOM document to XML using the serialize() function
            // from dom-serialize.hxx.

            serialize(/*std::cout*/ofs, *doc);

        }
        catch (const xml_schema::no_element_info& e)
        {
            // This exception indicates that we tried to parse or serialize
            // an unknown element.
            //
            std::cerr << "unknown request: " << e.element_namespace() << "#" <<
                e.element_name() << std::endl;
            r = false;
        }
        catch (const xml_schema::exception& e)
        {
            std::cerr << e << std::endl;
            r = false;
        }
        catch (const std::ios_base::failure& e)
        {
            std::cout << e.what() << std::endl;
            std::cerr << filename << ": unable to open or read failure" << std::endl;
            r = false;
        }

        ::xercesc::XMLPlatformUtils::Terminate();
        return r;
    }
}//namespace bellshire
