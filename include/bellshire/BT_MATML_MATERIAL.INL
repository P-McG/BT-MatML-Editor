#pragma once

#include "bellshire/matml31.hxx"
#include "bellshire/BT_MatML_Material.h"
#include "bellshire/BT_MatML_BulkDetails.h"
#include "bellshire/BT_MatML_ComponentDetails.h"
#include "bellshire/BT_MatML_Glossary.h"
#include "bellshire/BT_MatML_Graphs.h"

namespace bellshire
{
	template<class func_class>
	void Material_Base::TraverseMatMLTree(
		const observer_ptr < Material > element,
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

			SetUpChild<Material,
				BulkDetails,
				Material::BulkDetails_type,
				BulkDetails_Base,
				func_class
			>(element, &Material::BulkDetails, next_func, recursive);


			Material::ComponentDetails_sequence& (Material:: * structural_cont_func2)() = &Material::ComponentDetails;

			SetUpChildSequence<Material,
				ComponentDetails,
				Material::ComponentDetails_sequence,
				ComponentDetails_Base,
				func_class
			>(element, structural_cont_func2, next_func, recursive);


			Material::Graphs_optional& (Material:: * structural_cont_func3)() = &Material::Graphs;

			SetUpChildOptional<Material,
				Graphs,
				Material::Graphs_optional,
				Graphs_Base,
				func_class
			>(element, structural_cont_func3, next_func, recursive);


			Material::Glossary_optional& (Material:: * structural_cont_func4)() = &Material::Glossary;

			SetUpChildOptional<Material,
				Glossary,
				Material::Glossary_optional,
				Glossary_Base,
				func_class
			>(element, structural_cont_func4, next_func, recursive);
		}
	}

};//end bellshire namespace

