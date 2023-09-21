#pragma once

#include "bellshire/BT_MatML_MatML_Doc.h"
//#include "bellshire/BT_MatML_MatML_Doc_GUI.h"
#include "bellshire/BT_MatML_Material.h"
#include "bellshire/BT_MatML_Metadata.h"

namespace bellshire
{
	template<class func_class>
	void MatML_Doc_Base::TraverseMatMLTree(
		observer_ptr < MatML_Doc> element,
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

			MatML_Doc::Material_sequence& (MatML_Doc:: * structural_cont_func1)() = &MatML_Doc::Material;

			SetUpChildSequence<MatML_Doc,
				Material,
				MatML_Doc::Material_sequence,
				Material_Base,
				func_class
			>(element, structural_cont_func1, next_func, recursive);


			MatML_Doc::Metadata_optional& (MatML_Doc:: * structural_cont_func2)() = &MatML_Doc::Metadata;

			SetUpChildOptional<MatML_Doc,
				Metadata,
				MatML_Doc::Metadata_optional,
				Metadata_Base,
				func_class
			>(element, structural_cont_func2, next_func, recursive);
		}

	}

};//end bellshire namespace
