#pragma once

#include "bellshire/matml31.hxx"
#include "bellshire/BT_MatML_MatML_Base.h"

namespace bellshire
{
	class Associate_Base : public MatML_Base
	{
	public:
		Associate_Base() {};
		virtual ~Associate_Base() {};

		template<class func_class>
		static void TraverseMatMLTree(
			const observer_ptr<Associate> Element,
			func_class& func,
			RecursiveFlags recursive = {}
		);
	};

};//end namespace bellshire

#include "bellshire/BT_MatML_Associate.inl"


