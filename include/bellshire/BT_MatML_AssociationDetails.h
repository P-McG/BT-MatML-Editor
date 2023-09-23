#pragma once
#pragma once

#include "bellshire/matml31.hxx"
#include "bellshire/BT_MatML_MatML_Base.h"

namespace bellshire
{
	class AssociationDetails_Base : public MatML_Base
	{
	public:
		AssociationDetails_Base() {};
		virtual ~AssociationDetails_Base() {};

		template<class func_class>
		static void TraverseMatMLTree(
			const observer_ptr<AssociationDetails> Element,
			func_class& func,
			RecursiveFlags recursive = {}
		);
	};

};//end namespace bellshire

#include "bellshire/BT_MatML_AssociationDetails.inl"


