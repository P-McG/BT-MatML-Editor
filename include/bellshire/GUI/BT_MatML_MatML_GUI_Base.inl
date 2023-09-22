#pragma once

// For compilers that support pre-compilation, includes "wx/wx.h".
#include "wx/wxprec.h"
#include "wx/config.h"

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include <memory>
#include <utility>

#include "bellshire/GUI/BT_MatML_MatML_GUI_Base.h"

#include "bellshire/GUI/BT_MatML_TreeCtrlSorted.h"
#include "bellshire/GUI/BT_MatML_MatMLDropTarget.h"
#include "bellshire/Lib/BT_MatML_MatML_Lib.h"
#include "bellshire/utilities/BT_MatML_Get_Associated_Base_type.h"
#include "bellshire/GUI/utilities/BT_MatML_Get_Associated_GUI_type.h"

#include "bellshire/matml31.hxx"
#include "bellshire/Lib/matml31_lib.hxx"

using namespace bellshire::GUI;


template<typename EventTag, typename Class, typename EventArg, typename EventHandler >
void MatML_GUI_Base::PopupLinkBind(wxMenu& menu, ::std::string desc, const EventTag& eventType, void(Class::*& method)(EventArg&), EventHandler* handler)
{
    wxMenuItem* PopupMenuItem{ new wxMenuItem(&menu, wxID_ANY, wxString(desc.c_str()), wxEmptyString, wxITEM_NORMAL) };
    menu.Append(PopupMenuItem);
    wxEvtHandler::Bind(eventType, method, handler, PopupMenuItem->GetId(), wxID_ANY, NULL);

}


template<class MatML_Class>
observer_ptr < MatML_Class >  MatML_GUI_Base::GetSelMatML(TreeCtrlSorted* MatMLTreeCtrl)
{

    wxTreeItemId selItemId{ MatMLTreeCtrl->GetSelection() };
    MatMLTreeItemData* item{ NULL };

    if (selItemId.IsOk()) {

        item = (MatMLTreeItemData*)(MatMLTreeCtrl->GetItemData(selItemId));
        const ::boost::any& anyptr(item->GetAnyMatMLDataPointer());

        try {
            return boost::any_cast<observer_ptr<MatML_Class> >(anyptr);
        }
        catch (const boost::bad_any_cast&) {}
    }

    return observer_ptr<MatML_Class>();
}

template<class MatML_Class>
observer_ptr< MatML_Class >  MatML_GUI_Base::GetSelParentMatML(TreeCtrlSorted* MatMLTreeCtrl)
{
    wxTreeItemId selItemId{ MatMLTreeCtrl->GetSelection() };

    if (selItemId.IsOk()) {
        wxTreeItemId selItemParentId{ MatMLTreeCtrl->GetItemParent(selItemId) };

        if (selItemParentId.IsOk()) {

            MatMLTreeItemData* item{ (MatMLTreeItemData*)(MatMLTreeCtrl->GetItemData(selItemParentId)) };
            ::boost::any anyptr(item->GetAnyMatMLDataPointer());

            try {
                return boost::any_cast<observer_ptr<MatML_Class> >(anyptr);
            }
            catch (boost::bad_any_cast&) {}
        }
    }

    return observer_ptr<MatML_Class>();
}

template<typename MatML_ParentClass, typename GUI_ParentClass>
void  MatML_GUI_Base::SetupSel(TreeCtrlSorted* MatMLTreeCtrl)
{
    wxTreeItemId selItemId{ MatMLTreeCtrl->GetSelection() };
    wxTreeItemId selItemParentId{ MatMLTreeCtrl->GetItemParent(selItemId) };

    auto element{ remove_strongly_typed_on_observer_ptr_v(GetSelMatML<MatML_ParentClass>(MatMLTreeCtrl)) };
    if (element) {
        typename bellshire::GUI::utilities::Functor_SetupCtrl_MatMLTree_GUI::Data data{ 
            MatMLTreeCtrl, selItemParentId, wxTreeItemId(), selItemId 
        };
        typename bellshire::GUI::utilities::Functor_SetupCtrl_MatMLTree_GUI func1{ data };
        GUI_ParentClass::TraverseMatMLTree(element, func1);

        wxTreeItemId selNextItemId{ MatMLTreeCtrl->GetNextSibling(selItemId) };
        if (selNextItemId.IsOk()) {

            MatMLTreeCtrl->SelectItem(selNextItemId);
            MatMLTreeCtrl->Expand(selNextItemId);
        }
        if (selItemId.IsOk()) MatMLTreeCtrl->Delete(selItemId);
    }
}

template<typename MatML_ParentClass, typename GUI_ParentClass>
void  MatML_GUI_Base::SetupSelParent(TreeCtrlSorted* MatMLTreeCtrl)
{
    wxTreeItemId selItemId{ MatMLTreeCtrl->GetSelection() };
    wxTreeItemId selItemParentId{ MatMLTreeCtrl->GetItemParent(selItemId) };
    wxTreeItemId selItemGrandParentId{ MatMLTreeCtrl->GetItemParent(selItemParentId) };

    auto element{ remove_strongly_typed_on_observer_ptr_v(GetSelParentMatML<MatML_ParentClass>(MatMLTreeCtrl)) };
    typename bellshire::GUI::utilities::Functor_SetupCtrl_MatMLTree_GUI::Data data{ MatMLTreeCtrl, selItemGrandParentId, wxTreeItemId(), selItemParentId };
    typename bellshire::GUI::utilities::Functor_SetupCtrl_MatMLTree_GUI func1(data);
    GUI_ParentClass::TraverseMatMLTree(element, func1);

    wxTreeItemId selNextItemId{ MatMLTreeCtrl->GetNextSibling(selItemId) };
    if (selNextItemId.IsOk()) {

        MatMLTreeCtrl->SelectItem(selNextItemId);
        MatMLTreeCtrl->Expand(selNextItemId);
    }

    if (selItemParentId.IsOk())
        MatMLTreeCtrl->Delete(selItemParentId);
}


template<class InputIterator, class T>
InputIterator  MatML_GUI_Base::find(InputIterator first, InputIterator last, const T& val)
{
    while (first != last) {
        if (&*first == val) return first;
        ++first;
    }
    return last;
}

/// <summary>
/// 
/// 
///  Note: strongly typed not permited
/// </summary>
/// <typeparam name="Child_GUI"></typeparam>
/// <typeparam name="MatML_First"></typeparam>
/// <typeparam name="MatML_Second"></typeparam>
/// <param name="treectrl"></param>
/// <param name="itemParentId"></param>
/// <param name="itemId"></param>
/// <param name="first"></param>
/// <param name="nextitemId"></param>
/// <param name="second"></param>
template<class Child_GUI, class MatML_First, class MatML_Second>
void  MatML_GUI_Base::MatMLTreeCtrlBumpDown(TreeCtrlSorted*& treectrl,
    wxTreeItemId& itemParentId,
    wxTreeItemId& itemId,
    MatML_First first,
    wxTreeItemId& nextitemId,
    MatML_Second second
)
{
    if (first && second) {

        //set up the functor's data
        //for the first MatML element
        bellshire::GUI::utilities::Functor_SetupCtrl_MatMLTree_GUI::Data data_first{ 
            treectrl, itemParentId, wxTreeItemId(), itemId
        };
        //Traverse the MatML tree and execute the functor.
        //for the first MatML element
        bellshire::GUI::utilities::Functor_SetupCtrl_MatMLTree_GUI func1(data_first);
        Child_GUI::TraverseMatMLTree(first, func1);

        //set up the functor's data
        //for the second MatML element
        bellshire::GUI::utilities::Functor_SetupCtrl_MatMLTree_GUI::Data data_second{
            treectrl, itemParentId, wxTreeItemId(), nextitemId
        };
        //Traverse the MatML tree and execute the functor.
        //for the second MatML element
        bellshire::GUI::utilities::Functor_SetupCtrl_MatMLTree_GUI func2(data_second);
        Child_GUI::TraverseMatMLTree(second, func2);

        treectrl->SelectItem(treectrl->GetNextSibling(nextitemId));//setup so selection bumps down

        treectrl->Delete(itemId);
        treectrl->Delete(nextitemId);
    }
}


template<class Child_GUI, class MatML>
void  MatML_GUI_Base::MatMLTreeCtrlBumpUp(TreeCtrlSorted*& treectrl,
    wxTreeItemId& itemParentId,
    wxTreeItemId& previtemId,
    observer_ptr < MatML > first,
    wxTreeItemId& itemId,
    observer_ptr < MatML > second
)
{
    typename bellshire::GUI::utilities::Functor_SetupCtrl_MatMLTree_GUI::Data data1{ treectrl, itemParentId, wxTreeItemId(), previtemId };
    typename bellshire::GUI::utilities::Functor_SetupCtrl_MatMLTree_GUI func1(data1);
    Child_GUI::TraverseMatMLTree(first, func1);

    typename bellshire::GUI::utilities::Functor_SetupCtrl_MatMLTree_GUI::Data data2{ treectrl, itemParentId, wxTreeItemId(), itemId };
    typename bellshire::GUI::utilities::Functor_SetupCtrl_MatMLTree_GUI func2(data2);
    Child_GUI::TraverseMatMLTree(second, func2);

    treectrl->SelectItem(treectrl->GetNextSibling(previtemId));//setup so selection bumps down

    treectrl->Delete(previtemId);
    treectrl->Delete(itemId);//perform last so selection bumps down
}

template< class MatML_Class,
    class MatML_ParentClass,
    class MatML_ContClass,
    class MatML_GUI,
    MatML_ContClass& (MatML_ParentClass::* cont_func)()
>
void MatML_GUI_Base::IndividualBumpUp(boost::any anyptr,
    boost::any anyptrparent,
    TreeCtrlSorted* MatMLTreeCtrl,
    wxTreeItemId itemParentId,
    wxTreeItemId previtemId,
    wxTreeItemId itemId
)
{
    try {
        // Maybe called with different anyptrparent type than MatML_ParentClass.
        if (anyptrparent.type() == typeid(observer_ptr<MatML_ParentClass>)) {

            //Remove strongly typed from element
            auto element{
                remove_strongly_typed_on_observer_ptr_v(
                boost::any_cast<observer_ptr<MatML_Class>>(anyptr)
            )};

            //Remove strongly typed from elementParent
            const auto& element_parent{
                remove_strongly_typed_on_observer_ptr_v(
                boost::any_cast<observer_ptr<MatML_ParentClass>>(anyptrparent)
            )};

            assert(element_parent && element);

            //Find the element in the MatML Tree and bump down
            const auto data(MatML_Base::FindAndBumpUp(element, (element_parent->*cont_func)()));
            MatMLTreeCtrlBumpUp<MatML_GUI>(MatMLTreeCtrl, itemParentId, previtemId, data.first, itemId, data.second);

            return;
            
        }
    }
    catch (const boost::bad_any_cast&) {};//do nothing
}

template< class MatML_Class,
    class MatML_ParentClass,
    class MatML_ContClass,
    class MatML_GUI,
    MatML_ContClass& (MatML_ParentClass::* cont_func)()
>
void  MatML_GUI_Base::IndividualBumpUpHavingId(
    boost::any& anyptr,
    boost::any& anyptrparent,
    TreeCtrlSorted* MatMLTreeCtrl,
    wxTreeItemId itemParentId,
    wxTreeItemId previtemId,
    wxTreeItemId itemId
)
{
    try {
        if (anyptrparent.type() == typeid(observer_ptr<MatML_ParentClass>)) {
            auto element{ remove_strongly_typed_on_observer_ptr_v(boost::any_cast<observer_ptr<MatML_Class>>(anyptr)) };
            auto element_parent{ boost::any_cast<observer_ptr<MatML_ParentClass>>(anyptrparent) };

            assert(element_parent && element);

            auto data(FindAndBumpUpHavingId(element, (element_parent->*cont_func)()));
            MatMLTreeCtrlBumpUp<MatML_GUI>(MatMLTreeCtrl, itemParentId, previtemId, data.first, itemId, data.second);

            return;
            
        }
    }
    catch (const boost::bad_any_cast&) {};//do nothing
}


template< class MatML_Class,
    class MatML_ParentClass,
    class MatML_ContClass,
    class MatML_GUI,
    MatML_ContClass& (MatML_ParentClass::* cont_func)()
>
void  MatML_GUI_Base::IndividualBumpUpHavingOptionalId(boost::any anyptr,
    boost::any anyptrparent,
    TreeCtrlSorted* MatMLTreeCtrl,
    wxTreeItemId itemParentId,
    wxTreeItemId previtemId,
    wxTreeItemId itemId
)
{
    try {
        if (anyptrparent.type() == typeid(MatML_ParentClass*)) {
            auto element{ boost::any_cast<observer_ptr<MatML_Class>> (anyptr) };
            auto element_parent{ boost::any_cast<observer_ptr<MatML_ParentClass>>(anyptrparent) };

            if (element && element_parent) {
                auto data(FindAndBumpUpHavingOptionalId(element, (element_parent->*cont_func)()));
                if (data.first && data.second)
                    MatMLTreeCtrlBumpUp<MatML_GUI>(MatMLTreeCtrl, itemParentId, previtemId, data.first, itemId, data.second);

                return;
            }
        }
    }
    catch (const boost::bad_any_cast&) {};//do nothing
}



template< class MatML_Class,
    class MatML_ParentClass,
    class MatML_ContClass,
    class MatML_GUI,
    MatML_ContClass& (MatML_ParentClass::* cont_func)()
>
void MatML_GUI_Base::IndividualBumpDown(
    boost::any& anyptr,
    boost::any& anyptrparent,
    TreeCtrlSorted* MatMLTreeCtrl,
    wxTreeItemId itemParentId,
    wxTreeItemId itemId,
    wxTreeItemId nextitemId
)
{
    try {
        // Maybe called with different anyptrparent type than MatML_ParentClass.
        if (anyptrparent.type() == typeid(observer_ptr<MatML_ParentClass>)) {

            //Remove strongly typed from element
            auto element{ 
                remove_strongly_typed_on_observer_ptr_v(
                boost::any_cast<observer_ptr<MatML_Class>>(anyptr)
            )};

            //Remove strongly typed from elementParent
            const auto& element_parent{ 
                remove_strongly_typed_on_observer_ptr_v(
                boost::any_cast<observer_ptr<MatML_ParentClass>>(anyptrparent)
            )};
            
            assert(element_parent && element);

            //Find the element in the MatML Tree and bump down.
            const auto data{ MatML_Base::FindAndBumpDown(element, (element_parent->*cont_func)()) };
            MatMLTreeCtrlBumpDown<MatML_GUI>(MatMLTreeCtrl, itemParentId, itemId, data.first, nextitemId, data.second);
            

            return;
        }
    }
    catch (const boost::bad_any_cast&) {};//do nothing
}


template< class MatML_Class,
    class MatML_ParentClass,
    class MatML_ContClass,
    class MatML_GUI,
    MatML_ContClass& (MatML_ParentClass::* cont_func)()
>
void  MatML_GUI_Base::IndividualBumpDownHavingId(
    boost::any& anyptr,
    boost::any& anyptrparent,
    TreeCtrlSorted* MatMLTreeCtrl,
    wxTreeItemId itemParentId,
    wxTreeItemId itemId,
    wxTreeItemId nextitemId
)
{
    try {
        // Maybe called with different anyptrparent type than MatML_ParentClass.
        if (anyptrparent.type() == typeid(observer_ptr<MatML_ParentClass>)) {
            auto element{ remove_strongly_typed_on_observer_ptr_v(boost::any_cast<observer_ptr<MatML_Class>>(anyptr)) };
            auto element_parent{ boost::any_cast<observer_ptr<MatML_ParentClass>>(anyptrparent) };

            assert(element_parent && element);

            auto data{ FindAndBumpDownHavingId(element, (element_parent->*cont_func)()) };
            MatMLTreeCtrlBumpDown<MatML_GUI>(MatMLTreeCtrl, itemParentId, itemId, data.first, nextitemId, data.second);

            return;
            
        }
    }
    catch (const boost::bad_any_cast&) {};//do nothing
}

template< class MatML_Class,
    class MatML_ParentClass,
    class MatML_ContClass,
    class MatML_GUI,
    MatML_ContClass& (MatML_ParentClass::* cont_func)()
>
void  MatML_GUI_Base::IndividualBumpDownHavingOptionalId(
    boost::any& anyptr,
    boost::any& anyptrparent,
    TreeCtrlSorted* MatMLTreeCtrl,
    wxTreeItemId itemParentId,
    wxTreeItemId itemId,
    wxTreeItemId nextitemId
)
{
    try {
        // Maybe called with different anyptrparent type than MatML_ParentClass.
        if (anyptrparent.type() == typeid(observer_ptr < MatML_ParentClass>)) {

            auto element{ remove_strongly_typed_on_observer_ptr_v(boost::any_cast<observer_ptr<MatML_Class>> (anyptr)) };
            auto element_parent{ boost::any_cast<observer_ptr<MatML_ParentClass>>(anyptrparent) };

            assert(element_parent && element);

            auto data(FindAndBumpDownHavingOptionalId(element, (element_parent->*cont_func)()));
            MatMLTreeCtrlBumpDown<MatML_GUI>(MatMLTreeCtrl, itemParentId, itemId, data.first, nextitemId, data.second);

            return;
            
        }
    }
    catch (const boost::bad_any_cast&) {};//do nothing
}


template< class MatML_Class,
    class MatML_ParentClass,
    class MatML_ContClass,
    class MatML_GUI,
    MatML_ContClass& (MatML_ParentClass::* cont_func)()
>
void MatML_GUI_Base::OnDeleteLibMatML(wxCommandEvent& event) 
{

    auto element{ MatML_GUI_Base::GetSelMatML<MatML_Class>(m_MatMLLibTreeCtrl) };
    auto element_parent{ MatML_GUI_Base::GetSelParentMatML<MatML_ParentClass>(m_MatMLLibTreeCtrl) };
    if (element_parent) {
        MatML_Base::DeleteSeqContChild(element, (element_parent->*cont_func)());
        MatML_GUI_Base::SetupSelParent<MatML_ParentClass, MatML_GUI>(m_MatMLLibTreeCtrl);
    }
}
