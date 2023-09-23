#pragma once

#include "bellshire/matml31.hxx"
#include "bellshire/BT_MatML_MatML_Base.h"

namespace bellshire
{
	class ProcessingDetails_Base : public MatML_Base
	{
	public:
		ProcessingDetails_Base() {};
		virtual ~ProcessingDetails_Base() {};

		template<class func_class>
		static void TraverseMatMLTree(
			const observer_ptr < ProcessingDetails > Element,
			func_class& func,
			RecursiveFlags recursive = {}
		);
	};

};//end namespace bellshire

#include "bellshire/BT_MatML_ProcessingDetails.inl"



