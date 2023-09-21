#pragma once

#include "bellshire/matml31.hxx"
#include "bellshire/BT_MatML_Form.h"
#include "bellshire/BT_MatML_Description.h"
#include "bellshire/BT_MatML_Name.h"
#include "bellshire/BT_MatML_Geometry.h"
#include "bellshire/BT_MatML_Notes.h"

namespace bellshire
{
	template<class func_class>
	void Form_Base::TraverseMatMLTree(
		observer_ptr<Form> element,
		func_class& func,
		RecursiveFlags recursive
	)
	{
		func.operator()(element);//Setup current
		func_class next_func(func);//Setup child

		if (recursive.empty() //default
			|| (!recursive.empty() && recursive.front())
			) {
			if (!recursive.empty()) recursive.pop_front();


			SetUpChild<Form,
				Name,
				Form::Description_type,
				Description_Base,
				func_class
			>(element, &Form::Description, next_func, recursive);


			Form::Geometry_optional& (Form:: * structural_cont_func2)() = &Form::Geometry;

			SetUpChildOptional<Form,
				Geometry,
				Form::Geometry_optional,
				Geometry_Base,
				func_class
			>(element, structural_cont_func2, next_func, recursive);


			Form::Notes_optional& (Form:: * structural_cont_func3)() = &Form::Notes;

			SetUpChildOptional<Form,
				Notes,
				Form::Notes_optional,
				Notes_Base,
				func_class
			>(element, structural_cont_func3, next_func, recursive);
		}
	}

};//end bellshire namespace


