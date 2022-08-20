/////////////////////////////////////////////////////////////////////////////
// Name:        matml31_strongtypedef.h
// Purpose:     Extension to the matml31.h classes to include strongtypesdef.
// Author:      Paul McGrath
// Modified by:
// Created:
// Copyright:   (c) Paul McGrath
// Licence:     CC licence
/////////////////////////////////////////////////////////////////////////////
#pragma once
#include "matml31.hxx"

#include <boost/serialization/strong_typedef.hpp>

#include <boost/config.hpp>
#include <boost/operators.hpp>
#include <boost/type_traits/has_nothrow_assign.hpp>
#include <boost/type_traits/has_nothrow_constructor.hpp>
#include <boost/type_traits/has_nothrow_copy.hpp>

namespace bellshire {

//Breaks Strongtype to Weaktype linkage.
#define STRONG_TYPEDEF(T, D)																												\
	struct D																																\
		: boost::totally_ordered1< D																										\
		, boost::totally_ordered2< D, T																										\
		> >																																	\
	{																																		\
		T* t;																																\
		explicit D(T* t_) BOOST_NOEXCEPT_IF(boost::has_nothrow_copy_constructor<T>::value) : t((t_)) {}					\
		D() BOOST_NOEXCEPT_IF(boost::has_nothrow_default_constructor<T>::value) : t(nullptr) {}												\
		D( D* t_) BOOST_NOEXCEPT_IF(boost::has_nothrow_copy_constructor<T>::value) : t(t_->t) {}										\
		D* operator=( D* rhs) BOOST_NOEXCEPT_IF(boost::has_nothrow_assign<T>::value) { t = (rhs)->t; return this; }		\
		D* operator=( T* rhs) BOOST_NOEXCEPT_IF(boost::has_nothrow_assign<T>::value) { t = (rhs); return this; }			\
		operator const T* () const { return t; }																							\
		operator T* () { return t; }						\
		operator const T& () const { return *t; }                                                                        \
		operator T& () { return *t; }                                                                                    \
		bool operator==(const D* rhs) { return t == rhs->t; }																				\
		bool operator<(const D* rhs) { return t < rhs->t; }																					\
		void null() { t = nullptr; }																										\
	};

	/// Operator < for Class::ParentSubClass_type
	/// <summary>
	/// This was required for the creation of the ParentSubClass strongtype
	/// </summary>
	/// <param name="lhs"></param>
	/// <param name="rhs"></param>
	/// <returns></returns>
	inline bool operator< (const Class::ParentSubClass_type& lhs, const Class::ParentSubClass_type& rhs) {
		const Class& lhs_mod(lhs);/// ParentSubClass_type is a typedef of Class
		const Class& rhs_mod(rhs);/// ParentSubClass_type is a typedef of Class
		return lhs_mod < rhs_mod;
	}


	/// Allows for the boost::any_cast to work with uniquely identify typedefs in the MatML Schema
	/* The following is an example of how to use the strong_type created by the strong_typedef.
		It is important to note that all the data contained in MatMLTreeItemData is destroyed/deleted by
		MatMLTreeItemData::~MatMLTreeItemData using individual delete functions like 
		DeleteStrongType<Shape>() so the use of new is required and any new strongtypes have to be added 
		to the delete MatMLTreeItemData::~MatMLTreeItemData function.
	 
		MatMLTreeItemData data = new MatMLTreeItemData(new Shape(MatML_Element));
		CurrentId = m_MatMLTreeCtrl->AppendItem(ParentId, str, -1, -1,  data );

		It should be noted that the strongtypes are used for selections and comparisions. Actual
		manipulation of MatML data is done using the MatML data types.

		e.g. Use Definition strongtype for comparisions and selection of the data from the
		MatMLTreeCtrl. Use GlossaryTerms::Definition_type for the manipulation of the 
		MatML data. If a comparision is required between the strongtype and the MatML type
		then use strongtype->t which is the MatML type encased within the strongtype.
	*/ 
	STRONG_TYPEDEF(GlossaryTerm::Definition_type, Definition);
	STRONG_TYPEDEF(GlossaryTerm::Abbreviation_type, Abbreviation);
	STRONG_TYPEDEF(GlossaryTerm::Synonym_type, Synonym);
	STRONG_TYPEDEF(Geometry::Shape_type, Shape);
	STRONG_TYPEDEF(Geometry::Dimensions_type, Dimensions);
	STRONG_TYPEDEF(Geometry::Orientation_type, Orientation);
	STRONG_TYPEDEF(ProcessingDetails::Result_type, Result);
	STRONG_TYPEDEF(Class::ParentSubClass_type, ParentSubClass);
	STRONG_TYPEDEF(Form::Description_type, Description); // Form::Description is Name.  Use Name instead;


}//namespace bellshire
