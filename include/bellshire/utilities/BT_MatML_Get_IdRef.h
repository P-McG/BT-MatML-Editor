#pragma once
#include "bellshire/matml31.hxx"
#include "bellshire/matml31_strongly_typed_def.h"
#include <type_traits>

//List all the members that are a idref.
namespace bellshire::utilities
{

	template<class MatML>
	::xml_schema::idref Get_IdRef(const observer_ptr<MatML> element)
	{
		if (has_idref_type<MatML>::value && has_authority_type<MatML>::value) Get_Authority(element);
		else if (has_idref_type<MatML>::value && has_parameter_type<MatML>::value) Get_Parameter(element);
		else if (has_idref_type<MatML>::value && has_property_type<MatML>::value) Get_Property(element);
		else if (has_idref_type<MatML>::value && has_technique_type<MatML>::value) Get_Technique(element);
		else if (has_idref_type<MatML>::value && has_source_type<MatML>::value) Get_Source(element);
		else if (has_idref_type<MatML>::value && has_specimen_type<MatML>::value) Get_Specimen(element);
		else if (has_idref_type<MatML>::value && has_test_type<MatML>::value) Get_Test(element);
		else if (has_idref_type<MatML>::value && has_id_type<MatML>::value) Get_Id(element);
	}

	template<class MatML>
	::xml_schema::idref Get_Authority(const observer_ptr<MatML> element)
	{
		return element->authority();
	}

	template<class MatML>
	::xml_schema::idref Get_Parameter(const observer_ptr<MatML> element)
	{
		return element->parameter();
	}

	template<class MatML>
	::xml_schema::idref Get_Property(const observer_ptr<MatML> element)
	{
		return element->property();
	}

	template<class MatML>
	::xml_schema::idref Get_Technique(const observer_ptr<MatML> element)
	{
		return element->technique();
	}

	template<class MatML>
	::xml_schema::idref Get_Source(const observer_ptr<MatML> element)
	{
		return element->source();
	}

	template<class MatML>
	::xml_schema::idref Get_Specimen(const observer_ptr<MatML> element)
	{
		return element->specimen();
	}

	template<class MatML>
	::xml_schema::idref Get_Test(const observer_ptr<MatML> element)
	{
		return element->test();
	}

	//template<class MatML>
	//::xml_schema::idref Get_Id(const observer_ptr<MatML> element)
	//{
	//	return element->id();
	//}

};//namespace bellshire

#include "bellshire/utilities/BT_MatML_Get_IdRef.inl"
