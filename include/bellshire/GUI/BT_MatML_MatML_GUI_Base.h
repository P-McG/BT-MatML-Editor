/////////////////////////////////////////////////////////////////////////////
// Name:        BT_MatML_GUI_Base.h
// Purpose:     Classes of Base_GUI Base for GUI classes.
// Author:      Paul McGrath
// Modified by:
// Created:
// Copyright:   (c) Paul McGrath
// Licence:     CC licence
/////////////////////////////////////////////////////////////////////////////
#pragma once

#include <algorithm>    // std::find
#include <memory> // std::auto_ptr
#include <type_traits>

#include <wx/event.h>
#include <wx/msgdlg.h>
#include <wx/notebook.h>
#include <wx/frame.h>

#include "bellshire/matml31.hxx"
#include "bellshire/Lib/matml31_lib.hxx"
#include "bellshire/Lib/dom-serialize.hxx"
#include "bellshire/lib/dom-parse.hxx"

#include "bellshire/BT_MatML_MatML_Base.h"
#include "bellshire/Lib/BT_MatML_MatML_Lib.h"
#include "bellshire/GUI/BT_MatML_MatML_GUI_Base_Macros.h"

//#include "bellshire/BT_MatML_MatMLTreeItemData.h"
//#include "bellshire/BT_MatML_TreeCtrlSorted.h"
//#include "bellshire/BT_MatML_Default.h"
#include "bellshire/GUI/utilities/BT_MatML_Utilities_GUI.h"
//
//#include "bellshire/BT_MatML_TreeCtrlSorted.h"
////#include "bellshire/BT_MatML_MatMLDropTarget.h"
//#include "bellshire/BT_MatML_MatML_Lib.h"
//
//#include "bellshire/BT_MatML_Functor_SetupCtrl_MatMLTree_GUI.h"
//
////#include "bellshire/BT_MatML_Get_Associated_GUI_type.h"

namespace bellshire::GUI
{
    class MatML_GUI_Base : public wxFrame, public Utilities, public MatML_Base
    {
    protected:
        wxNotebook* m_GUI{ nullptr };
        //MatML_Lib m_lib;
        TreeCtrlSorted* m_MatMLLibTreeCtrl{ nullptr };
        //std::unique_ptr< xml_schema::element_type > m_lib_element;


    public:
        MatML_GUI_Base();
        virtual ~MatML_GUI_Base();

        wxNotebook* GetGUI();
        //MatML_Lib GetLib();
        TreeCtrlSorted* GetMatMLLibTreeCtrl();
        //observer_ptr< xml_schema::element_type > GetLibElement();

        void ShowGUI(bool show = true) {
            if (m_GUI) m_GUI->Show(show);
        }

        bool IsShown() { return m_GUI->IsShown(); };
        wxNotebook* get() { return m_GUI; };

        void SetLibConnect();

        bool Warning(::std::string msg)
        {
            wxMessageDialog WarningDialog(NULL, msg, _("MatML Editor"), wxOK | wxICON_EXCLAMATION, wxDefaultPosition);
            return (WarningDialog.ShowModal() == wxID_YES);
        }

        void OnLeftDown(wxTreeEvent& event);
        void OnRightDown(wxTreeEvent& event);
        void OnMatMLLibItemMenu(wxTreeEvent& event);
        void ShowContextMenu(wxTreeItemId id, const wxPoint& pt);

        //The following are test functions for the erasiur of the Unit in MatML_lib tree.
        template<typename EventTag, typename Class, typename EventArg, typename EventHandler >
        void PopupLinkBind(wxMenu& menu, ::std::string desc, const EventTag& eventType, void(Class::*& method)(EventArg&), EventHandler* handler);
        void OnDelete(/*wxTreeEvent& event*/ wxCommandEvent& event);
        void OnDeleteUnit(wxCommandEvent& event);

        template<class MatML_Class>
        static observer_ptr<MatML_Class>  GetSelMatML(TreeCtrlSorted* MatMLTreeCtrl);

        template<class MatML_Class>
        static observer_ptr<MatML_Class> GetSelParentMatML(TreeCtrlSorted* MatMLTreeCtrl);

        template<typename MatML_ParentClass, typename GUI_ParentClass>
        static void SetupSel(TreeCtrlSorted* MatMLTreeCtrl);

        //template<typename MatML_ParentClass, typename GUI_ParentClass>
        //void SetupStrongTypeSel(TreeCtrlSorted* MatMLTreeCtrl);

        template<typename MatML_ParentClass, typename GUI_ParentClass>
        static void SetupSelParent(TreeCtrlSorted* MatMLTreeCtrl);

        //template<typename MatML_ParentClass, typename GUI_ParentClass>
        //void SetupStrongTypeSelParent(TreeCtrlSorted* MatMLTreeCtrl);

        template<class InputIterator, class T>
        static InputIterator find(InputIterator first, InputIterator last, const T& val);

        //template<typename MatML_Class, typename MatML_ContClass >
        //void InsertChild(MatML_ContClass& MatML_Cont);

        //template<typename MatML_Class, typename MatML_ContClass >
        //void InsertContChild(MatML_ContClass& MatML_Cont);

        //template<typename MatML_Class, typename MatML_ContClass >
        //void InsertSeqContChild(MatML_ContClass& MatML_Cont);

        //template<typename MatML_ContClass >
        //void DeleteChild(MatML_ContClass& MatML);

        //template<typename MatML_ContClass >
        //void DeleteContChild(MatML_ContClass& MatML_Cont);

        //template<typename MatML_Class, typename MatML_ContClass>
        //void DeleteSeqContChild(observer_ptr<MatML_Class> MatML, MatML_ContClass& MatML_Cont);

        //template<typename MatML_Class, typename MatML_ContClass>
        //void PasteChild(observer_ptr<MatML_Class> MatML, MatML_ContClass& MatML_Cont);

        //template<typename MatML_Class, typename MatML_ContClass>
        //void PasteContChild(observer_ptr<MatML_Class> MatML, MatML_ContClass& MatML_Cont);

        //template<typename MatML_Class, typename MatML_ContClass>
        //void PasteSeqContChild(observer_ptr<MatML_Class> MatML, MatML_ContClass& MatML_Cont);

        //template<class MatML_Class>
        //void SwapHavingId(observer_ptr<MatML_Class> matml0, observer_ptr<MatML_Class> matml1);

        //template<class MatML_Class>
        //void SwapHavingOptionalId(observer_ptr<MatML_Class> matml0, observer_ptr<MatML_Class> matml1);

        //template< class MatML_Class, class MatML_ContClass >
        //decltype(auto)
        //    MatMLFindAndBumpDown(MatML_Class matml, MatML_ContClass& cont);

        //template< class MatML_Class, class MatML_ContClass >
        //std::pair<  observer_ptr<MatML_Class>, observer_ptr<MatML_Class> >
        //    MatMLFindAndBumpDownStrongtype(observer_ptr<MatML_Class> matml, MatML_ContClass& cont);

        //template< class MatML_Class, class MatML_ContClass>
        //std::pair<observer_ptr<MatML_Class>, observer_ptr<MatML_Class> >
        //    MatMLFindAndBumpDownHavingId(observer_ptr<MatML_Class> matml, MatML_ContClass& cont);

        //template<class MatML_Class, class MatML_ContClass>
        //std::pair<  observer_ptr<MatML_Class>, observer_ptr<MatML_Class> >
        //    MatMLFindAndBumpDownHavingOptionalId(observer_ptr<MatML_Class> matml, MatML_ContClass& cont);

        template<class Child_GUI, class MatMLFirst, class MatMLSecond>
        static void MatMLTreeCtrlBumpDown(TreeCtrlSorted*& treectrl,
            wxTreeItemId& itemParentId,
            wxTreeItemId& itemId,
            MatMLFirst first,
            wxTreeItemId& nextitemId,
            MatMLSecond second
        );
 
        //template<class MatML_Class, class MatML_ContClass>
        //std::pair<observer_ptr<MatML_Class>, observer_ptr<MatML_Class>>
        //    MatMLFindAndBumpUp(observer_ptr<MatML_Class> matml, MatML_ContClass& cont);
 
        //template<class MatML_Class, class MatML_ContClass>
        //std::pair<observer_ptr<MatML_Class>, observer_ptr<MatML_Class>>
        //    MatMLFindAndBumpUpStrongtype(observer_ptr<MatML_Class> matml, MatML_ContClass& cont);

        //template<class MatML_ContClass>
        //std::pair<typename MatML_ContClass::value_type*, typename MatML_ContClass::value_type*>
        //    MatMLFindAndBumpUpHavingId(typename MatML_ContClass::value_type* matml, MatML_ContClass& cont);

        //template<class MatML_ContClass>
        //std::pair<typename MatML_ContClass::value_type*, typename MatML_ContClass::value_type*>
        //    MatMLFindAndBumpUpHavingOptionalId(typename MatML_ContClass::value_type* matml, MatML_ContClass& cont);

        template<class Child_GUI, class MatML>
        static void MatMLTreeCtrlBumpUp(TreeCtrlSorted*& treectrl,
            wxTreeItemId& itemParentId,
            wxTreeItemId& previtemId,
            observer_ptr < MatML> first,
            wxTreeItemId& itemId,
            observer_ptr < MatML> second
        );

        //template<class Child_GUI, class MatML>
        //void MatMLTreeCtrlBumpUpStrongtype(TreeCtrlSorted*& treectrl,
        //    wxTreeItemId& itemParentId,
        //    wxTreeItemId& previtemId,
        //    MatML* first,
        //    wxTreeItemId& itemId,
        //    MatML* second
        //);

        template< class MatML_Class,
            class MatML_ParentClass,
            class MatML_ContClass,
            class MatML_GUI,
            MatML_ContClass& (MatML_ParentClass::* cont_func)()
        >
            static void IndividualBumpUp(boost::any anyptr,
                boost::any anyptrparent,
                TreeCtrlSorted* MatMLTreeCtrl,
                wxTreeItemId itemParentId,
                wxTreeItemId itemId,
                wxTreeItemId nextitemId
            );

        //template< class MatML_Class,
        //    class MatML_ParentClass,
        //    class MatML_ContClass,
        //    class MatML_GUI,
        //    MatML_ContClass& (MatML_ParentClass::* cont_func)()
        //>
        //    void IndividualBumpUpStrongtype(boost::any anyptr,
        //        boost::any anyptrparent,
        //        TreeCtrlSorted* MatMLTreeCtrl,
        //        wxTreeItemId itemParentId,
        //        wxTreeItemId itemId,
        //        wxTreeItemId nextitemId
        //    );

        template< class MatML_Class,
            class MatML_ParentClass,
            class MatML_ContClass,
            class MatML_GUI,
            MatML_ContClass& (MatML_ParentClass::* cont_func)()
        >
         static void IndividualBumpUpHavingId(
            boost::any& anyptr,
            boost::any& anyptrparent,
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

        //template< class MatML_Class,
        //    class MatML_ParentClass,
        //    class MatML_ContClass,
        //    class MatML_GUI,
        //    MatML_ContClass& (MatML_ParentClass::* cont_func)()
        //>
        //    void IndividualBumpDownStrongtype(boost::any& anyptr,
        //        boost::any& anyptrparent,
        //        TreeCtrlSorted* MatMLTreeCtrl,
        //        wxTreeItemId itemParentId,
        //        wxTreeItemId previtemId,
        //        wxTreeItemId itemId
        //    );

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

        static void DnDSource(wxTreeEvent& event, TreeCtrlSorted* MatMLLibTreeCtrl, wxWindow* GUI);

        template< class MatML_Class,
            class MatML_ParentClass,
            class MatML_ContClass,
            class MatML_GUI,
            MatML_ContClass& (MatML_ParentClass::* cont_func)()
        >
            void OnDeleteLibMatML(wxCommandEvent& event);
  
    };
 
}//bellshire namespace

#include "bellshire/GUI/BT_MatML_MatML_GUI_Base.inl"
