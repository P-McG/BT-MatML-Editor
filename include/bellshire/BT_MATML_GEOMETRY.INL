#pragma once

#include "bellshire/matml31.hxx"
#include "bellshire/BT_MatML_Geometry.h"
#include "bellshire/BT_MatML_Shape.h"
#include "bellshire/BT_MatML_Dimensions.h"
#include "bellshire/BT_MatML_Orientation.h"
#include "bellshire/BT_MatML_Notes.h"

namespace bellshire
{
	template<class func_class>
	void Geometry_Base::TraverseMatMLTree(
		const observer_ptr < Geometry > element,
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

			SetUpChild<Geometry,
				Geometry::Shape_type,
				Geometry::Shape_type,
				Shape_Base,
				func_class
			>(element, &Geometry::Shape, next_func, recursive);


			Geometry::Dimensions_optional& (Geometry:: * structural_cont_func2)() = &Geometry::Dimensions;

			SetUpChildOptional<Geometry,
				Geometry::Dimensions_type,
				Geometry::Dimensions_optional,
				Dimensions_Base,
				func_class
			>(element, structural_cont_func2, next_func, recursive);


			Geometry::Orientation_optional& (Geometry:: * structural_cont_func3)() = &Geometry::Orientation;

			SetUpChildOptional<Geometry,
				Geometry::Orientation_type,
				Geometry::Orientation_optional,
				Orientation_Base,
				func_class
			>(element, structural_cont_func3, next_func, recursive);


			Geometry::Notes_optional& (Geometry:: * structural_cont_func4)() = &Geometry::Notes;

			SetUpChildOptional<Geometry,
				Notes,
				Geometry::Notes_optional,
				Notes_Base,
				func_class
			>(element, structural_cont_func4, next_func, recursive);
		}
	}

};//end bellshire namespace

