#pragma once
#include <boost/any.hpp>

using namespace bellshire::GUI;

template<class MatML_Class>
void ID_GUI::ExchangeIDRefWithID(::boost::any any_ptr)
{
	try {
		const auto element_observer{ boost::any_cast<observer_ptr<MatML_Class>>(any_ptr)};
		if (!element_observer->id().empty() && !GetReplaceIDRefs()->IsChecked())
			if (!Warning()) 
				return;

		xml_schema::idref oldid("");
		oldid = element_observer->id();

		GenerateUuid(element_observer);
		Update(element_observer);

		xml_schema::idref newid(element_observer->id());
		if (GetReplaceIDRefs()->IsChecked())
			SwapIDRefs(m_MatMLDoc, oldid, newid);

		return;
	}
	catch (const boost::bad_any_cast&) {}
}

template<class MatML_Class>
void ID_GUI::ExchangeIDRefWithOptionalID(::boost::any any_ptr)
{
	try {
		auto const element_observer = boost::any_cast<observer_ptr<MatML_Class>>(any_ptr);
		if ((element_observer->id().present() && !element_observer->id().get().empty()) && !GetReplaceIDRefs()->IsChecked())
			if (!Warning())
				return;

		xml_schema::idref oldid("");
		if (element_observer->id().present()) oldid = element_observer->id().get();


		GenerateUuid(element_observer);
		Update(element_observer);

		xml_schema::idref newid(element_observer->id().get());
		if (GetReplaceIDRefs()->IsChecked())
			SwapIDRefs(m_MatMLDoc, oldid, newid);

		return;
	}
	catch (const boost::bad_any_cast&) {}
}
