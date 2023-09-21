#pragma once

#include "bellshire/matml31.hxx"
#include "bellshire/BT_MatML_ComponentDetails.h"
#include "bellshire/BT_MatML_Name.h"
#include "bellshire/BT_MatML_Class.h"
#include "bellshire/BT_MatML_Subclass.h"
#include "bellshire/BT_MatML_Specification.h"
#include "bellshire/BT_MatML_Source.h"
#include "bellshire/BT_MatML_Form.h"
#include "bellshire/BT_MatML_ProcessingDetails.h"
#include "bellshire/BT_MatML_Characterization.h"
#include "bellshire/BT_MatML_PropertyData.h"
#include "bellshire/BT_MatML_AssociationDetails.h"
//#include "bellshire/BT_MatML_ComponentDetails1.h"

namespace bellshire
{
	template<class MatML_Class, class func_class>
	void ComponentDetails_Base::TraverseMatMLTree(
		observer_ptr<MatML_Class> element,
		func_class& func,
		RecursiveFlags recursive
	)
	{
		func.operator()(element);//Setup current
		func_class next_func(func);// Setup child

		if (recursive.empty() //default
			|| (!recursive.empty() && recursive.front())
			) {
			if(!recursive.empty()) recursive.pop_front();

			SetUpChild<ComponentDetails,
				Name,
				ComponentDetails::Name_type,
				Name_Base,
				func_class
			>(element, &ComponentDetails::Name, next_func, recursive);


			ComponentDetails::Class_sequence& (ComponentDetails:: * structural_cont_func2)() = &ComponentDetails::Class;

			SetUpChildSequence<ComponentDetails,
				Class,
				ComponentDetails::Class_sequence,
				Class_Base,
				func_class
			>(element, structural_cont_func2, next_func, recursive);


			//ComponentDetails::Subclass_sequence& (ComponentDetails:: * structural_cont_func3)() = &ComponentDetails::Subclass;

			//SetUpChildSequence<ComponentDetails,
			//	Subclass,
			//	ComponentDetails::Subclass_sequence,
			//	Subclass_Base,
			//	func_class
			//>(element, structural_cont_func3, next_func, recursive);


			ComponentDetails::Specification_sequence& (ComponentDetails:: * structural_cont_func4)() = &ComponentDetails::Specification;

			SetUpChildSequence<ComponentDetails,
				Specification,
				ComponentDetails::Specification_sequence,
				Specification_Base,
				func_class
			>(element, structural_cont_func4, next_func, recursive);


			ComponentDetails::Source_optional& (ComponentDetails:: * structural_cont_func5)() = &ComponentDetails::Source;

			SetUpChildOptional<ComponentDetails,
				Source,
				ComponentDetails::Source_optional,
				Source_Base,
				func_class
			>(element, structural_cont_func5, next_func, recursive);


			ComponentDetails::Form_optional& (ComponentDetails:: * structural_cont_func6)() = &ComponentDetails::Form;

			SetUpChildOptional<ComponentDetails,
				Form,
				ComponentDetails::Form_optional,
				Form_Base,
				func_class
			>(element, structural_cont_func6, next_func, recursive);


			ComponentDetails::ProcessingDetails_sequence& (ComponentDetails:: * structural_cont_func7)() = &ComponentDetails::ProcessingDetails;

			SetUpChildSequence<ComponentDetails,
				ProcessingDetails,
				ComponentDetails::ProcessingDetails_sequence,
				ProcessingDetails_Base,
				func_class
			>(element, structural_cont_func7, next_func, recursive);


			ComponentDetails::Characterization_optional& (ComponentDetails:: * structural_cont_func8)() = &ComponentDetails::Characterization;

			SetUpChildOptional<ComponentDetails,
				Characterization,
				ComponentDetails::Characterization_optional,
				Characterization_Base,
				func_class
			>(element, structural_cont_func8, next_func, recursive);


			ComponentDetails::PropertyData_sequence& (ComponentDetails:: * structural_cont_func9)() = &ComponentDetails::PropertyData;

			SetUpChildSequence<ComponentDetails,
				PropertyData,
				ComponentDetails::PropertyData_sequence,
				PropertyData_Base,
				func_class
			>(element, structural_cont_func9, next_func, recursive);


			ComponentDetails::AssociationDetails_sequence& (ComponentDetails:: * structural_cont_func10)() = &ComponentDetails::AssociationDetails;

			SetUpChildSequence<ComponentDetails,
				AssociationDetails,
				ComponentDetails::AssociationDetails_sequence,
				AssociationDetails_Base,
				func_class
			>(element, structural_cont_func10, next_func, recursive);


			//ComponentDetails::ComponentDetails1_sequence& (ComponentDetails:: * structural_cont_func11)() = &ComponentDetails::ComponentDetails1;

			//SetUpChildSequence<ComponentDetails,
			//	ComponentDetails1,
			//	ComponentDetails::ComponentDetails1_sequence,
			//	ComponentDetails1_Base,
			//	func_class
			//>(element, structural_cont_func11, next_func, recursive);
		}

	}

};//end bellshire namespace

