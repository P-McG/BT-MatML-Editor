#pragma once

#include <memory>   // std::auto_ptr
#include <string>
#include <fstream>
#include <typeinfo>
#include <iostream>

#include <xercesc/dom/DOM.hpp>
#include <xercesc/dom/DOMLSSerializer.hpp>
#include <xercesc/util/PlatformUtils.hpp>

#include <xsd/cxx/xml/string.hxx>

#include "bellshire/lib/dom-parse.hxx"
#include "bellshire/Lib/dom-serialize.hxx"
#include "bellshire/matml31.hxx"
#include "bellshire/Lib/matml31_lib.hxx"

namespace bellshire::Lib {

	class MatML_Lib
	{
	protected:
		std::unique_ptr< xml_schema::element_type > m_lib_element;
	public:
		MatML_Lib() {};
		MatML_Lib(std::unique_ptr< xml_schema::element_type >lib_element):m_lib_element(std::move(lib_element))
		{};
		virtual ~MatML_Lib() {};
		
		template <class MatML_Class>
		static bool Get(const std::string& filename, std::unique_ptr<MatML_Class>& element);

		template <class MatML_Class>
		static bool Set(const std::string& filename, std::unique_ptr<MatML_Class>& element);
	};

}//bellshire

#include "bellshire/Lib/BT_MatML_MatML_Lib.inl"