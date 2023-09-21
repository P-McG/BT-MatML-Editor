#pragma once

#include "bellshire/matml31.hxx"
#include "bellshire/matml31_strongly_typed_def.h"
#include "bellshire/BT_MatML_Subclass.h"
#include "bellshire/BT_MatML_Name.h"
#include "bellshire/BT_MatML_ParentMaterial.h"
#include "bellshire/BT_MatML_ParentSubClass.h"

namespace bellshire
{
	//template<class func_class>
	//void Subclass_Base::TraverseMatMLTree(Subclass* element,
	//	func_class& func,
	//	RecursiveFlags recursive
	//)
	template<class func_class>
	void Subclass_Base::TraverseMatMLTree(
		observer_ptr < Class::ParentSubClass_type > element,
		func_class& func,
		RecursiveFlags recursive
	)	
	{
		//Convert from a weaktype to a strongtype required by specialization of the functor
		 auto element_strongly_typed = std::make_shared<Subclass>(element);

		func.operator()(element_strongly_typed.get());//Setup current
		func_class next_func(func);

		if (recursive.empty() //default
			|| (!recursive.empty() && recursive.front())
			) {
			if (!recursive.empty()) recursive.pop_front();


			BulkDetails::Subclass_type::Name_optional& (BulkDetails::Subclass_type:: * structural_cont_func1)() = &BulkDetails::Subclass_type::Name;

			SetUpChildOptional<BulkDetails::Subclass_type,
				Name,
				BulkDetails::Subclass_type::Name_optional,
				Name_Base,
				func_class
			>(element, structural_cont_func1, next_func, recursive);


			BulkDetails::Subclass_type::ParentMaterial_sequence& (BulkDetails::Subclass_type:: * structural_cont_func2)() = &BulkDetails::Subclass_type::ParentMaterial;

			SetUpChildSequence<BulkDetails::Subclass_type,
				ParentMaterial,
				BulkDetails::Subclass_type::ParentMaterial_sequence,
				ParentMaterial_Base,
				func_class
			>(element, structural_cont_func2, next_func, recursive);


			BulkDetails::Subclass_type::ParentSubClass_sequence& (BulkDetails::Subclass_type:: * structural_cont_func3)() = &BulkDetails::Subclass_type::ParentSubClass;

			SetUpChildSequence<BulkDetails::Subclass_type,
				ParentSubClass,
				BulkDetails::Subclass_type::ParentSubClass_sequence,
				ParentSubClass_Base,
				func_class
			>(element, structural_cont_func3, next_func, recursive);
		}
	}

};//end bellshire namespace


