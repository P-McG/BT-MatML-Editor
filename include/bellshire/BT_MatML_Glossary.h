#pragma once

#include "bellshire/matml31.hxx"
#include "bellshire/BT_MatML_MatML_Base.h"

namespace bellshire
{

	class Glossary_Base : public MatML_Base
	{
	public:
		Glossary_Base() {};
		virtual ~Glossary_Base() {};

		template<class func_class>
		static void TraverseMatMLTree(
			const observer_ptr<Glossary> Element,
			func_class& func,
			RecursiveFlags recursive = {}
			);

	};

}//end namespace bellshire

#include "bellshire/BT_MatML_Glossary.inl"