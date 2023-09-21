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
//#include "bellshire/Lib/utilities/BT_MatML_Get_Associated_Lib_type.h"
//#include "bellshire/GUI/utilities/BT_MatML_Functor_SetupCtrl_MatMLTree_GUI.h"

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
//
///// <summary>
// /// Setup the selected wxTreeCtrl Item for MatML strongtypes 
// /// </summary>
// /// <typeparam name="MatML_ParentClass"></typeparam>
// /// <typeparam name="GUI_ParentClass"></typeparam>
// /// <param name="MatMLTreeCtrl"></param>
//template<typename MatML_ParentClass, typename GUI_ParentClass>
//void MatML_GUI_Base::SetupStrongTypeSel(TreeCtrlSorted* MatMLTreeCtrl)
//{
//    wxTreeItemId selItemId{ MatMLTreeCtrl->GetSelection() };
//    wxTreeItemId selItemParentId{ MatMLTreeCtrl->GetItemParent(selItemId) };
//
//    /* Get the MatML Data, which is selected in the wxTreeCtrl */
//    MatML_ParentClass* element{ GetSelMatML<MatML_ParentClass>(MatMLTreeCtrl) };
//
//    /* Set up wxTreeCtrl to mimic the MatML Data starting at the selItemParent as the parent and the
//       selItemId as the previous Item in the tree.
//       Creates a new strongtype to weaktype linkage.
//    */
//    Functor_SetupCtrl_MatMLTree_GUI func1(Functor_SetupCtrl_MatMLTree_GUI::Data{ MatMLTreeCtrl, selItemParentId, wxTreeItemId(), selItemId });
//    GUI_ParentClass::TraverseMatMLTree(element->t, func1);
//
//    const wxTreeItemId selNextItemId{ MatMLTreeCtrl->GetNextSibling(selItemId) };/* Get the next sibling in the tree () */
//    /* If the next sibling is okay then select and expand */
//    if (selNextItemId.IsOk()) {
//
//        MatMLTreeCtrl->SelectItem(selNextItemId);
//        MatMLTreeCtrl->Expand(selNextItemId);
//    }
//
//    /* No longer need the original Selected Item, so delete */
//    element->null();//Break old Strongtype to Weaktype linkage.
//    if (selItemId.IsOk())  MatMLTreeCtrl->Delete(selItemId);
//
//}

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

//
//template<typename MatML_ParentClass, typename GUI_ParentClass>
//void  MatML_GUI_Base::SetupStrongTypeSelParent(TreeCtrlSorted* MatMLTreeCtrl)
//{
//    wxTreeItemId selItemId{ MatMLTreeCtrl->GetSelection() };
//    wxTreeItemId selItemParentId{ MatMLTreeCtrl->GetItemParent(selItemId) };
//    wxTreeItemId selItemGrandParentId{ MatMLTreeCtrl->GetItemParent(selItemParentId) };
//
//    MatML_ParentClass* element{ GetSelParentMatML<MatML_ParentClass>(MatMLTreeCtrl) };
//
//    Functor_SetupCtrl_MatMLTree_GUI func1(Functor_SetupCtrl_MatMLTree_GUI::Data{ MatMLTreeCtrl, selItemGrandParentId, wxTreeItemId(), selItemParentId });
//    GUI_ParentClass::TraverseMatMLTree(element->t, func1);
//
//    wxTreeItemId selNextItemId{ MatMLTreeCtrl->GetNextSibling(selItemId) };
//    if (selNextItemId.IsOk()) {
//
//        MatMLTreeCtrl->SelectItem(selNextItemId);
//        MatMLTreeCtrl->Expand(selNextItemId);
//    }
//
//    if (selItemParentId.IsOk())
//        MatMLTreeCtrl->Delete(selItemParentId);
//}


template<class InputIterator, class T>
InputIterator  MatML_GUI_Base::find(InputIterator first, InputIterator last, const T& val)
{
    while (first != last) {
        if (&*first == val) return first;
        ++first;
    }
    return last;
}
//
///// <summary>
///// Does Nothing. 
///// Child are required in the MatML structure and are
///// inserted automatically through the Default classes.
///// </summary>
///// <typeparam name="MatML_Class"></typeparam>
///// <typeparam name="MatML_ContClass"></typeparam>
///// <param name="MatML"></param>
//template<typename MatML_Class, typename MatML_ContClass >
//void  MatML_GUI_Base::InsertChild(MatML_ContClass& MatML_Cont) {
//    Warning("Required element already exist");
//}
//
///// <summary>
///// Inserts the MatML Data into the MatML container element
///// </summary>
///// <typeparam name="MatML_Class"></typeparam>
///// <typeparam name="MatML_ContClass"></typeparam>
///// <param name="MatML">MatML Container Class</param>
//template<typename MatML_Class, typename MatML_ContClass >
//void MatML_GUI_Base::InsertContChild(MatML_ContClass& MatML_Cont)
//{
//    auto& cont(MatML_Cont);
//    if (cont.present())
//        cont = Default<MatML_Class>();
//    else {
//        cont.set(Default<MatML_Class>());
//    }
//}
//
///// <summary>
///// Inserts the MatML Data into the MatML sequence container element
///// </summary>
///// <typeparam name="MatML_Class"></typeparam>
///// <typeparam name="MatML_ContClass"></typeparam>
///// <param name="MatML"></param>
//template<typename MatML_Class, typename MatML_ContClass >
//void  MatML_GUI_Base::InsertSeqContChild(MatML_ContClass& MatML_Cont)
//{
//    auto& cont(MatML_Cont);
//    try {
//        cont.push_back(Default<MatML_Class>());
//    }
//    catch (const xml_schema::duplicate_id&) {}
//}

///// <summary>
///// Does Nothing. 
///// Child are REQUIRED in the MatML structure and are
///// inserted automatically through the Default classes.
///// </summary>
///// <typeparam name="MatML_Class"></typeparam>
///// <typeparam name="MatML_ContClass"></typeparam>
///// <param name="MatML"></param>
//template<typename MatML_ContClass >
//void  MatML_GUI_Base::DeleteChild(MatML_ContClass& MatML)
//{
//    Warning("Can not delete required element");
//}
//
//template<typename MatML_ContClass >
//void  MatML_GUI_Base::DeleteContChild(MatML_ContClass& MatML_Cont)
//{
//    auto& cont(MatML_Cont);
//    if (cont.present())
//        cont.reset();
//}

//template<typename MatML_Class, typename MatML_ContClass>
//void MatML_GUI_Base::DeleteSeqContChild(observer_ptr < MatML_Class > MatML, MatML_ContClass& MatML_Cont)
//{
//    auto& cont(MatML_Cont);
//
//    auto iter = find(cont.begin(), cont.end(), MatML);
//    if (iter != cont.end())
//        cont.erase(iter);
//}
//
///// <summary>
// /// Does Nothing. 
// /// Child are required in the MatML structure and are
// /// inserted automatically through the Default classes.
// /// </summary>
//template<typename MatML_Class, typename MatML_ContClass>
//void  MatML_GUI_Base::PasteChild(observer_ptr < MatML_Class > MatML, MatML_ContClass& MatML_Cont)
//{
//    Warning("Can not paste over Required element");
//}
//
//template<typename MatML_Class, typename MatML_ContClass>
//void  MatML_GUI_Base::PasteContChild(observer_ptr < MatML_Class > MatML, MatML_ContClass& MatML_Cont)
//{
//    auto& cont(MatML_Cont);
//
//    if (cont.present())
//        cont = *MatML;
//    else {
//        cont.set(*MatML);
//    }
//}
//
//template<typename MatML_Class, typename MatML_ContClass>
//void  MatML_GUI_Base::PasteSeqContChild(observer_ptr < MatML_Class > MatML, MatML_ContClass& MatML_Cont)
//{
//    auto& cont(MatML_Cont);
//
//    try {
//        cont.push_back(*MatML);
//    }
//    catch (const xml_schema::duplicate_id&) {}
//}
//
///// <summary>
///// Swap function with MatML Classes that have required Id.
///// This has the added complication that the id's can not
///// be duplicated during the swap.
///// </summary>
///// <typeparam name="MatML_Class"></typeparam>
///// <param name="matml0"></param>
///// <param name="matml1"></param>
//template<class MatML_Class>
//void MatML_GUI_Base::SwapHavingId(observer_ptr < MatML_Class >matml0, observer_ptr < MatML_Class > matml1)
//{
//    auto temp0(*matml0);
//    auto temp1(*matml1);
//
//    //Replace the id to prevent id collision
//    xml_schema::id tempid(temp1.id());
//    temp1.id(xml_schema::id(std::string("BT-TEMP-ID")));
//
//    *matml0 = temp1;
//    *matml1 = temp0;
//
//    //Replace the temp id with the previous one
//    matml0->id(tempid);
//}
//
///// <summary>
///// Swap function with MatML Classes that have Optional Id.
///// This has the added complication that the id's can not
///// be duplicated during the swap.
///// </summary>
///// <typeparam name="MatML_Class"></typeparam>
///// <param name="matml0"></param>
///// <param name="matml1"></param>
//template<class MatML_Class>
//void  MatML_GUI_Base::SwapHavingOptionalId(observer_ptr < MatML_Class > matml0, observer_ptr < MatML_Class > matml1)
//{
//    auto temp0(*matml0);
//    auto temp1(*matml1);
//
//    xml_schema::id tempid("");
//
//    //Replace the id to prevent id collision
//    if (temp1.id().present()) {
//        tempid = temp1.id().get();
//        temp1.id(xml_schema::id(std::string("BT-TEMP-ID")));
//    }
//
//    *matml0 = temp1;
//    *matml1 = temp0;
//
//    //Replace the temp id with the previous one
//    if (temp1.id().present())
//        matml0->id().set(tempid);
//}
//
///// <summary>
///// For the MatML Data finds the matching
///// MatML Class element and bumps it down one.
///// 
///// Note: No strongtype allowed
///// </summary>
///// <typeparam name="MatML_Class"></typeparam>
///// <typeparam name="MatML_ContClass"></typeparam>
///// <param name="matml">Element to be found and bumped down</param>
///// <param name="cont">Container of the element</param>
///// <returns></returns>
//template<class MatML_Class, class MatML_ContClass>
//decltype(auto)
//MatML_GUI_Base::MatMLFindAndBumpDown(MatML_Class matml, MatML_ContClass& cont)
//{
//
//    if (cont.empty() || cont.size() < 2)
//        return std::make_pair(
//            MatML_Class{ nullptr },
//            MatML_Class{ nullptr }
//        );
//
//    for (auto iter = cont.begin(); iter != cont.end() - 1; ++iter) {
//        if ( (void*)(& *matml) == (void*)(&*iter)) {//shallow comparator: if the pointer are the same (aka same memory location)
//            std::swap(*(iter), *(iter + 1));
//
//            return std::make_pair( observer_ptr< MatML_Class::element_type >( & *iter), 
//                observer_ptr< MatML_Class::element_type >( & *(iter + 1)) 
//            );
//        }
//    }
//    
//    return std::make_pair(MatML_Class(nullptr), MatML_Class(nullptr));
//}

//template< class MatML_Class, class MatML_ContClass >
//std::pair< observer_ptr<MatML_Class>, observer_ptr<MatML_Class> >
// MatML_GUI_Base::MatMLFindAndBumpDownStrongtype(observer_ptr < MatML_Class > matml, MatML_ContClass& cont)
//{
//    if (cont.empty() || cont.size() < 2)  return std::make_pair(nullptr, nullptr);
//
//    for (auto iter = cont.begin(); iter != cont.end() - 1; ++iter) {
//        if ((matml->t) == (&*iter)) {//if the pointer are the same (aka same memory location
//            std::swap(*(iter), *(iter + 1));
//
//            return std::make_pair(&*iter, &*(iter + 1));
//        }
//    }
//    return std::make_pair(nullptr, nullptr);
//}

//
///// <summary>
///// Similar to MatMLFindAndBumpDown with the added complication 
///// that the Required Id's cannot be duplicated during the swap.
///// </summary>
///// <typeparam name="MatML_Class"></typeparam>
///// <typeparam name="MatML_ContClass"></typeparam>
///// <param name="matml"></param>
///// <param name="cont"></param>
///// <returns></returns>
//template<class MatML_Class, class MatML_ContClass>
//std::pair< observer_ptr<MatML_Class>, observer_ptr<MatML_Class> >
//MatML_GUI_Base::MatMLFindAndBumpDownHavingId(observer_ptr < MatML_Class> matml, MatML_ContClass& cont)
//{
//    if (cont.empty() || cont.size() < 2)  return std::make_pair(nullptr, nullptr);
//
//    for (auto iter = cont.begin(); iter != cont.end() - 1; ++iter) {
//        if ((matml) == (&*iter)) {//if the pointer are the same (aka same memory location
//
//            SwapHavingId(&*(iter), &*(iter + 1));
//
//            return std::make_pair(&*iter, &*(iter + 1));
//        }
//    }
//    return std::make_pair(nullptr, nullptr);
//}
//
///// <summary>
///// Similar to MatMLFindAndBumpDown with the added complication 
///// that the optional Id's cannot be duplicated during the swap.
///// </summary>
///// <typeparam name="MatML_Class"></typeparam>
///// <typeparam name="MatML_ContClass"></typeparam>
///// <param name="matml"></param>
///// <param name="cont"></param>
///// <returns></returns>
//template<class MatML_Class, class MatML_ContClass>
//std::pair< observer_ptr<MatML_Class>, observer_ptr<MatML_Class> >
// MatML_GUI_Base::MatMLFindAndBumpDownHavingOptionalId(observer_ptr < MatML_Class> matml, MatML_ContClass& cont)
//{
//    if (cont.empty() || cont.size() < 2)  return std::make_pair(nullptr, nullptr);
//
//    for (auto iter = cont.begin(); iter != cont.end() - 1; ++iter) {
//        if ((matml) == (&*iter)) {//if the pointer are the same (aka same memory location
//
//            SwapHavingOptionalId(&*(iter), &*(iter + 1));
//
//            return std::make_pair(&*iter, &*(iter + 1));
//        }
//    }
//    return std::make_pair(nullptr, nullptr);
//}

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
        bellshire::GUI::utilities::Functor_SetupCtrl_MatMLTree_GUI::Data data_first{ 
            treectrl, itemParentId, wxTreeItemId(), itemId
        };
        bellshire::GUI::utilities::Functor_SetupCtrl_MatMLTree_GUI func1(data_first);
        Child_GUI::TraverseMatMLTree(first, func1);

        bellshire::GUI::utilities::Functor_SetupCtrl_MatMLTree_GUI::Data data_second{
            treectrl, itemParentId, wxTreeItemId(), nextitemId
        };
        bellshire::GUI::utilities::Functor_SetupCtrl_MatMLTree_GUI func2(data_second);
        Child_GUI::TraverseMatMLTree(second, func2);

        treectrl->SelectItem(treectrl->GetNextSibling(nextitemId));//setup so selection bumps down

        treectrl->Delete(itemId);
        treectrl->Delete(nextitemId);
    }
}
//
//template<class MatML_Class, class MatML_ContClass>
//std::pair< observer_ptr<MatML_Class>, observer_ptr<MatML_Class> >
// MatML_GUI_Base::MatMLFindAndBumpUp(observer_ptr < MatML_Class> matml, MatML_ContClass& cont)
//{
//    if (cont.empty() || cont.size() < 2)  return  std::make_pair(observer_ptr<MatML_Class>(nullptr), observer_ptr<MatML_Class>(nullptr));
//
//    for (auto iter = cont.begin() + 1; iter != cont.end(); ++iter) {
//        if (matml.get() == (&*iter)) {//if the pointer are the same (aka same memory location
//
//            std::swap(*(iter - 1), *(iter));
//
//            return std::make_pair(observer_ptr<MatML_Class>(&*(iter - 1)), observer_ptr<MatML_Class>(&*iter));
//        }
//    }
//    return  std::make_pair(observer_ptr<MatML_Class>(nullptr), observer_ptr<MatML_Class>(nullptr));
//}
//
//template<class MatML_Class, class MatML_ContClass>
//std::pair< observer_ptr<MatML_Class>, observer_ptr<MatML_Class>>
//MatML_GUI_Base::MatMLFindAndBumpUpStrongtype(observer_ptr<MatML_Class> matml, MatML_ContClass& cont)
//{
//    if (cont.empty() || cont.size() < 2)  return  std::make_pair(nullptr, nullptr);
//
//    for (auto iter = cont.begin() + 1; iter != cont.end(); ++iter) {
//        if ((matml->t) == (&*iter)) {//if the pointer are the same (aka same memory location
//
//            std::swap(*(iter - 1), *(iter));
//
//            return std::make_pair(&*(iter - 1), &*iter);
//        }
//    }
//    return  std::make_pair(nullptr, nullptr);
//}
//
///// <summary>
///// Similar to MatMLFindAndBumpUp with the added complication 
///// that the Required Id's cannot be duplicated during the swap.
///// </summary>
///// <typeparam name="MatML_ContClass"></typeparam>
///// <param name="matml"></param>
///// <param name="cont"></param>
///// <returns></returns>
//template<class MatML_ContClass>
//std::pair<typename MatML_ContClass::value_type*, typename MatML_ContClass::value_type*>
// MatML_GUI_Base::MatMLFindAndBumpUpHavingId(typename MatML_ContClass::value_type* matml, MatML_ContClass& cont)
//{
//    if (cont.empty() || cont.size() < 2)  return  std::make_pair(nullptr, nullptr);
//
//    for (auto iter = cont.begin() + 1; iter != cont.end(); ++iter) {
//        if ((matml) == (&*iter)) {//if the pointer are the same (aka same memory location
//
//            SwapHavingId(&*(iter - 1), &*(iter));
//
//            return std::make_pair(&*(iter - 1), &*iter);
//        }
//    }
//    return  std::make_pair(nullptr, nullptr);
//}
//
///// <summary>
///// Similar to MatMLFindAndBumpUp with the added complication 
///// that the optional Id's cannot be duplicated during the swap.
///// </summary>
///// <typeparam name="MatML_ContClass"></typeparam>
///// <param name="matml"></param>
///// <param name="cont"></param>
///// <returns></returns>
//template<class MatML_ContClass>
//std::pair<typename MatML_ContClass::value_type*, typename MatML_ContClass::value_type*>
// MatML_GUI_Base::MatMLFindAndBumpUpHavingOptionalId(typename MatML_ContClass::value_type* matml, MatML_ContClass& cont)
//{
//    if (cont.empty() || cont.size() < 2)  return  std::make_pair(nullptr, nullptr);
//
//    for (auto iter = cont.begin() + 1; iter != cont.end(); ++iter) {
//        if ((matml) == (&*iter)) {//if the pointer are the same (aka same memory location
//
//            SwapHavingOptionalId(&*(iter - 1), &*(iter));
//
//            return std::make_pair(&*(iter - 1), &*iter);
//        }
//    }
//    return  std::make_pair(nullptr, nullptr);
//}

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

//
//template< class MatML_Class,
//    class MatML_ParentClass,
//    class MatML_ContClass,
//    class MatML_GUI,
//    MatML_ContClass& (MatML_ParentClass::* cont_func)()
//>
//void  MatML_GUI_Base::IndividualBumpUpStrongtype(boost::any anyptr,
//    boost::any anyptrparent,
//    TreeCtrlSorted* MatMLTreeCtrl,
//    wxTreeItemId itemParentId,
//    wxTreeItemId previtemId,
//    wxTreeItemId itemId
//)
//{
//    //using Type = remove_strongly_typed_on_t<MatML_Class>;
//    //using ParentType = remove_strongly_typed_on_t<MatML_ParentClass>;
//
//    try {
//        if (anyptrparent.type() == typeid(MatML_ParentClass*)) {
//            auto matmlElement 
//                = remove_strongly_typed_on_observer_ptr_v(boost::any_cast< MatML_Class* >(anyptr));
//            auto matmlParentElement 
//                = remove_strongly_typed_on_observer_ptr_v(boost::any_cast<MatML_ParentClass*>(anyptr));
//
//            using Type = remove_strongly_typed_on_t<typename MatML_Class>;
//            using ParentType = remove_strongly_typed_on_t<typename MatML_ParentClass>;
//
//            auto element=observer_ptr<Type>( matmlElement );
//            auto elementParent=observer_ptr<ParentType>(matmlParentElement );
//
//                auto data{
//                    FindAndBumpUp(element, (elementParent.get()->*cont_func)())
//                };
//         
//            if (data.second)
//                MatMLTreeCtrlBumpUp<MatML_GUI>(MatMLTreeCtrl, itemParentId, previtemId, data.first, itemId, data.second);
//
//            return;
//        }
//    }
//    catch (const boost::bad_any_cast&) {};//do nothing
//}

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
void  MatML_GUI_Base::IndividualBumpDownHavingOptionalId(boost::any& anyptr,
    boost::any& anyptrparent,
    TreeCtrlSorted* MatMLTreeCtrl,
    wxTreeItemId itemParentId,
    wxTreeItemId itemId,
    wxTreeItemId nextitemId
)
{
    try {
        if (anyptrparent.type() == typeid(MatML_ParentClass*)) {
            auto element{ remove_strongly_typed_on_observer_ptr_v(boost::any_cast<observer_ptr<MatML_Class>> (anyptr)) };
            auto element_parent{ boost::any_cast<observer_ptr<MatML_ParentClass>>(anyptrparent) };
            if (element && element_parent) {
                auto data(FindAndBumpDownHavingOptionalId(element, (element_parent->*cont_func)()));
                if (data.first && data.second)
                    MatMLTreeCtrlBumpDown<MatML_GUI>(MatMLTreeCtrl, itemParentId, itemId, data.first, nextitemId, data.second);

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
void MatML_GUI_Base::OnDeleteLibMatML(wxCommandEvent& event) 
{

    auto element{ MatML_GUI_Base::GetSelMatML<MatML_Class>(m_MatMLLibTreeCtrl) };
    auto element_parent{ MatML_GUI_Base::GetSelParentMatML<MatML_ParentClass>(m_MatMLLibTreeCtrl) };
    if (element_parent) {
        MatML_Base::DeleteSeqContChild(element, (element_parent->*cont_func)());
        MatML_GUI_Base::SetupSelParent<MatML_ParentClass, MatML_GUI>(m_MatMLLibTreeCtrl);
    }
}
