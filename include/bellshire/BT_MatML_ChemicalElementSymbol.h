#pragma once

#include "bellshire/matml31.hxx"
#include "bellshire/BT_MatML_MatML_Base.h"

namespace bellshire
{
	class ChemicalElementSymbol_Base : public MatML_Base
	{
	public:
		ChemicalElementSymbol_Base() {};
		virtual ~ChemicalElementSymbol_Base() {};

		template<class func_class>
		static void TraverseMatMLTree(
			const observer_ptr<ChemicalElementSymbol> Element,
			func_class& func,
			RecursiveFlags recursive = {}
		);
	};

};//end namespace bellshire

#include "bellshire/BT_MatML_ChemicalElementSymbol.inl"



