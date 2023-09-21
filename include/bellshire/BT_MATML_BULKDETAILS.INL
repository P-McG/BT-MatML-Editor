#pragma once
#include "bellshire/BT_MatML_BulkDetails.h"
#include "bellshire/BT_MatML_Name.h"
#include "bellshire/BT_MatML_Class.h"
#include "bellshire/BT_MatML_Subclass.h"
#include "bellshire/BT_MatML_Specification.h"
#include "bellshire/BT_MatML_Source.h"
#include "bellshire/BT_MatML_Form.h"
#include "bellshire/BT_MatML_ProcessingDetails.h"
#include "bellshire/BT_MatML_Characterization.h"
#include "bellshire/BT_MatML_PropertyData.h"
#include "bellshire/BT_MatML_Notes.h"

namespace bellshire
{
	template<class func_class>
	void BulkDetails_Base::TraverseMatMLTree(
		observer_ptr<BulkDetails> element,
		func_class& func,
		RecursiveFlags recursive
	)
	{
		func.operator()(element);
		func_class next_func(func);

		if ( recursive.empty() //default
			|| (!recursive.empty() && recursive.front())
			) {
			if(!recursive.empty()) recursive.pop_front();

			SetUpChild<BulkDetails,
				Name,
				BulkDetails::Name_type,
				Name_Base,
				func_class
			>(element, &BulkDetails::Name, next_func, recursive);


			BulkDetails::Class_sequence& (BulkDetails:: * structural_cont_func2)() = &BulkDetails::Class;

			SetUpChildSequence<BulkDetails,
				Class,
				BulkDetails::Class_sequence,
				Class_Base,
				func_class
			>(element, structural_cont_func2, next_func, recursive);


			//BulkDetails::Subclass_sequence& (BulkDetails:: * structural_cont_func3)() = &BulkDetails::Subclass;

			//SetUpChildSequence<BulkDetails,
			//	Subclass,
			//	BulkDetails::Subclass_sequence,
			//	Subclass_Base,
			//	func_class
			//>(element, structural_cont_func3, next_func, recursive);


			BulkDetails::Specification_sequence& (BulkDetails:: * structural_cont_func4)() = &BulkDetails::Specification;

			SetUpChildSequence<BulkDetails,
				Specification,
				BulkDetails::Specification_sequence,
				Specification_Base,
				func_class
			>(element, structural_cont_func4, next_func, recursive);


			BulkDetails::Source_optional& (BulkDetails:: * structural_cont_func5)() = &BulkDetails::Source;

			SetUpChildOptional<BulkDetails,
				Source,
				BulkDetails::Source_optional,
				Source_Base,
				func_class
			>(element, structural_cont_func5, next_func, recursive);


			BulkDetails::Form_optional& (BulkDetails:: * structural_cont_func6)() = &BulkDetails::Form;

			SetUpChildOptional<BulkDetails,
				Form,
				BulkDetails::Form_optional,
				Form_Base,
				func_class
			>(element, structural_cont_func6, next_func, recursive);


			BulkDetails::ProcessingDetails_sequence& (BulkDetails:: * structural_cont_func7)() = &BulkDetails::ProcessingDetails;

			SetUpChildSequence<BulkDetails,
				ProcessingDetails,
				BulkDetails::ProcessingDetails_sequence,
				ProcessingDetails_Base,
				func_class
			>(element, structural_cont_func7, next_func, recursive);


			BulkDetails::Characterization_optional& (BulkDetails:: * structural_cont_func8)() = &BulkDetails::Characterization;

			SetUpChildOptional<BulkDetails,
				Characterization,
				BulkDetails::Characterization_optional,
				Characterization_Base,
				func_class
			>(element, structural_cont_func8, next_func, recursive);


			BulkDetails::PropertyData_sequence& (BulkDetails:: * structural_cont_func9)() = &BulkDetails::PropertyData;

			SetUpChildSequence<BulkDetails,
				PropertyData,
				BulkDetails::PropertyData_sequence,
				PropertyData_Base,
				func_class
			>(element, structural_cont_func9, next_func, recursive);


			BulkDetails::Notes_optional& (BulkDetails:: * structural_cont_func10)() = &BulkDetails::Notes;

			SetUpChildOptional<BulkDetails,
				Notes,
				BulkDetails::Notes_optional,
				Notes_Base,
				func_class
			>(element, structural_cont_func10, next_func, recursive);

		}
	}

};//end bellshire namespace