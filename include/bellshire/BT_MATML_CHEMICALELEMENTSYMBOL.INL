#pragma once

#include "bellshire/matml31.hxx"
#include "bellshire/BT_MatML_ChemicalElementSymbol.h"

namespace bellshire
{
	template<class func_class>
	void ChemicalElementSymbol_Base::TraverseMatMLTree(
		std::shared_ptr<ChemicalElementSymbol> element,
		func_class& func,
		RecursiveFlags recursive
	)
	{
		func.operator()(element);//Setup current
	}

};//end bellshire namespace


