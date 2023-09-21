#pragma once

// The following are added in the MatML_defaults already. 
// Therefore inserting new elements is not allowed. So do nothing.
// Note: PARENT is Selected in the menu 
#define ON_PARENT_INSERT_CHILD(parent, child) \
	 auto element= MatML_GUI_Base::GetSelMatML<parent>(m_MatMLTreeCtrl);\
	if (element) {\
		MatML_GUI_Base::InsertChild<child>(element->child());\
		MatML_GUI_Base::SetupSel<parent, parent ##_GUI>(m_MatMLTreeCtrl);\
	}

// Note: PARENT is Selected in the menu 
#define ON_PARENT_INSERT_CONT_CHILD(parent,child) \
	 auto element { remove_strongly_typed_on_observer_ptr_v(MatML_GUI_Base::GetSelMatML<parent>(m_MatMLTreeCtrl))};\
	if (element) {\
		MatML_GUI_Base::InsertContChild<child>(element->child());\
		MatML_GUI_Base::SetupSel<parent, parent ##_GUI>(m_MatMLTreeCtrl);\
	}

//#define ON_PARENT_STRONGTYPE_INSERT_CONT_CHILD(parent,child) \
//    parent* element = MatML_GUI_Base::GetSelMatML<parent>(m_MatMLTreeCtrl); \
//    if (element) { \
//        MatML_GUI_Base::InsertContChild<child>((element->t)->child()); \
//        MatML_GUI_Base::SetupStrongTypeSel<parent, parent ##_GUI>(m_MatMLTreeCtrl); \
//    }

// Note: PARENT is Selected in the menu 
#define ON_PARENT_INSERT_ITER_CONT_CHILD(parent,child) \
	 auto element { remove_strongly_typed_on_observer_ptr_v(MatML_GUI_Base::GetSelMatML<parent>(m_MatMLTreeCtrl))};\
if (element) {\
   	MatML_GUI_Base::InsertSeqContChild<child>(element->child());\
	MatML_GUI_Base::SetupSel<parent, parent ##_GUI>(m_MatMLTreeCtrl);\
}

//	// Note: PARENT is Selected in the menu 
//#define ON_PARENT_STRONGTYPE_INSERT_ITER_CONT_CHILD(parent,child) \
//	parent* element = MatML_GUI_Base::GetSelMatML<parent>(m_MatMLTreeCtrl);\
//if (element) {\
//   	MatML_GUI_Base::InsertSeqContChild<child>(element->t->child());\
//	MatML_GUI_Base::SetupStrongTypeSel<parent, parent ##_GUI>(m_MatMLTreeCtrl);\
//}

// Note: PARENT is Selected in the menu 
#define ON_PARENT_PASTE_CHILD(parent,child) \
     auto element= GetSelMatML< parent>(m_MatMLTreeCtrl); \
    auto copy_element = remove_strongly_typed_on_observer_ptr_v(boost::any_cast< observer_ptr<child> >(m_MatMLItemToCopy)); \
    if (element) {\
		    MatML_Base::PasteChild(copy_element, element->child()); \
		    SetupSel<parent, parent ##_GUI>(m_MatMLTreeCtrl); \
    }

// Note: PARENT is Selected in the menu 
#define ON_PARENT_PASTE_CONT_CHILD(parent,child) \
	auto element {remove_strongly_typed_on_observer_ptr_v(MatML_GUI_Base::GetSelMatML< parent>(m_MatMLTreeCtrl)) };\
	auto copy_element { boost::any_cast< observer_ptr<child> >(m_MatMLItemToCopy)};\
	if (element) {\
		MatML_Base::PasteContChild(copy_element, element->child());\
		MatML_GUI_Base::SetupSel<parent, parent ##_GUI>(m_MatMLTreeCtrl);\
	}

//// Note: PARENT is Selected in the menu 
//#define ON_PARENT_STRONGTYPE_PASTE_CONT_CHILD(parent,child) \
//	parent* element = MatML_GUI_Base::GetSelMatML< parent>(m_MatMLTreeCtrl);\
//	child* copy_element = boost::any_cast< child* >(m_MatMLItemToCopy);\
//	if (element && copy_element) {\
//		PasteContChild(copy_element, (element->t)->child());\
//		MatML_GUI_Base::SetupStrongTypeSel<parent, parent ##_GUI>(m_MatMLTreeCtrl);\
//	}

// Note: PARENT is Selected in the menu 
#define ON_PARENT_PASTE_ITER_CONT_CHILD(parent,child) \
	auto element_observer { remove_strongly_typed_on_observer_ptr_v( MatML_GUI_Base::GetSelMatML< parent >(m_MatMLTreeCtrl))};\
	auto copy_element { remove_strongly_typed_on_observer_ptr_v(boost::any_cast< observer_ptr<child> >(m_MatMLItemToCopy))};\
	if (element_observer) {\
		MatML_Base::PasteSeqContChild(copy_element, element_observer->child());\
		MatML_GUI_Base::SetupSel<parent, parent ##_GUI>(m_MatMLTreeCtrl);\
	}

// Note: PARENT is Selected in the menu 
#define ON_PARENT_STRONGTYPE_PASTE_ITER_CONT_CHILD(parent,child) \
	parent* element = MatML_GUI_Base::GetSelMatML<parent>(m_MatMLTreeCtrl);\
	child* copy_element = boost::any_cast<child* >(m_MatMLItemToCopy);\
	if (element && copy_element) {\
		PasteSeqContChild(copy_element, (element->t)->child());\
		MatML_GUI_Base::SetupStrongTypeSel<parent, parent ##_GUI>(m_MatMLTreeCtrl);\
	}

// Note: CHILD is Selected in the menu 
#define ON_PARENT_DELETE_CHILD(parent,child) \
	 auto element= MatML_GUI_Base::GetSelParentMatML<parent>(m_MatMLTreeCtrl);\
	if (element) {\
		MatML_GUI_Base::DeleteChild(element->child());\
		MatML_GUI_Base::SetupSelParent<parent, parent ##_GUI>(m_MatMLTreeCtrl);\
	}

// Note: CHILD is Selected in the menu 
#define ON_PARENT_DELETE_CONT_CHILD(parent,child) \
	 auto element { remove_strongly_typed_on_observer_ptr_v(MatML_GUI_Base::GetSelParentMatML<parent>(m_MatMLTreeCtrl))};\
	if (element) {\
		MatML_GUI_Base::DeleteContChild(element->child());\
		MatML_GUI_Base::SetupSelParent<parent, parent ##_GUI>(m_MatMLTreeCtrl);\
	}

// Note: CHILD is Selected in the menu 
#define ON_PARENT_DELETE_ITER_CONT_CHILD(parent,child) \
	 auto element{ remove_strongly_typed_on_observer_ptr_v(MatML_GUI_Base::GetSelMatML<child>(m_MatMLTreeCtrl))};\
	 auto element_parent { remove_strongly_typed_on_observer_ptr_v(MatML_GUI_Base::GetSelParentMatML<parent>(m_MatMLTreeCtrl))};\
	if (element_parent) {\
		MatML_Base::DeleteSeqContChild(element, element_parent->child());\
		MatML_GUI_Base::SetupSelParent<parent, parent ##_GUI>(m_MatMLTreeCtrl);\
	}

//// Note: CHILD is Selected in the menu 
//#define ON_PARENT_DELETE_ITER_CONT_CHILD_STRONGTYPE(parent,child) \
//	child* element = MatML_GUI_Base::GetSelMatML<child>(m_MatMLTreeCtrl);\
//	parent* elementparent = MatML_GUI_Base::GetSelParentMatML<parent>(m_MatMLTreeCtrl);\
//	if (element && elementparent) {\
//		MatML_GUI_Base::DeleteSeqContChild(element->t, elementparent->child());\
//		MatML_GUI_Base::SetupSelParent<parent, parent ##_GUI>(m_MatMLTreeCtrl);\
//	}
//
//// Note: CHILD is Selected in the menu 
//#define ON_PARENT_STRONGTYPE_DELETE_ITER_CONT_CHILD(parent,child) \
//	child* element = MatML_GUI_Base::GetSelMatML<child>(m_MatMLTreeCtrl);\
//	parent* elementparent = MatML_GUI_Base::GetSelParentMatML<parent>(m_MatMLTreeCtrl);\
//	if (element && elementparent) {\
//		MatML_GUI_Base::DeleteSeqContChild(element, (elementparent->t)->child());\
//		MatML_GUI_Base::SetupStrongTypeSelParent<parent, parent ##_GUI>(m_MatMLTreeCtrl);\
//	}

