#pragma once

#include "bellshire/matml31.hxx"
#include "bellshire/BT_MatML_AssociationDetails.h"
#include "bellshire/BT_MatML_Associate.h"
#include "bellshire/BT_MatML_Relationship.h"
#include "bellshire/BT_MatML_Notes.h"

namespace bellshire
{
	template<class func_class>
	void AssociationDetails_Base::TraverseMatMLTree(
		const observer_ptr<AssociationDetails> element,
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

			AssociationDetails::Associate_optional& (AssociationDetails:: * structural_cont_func1)() = &AssociationDetails::Associate;

			SetUpChildOptional<AssociationDetails,
				Associate,
				AssociationDetails::Associate_optional,
				Associate_Base,
				func_class
			>(element, structural_cont_func1, next_func, recursive);


			AssociationDetails::Relationship_optional& (AssociationDetails:: * structural_cont_func2)() = &AssociationDetails::Relationship;

			SetUpChildOptional<AssociationDetails,
				Relationship,
				AssociationDetails::Relationship_optional,
				Relationship_Base,
				func_class
			>(element, structural_cont_func2, next_func, recursive);


			AssociationDetails::Notes_optional& (AssociationDetails:: * structural_cont_func3)() = &AssociationDetails::Notes;

			SetUpChildOptional<AssociationDetails,
				Notes,
				AssociationDetails::Notes_optional,
				Notes_Base,
				func_class
			>(element, structural_cont_func3, next_func, recursive);
		}
	}

};//end bellshire namespace


