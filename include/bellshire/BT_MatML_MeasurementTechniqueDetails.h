#pragma once

#include "bellshire/matml31.hxx"
#include "bellshire/BT_MatML_MatML_Base.h"

namespace bellshire
{
	class MeasurementTechniqueDetails_Base : public MatML_Base
	{
	public:
		MeasurementTechniqueDetails_Base() {};
		virtual ~MeasurementTechniqueDetails_Base() {};

		template<class func_class>
		static void TraverseMatMLTree(
			observer_ptr < MeasurementTechniqueDetails > Element,
			func_class& func,
			RecursiveFlags recursive = {}
		);
	};

};//end namespace bellshire

#include "bellshire/BT_MatML_MeasurementTechniqueDetails.inl"



