#pragma once
#include "bellshire/matml31.hxx"
#include "bellshire/matml31_strongly_typed_def.h"
#include <type_traits>

//List all the members that are a idref.
namespace bellshire::utilities
{

	template<typename T, typename U = void>
	struct has_idref_type : std::false_type {};

	template<typename T>
	struct has_idref_type<T, std::void_t<typename T::authority_type> > : std::true_type {};

	template<typename T>
	struct has_idref_type<T, std::void_t<typename T::parameter_type> > : std::true_type {};

	template<typename T>
	struct has_idref_type<T, std::void_t<typename T::property_type> > : std::true_type {};

	template<typename T>
	struct has_idref_type<T, std::void_t<typename T::technique_type> > : std::true_type {};

	template<typename T>
	struct has_idref_type<T, std::void_t<typename T::source_type> > : std::true_type {};

	template<typename T>
	struct has_idref_type<T, std::void_t<typename T::specimen_type> > : std::true_type {};

	template<typename T>
	struct has_idref_type<T, std::void_t<typename T::test_type> > : std::true_type {};

	template<typename T>
	struct has_idref_type<T, std::void_t<typename T::id_type> > : std::true_type {};


	//break down to the idividual types

	//authority
	template<typename T, typename U = void>
	struct has_authority_type : ::std::false_type {};

	template<typename T>
	struct has_authority_type<T, ::std::void_t<typename T::authority_type> > : ::std::true_type {};

	template<typename T, typename U = void>
	struct has_authority_optional : ::std::false_type {};

	template<typename T>
	struct has_authority_optional<T, ::std::void_t<typename T::authority_optional> > : ::std::true_type {};

	//parameter
	template<typename T, typename U = void>
	struct has_parameter_type : std::false_type {};

	template<typename T>
	struct has_parameter_type<T, std::void_t<typename T::parameter_type> > : std::true_type {};

	//property
	template<typename T, typename U = void>
	struct has_property_type : std::false_type {};

	template<typename T>
	struct has_property_type<T, std::void_t<typename T::property_type> > : std::true_type {};

	//technique
	template<typename T, typename U = void>
	struct has_technique_type : std::false_type {};

	template<typename T>
	struct has_technique_type<T, std::void_t<typename T::technique_type> > : std::true_type {};

	template<typename T, typename U = void>
	struct has_technique_optional : ::std::false_type {};

	template<typename T>
	struct has_technique_optional<T, std::void_t<typename T::technique_optional> > : std::true_type {};

	//source
	template<typename T, typename U = void>
	struct has_source_type : std::false_type {};

	template<typename T>
	struct has_source_type<T, std::void_t<typename T::source_type> > : std::true_type {};

	template<typename T, typename U = void>
	struct has_source_optional : ::std::false_type {};

	template<typename T>
	struct has_source_optional<T, std::void_t<typename T::source_optional> > : std::true_type {};

	//specimen
	template<typename T, typename U = void>
	struct has_specimen_type : std::false_type {};

	template<typename T>
	struct has_specimen_type<T, std::void_t<typename T::specimen_type> > : std::true_type {};

	template<typename T, typename U = void>
	struct has_specimen_optional : ::std::false_type {};

	template<typename T>
	struct has_specimen_optional<T, std::void_t<typename T::specimen_optional> > : std::true_type {};

	//test
	template<typename T, typename U = void>
	struct has_test_type : std::false_type {};

	template<typename T>
	struct has_test_type<T, std::void_t<typename T::test_type> > : std::true_type {};

	template<typename T, typename U = void>
	struct has_test_optional : ::std::false_type {};

	template<typename T>
	struct has_test_optional<T, std::void_t<typename T::test_optional> > : std::true_type {};

	//id
	template<typename T, typename U = void>
	struct has_id_type : std::false_type {};

	template<typename T>
	struct has_id_type<T, std::void_t<typename T::id_type> > : std::true_type {};

	template<typename T, typename U = void>
	struct has_id_optional : ::std::false_type {};

	template<typename T>
	struct has_id_optional<T, std::void_t<typename T::id_optional> > : std::true_type {};




};//namespace bellshire

#include "bellshire/utilities/BT_MatML_has_a_idref.inl"
