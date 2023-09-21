#pragma once

#include "bellshire/matml31.hxx"
#include "bellshire/BT_MatML_AuthorityDetails.h"
#include "bellshire/BT_MatML_Name.h"
#include "bellshire/BT_MatML_Notes.h"

namespace bellshire
{
	template<class func_class>
	void AuthorityDetails_Base::TraverseMatMLTree(
		observer_ptr<AuthorityDetails> element,
		func_class& func, 
		RecursiveFlags recursive
	)
	{
		func.operator()(element);// Setup current
		func_class next_func(func);// Setup child

		if (recursive.empty() //default
			|| (!recursive.empty() && recursive.front())
			) {
			if (!recursive.empty()) recursive.pop_front();

			SetUpChild<AuthorityDetails,
				Name,
				AuthorityDetails::Name_type,
				Name_Base,
				func_class
			>(element, &AuthorityDetails::Name, next_func, recursive);


			AuthorityDetails::Notes_optional& (AuthorityDetails:: * structural_cont_func2)() = &AuthorityDetails::Notes;

			SetUpChildOptional<AuthorityDetails,
				Notes,
				AuthorityDetails::Notes_optional,
				Notes_Base,
				func_class
			>(element, structural_cont_func2, next_func, recursive);
		}
	}

};//end bellshire namespace


