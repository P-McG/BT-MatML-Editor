#pragma once

#include "bellshire/matml31.hxx"
#include "bellshire/BT_MatML_MatML_Base.h"

namespace bellshire
{
	class Notes_Base : public MatML_Base
	{
	public:
		Notes_Base() {};
		virtual ~Notes_Base() {};

		template<class func_class>
		static void TraverseMatMLTree(
			const observer_ptr < Notes > Element,
			func_class& func,
			RecursiveFlags recursive = {}
		);
	};

};//end namespace bellshire

#include "bellshire/BT_MatML_Notes.inl"



