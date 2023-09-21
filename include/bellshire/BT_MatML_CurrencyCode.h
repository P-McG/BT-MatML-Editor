#pragma once

#include "bellshire/matml31.hxx"
#include "bellshire/BT_MatML_MatML_Base.h"

namespace bellshire
{
	class CurrencyCode_Base : public MatML_Base
	{
	public:
		CurrencyCode_Base() {};
		virtual ~CurrencyCode_Base() {};

		template<class func_class>
		static void TraverseMatMLTree(
			std::shared_ptr<CurrencyCode> Element,
			func_class& func,
			RecursiveFlags recursive = {}
		);
	};

};//end namespace bellshire

#include "bellshire/BT_MatML_CurrencyCode.inl"



