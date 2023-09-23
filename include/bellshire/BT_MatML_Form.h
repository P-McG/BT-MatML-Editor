#pragma once

#include "bellshire/matml31.hxx"
#include "bellshire/BT_MatML_MatML_Base.h"

namespace bellshire
{
	class Form_Base : public MatML_Base
	{
	public:
		Form_Base() {};
		virtual ~Form_Base() {};

		template<class func_class>
		static void TraverseMatMLTree(
			const observer_ptr<Form> element,
			func_class& func,
			RecursiveFlags recursive = {}
		);
	};

};//end namespace bellshire

#include "bellshire/BT_MatML_Form.inl"



