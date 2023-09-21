#pragma once
#include "bellshire/GUI/BT_MatML_MatMLLibDropTarget.h"
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
	wxDragResult MatMLLibDropTarget::InsertSequenceData(boost::any parentdata, boost::any data, wxDragResult defResult)
	{
		if (parentdata.type() == typeid(MatML_ParentClass*) && data.type() == typeid(MatML_Class*))
		{
			try {

				auto element_parent_observer{ remove_strongly_typed_on_observer_ptr_v(boost::any_cast<observer_ptr<MatML_ParentClass>>(parentdata))};
				auto element_observer{ remove_strongly_typed_on_observer_ptr_v(boost::any_cast<observer_ptr<MatML_Class>>(data)) };

				if (element_parent_observer && element_observer)
				{

					(element_parent_observer->*cont_func)().push_back(*element_observer);//copy matml element

					MatML_GUI_Base::SetupSel<MatML_ParentClass, MatML_GUI>(m_MatMLTreeCtrl);

					return defResult;
				}

			}
			catch (const boost::bad_any_cast& e) {};
		}
		return wxDragNone;
	}

}//namespace bellshire