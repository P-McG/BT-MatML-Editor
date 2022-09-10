#pragma once
#include <boost/any.hpp>

using namespace bellshire;

template<class MatML_Class>
void ID_GUI::ExchangeIDRefWithID(::boost::any any_ptr)
{
	try {
		MatML_Class* const element = boost::any_cast<MatML_Class* const>(any_ptr);
		if (!element->id().empty() && !m_ReplaceIDRefs->IsChecked())
			if (!Warning()) 
				return;

		xml_schema::idref oldid("");
		oldid = element->id();

		GenerateUuid(element);
		Update(element);

		xml_schema::idref newid(element->id());
		if (m_ReplaceIDRefs->IsChecked())
			SwapIDRefs(m_MatMLDoc.get(), oldid, newid);

		return;
	}
	catch (const boost::bad_any_cast&) {}
}

template<class MatML_Class>
void ID_GUI::ExchangeIDRefWithOptionalID(::boost::any any_ptr)
{
	try {
		MatML_Class* const element = boost::any_cast<MatML_Class* const>(any_ptr);
		if ((element->id().present() && !element->id().get().empty()) && !m_ReplaceIDRefs->IsChecked())
			if (!Warning())
				return;

		xml_schema::idref oldid("");
		if (element->id().present()) oldid = element->id().get();


		GenerateUuid(element);
		Update(element);

		xml_schema::idref newid(element->id().get());
		if (m_ReplaceIDRefs->IsChecked())
			SwapIDRefs(m_MatMLDoc.get(), oldid, newid);

		return;
	}
	catch (const boost::bad_any_cast&) {}
}
