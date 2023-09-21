#pragma once

#include "bellshire/matml31.hxx"
#include "bellshire/BT_MatML_Result.h"

namespace bellshire
{
	template<class func_class>
	void Result_Base::TraverseMatMLTree(
		std::shared_ptr < Result > element,
		func_class& func,
		RecursiveFlags recursive
	)
	{
		//Convert from a weaktype to a strongtype required by the specialization of this functor
		auto test = std::make_shared<Result>();
		test->operator=(element);//Why this works and not test=element is unknown.

		func.operator()(test);//Setup current
	}

};//end bellshire namespace


