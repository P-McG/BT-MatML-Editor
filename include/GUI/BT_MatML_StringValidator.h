/////////////////////////////////////////////////////////////////////////////
// Name:        BT_MatML_StringValidator.h
// Purpose:     Classes of StringValidator.
// Author:      Paul McGrath
// Modified by:
// Created:
// Copyright:   (c) Paul McGrath
// Licence:     CC licence
/////////////////////////////////////////////////////////////////////////////
#pragma once

#include <string>
#include <list>

#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/classification.hpp>

namespace bellshire {


	class StringValidator
	{
	public:
		StringValidator() {};//ctor
		~StringValidator() {};//dtor

		bool ValidateString(
			::std::string input,
			::std::string Format,
			::std::string Delimiter,
			bool NewLineRemoval,
			::std::string* msg
		);

		template<typename T> bool isValid(const std::string& num);

	};

}//bellshire namespace
