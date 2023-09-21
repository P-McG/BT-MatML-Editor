/////////////////////////////////////////////////////////////////////////////
// Name:        matml31_strongly_typed_def.h
// Purpose:     Extension to the matml31.h classes to include strongtypesdef.
// Author:      Paul McGrath
// Modified by:
// Created:
// Copyright:   (c) Paul McGrath
// Licence:     CC licence
/////////////////////////////////////////////////////////////////////////////
#pragma once
#include "bellshire/Lib/matml31_lib.hxx"

#include <boost/serialization/strong_typedef.hpp>

#include <boost/config.hpp>
#include <boost/operators.hpp>
#include <boost/type_traits/has_nothrow_assign.hpp>
#include <boost/type_traits/has_nothrow_constructor.hpp>
#include <boost/type_traits/has_nothrow_copy.hpp>

namespace bellshire {
	namespace Lib {

		//Breaks Strongtype to Weaktype linkage.
#ifndef STRONGLY_TYPED_DEF
#define STRONGLY_TYPED_DEF(T, D)	\
			{ \
	struct D																																\
		: boost::totally_ordered1< D																										\
		, boost::totally_ordered2< D, T																										\
		> >																																	\
	{					\
        typedef T* value_type;\
		using strongly_typed = std::true_type; \
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
#endif;

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
		/* The following is an example of how to use the strong_type created by the STRONGLY_TYPED_DEF.
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
		STRONGLY_TYPED_DEF(GlossaryTerm::Definition_type, Definition_lib);
		STRONGLY_TYPED_DEF(GlossaryTerm::Abbreviation_type, Abbreviation_lib);
		STRONGLY_TYPED_DEF(GlossaryTerm::Synonym_type, Synonym_lib);
		STRONGLY_TYPED_DEF(Geometry::Shape_type, Shape_lib);
		STRONGLY_TYPED_DEF(Geometry::Dimensions_type, Dimensions_lib);
		STRONGLY_TYPED_DEF(Geometry::Orientation_type, Orientation_lib);
		STRONGLY_TYPED_DEF(ProcessingDetails::Result_type, Result_lib);
		STRONGLY_TYPED_DEF(Class::ParentSubClass_type, ParentSubClass_lib);
		STRONGLY_TYPED_DEF(Form::Description_type, Description_lib); // Form::Description is Name.  Use Name instead;
		STRONGLY_TYPED_DEF(BulkDetails::Subclass_type, Subclass_lib);
		STRONGLY_TYPED_DEF(ComponentDetails::Subclass_type, Subclass1_lib);

	}//namespace lib
}//namespace bellshire
