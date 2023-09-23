#pragma once

#include "bellshire/BT_MatML_Class.h"

#pragma once

#include "bellshire/matml31.hxx"
#include "bellshire/BT_MatML_Class.h"
#include "bellshire/BT_MatML_Name.h"
#include "bellshire/BT_MatML_ParentMaterial.h"
#include "bellshire/BT_MatML_ParentSubClass.h"

namespace bellshire
{
	template<class func_class>
	void Class_Base::TraverseMatMLTree(
		const observer_ptr<Class> element,
		func_class& func,
		RecursiveFlags recursive
	)
	{
		func.operator()(element);//Setup current
		func_class next_func(func);//Setup child

		if (recursive.empty() //default
			|| (!recursive.empty() && recursive.front())
			) {
			if(!recursive.empty()) recursive.pop_front();

			Class::Name_optional& (Class:: * structural_cont_func2)() = &Class::Name;

			SetUpChildOptional<Class,
				Name,
				Class::Name_optional,
				Name_Base,
				func_class
			>(element, structural_cont_func2, next_func, recursive);


			Class::ParentMaterial_sequence& (Class:: * structural_cont_func3)() = &Class::ParentMaterial;

			SetUpChildSequence<Class,
				ParentMaterial,
				Class::ParentMaterial_sequence,
				ParentMaterial_Base,
				func_class
			>(element, structural_cont_func3, next_func, recursive);


			//Class::ParentSubClass_sequence& (Class:: * structural_cont_func4)() = &Class::ParentSubClass;

			//SetUpChildSequence<Class,
			//	ParentSubClass,
			//	Class::ParentSubClass_sequence,
			//	ParentSubClass_Base,
			//	func_class
			//>(element, structural_cont_func4, next_func, recursive);
		}

	}

};//end bellshire namespace

