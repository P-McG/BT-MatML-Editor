#pragma once

#include "bellshire/matml31.hxx"
#include "bellshire/BT_MatML_Metadata.h"
#include "bellshire/BT_MatML_AuthorityDetails.h"
#include "bellshire/BT_MatML_DataSourceDetails.h"
#include "bellshire/BT_MatML_MeasurementTechniqueDetails.h"
#include "bellshire/BT_MatML_ParameterDetails.h"
#include "bellshire/BT_MatML_PropertyDetails.h"
#include "bellshire/BT_MatML_SourceDetails.h"
#include "bellshire/BT_MatML_SpecimenDetails.h"
#include "bellshire/BT_MatML_TestConditionDetails.h"

namespace bellshire
{
	template<class func_class>
	void Metadata_Base::TraverseMatMLTree(observer_ptr<Metadata> element,
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

			Metadata::AuthorityDetails_sequence& (Metadata:: * structural_cont_func2)() = &Metadata::AuthorityDetails;

			SetUpChildSequence<Metadata,
				AuthorityDetails,
				Metadata::AuthorityDetails_sequence,
				AuthorityDetails_Base,
				func_class
			>(element, structural_cont_func2, next_func, recursive);


			Metadata::DataSourceDetails_sequence& (Metadata:: * structural_cont_func3)() = &Metadata::DataSourceDetails;

			SetUpChildSequence<Metadata,
				DataSourceDetails,
				Metadata::DataSourceDetails_sequence,
				DataSourceDetails_Base,
				func_class
			>(element, structural_cont_func3, next_func, recursive);


			Metadata::MeasurementTechniqueDetails_sequence& (Metadata:: * structural_cont_func4)() = &Metadata::MeasurementTechniqueDetails;

			SetUpChildSequence<Metadata,
				MeasurementTechniqueDetails,
				Metadata::MeasurementTechniqueDetails_sequence,
				MeasurementTechniqueDetails_Base,
				func_class
			>(element, structural_cont_func4, next_func, recursive);


			Metadata::ParameterDetails_sequence& (Metadata:: * structural_cont_func5)() = &Metadata::ParameterDetails;

			SetUpChildSequence<Metadata,
				ParameterDetails,
				Metadata::ParameterDetails_sequence,
				ParameterDetails_Base,
				func_class
			>(element, structural_cont_func5, next_func, recursive);


			Metadata::PropertyDetails_sequence& (Metadata:: * structural_cont_func6)() = &Metadata::PropertyDetails;

			SetUpChildSequence<Metadata,
				PropertyDetails,
				Metadata::PropertyDetails_sequence,
				PropertyDetails_Base,
				func_class
			>(element, structural_cont_func6, next_func, recursive);


			Metadata::SourceDetails_sequence& (Metadata:: * structural_cont_func7)() = &Metadata::SourceDetails;

			SetUpChildSequence<Metadata,
				SourceDetails,
				Metadata::SourceDetails_sequence,
				SourceDetails_Base,
				func_class
			>(element, structural_cont_func7, next_func, recursive);


			Metadata::SpecimenDetails_sequence& (Metadata:: * structural_cont_func8)() = &Metadata::SpecimenDetails;

			SetUpChildSequence<Metadata,
				SpecimenDetails,
				Metadata::SpecimenDetails_sequence,
				SpecimenDetails_Base,
				func_class
			>(element, structural_cont_func8, next_func, recursive);


			Metadata::TestConditionDetails_sequence& (Metadata:: * structural_cont_func9)() = &Metadata::TestConditionDetails;

			SetUpChildSequence<Metadata,
				TestConditionDetails,
				Metadata::TestConditionDetails_sequence,
				TestConditionDetails_Base,
				func_class
			>(element, structural_cont_func9, next_func, recursive);
		}

	}

};//end bellshire namespace


