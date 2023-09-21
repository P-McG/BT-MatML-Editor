#pragma once
#include "bellshire/matml31.hxx"
#include "bellshire/matml31_strongly_typed_def.h"
#include <type_traits>
#include "bellshire/BT_MatML_has_a_idref.h"

//List all the members that are a idref.
namespace bellshire::utilities
{

	template<class MatML>
	::xml_schema::idref Replace_IdRef(MatML* element, ::xml_schema::idref find, ::xml_schema::idref replace)
	{
		if (has_idref_type<MatML>::value && has_authority_type<MatML>::value) Replace_Authority(element, find, replace);
		else if (has_idref_type<MatML>::value && has_parameter_type<MatML>::value) Replace_Parameter(element, find, replace);
		else if (has_idref_type<MatML>::value && has_property_type<MatML>::value) Replace_Property(element, find, replace);
		else if (has_idref_type<MatML>::value && has_technique_type<MatML>::value) Replace_Technique(element, find, replace);
		else if (has_idref_type<MatML>::value && has_source_type<MatML>::value) Replace_Source(element, find, replace);
		else if (has_idref_type<MatML>::value && has_specimen_type<MatML>::value) Replace_Specimen(element, find, replace);
		else if (has_idref_type<MatML>::value && has_test_type<MatML>::value) Replace_Test(element, find, replace);
		else if (has_idref_type<MatML>::value && has_id_type<MatML>::value) Replace_Id(element, find, replace);
	}

	template<class MatML>
	::xml_schema::idref Replace_Authority(MatML* element, ::xml_schema::idref find, ::xml_schema::idref replace)
	{
		return if( element->authority() == find) element->authority() = replace;
	}

	template<class MatML>
	::xml_schema::idref Replace_Parameter(MatML* element, ::xml_schema::idref find, ::xml_schema::idref replace)
	{
		return if (element->parameter() == find) element->parameter() = replace;
	}

	template<class MatML>
	::xml_schema::idref Replace_Property(MatML* element, ::xml_schema::idref find, ::xml_schema::idref replace)
	{
		return if (element->property() == find) element->property() = replace;
	}

	template<class MatML>
	::xml_schema::idref Replace_Technique(MatML* element, ::xml_schema::idref find, ::xml_schema::idref replace)
	{
		return if (element->technique() == find) element->technique() = replace;
	}

	template<class MatML>
	::xml_schema::idref Replace_Source(MatML* element, ::xml_schema::idref find, ::xml_schema::idref replace)
	{
		return if (element->source() == find) element->source() = replace;
	}

	template<class MatML>
	::xml_schema::idref Replace_Specimen(MatML* element, ::xml_schema::idref find, ::xml_schema::idref replace)
	{
		return if (element->specimen() == find) element->specimen() = replace;
	}

	template<class MatML>
	::xml_schema::idref Replace_Test(MatML* element, ::xml_schema::idref find, ::xml_schema::idref replace)
	{
		return if (element->test() == find) element->test() = replace;
	}

	template<class MatML>
	::xml_schema::idref Replace_Id(MatML* element, ::xml_schema::idref find, ::xml_schema::idref replace)
	{
		return if (element->id() == find) element->id() = replace;
	}

};//namespace bellshire

#include "bellshire/BT_MatML_has_a_idref.inl"
