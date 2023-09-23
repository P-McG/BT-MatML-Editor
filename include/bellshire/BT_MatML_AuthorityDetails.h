#pragma once

#include "bellshire/matml31.hxx"
#include "bellshire/BT_MatML_MatML_Base.h"

namespace bellshire
{
	class AuthorityDetails_Base : public MatML_Base
	{
	public:
		AuthorityDetails_Base() {};
		virtual ~AuthorityDetails_Base() {};

		template<class func_class>
		static void TraverseMatMLTree(
			const observer_ptr<AuthorityDetails> Element,
			func_class& func,
			RecursiveFlags recursive = {}
		);
	};

};//end namespace bellshire

#include "bellshire/BT_MatML_AuthorityDetails.inl"



