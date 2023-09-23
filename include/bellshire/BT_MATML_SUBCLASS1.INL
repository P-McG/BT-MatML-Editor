#pragma once

#include "bellshire/matml31.hxx"
#include "bellshire/BT_MatML_Subclass1.h"
#include "bellshire/BT_MatML_Name.h"
#include "bellshire/BT_MatML_ParentMaterial.h"
#include "bellshire/BT_MatML_ParentSubClass.h"

namespace bellshire
{
	template<class func_class>
	void Subclass1_Base::TraverseMatMLTree(
		const observer_ptr < ComponentDetails::Subclass_type > element,
		func_class& func,
		RecursiveFlags recursive
	)
	{
		////Convert from a weakly typed to a strongly typed required by specialization of the functor
		// auto& element_observer = std::make_shared<Subclass1>(element);

		func.operator()(element);//Setup current
		func_class next_func(func);

		if (recursive.empty() //default
			|| (!recursive.empty() && recursive.front())
			) {
			if (!recursive.empty()) recursive.pop_front();


			ComponentDetails::Subclass_type::Name_optional& (ComponentDetails::Subclass_type:: * structural_cont_func1)() = &ComponentDetails::Subclass_type::Name;

			SetUpChildOptional<ComponentDetails::Subclass_type,
				Name,
				ComponentDetails::Subclass_type::Name_optional,
				Name_Base,
				func_class
			>(element, structural_cont_func1, next_func, recursive);



			ComponentDetails::Subclass_type::ParentMaterial_sequence& (ComponentDetails::Subclass_type:: * structural_cont_func2)() = &ComponentDetails::Subclass_type::ParentMaterial;

			SetUpChildSequence<ComponentDetails::Subclass_type,
				ParentMaterial,
				ComponentDetails::Subclass_type::ParentMaterial_sequence,
				ParentMaterial_Base,
				func_class
			>(element, structural_cont_func2, next_func, recursive);


			ComponentDetails::Subclass_type::ParentSubClass_sequence& (ComponentDetails::Subclass_type:: * structural_cont_func3)() = &ComponentDetails::Subclass_type::ParentSubClass;

			SetUpChildSequence<ComponentDetails::Subclass_type,
				ParentSubClass,
				ComponentDetails::Subclass_type::ParentSubClass_sequence,
				ParentSubClass_Base,
				func_class
			>(element, structural_cont_func3, next_func, recursive);
		}
	}

};//end bellshire namespace


