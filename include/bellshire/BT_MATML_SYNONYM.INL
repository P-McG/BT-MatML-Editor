#pragma once

#include "bellshire/matml31.hxx"
#include "bellshire/BT_MatML_Synonym.h"
#include "bellshire/BT_MatML_BulkDetails.h"
#include "bellshire/BT_MatML_ComponentDetails.h"
#include "bellshire/BT_MatML_Glossary.h"
#include "bellshire/BT_MatML_Graphs.h"

namespace bellshire
{
	template<class func_class>
	void Synonym_Base::TraverseMatMLTree(
		observer_ptr < GlossaryTerm::Synonym_type > element,
		func_class& func,
		RecursiveFlags recursive
	)
	{
		//Convert to a strongly typed required by specialization of the functor
		observer_ptr<Synonym> test = std::make_shared<Synonym>(element).get();

		func.operator()(test);//Setup current
	}

};//end bellshire namespace


