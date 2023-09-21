#pragma once

#include "bellshire/matml31.hxx"
#include "bellshire/BT_MatML_DataSourceDetails.h"
#include "bellshire/BT_MatML_Name.h"
#include "bellshire/BT_MatML_Notes.h"

namespace bellshire
{
	template<class func_class>
	void DataSourceDetails_Base::TraverseMatMLTree(
		observer_ptr<DataSourceDetails> element,
		func_class& func,
		RecursiveFlags recursive
	)
	{
		func.operator()(element);//Setup current
		func_class next_func(func);//Setup child

		if (recursive.empty() //default
			|| (!recursive.empty() && recursive.front())
			) {
			if (!recursive.empty()) recursive.pop_front();

			SetUpChild<DataSourceDetails,
				Name,
				DataSourceDetails::Name_type,
				Name_Base,
				func_class
			>(element, &DataSourceDetails::Name, next_func, recursive);


			DataSourceDetails::Notes_optional& (DataSourceDetails:: * structural_cont_func2)() = &DataSourceDetails::Notes;

			SetUpChildOptional<DataSourceDetails,
				Notes,
				DataSourceDetails::Notes_optional,
				Notes_Base,
				func_class
			>(element, structural_cont_func2, next_func, recursive);
		}
	}

};//end bellshire namespace


