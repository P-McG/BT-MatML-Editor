#pragma once

#include "bellshire/matml31.hxx"
#include "bellshire/BT_MatML_PropertyData.h"
#include "bellshire/BT_MatML_Data1.h"
#include "bellshire/BT_MatML_Uncertainty.h"
#include "bellshire/BT_MatML_Qualifier.h"
#include "bellshire/BT_MatML_ParameterValue.h"
#include "bellshire/BT_MatML_Notes.h"

namespace bellshire
{
	template<class func_class>
	void PropertyData_Base::TraverseMatMLTree(
		observer_ptr < PropertyData > element,
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

			SetUpChild<PropertyData,
				Data1,
				PropertyData::Data_type,
				Data1_Base,
				func_class
			>(element, &PropertyData::Data, next_func, recursive);


			PropertyData::Uncertainty_sequence& (PropertyData:: * structural_cont_func2)() = &PropertyData::Uncertainty;

			SetUpChildSequence<PropertyData,
				Uncertainty,
				PropertyData::Uncertainty_sequence,
				Uncertainty_Base,
				func_class
			>(element, structural_cont_func2, next_func, recursive);


			PropertyData::Qualifier_sequence& (PropertyData:: * structural_cont_func3)() = &PropertyData::Qualifier;

			SetUpChildSequence<PropertyData,
				Qualifier,
				PropertyData::Qualifier_sequence,
				Qualifier_Base,
				func_class
			>(element, structural_cont_func3, next_func, recursive);


			PropertyData::ParameterValue_sequence& (PropertyData:: * structural_cont_func4)() = &PropertyData::ParameterValue;

			SetUpChildSequence<PropertyData,
				ParameterValue,
				PropertyData::ParameterValue_sequence,
				ParameterValue_Base,
				func_class
			>(element, structural_cont_func4, next_func, recursive);

			PropertyData::Notes_optional& (PropertyData:: * structural_cont_func5)() = &PropertyData::Notes;

			SetUpChildOptional<PropertyData,
				Notes,
				PropertyData::Notes_optional,
				Notes_Base,
				func_class
			>(element, structural_cont_func5, next_func, recursive);
		}
	}

};//end bellshire namespace

