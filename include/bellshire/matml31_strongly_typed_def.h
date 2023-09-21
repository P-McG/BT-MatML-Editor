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


#include <type_traits>

#include <boost/serialization/strong_typedef.hpp>

#include <boost/config.hpp>
#include <boost/operators.hpp>
#include <boost/type_traits/has_nothrow_assign.hpp>
#include <boost/type_traits/has_nothrow_constructor.hpp>
#include <boost/type_traits/has_nothrow_copy.hpp>

#include "bellshire/matml31.hxx"
#include "observer_ptr.h"


namespace bellshire {



//Breaks Strongtype to Weaktype linkage.
#ifndef STRONGLY_TYPED_DEF
//#define STRONGLY_TYPED_DEF(T, D) \
	//struct D : std::enable_shared_from_this<D>,\
	//	  boost::totally_ordered1< D, boost::totally_ordered2< D, T	> > \
	//{	\
	//	using strongly_typed = std::true_type; \
 //	    using D_ptr = observer_ptr<D>; \
 //	    using T_ptr = observer_ptr<T>; \
	//	using this_ptr = observer_ptr<D>; \
	//	using value_type = T_ptr; \
	//	T_ptr t; \
	//	explicit D(T_ptr t_) BOOST_NOEXCEPT_IF(boost::has_nothrow_copy_constructor<T>::value) : t((t_)) {} \
	//	D() BOOST_NOEXCEPT_IF(boost::has_nothrow_default_constructor<T>::value):t(nullptr) {}	\
	//	D( D_ptr t_) BOOST_NOEXCEPT_IF(boost::has_nothrow_copy_constructor<T>::value) {t = t_->t;} \
	//	template <typename V, typename U> inline bool is_equal(const observer_ptr<V>& v, const observer_ptr<U>& u) { return !t.owner_before(u) && !u.owner_before(v); } \
	//	D_ptr operator=( D_ptr rhs) BOOST_NOEXCEPT_IF(boost::has_nothrow_assign<T>::value) {auto tmp{ rhs.lock() };	if (tmp) t = tmp.get()->t; else	t = T_ptr(); return this->weak_from_this();} \
	//	D_ptr operator=( T_ptr rhs) BOOST_NOEXCEPT_IF(boost::has_nothrow_assign<T>::value) { t = (rhs); return this->weak_from_this();} \
	//	operator const T_ptr () const { return t; } \
	//	operator T_ptr () { return t; } \
	//	bool operator==(const D_ptr rhs) { auto tmp1 = rhs.lock(); return is_equal(t, tmp1->t); } \
	//	bool operator==(const T_ptr rhs) { return is_equal(t, rhs); } \
	//	void null() { t.reset(); } \
	//}
	//#endif


#define STRONGLY_TYPED_DEF(T, D) \
	struct D \
		: boost::totally_ordered1< D \
		, boost::totally_ordered2< D, T	> > \
	{					\
		using strongly_typed = std::true_type; \
 	    using D_ptr = observer_ptr<D>; \
 	    using T_ptr = observer_ptr<T>; \
		using this_ptr = observer_ptr<D>; \
		using value_type = T_ptr; \
		T_ptr t;			\
		explicit D(T_ptr t_) BOOST_NOEXCEPT_IF(boost::has_nothrow_copy_constructor<T>::value) : t((t_)) {} \
		D() BOOST_NOEXCEPT_IF(boost::has_nothrow_default_constructor<T>::value) : t(nullptr) {}	\
		D( D_ptr t_) BOOST_NOEXCEPT_IF(boost::has_nothrow_copy_constructor<T>::value) : t(t_->t) {} \
		D_ptr operator=( D_ptr rhs) BOOST_NOEXCEPT_IF(boost::has_nothrow_assign<T>::value) { t = (rhs)->t; return this_ptr(this); } \
		D_ptr operator=( T_ptr rhs) BOOST_NOEXCEPT_IF(boost::has_nothrow_assign<T>::value) { t = (rhs); return this_ptr(this); } \
		operator const T_ptr () const { return t; } \
		operator T_ptr () { return t; } \
		operator const T& () const { return *t; } \
		operator T& () { return *t; } \
		bool operator==(const D_ptr rhs) { return t == rhs->t; } \
		bool operator<(const D_ptr rhs) { return t < rhs->t; } \
		void null() { nullptr; } \
	}

#endif

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

	template<typename T, typename U = void>
	struct is_strongly_typed : std::false_type {};

	template<typename T>
	struct is_strongly_typed<T, std::void_t<typename T::strongly_typed> > : std::true_type {};

	template< typename T>
	/*inline */constexpr bool is_strongly_typed_v = is_strongly_typed<T>::value;

	/// <summary>
	/// 
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <param name="value"></param>
	/// <returns></returns>
	//template <typename T>
	//decltype(auto) remove_strongly_typed_on_observer_ptr_v(observer_ptr<T> value) {
	//	if constexpr (is_strongly_typed_v<T>) {
	//		const std::shared_ptr<T>& tmp = value.lock();
	//		return (tmp?tmp->t : decltype(tmp->t)());
	//	}
	//	else {
	//		return value;
	//	}
	//}

	//template <typename T>
	//decltype(auto) remove_strongly_typed_on_observer_ptr_v(observer_ptr<T> value) {
	//	if constexpr (is_strongly_typed_v<T>) {
	//		const std::shared_ptr<T>& tmp = value.lock();
	//		return (tmp?tmp->t : decltype(tmp->t)());
	//	}
	//	else {
	//		return value;
	//	}
	//}

	/// <summary>
/// 
/// </summary>
/// <typeparam name="T"></typeparam>
/// <param name="value"></param>
/// <returns></returns>
	template <typename T>
	decltype(auto) remove_strongly_typed_on_observer_ptr_v(observer_ptr<T> value) {
		if constexpr (is_strongly_typed_v<T>) {
			return value->t;
		}
		else {
			return value;
		}
	}

	//template <typename T>
	//struct remove_strongly_typed_on_observer_ptr_ {
	//	using type = typename
	//		std::remove_pointer_t<
	//		std::remove_const_t<
	//		std::remove_reference_t<
	//		decltype(remove_strongly_typed_on_observer_ptr_v<T>( std::declval<observer_ptr<T> >()))
	//		>
	//		>
	//		>;
	//};

	template <typename T>
	struct remove_strongly_typed_on_observer_ptr_ {
		using type = typename
			std::remove_pointer_t<
			std::remove_const_t<
			std::remove_reference_t<
			decltype(remove_strongly_typed_on_observer_ptr_v<T>(std::declval<T*>()))
			>
			>
			>;
	};

	//template <typename T>
	//using remove_strongly_typed_on_observer_ptr_t = typename remove_strongly_typed_on_observer_ptr_<T>::type;

	template <typename T>
	using remove_strongly_typed_on_observer_ptr_t = typename remove_strongly_typed_on_observer_ptr_<T>::type;


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

	STRONGLY_TYPED_DEF(GlossaryTerm::Definition_type, Definition);
	STRONGLY_TYPED_DEF(GlossaryTerm::Abbreviation_type, Abbreviation);
	STRONGLY_TYPED_DEF(GlossaryTerm::Synonym_type, Synonym);
	STRONGLY_TYPED_DEF(Geometry::Shape_type, Shape);
	STRONGLY_TYPED_DEF(Geometry::Dimensions_type, Dimensions);
	STRONGLY_TYPED_DEF(Geometry::Orientation_type, Orientation);
	STRONGLY_TYPED_DEF(ProcessingDetails::Result_type, Result);
	STRONGLY_TYPED_DEF(Class::ParentSubClass_type, ParentSubClass);
	STRONGLY_TYPED_DEF(Form::Description_type, Description); // Form::Description is Name.  Use Name instead;
	STRONGLY_TYPED_DEF(BulkDetails::Subclass_type, Subclass);
	STRONGLY_TYPED_DEF(ComponentDetails::Subclass_type, Subclass1);

}//namespace bellshire
