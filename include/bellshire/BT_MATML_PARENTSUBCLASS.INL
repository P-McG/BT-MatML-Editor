#pragma once

#include "bellshire/matml31.hxx"
#include "bellshire/BT_MatML_ParentSubClass.h"
#include "bellshire/BT_MatML_Name.h"
#include "bellshire/BT_MatML_ParentMaterial.h"
#include "bellshire/BT_MatML_ParentSubClass.h"

namespace bellshire
{
	template<class func_class>
	void ParentSubClass_Base::TraverseMatMLTree(
		const observer_ptr < Class::ParentSubClass_type > element,
		func_class& func,
		RecursiveFlags recursive
	)
	{
		// auto& element_strongly_typed_shared = std::make_shared<ParentSubClass>(element);

		func.operator()(element);//Setup current
		func_class next_func(func);//Setup child


		Class::ParentSubClass_type::Name_optional& (Class::ParentSubClass_type:: * structural_cont_func1)() = &Class::ParentSubClass_type::Name;

		SetUpChildOptional<Class::ParentSubClass_type,
			Name,
			Class::ParentSubClass_type::Name_optional,
			Name_Base,
			func_class
		>(element, structural_cont_func1, next_func);


		Class::ParentSubClass_type::ParentMaterial_sequence& (Class::ParentSubClass_type:: * structural_cont_func2)() = &Class::ParentSubClass_type::ParentMaterial;

		SetUpChildSequence<Class::ParentSubClass_type,
			ParentMaterial,
			Class::ParentSubClass_type::ParentMaterial_sequence,
			ParentMaterial_Base,
			func_class
		>(element, structural_cont_func2, next_func);


		Class::ParentSubClass_type::ParentSubClass_sequence& (Class::ParentSubClass_type:: * structural_cont_func3)() = &Class::ParentSubClass_type::ParentSubClass;

		SetUpChildSequence<Class::ParentSubClass_type,
			ParentSubClass,
			Class::ParentSubClass_type::ParentSubClass_sequence,
			ParentSubClass_Base,
			func_class
		>(element, structural_cont_func3, next_func);
	}

};//end bellshire namespace


