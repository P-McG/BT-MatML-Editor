#pragma once

#include <list>
#include <utility>

#include "bellshire/matml31.hxx"
#include "bellshire/matml31_strongly_typed_def.h"
#include "observer_ptr.h"

namespace bellshire {

	using RecursiveFlags = ::std::list<bool>;

	class MatML_Base
	{
	public:
		MatML_Base() {};
		virtual ~MatML_Base() {};

		template<class Parent,
			class Child,
			class Child_cont,
			class Child_MatML_Base,
			class func_class
		>
		static void SetUpChild(
			observer_ptr<Parent> element,
			Child_cont& (Parent::* cont_func)(),
			func_class& func,
			RecursiveFlags recursive = {}
		);

		template<class Parent,
			class Child,
			class Child_cont,
			class Child_MatML_Base,
			class func_class
		>
		static void SetUpChildOptional(
			observer_ptr<Parent> Element,
			Child_cont& (Parent::* cont_func)(),
			func_class& func,
			RecursiveFlags recursive = {}
		);

		template<class Parent,
			class Child,
			class Child_cont,
			class Child_MatML_Base,
			class func_class
		>
		static void SetUpChildSequence(
			observer_ptr<Parent> Element,
			Child_cont& (Parent::* cont_func)(),
			func_class& func,
			RecursiveFlags recursive = {}
		);

		template<typename MatML_ContClass >
		static void  DeleteChild(MatML_ContClass& MatML);

		template<typename MatML_ContClass >
		static void DeleteContChild(MatML_ContClass& MatML_Cont);

		template<typename MatML_Class, typename MatML_ContClass>
		static void DeleteSeqContChild(observer_ptr < MatML_Class > MatML, MatML_ContClass& MatML_Cont);

		template<typename MatML_Class, typename MatML_ContClass>
		static void PasteChild(observer_ptr<MatML_Class> element, MatML_ContClass& MatML_Cont);

		template<typename MatML_Class, typename MatML_ContClass>
		static void PasteContChild(observer_ptr<MatML_Class> MatML, MatML_ContClass& MatML_Cont);

		template<typename MatML_Class, typename MatML_ContClass>
		static void PasteSeqContChild(observer_ptr<MatML_Class> MatML, MatML_ContClass& MatML_Cont);

		template<typename MatML_Class, typename MatML_ContClass >
		static void InsertChild(MatML_ContClass& MatML_Cont);

		template<typename MatML_Class, typename MatML_ContClass >
		static void InsertContChild(MatML_ContClass& MatML_Cont);

		template<typename MatML_Class, typename MatML_ContClass >
		static void InsertSeqContChild(MatML_ContClass& MatML_Cont);

		template<class MatML_Class>
		static void Swap(observer_ptr < MatML_Class >& matml0, observer_ptr < MatML_Class >& matml1);

		template<class MatML_Class>
		static void SwapHavingId(observer_ptr<MatML_Class>& matml0, observer_ptr<MatML_Class>& matml1);

		template<class MatML_Class>
		static void SwapHavingOptionalId(observer_ptr<MatML_Class>& matml0, observer_ptr<MatML_Class>& matml1);

		template< 
			class MatML_ContClass,
			class MatML_Class = typename MatML_ContClass::value_type
		>
		static decltype(auto)
			FindAndBumpUp(const observer_ptr<MatML_Class> matml, MatML_ContClass& cont);

		template<
			class MatML_ContClass,
			class MatML_Class = typename MatML_ContClass::value_type
		>
		static std::pair<observer_ptr<MatML_Class>, observer_ptr<MatML_Class> >
			FindAndBumpUpHavingId(const observer_ptr<MatML_Class> element, MatML_ContClass& cont);

		template<
			class MatML_ContClass,
			class MatML_Class = typename MatML_ContClass::value_type
		>
		static decltype(auto)
			FindAndBumpUpHavingOptionalId(const observer_ptr<MatML_Class> element, MatML_ContClass& cont);

		template<
			class MatML_ContClass,
			class MatML_Class = typename MatML_ContClass::value_type
		>
		static decltype(auto)
			FindAndBumpDown(const observer_ptr<MatML_Class>& matml, MatML_ContClass& cont);

		template< 
			class MatML_ContClass,
			class MatML_Class = typename MatML_ContClass::value_type
		>
		std::pair<observer_ptr<MatML_Class>, observer_ptr<MatML_Class> >
			FindAndBumpDownHavingId(const observer_ptr<MatML_Class> matml, MatML_ContClass& cont);

		template<
			class MatML_ContClass,
			class MatML_Class = typename MatML_ContClass::value_type
		>
		static decltype(auto)
			FindAndBumpDownHavingOptionalId(const observer_ptr<MatML_Class> element, MatML_ContClass& cont);

	};

};//end namespace bellshire

#include "bellshire/BT_MatML_MatML_Base.inl"