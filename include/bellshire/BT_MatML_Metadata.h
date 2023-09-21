#pragma once

#include "bellshire/matml31.hxx"
#include "bellshire/BT_MatML_MatML_Base.h"

namespace bellshire
{
	class Metadata_Base : public MatML_Base
	{
	public:
		Metadata_Base() {};
		virtual ~Metadata_Base() {};

		template<class func_class>
		static void TraverseMatMLTree(
			observer_ptr<Metadata> element,
			func_class& func,
			RecursiveFlags recursive = {}
		);
	};

};//end namespace bellshire

#include "bellshire/BT_MatML_Metadata.inl"


