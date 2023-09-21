#pragma once
#include "bellshire/GUI/BT_MatML_MatMLDropTarget.h"
#include "bellshire/utilities/BT_MatML_Functor_GatherIdRefPtrs_MatMLTree.h"
#include "bellshire/BT_MatML.h"
#include "bellshire/GUI/BT_MatML_MatML_GUI_Base.h"

namespace bellshire::GUI
{
	/// <summary>

	/// </summary>
	/// <typeparam name="MatML_Class"></typeparam>
	/// <typeparam name="MatML_ParentClass"></typeparam>
	/// <typeparam name="MatML_ContClass"></typeparam>
	/// <typeparam name="MatML_GUI"></typeparam>
	/// <param name="parentdata"></param>
	/// <param name="data"></param>
	/// <param name="defResult"></param>
	/// <returns></returns>
	template< class MatML_Class,
		class MatML_ParentClass,
		class MatML_ContClass,
		class MatML_GUI,
		MatML_ContClass& (MatML_ParentClass::* cont_func)()
	>
		wxDragResult MatMLDropTarget::InsertSequenceData(boost::any parentdata, boost::any data, wxDragResult defResult)
	{
		if (parentdata.type() == typeid(observer_ptr<MatML_ParentClass>) && data.type() == typeid(observer_ptr<MatML_Class>))
		{
			try {

				 auto element_parent_observer = boost::any_cast<observer_ptr<MatML_ParentClass>>(parentdata);
				 auto element_observer = remove_strongly_typed_on_observer_ptr_v(boost::any_cast<observer_ptr<MatML_Class>>(data));

				if (element_parent_observer && element_observer)
				{
					//Make a unique element to go into the MatML Tree container.
					 auto& element_unique=make_unique<MatML_ContClass::value_type>(*element_observer);
					(element_parent_observer->*cont_func)().push_back(std::move(element_unique));//copy matml element

					MatML_GUI_Base::SetupSel<MatML_ParentClass, MatML_GUI>(m_MatMLTreeCtrl);

					return defResult;
				}

			}
			catch (const boost::bad_any_cast&) {};
		}
		return wxDragNone;
	}

	template<class MatML_Class, 
		class MatML_Base_Class
	>
	void  MatMLDropTarget::ClearIdRefs(boost::any data)
	{
		if (data.type() == typeid(MatML_Class*))
		{
			try {
				 auto element= remove_strongly_typed_on_observer_ptr_v(boost::any_cast<observer_ptr<MatML_Class>>(data));

				//Load data into functor
				bellshire::utilities::Functor_GatherIdRefPtrs_MatMLTree::Data::Gather_type idrefptrs;
				bellshire::utilities::Functor_GatherIdRefPtrs_MatMLTree::Data data{ idrefptrs };
				bellshire::utilities::Functor_GatherIdRefPtrs_MatMLTree func(data);

				//Gather IdRef
				//if constexpr(is_strongly_typed_v<MatML_Class>)
				//	MatML_Base_Class::TraverseMatMLTree(element->t, func);
				//else
				MatML_Base_Class::TraverseMatMLTree(element, func);

				//Clear out the idrefs
				for (auto i : idrefptrs)
					(*i).clear();
			}
			catch (const boost::bad_any_cast&) {}
		}
	}

}//namespace bellshire