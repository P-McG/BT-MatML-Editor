/////////////////////////////////////////////////////////////////////////////
// Name:        BT_MatML_Base_GUI.h
// Purpose:     Classes of Base_GUI Base for GUI classes.
// Author:      Paul McGrath
// Modified by:
// Created:
// Copyright:   (c) Paul McGrath
// Licence:     CC licence
/////////////////////////////////////////////////////////////////////////////
#pragma once

#include <algorithm>    // std::find

#include <wx/event.h>
#include <wx/msgdlg.h>

#include "matml31.hxx"
#include "BT_MatML_MatMLTreeItemData.h"
#include "BT_MatML_TreeCtrlSorted.h"
#include "BT_MatML_Default.h"
#include "BT_MatML_Utilities_GUI.h"

namespace bellshire {

// The following are added in the MatML_defaults already. 
// Therefore inserting new elements is not allowed. So do nothing.
// Note: PARENT is Selected in the menu 
#define ON_PARENT_INSERT_CHILD(parent, child) \
	parent* element = MatML_Base_GUI::GetSelMatML<parent>(m_MatMLTreeCtrl);\
	if (element) {\
		MatML_Base_GUI::InsertChild<child>(element->child());\
		MatML_Base_GUI::SetupSel<parent, parent ##_GUI>(m_MatMLTreeCtrl);\
	}

// Note: PARENT is Selected in the menu 
#define ON_PARENT_INSERT_CONT_CHILD(parent,child) \
	parent* element = MatML_Base_GUI::GetSelMatML<parent>(m_MatMLTreeCtrl);\
	if (element) {\
		MatML_Base_GUI::InsertContChild<child>(element->child());\
		MatML_Base_GUI::SetupSel<parent, parent ##_GUI>(m_MatMLTreeCtrl);\
	}

#define ON_PARENT_STRONGTYPE_INSERT_CONT_CHILD(parent,child) \
    parent* element = MatML_Base_GUI::GetSelMatML<parent>(m_MatMLTreeCtrl); \
    if (element) { \
        MatML_Base_GUI::InsertContChild<child>((element->t)->child()); \
        MatML_Base_GUI::SetupSel<parent, parent ##_GUI>(m_MatMLTreeCtrl); \
    }

// Note: PARENT is Selected in the menu 
#define ON_PARENT_INSERT_ITER_CONT_CHILD(parent,child) \
	parent* element = MatML_Base_GUI::GetSelMatML<parent>(m_MatMLTreeCtrl);\
if (element) {\
   	MatML_Base_GUI::InsertSeqContChild<child>(element->child());\
	MatML_Base_GUI::SetupSel<parent, parent ##_GUI>(m_MatMLTreeCtrl);\
}

    // Note: PARENT is Selected in the menu 
#define ON_PARENT_STRONGTYPE_INSERT_ITER_CONT_CHILD(parent,child) \
	parent* element = MatML_Base_GUI::GetSelMatML<parent>(m_MatMLTreeCtrl);\
if (element) {\
   	MatML_Base_GUI::InsertSeqContChild<child>(element->t->child());\
	MatML_Base_GUI::SetupSel<parent, parent ##_GUI>(m_MatMLTreeCtrl);\
}

// Note: PARENT is Selected in the menu 
#define ON_PARENT_PASTE_CHILD(parent,child) \
    parent* element = GetSelMatML< parent>(m_MatMLTreeCtrl); \
    child* copy_element = boost::any_cast< child* >(m_MatMLItemToCopy); \
    if (element && copy_element) {\
		    PasteChild(copy_element, element->child()); \
		    SetupSel<parent, parent ##_GUI>(m_MatMLTreeCtrl); \
    }

// Note: PARENT is Selected in the menu 
#define ON_PARENT_PASTE_CONT_CHILD(parent,child) \
	parent* element = MatML_Base_GUI::GetSelMatML< parent>(m_MatMLTreeCtrl);\
	child* copy_element = boost::any_cast< child* >(m_MatMLItemToCopy);\
	if (element && copy_element) {\
		PasteContChild(copy_element, element->child());\
		MatML_Base_GUI::SetupSel<parent, parent ##_GUI>(m_MatMLTreeCtrl);\
	}

// Note: PARENT is Selected in the menu 
#define ON_PARENT_STRONGTYPE_PASTE_CONT_CHILD(parent,child) \
	parent* element = MatML_Base_GUI::GetSelMatML< parent>(m_MatMLTreeCtrl);\
	child* copy_element = boost::any_cast< child* >(m_MatMLItemToCopy);\
	if (element && copy_element) {\
		PasteContChild(copy_element, (element->t)->child());\
		MatML_Base_GUI::SetupSel<parent, parent ##_GUI>(m_MatMLTreeCtrl);\
	}

// Note: PARENT is Selected in the menu 
#define ON_PARENT_PASTE_ITER_CONT_CHILD(parent,child) \
	parent* element = MatML_Base_GUI::GetSelMatML<parent>(m_MatMLTreeCtrl);\
	child* copy_element = boost::any_cast<child* >(m_MatMLItemToCopy);\
	if (element && copy_element) {\
		PasteSeqContChild(copy_element, element->child());\
		MatML_Base_GUI::SetupSel<parent, parent ##_GUI>(m_MatMLTreeCtrl);\
	}

// Note: PARENT is Selected in the menu 
#define ON_PARENT_STRONGTYPE_PASTE_ITER_CONT_CHILD(parent,child) \
	parent* element = MatML_Base_GUI::GetSelMatML<parent>(m_MatMLTreeCtrl);\
	child* copy_element = boost::any_cast<child* >(m_MatMLItemToCopy);\
	if (element && copy_element) {\
		PasteSeqContChild(copy_element, (element->t)->child());\
		MatML_Base_GUI::SetupSel<parent, parent ##_GUI>(m_MatMLTreeCtrl);\
	}

// Note: CHILD is Selected in the menu 
#define ON_PARENT_DELETE_CHILD(parent,child) \
	parent* element = MatML_Base_GUI::GetSelParentMatML<parent>(m_MatMLTreeCtrl);\
	if (element) {\
		MatML_Base_GUI::DeleteChild(element->child());\
		MatML_Base_GUI::SetupSelParent<parent, parent ##_GUI>(m_MatMLTreeCtrl);\
	}

// Note: CHILD is Selected in the menu 
#define ON_PARENT_DELETE_CONT_CHILD(parent,child) \
	parent* element = MatML_Base_GUI::GetSelParentMatML<parent>(m_MatMLTreeCtrl);\
	if (element) {\
		MatML_Base_GUI::DeleteContChild(element->child());\
		MatML_Base_GUI::SetupSelParent<parent, parent ##_GUI>(m_MatMLTreeCtrl);\
	}

// Note: CHILD is Selected in the menu 
#define ON_PARENT_STRONGTYPE_DELETE_CONT_CHILD(parent,child) \
	parent* element = MatML_Base_GUI::GetSelParentMatML<parent>(m_MatMLTreeCtrl);\
	if (element) {\
		MatML_Base_GUI::DeleteContChild((element->t)->child());\
		MatML_Base_GUI::SetupSelParent<parent, parent ##_GUI>(m_MatMLTreeCtrl);\
	}

// Note: CHILD is Selected in the menu 
#define ON_PARENT_DELETE_ITER_CONT_CHILD(parent,child) \
	child* element = MatML_Base_GUI::GetSelMatML<child>(m_MatMLTreeCtrl);\
	parent* elementparent = MatML_Base_GUI::GetSelParentMatML<parent>(m_MatMLTreeCtrl);\
	if (element && elementparent) {\
		MatML_Base_GUI::DeleteSeqContChild(element, elementparent->child());\
		MatML_Base_GUI::SetupSelParent<parent, parent ##_GUI>(m_MatMLTreeCtrl);\
	}

// Note: CHILD is Selected in the menu 
#define ON_PARENT_DELETE_ITER_CONT_CHILD_STRONGTYPE(parent,child) \
	child* element = MatML_Base_GUI::GetSelMatML<child>(m_MatMLTreeCtrl);\
	parent* elementparent = MatML_Base_GUI::GetSelParentMatML<parent>(m_MatMLTreeCtrl);\
	if (element && elementparent) {\
		MatML_Base_GUI::DeleteSeqContChild(element->t, elementparent->child());\
		MatML_Base_GUI::SetupSelParent<parent, parent ##_GUI>(m_MatMLTreeCtrl);\
	}

// Note: CHILD is Selected in the menu 
#define ON_PARENT_STRONGTYPE_DELETE_ITER_CONT_CHILD(parent,child) \
	child* element = MatML_Base_GUI::GetSelMatML<child>(m_MatMLTreeCtrl);\
	parent* elementparent = MatML_Base_GUI::GetSelParentMatML<parent>(m_MatMLTreeCtrl);\
	if (element && elementparent) {\
		MatML_Base_GUI::DeleteSeqContChild(element, (elementparent->t)->child());\
		MatML_Base_GUI::SetupSelParent<parent, parent ##_GUI>(m_MatMLTreeCtrl);\
	}

    class MatML_Base_GUI : public wxEvtHandler, public Utilities
    {
    public:
        MatML_Base_GUI() {};
        virtual ~MatML_Base_GUI() {};

        bool Warning(::std::string msg)
        {
            wxMessageDialog WarningDialog(NULL, msg, _("MatML Editer"), wxOK | wxICON_EXCLAMATION, wxDefaultPosition);
            return (WarningDialog.ShowModal() == wxID_YES);
        }

        template<class MatML_Class>
        static MatML_Class*GetSelMatML(TreeCtrlSorted* MatMLTreeCtrl);

        template<class MatML_Class>
        MatML_Class* GetSelParentMatML(TreeCtrlSorted* MatMLTreeCtrl);

        template<typename MatML_ParentClass, typename GUI_ParentClass>
        void static SetupSel(TreeCtrlSorted* MatMLTreeCtrl);

        template<typename MatML_ParentClass, typename GUI_ParentClass>
        void SetupStrongTypeSel(TreeCtrlSorted* MatMLTreeCtrl);

        template<typename MatML_ParentClass, typename GUI_ParentClass>
        void SetupSelParent(TreeCtrlSorted* MatMLTreeCtrl);

        template<class InputIterator, class T>
        InputIterator find(InputIterator first, InputIterator last, const T& val);

        template<typename MatML_Class, typename MatML_ContClass >
        void InsertChild(MatML_ContClass& MatML_Cont);

        template<typename MatML_Class, typename MatML_ContClass >
        void InsertContChild(MatML_ContClass& MatML_Cont);

        template<typename MatML_Class, typename MatML_ContClass >
        void InsertSeqContChild(MatML_ContClass& MatML_Cont);

        template<typename MatML_ContClass >
        void DeleteChild(MatML_ContClass& MatML);

        template<typename MatML_ContClass >
        void DeleteContChild(MatML_ContClass& MatML_Cont);

        template<typename MatML_Class, typename MatML_ContClass>
        void DeleteSeqContChild(MatML_Class* MatML, MatML_ContClass& MatML_Cont);

        template<typename MatML_Class, typename MatML_ContClass>
        void PasteChild(MatML_Class* MatML, MatML_ContClass& MatML_Cont);

        template<typename MatML_Class, typename MatML_ContClass>
        void PasteContChild(MatML_Class* MatML, MatML_ContClass& MatML_Cont);

        template<typename MatML_Class, typename MatML_ContClass>
        void PasteSeqContChild(MatML_Class* MatML, MatML_ContClass& MatML_Cont);

        template<class MatML_Class>
        void SwapHavingId(MatML_Class* matml0, MatML_Class* matml1);

        template<class MatML_Class>
        void SwapHavingOptionalId(MatML_Class* matml0, MatML_Class* matml1);

        template< class MatML_Class, class MatML_ContClass >
        std::pair< MatML_Class*, MatML_Class* >
            MatMLFindAndBumpDown(MatML_Class* matml, MatML_ContClass& cont);

        template< class MatML_Class, class MatML_ContClass >
        std::pair<  MatML_Class*, MatML_Class* >
            MatMLFindAndBumpDownStrongtype(MatML_Class* matml, MatML_ContClass& cont);

        template< class MatML_Class, class MatML_ContClass>
        std::pair<MatML_Class*, MatML_Class* >
            MatMLFindAndBumpDownHavingId(MatML_Class* matml, MatML_ContClass& cont);

        template<class MatML_Class, class MatML_ContClass>
        std::pair<  MatML_Class*, MatML_Class* >
            MatMLFindAndBumpDownHavingOptionalId(MatML_Class* matml, MatML_ContClass& cont);

        template<class Child_GUI, class MatML>
        void MatMLTreeCtrlBumpDown(TreeCtrlSorted*& treectrl,
            wxTreeItemId& itemParentId,
            wxTreeItemId& itemId,
            MatML* first,
            wxTreeItemId& nextitemId,
            MatML* second
        );
 
        template<class MatML_Class, class MatML_ContClass>
        std::pair<MatML_Class*, MatML_Class*>
            MatMLFindAndBumpUp(MatML_Class* matml, MatML_ContClass& cont);
 
        template<class MatML_Class, class MatML_ContClass>
        std::pair<MatML_Class*, MatML_Class*>
            MatMLFindAndBumpUpStrongtype(MatML_Class* matml, MatML_ContClass& cont);

        template<class MatML_ContClass>
        std::pair<typename MatML_ContClass::value_type*, typename MatML_ContClass::value_type*>
            MatMLFindAndBumpUpHavingId(typename MatML_ContClass::value_type* matml, MatML_ContClass& cont);

        template<class MatML_ContClass>
        std::pair<typename MatML_ContClass::value_type*, typename MatML_ContClass::value_type*>
            MatMLFindAndBumpUpHavingOptionalId(typename MatML_ContClass::value_type* matml, MatML_ContClass& cont);

        template<class Child_GUI, class MatML>
        void MatMLTreeCtrlBumpUp(TreeCtrlSorted*& treectrl,
            wxTreeItemId& itemParentId,
            wxTreeItemId& previtemId,
            MatML* first,
            wxTreeItemId& itemId,
            MatML* second
        );

        template<class Child_GUI, class MatML>
        void MatMLTreeCtrlBumpUpStrongtype(TreeCtrlSorted*& treectrl,
            wxTreeItemId& itemParentId,
            wxTreeItemId& previtemId,
            MatML* first,
            wxTreeItemId& itemId,
            MatML* second
        );

        template< class MatML_Class,
            class MatML_ParentClass,
            class MatML_ContClass,
            class MatML_GUI,
            MatML_ContClass& (MatML_ParentClass::* cont_func)()
        >
            void IndividualBumpUp(boost::any anyptr,
                boost::any anyptrparent,
                TreeCtrlSorted* MatMLTreeCtrl,
                wxTreeItemId itemParentId,
                wxTreeItemId itemId,
                wxTreeItemId nextitemId
            );

        template< class MatML_Class,
            class MatML_ParentClass,
            class MatML_ContClass,
            class MatML_GUI,
            MatML_ContClass& (MatML_ParentClass::* cont_func)()
        >
            void IndividualBumpUpStrongtype(boost::any anyptr,
                boost::any anyptrparent,
                TreeCtrlSorted* MatMLTreeCtrl,
                wxTreeItemId itemParentId,
                wxTreeItemId itemId,
                wxTreeItemId nextitemId
            );

        template< class MatML_Class,
            class MatML_ParentClass,
            class MatML_ContClass,
            class MatML_GUI,
            MatML_ContClass& (MatML_ParentClass::* cont_func)()
        >
            void IndividualBumpUpHavingId(boost::any anyptr,
                boost::any anyptrparent,
                TreeCtrlSorted* MatMLTreeCtrl,
                wxTreeItemId itemParentId,
                wxTreeItemId itemId,
                wxTreeItemId nextitemId
            );

        template< class MatML_Class,
            class MatML_ParentClass,
            class MatML_ContClass,
            class MatML_GUI,
            MatML_ContClass& (MatML_ParentClass::* cont_func)()
        >
            void IndividualBumpUpHavingOptionalId(boost::any anyptr,
                boost::any anyptrparent,
                TreeCtrlSorted* MatMLTreeCtrl,
                wxTreeItemId itemParentId,
                wxTreeItemId itemId,
                wxTreeItemId nextitemId
            );

        template< class MatML_Class,
            class MatML_ParentClass,
            class MatML_ContClass,
            class MatML_GUI,
            MatML_ContClass& (MatML_ParentClass::* cont_func)()
        >
            void IndividualBumpDown(boost::any& anyptr,
                boost::any& anyptrparent,
                TreeCtrlSorted* MatMLTreeCtrl,
                wxTreeItemId itemParentId,
                wxTreeItemId previtemId,
                wxTreeItemId itemId
            );

        template< class MatML_Class,
            class MatML_ParentClass,
            class MatML_ContClass,
            class MatML_GUI,
            MatML_ContClass& (MatML_ParentClass::* cont_func)()
        >
            void IndividualBumpDownStrongtype(boost::any& anyptr,
                boost::any& anyptrparent,
                TreeCtrlSorted* MatMLTreeCtrl,
                wxTreeItemId itemParentId,
                wxTreeItemId previtemId,
                wxTreeItemId itemId
            );

        template< class MatML_Class,
            class MatML_ParentClass,
            class MatML_ContClass,
            class MatML_GUI,
            MatML_ContClass& (MatML_ParentClass::* cont_func)()
        >
            void IndividualBumpDownHavingId(boost::any& anyptr,
                boost::any& anyptrparent,
                TreeCtrlSorted* MatMLTreeCtrl,
                wxTreeItemId itemParentId,
                wxTreeItemId previtemId,
                wxTreeItemId itemId
            );

        template< class MatML_Class,
            class MatML_ParentClass,
            class MatML_ContClass,
            class MatML_GUI,
            MatML_ContClass& (MatML_ParentClass::* cont_func)()
        >
            void IndividualBumpDownHavingOptionalId(boost::any& anyptr,
                boost::any& anyptrparent,
                TreeCtrlSorted* MatMLTreeCtrl,
                wxTreeItemId itemParentId,
                wxTreeItemId previtemId,
                wxTreeItemId itemId
            );
  
    };
};//bellshire namespace

#include "BT_MatML_Base_GUI.inl"
