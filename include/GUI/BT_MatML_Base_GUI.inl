#pragma once


template<class MatML_Class>
MatML_Class* bellshire::MatML_Base_GUI::GetSelMatML(TreeCtrlSorted* MatMLTreeCtrl)
{

    wxTreeItemId selItemId = MatMLTreeCtrl->GetSelection();
    MatMLTreeItemData* item = NULL;

    if (selItemId.IsOk()) {

        item = (MatMLTreeItemData*)(MatMLTreeCtrl->GetItemData(selItemId));
        const ::boost::any& anyptr(item->GetAnyMatMLDataPointer());

        try {
            MatML_Class* element = boost::any_cast<MatML_Class*>(anyptr);
            if (element != 0) {

                return element;
            }
        }
        catch (const boost::bad_any_cast&) {}
    }

    return nullptr;
}

template<class MatML_Class>
MatML_Class* bellshire::MatML_Base_GUI::GetSelParentMatML(TreeCtrlSorted* MatMLTreeCtrl)
{

    wxTreeItemId selItemId = MatMLTreeCtrl->GetSelection();

    if (selItemId.IsOk()) {
        wxTreeItemId selItemParentId = MatMLTreeCtrl->GetItemParent(selItemId);

        if (selItemParentId.IsOk()) {

            MatMLTreeItemData* item = (MatMLTreeItemData*)(MatMLTreeCtrl->GetItemData(selItemParentId));
            ::boost::any anyptr(item->GetAnyMatMLDataPointer());

            try {
                MatML_Class* element = boost::any_cast<MatML_Class*>(anyptr);
                if (element != 0) {

                    return element;
                }
            }
            catch (boost::bad_any_cast&) {}
        }
    }

    return nullptr;
}

template<typename MatML_ParentClass, typename GUI_ParentClass>
void bellshire::MatML_Base_GUI::SetupSel(TreeCtrlSorted* MatMLTreeCtrl)
{
    wxTreeItemId selItemId = MatMLTreeCtrl->GetSelection();
    wxTreeItemId selItemParentId = MatMLTreeCtrl->GetItemParent(selItemId);

    MatML_ParentClass* element = GetSelMatML<MatML_ParentClass>(MatMLTreeCtrl);

    GUI_ParentClass::SetupMatMLTreeCtrl(MatMLTreeCtrl, selItemParentId, *element, selItemId);

    wxTreeItemId selNextItemId = MatMLTreeCtrl->GetNextSibling(selItemId);
    if (selNextItemId.IsOk()) {

        MatMLTreeCtrl->SelectItem(selNextItemId);
        MatMLTreeCtrl->Expand(selNextItemId);
    }
    if (selItemId.IsOk()) MatMLTreeCtrl->Delete(selItemId);
}

/// <summary>
 /// Setup the selected wxTreeCtrl Item for MatML strongtypes 
 /// </summary>
 /// <typeparam name="MatML_ParentClass"></typeparam>
 /// <typeparam name="GUI_ParentClass"></typeparam>
 /// <param name="MatMLTreeCtrl"></param>
template<typename MatML_ParentClass, typename GUI_ParentClass>
void bellshire::MatML_Base_GUI::SetupStrongTypeSel(TreeCtrlSorted* MatMLTreeCtrl)
{
    const wxTreeItemId selItemId = MatMLTreeCtrl->GetSelection();
    const wxTreeItemId selItemParentId = MatMLTreeCtrl->GetItemParent(selItemId);

    /* Get the MatML Data, which is selected in the wxTreeCtrl */
    MatML_ParentClass* element = GetSelMatML<MatML_ParentClass>(MatMLTreeCtrl);

    /* Set up wxTreeCtrl to mimic the MatML Data starting at the selItemParent as the parent and the
       selItemId as the previous Item in the tree.
       Creates a new strongtype to weaktype linkage.
    */
    GUI_ParentClass::SetupMatMLTreeCtrl(MatMLTreeCtrl, selItemParentId, *(element->t), selItemId);

    const wxTreeItemId selNextItemId = MatMLTreeCtrl->GetNextSibling(selItemId);/* Get the next sibling in the tree () */
    /* If the next sibling is okay then select and expand */
    if (selNextItemId.IsOk()) {

        MatMLTreeCtrl->SelectItem(selNextItemId);
        MatMLTreeCtrl->Expand(selNextItemId);
    }

    /* No longer need the original Selected Item, so delete */
    element->null();//Break old Strongtype to Weaktype linkage.
    if (selItemId.IsOk())  MatMLTreeCtrl->Delete(selItemId);

}

template<typename MatML_ParentClass, typename GUI_ParentClass>
void bellshire::MatML_Base_GUI::SetupSelParent(TreeCtrlSorted* MatMLTreeCtrl)
{
    wxTreeItemId selItemId = MatMLTreeCtrl->GetSelection();
    wxTreeItemId selItemParentId = MatMLTreeCtrl->GetItemParent(selItemId);
    wxTreeItemId selItemGrandParentId = MatMLTreeCtrl->GetItemParent(selItemParentId);

    MatML_ParentClass* element = GetSelParentMatML<MatML_ParentClass>(MatMLTreeCtrl);

    GUI_ParentClass::SetupMatMLTreeCtrl(MatMLTreeCtrl, selItemGrandParentId, *element, selItemParentId);

    wxTreeItemId selNextItemId = MatMLTreeCtrl->GetNextSibling(selItemId);
    if (selNextItemId.IsOk()) {

        MatMLTreeCtrl->SelectItem(selNextItemId);
        MatMLTreeCtrl->Expand(selNextItemId);
    }

    if (selItemParentId.IsOk())
        MatMLTreeCtrl->Delete(selItemParentId);
}

template<class InputIterator, class T>
InputIterator bellshire::MatML_Base_GUI::find(InputIterator first, InputIterator last, const T& val)
{
    while (first != last) {
        if (&*first == val) return first;
        ++first;
    }
    return last;
}

/// <summary>
/// Does Nothing. 
/// Child are required in the MatML structure and are
/// inserted automatically through the Default classes.
/// </summary>
/// <typeparam name="MatML_Class"></typeparam>
/// <typeparam name="MatML_ContClass"></typeparam>
/// <param name="MatML"></param>
template<typename MatML_Class, typename MatML_ContClass >
void bellshire::MatML_Base_GUI::InsertChild(MatML_ContClass& MatML_Cont) {
    Warning("Required element already exist");
}

/// <summary>
/// Inserts the MatML Data into the MatML container element
/// </summary>
/// <typeparam name="MatML_Class"></typeparam>
/// <typeparam name="MatML_ContClass"></typeparam>
/// <param name="MatML">MatML Container Class</param>
template<typename MatML_Class, typename MatML_ContClass >
void bellshire::MatML_Base_GUI::InsertContChild(MatML_ContClass& MatML_Cont)
{
    auto& cont(MatML_Cont);
    if (cont.present())
        cont = Default<MatML_Class>();
    else {
        cont.set(Default<MatML_Class>());
    }
}

/// <summary>
/// Inserts the MatML Data into the MatML sequence container element
/// </summary>
/// <typeparam name="MatML_Class"></typeparam>
/// <typeparam name="MatML_ContClass"></typeparam>
/// <param name="MatML"></param>
template<typename MatML_Class, typename MatML_ContClass >
void bellshire::MatML_Base_GUI::InsertSeqContChild(MatML_ContClass& MatML_Cont)
{
    auto& cont(MatML_Cont);
    try {
        cont.push_back(Default<MatML_Class>());
    }
    catch (const xml_schema::duplicate_id&) {}
}

/// <summary>
/// Does Nothing. 
/// Child are REQUIRED in the MatML structure and are
/// inserted automatically through the Default classes.
/// </summary>
/// <typeparam name="MatML_Class"></typeparam>
/// <typeparam name="MatML_ContClass"></typeparam>
/// <param name="MatML"></param>
template<typename MatML_ContClass >
void bellshire::MatML_Base_GUI::DeleteChild(MatML_ContClass& MatML)
{
    Warning("Can not delete required element");
}

template<typename MatML_ContClass >
void bellshire::MatML_Base_GUI::DeleteContChild(MatML_ContClass& MatML_Cont)
{
    auto& cont(MatML_Cont);
    if (cont.present())
        cont.reset();
}

template<typename MatML_Class, typename MatML_ContClass>
void bellshire::MatML_Base_GUI::DeleteSeqContChild(MatML_Class* MatML, MatML_ContClass& MatML_Cont)
{
    auto& cont(MatML_Cont);

    auto iter = find(cont.begin(), cont.end(), MatML);
    if (iter != cont.end())
        cont.erase(iter);
}

/// <summary>
 /// Does Nothing. 
 /// Child are required in the MatML structure and are
 /// inserted automatically through the Default classes.
 /// </summary>
template<typename MatML_Class, typename MatML_ContClass>
void bellshire::MatML_Base_GUI::PasteChild(MatML_Class* MatML, MatML_ContClass& MatML_Cont)
{
    Warning("Can not paste over Required element");
}

template<typename MatML_Class, typename MatML_ContClass>
void bellshire::MatML_Base_GUI::PasteContChild(MatML_Class* MatML, MatML_ContClass& MatML_Cont)
{
    auto& cont(MatML_Cont);

    if (cont.present())
        cont = *MatML;
    else {
        cont.set(*MatML);
    }
}

template<typename MatML_Class, typename MatML_ContClass>
void bellshire::MatML_Base_GUI::PasteSeqContChild(MatML_Class* MatML, MatML_ContClass& MatML_Cont)
{
    auto& cont(MatML_Cont);

    try {
        cont.push_back(*MatML);
    }
    catch (const xml_schema::duplicate_id&) {}
}

/// <summary>
/// Swap function with MatML Classes that have required Id.
/// This has the added complication that the id's can not
/// be duplicated during the swap.
/// </summary>
/// <typeparam name="MatML_Class"></typeparam>
/// <param name="matml0"></param>
/// <param name="matml1"></param>
template<class MatML_Class>
void bellshire::MatML_Base_GUI::SwapHavingId(MatML_Class* matml0, MatML_Class* matml1)
{
    auto temp0(*matml0);
    auto temp1(*matml1);

    //Replace the id to prevent id collision
    xml_schema::id tempid(temp1.id());
    temp1.id(xml_schema::id(std::string("BT-TEMP-ID")));

    *matml0 = temp1;
    *matml1 = temp0;

    //Replace the temp id with the previous one
    matml0->id(tempid);
}

/// <summary>
/// Swap function with MatML Classes that have Optional Id.
/// This has the added complication that the id's can not
/// be duplicated during the swap.
/// </summary>
/// <typeparam name="MatML_Class"></typeparam>
/// <param name="matml0"></param>
/// <param name="matml1"></param>
template<class MatML_Class>
void bellshire::MatML_Base_GUI::SwapHavingOptionalId(MatML_Class* matml0, MatML_Class* matml1)
{
    auto temp0(*matml0);
    auto temp1(*matml1);

    xml_schema::id tempid("");

    //Replace the id to prevent id collision
    if (temp1.id().present()) {
        tempid = temp1.id().get();
        temp1.id(xml_schema::id(std::string("BT-TEMP-ID")));
    }

    *matml0 = temp1;
    *matml1 = temp0;

    //Replace the temp id with the previous one
    if (temp1.id().present())
        matml0->id().set(tempid);
}

template<class MatML_Class, class MatML_ContClass>
std::pair<MatML_Class*, MatML_Class*>
bellshire::MatML_Base_GUI::MatMLFindAndBumpDown(MatML_Class* matml, MatML_ContClass& cont)
{
    if (cont.empty() || cont.size() < 2)  return std::make_pair(nullptr, nullptr);

    for (auto iter = cont.begin(); iter != cont.end() - 1; ++iter) {
        if ((matml) == (&*iter)) {//if the pointer are the same (aka same memory location
            std::swap(*(iter), *(iter + 1));

            return std::make_pair(&*iter, &*(iter + 1));
        }
    }
    return std::make_pair(nullptr, nullptr);
}

template< class MatML_Class, class MatML_ContClass >
std::pair< MatML_Class*,MatML_Class* >
bellshire::MatML_Base_GUI::MatMLFindAndBumpDownStrongtype(MatML_Class* matml, MatML_ContClass& cont)
{
    if (cont.empty() || cont.size() < 2)  return std::make_pair(nullptr, nullptr);

    for (auto iter = cont.begin(); iter != cont.end() - 1; ++iter) {
        if ((matml->t) == (&*iter)) {//if the pointer are the same (aka same memory location
            std::swap(*(iter), *(iter + 1));

            return std::make_pair(&*iter, &*(iter + 1));
        }
    }
    return std::make_pair(nullptr, nullptr);
}


/// <summary>
/// Similar to MatMLFindAndBumpDown with the added complication 
/// that the Required Id's cannot be duplicated during the swap.
/// </summary>
/// <typeparam name="MatML_Class"></typeparam>
/// <typeparam name="MatML_ContClass"></typeparam>
/// <param name="matml"></param>
/// <param name="cont"></param>
/// <returns></returns>
template<class MatML_Class, class MatML_ContClass>
std::pair<MatML_Class*,MatML_Class*>
bellshire::MatML_Base_GUI::MatMLFindAndBumpDownHavingId(MatML_Class* matml, MatML_ContClass& cont)
{
    if (cont.empty() || cont.size() < 2)  return std::make_pair(nullptr, nullptr);

    for (auto iter = cont.begin(); iter != cont.end() - 1; ++iter) {
        if ((matml) == (&*iter)) {//if the pointer are the same (aka same memory location

            SwapHavingId(&*(iter), &*(iter + 1));

            return std::make_pair(&*iter, &*(iter + 1));
        }
    }
    return std::make_pair(nullptr, nullptr);
}

/// <summary>
/// Similar to MatMLFindAndBumpDown with the added complication 
/// that the optional Id's cannot be duplicated during the swap.
/// </summary>
/// <typeparam name="MatML_Class"></typeparam>
/// <typeparam name="MatML_ContClass"></typeparam>
/// <param name="matml"></param>
/// <param name="cont"></param>
/// <returns></returns>
template<class MatML_Class, class MatML_ContClass>
std::pair<MatML_Class*,MatML_Class*>
bellshire::MatML_Base_GUI::MatMLFindAndBumpDownHavingOptionalId(MatML_Class* matml, MatML_ContClass& cont)
{
    if (cont.empty() || cont.size() < 2)  return std::make_pair(nullptr, nullptr);

    for (auto iter = cont.begin(); iter != cont.end() - 1; ++iter) {
        if ((matml) == (&*iter)) {//if the pointer are the same (aka same memory location

            SwapHavingOptionalId(&*(iter), &*(iter + 1));

            return std::make_pair(&*iter, &*(iter + 1));
        }
    }
    return std::make_pair(nullptr, nullptr);
}

template<class Child_GUI, class MatML>
void bellshire::MatML_Base_GUI::MatMLTreeCtrlBumpDown(TreeCtrlSorted*& treectrl,
    wxTreeItemId& itemParentId,
    wxTreeItemId& itemId,
    MatML* first,
    wxTreeItemId& nextitemId,
    MatML* second
)
{
    Child_GUI::SetupMatMLTreeCtrl(treectrl, itemParentId, *first, itemId);
    Child_GUI::SetupMatMLTreeCtrl(treectrl, itemParentId, *second, nextitemId);

    treectrl->SelectItem(treectrl->GetNextSibling(nextitemId));//setup so selection bumps down

    treectrl->Delete(itemId);
    treectrl->Delete(nextitemId);
}

template<class MatML_Class, class MatML_ContClass>
std::pair< MatML_Class*, MatML_Class*>
bellshire::MatML_Base_GUI::MatMLFindAndBumpUp(MatML_Class* matml, MatML_ContClass& cont)
{
    if (cont.empty() || cont.size() < 2)  return  std::make_pair(nullptr, nullptr);

    for (auto iter = cont.begin() + 1; iter != cont.end(); ++iter) {
        if ((matml) == (&*iter)) {//if the pointer are the same (aka same memory location

            std::swap(*(iter - 1), *(iter));

            return std::make_pair(&*(iter - 1), &*iter);
        }
    }
    return  std::make_pair(nullptr, nullptr);
}

template<class MatML_Class, class MatML_ContClass>
std::pair< MatML_Class*, MatML_Class*>
bellshire::MatML_Base_GUI::MatMLFindAndBumpUpStrongtype(MatML_Class* matml, MatML_ContClass& cont)
{
    if (cont.empty() || cont.size() < 2)  return  std::make_pair(nullptr, nullptr);

    for (auto iter = cont.begin() + 1; iter != cont.end(); ++iter) {
        if ((matml->t) == (&*iter)) {//if the pointer are the same (aka same memory location

            std::swap(*(iter - 1), *(iter));

            return std::make_pair(&*(iter - 1), &*iter);
        }
    }
    return  std::make_pair(nullptr, nullptr);
}

/// <summary>
/// Similar to MatMLFindAndBumpUp with the added complication 
/// that the Required Id's cannot be duplicated during the swap.
/// </summary>
/// <typeparam name="MatML_ContClass"></typeparam>
/// <param name="matml"></param>
/// <param name="cont"></param>
/// <returns></returns>
template<class MatML_ContClass>
std::pair<typename MatML_ContClass::value_type*, typename MatML_ContClass::value_type*>
bellshire::MatML_Base_GUI::MatMLFindAndBumpUpHavingId(typename MatML_ContClass::value_type* matml, MatML_ContClass& cont)
{
    if (cont.empty() || cont.size() < 2)  return  std::make_pair(nullptr, nullptr);

    for (auto iter = cont.begin() + 1; iter != cont.end(); ++iter) {
        if ((matml) == (&*iter)) {//if the pointer are the same (aka same memory location

            SwapHavingId(&*(iter - 1), &*(iter));

            return std::make_pair(&*(iter - 1), &*iter);
        }
    }
    return  std::make_pair(nullptr, nullptr);
}

/// <summary>
/// Similar to MatMLFindAndBumpUp with the added complication 
/// that the optional Id's cannot be duplicated during the swap.
/// </summary>
/// <typeparam name="MatML_ContClass"></typeparam>
/// <param name="matml"></param>
/// <param name="cont"></param>
/// <returns></returns>
template<class MatML_ContClass>
std::pair<typename MatML_ContClass::value_type*, typename MatML_ContClass::value_type*>
bellshire::MatML_Base_GUI::MatMLFindAndBumpUpHavingOptionalId(typename MatML_ContClass::value_type* matml, MatML_ContClass& cont)
{
    if (cont.empty() || cont.size() < 2)  return  std::make_pair(nullptr, nullptr);

    for (auto iter = cont.begin() + 1; iter != cont.end(); ++iter) {
        if ((matml) == (&*iter)) {//if the pointer are the same (aka same memory location

            SwapHavingOptionalId(&*(iter - 1), &*(iter));

            return std::make_pair(&*(iter - 1), &*iter);
        }
    }
    return  std::make_pair(nullptr, nullptr);
}

template<class Child_GUI, class MatML>
void bellshire::MatML_Base_GUI::MatMLTreeCtrlBumpUp(TreeCtrlSorted*& treectrl,
    wxTreeItemId& itemParentId,
    wxTreeItemId& previtemId,
    MatML* first,
    wxTreeItemId& itemId,
    MatML* second
)
{
    Child_GUI::SetupMatMLTreeCtrl(treectrl, itemParentId, *first, previtemId);
    Child_GUI::SetupMatMLTreeCtrl(treectrl, itemParentId, *second, itemId);

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
void bellshire::MatML_Base_GUI::IndividualBumpUp(boost::any anyptr,
    boost::any anyptrparent,
    TreeCtrlSorted* MatMLTreeCtrl,
    wxTreeItemId itemParentId,
    wxTreeItemId previtemId,
    wxTreeItemId itemId
)
{
    try {
        if (anyptrparent.type() == typeid(MatML_ParentClass*)) {
            MatML_Class* element = boost::any_cast<MatML_Class*>(anyptr);
            MatML_ParentClass* elementParent = boost::any_cast<MatML_ParentClass*>(anyptrparent);

            std::pair<MatML_Class*, MatML_Class*> data(MatMLFindAndBumpUp(element, (elementParent->*cont_func)()));
            if (data.second)
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
void bellshire::MatML_Base_GUI::IndividualBumpUpStrongtype(boost::any anyptr,
    boost::any anyptrparent,
    TreeCtrlSorted* MatMLTreeCtrl,
    wxTreeItemId itemParentId,
    wxTreeItemId previtemId,
    wxTreeItemId itemId
)
{
    try {
        if (anyptrparent.type() == typeid(MatML_ParentClass*)) {
            MatML_Class* element = boost::any_cast<MatML_Class*>(anyptr);
            MatML_ParentClass* elementParent = boost::any_cast<MatML_ParentClass*>(anyptrparent);

            std::pair<typename MatML_Class::value_type, typename MatML_Class::value_type> data(MatMLFindAndBumpUp(element->t, (elementParent->*cont_func)()));
            if (data.second)
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
void bellshire::MatML_Base_GUI::IndividualBumpUpHavingId(boost::any anyptr,
    boost::any anyptrparent,
    TreeCtrlSorted* MatMLTreeCtrl,
    wxTreeItemId itemParentId,
    wxTreeItemId previtemId,
    wxTreeItemId itemId
)
{
    try {
        if (anyptrparent.type() == typeid(MatML_ParentClass*)) {
            MatML_Class* element = boost::any_cast<MatML_Class*>(anyptr);
            MatML_ParentClass* elementParent = boost::any_cast<MatML_ParentClass*>(anyptrparent);

            std::pair<MatML_Class*, MatML_Class*> data(MatMLFindAndBumpUpHavingId(element, (elementParent->*cont_func)()));
            if (data.second)
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
void bellshire::MatML_Base_GUI::IndividualBumpUpHavingOptionalId(boost::any anyptr,
    boost::any anyptrparent,
    TreeCtrlSorted* MatMLTreeCtrl,
    wxTreeItemId itemParentId,
    wxTreeItemId previtemId,
    wxTreeItemId itemId
)
{
    try {
        if (anyptrparent.type() == typeid(MatML_ParentClass*)) {
            MatML_Class* element = boost::any_cast<MatML_Class*>(anyptr);
            MatML_ParentClass* elementParent = boost::any_cast<MatML_ParentClass*>(anyptrparent);

            std::pair<MatML_Class*, MatML_Class*> data(MatMLFindAndBumpUpHavingOptionalId(element, (elementParent->*cont_func)()));
            if (data.second)
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
void bellshire::MatML_Base_GUI::IndividualBumpDown(boost::any& anyptr,
    boost::any& anyptrparent,
    TreeCtrlSorted* MatMLTreeCtrl,
    wxTreeItemId itemParentId,
    wxTreeItemId itemId,
    wxTreeItemId nextitemId
)
{
    try {
        if (anyptrparent.type() == typeid(MatML_ParentClass*)) {
            MatML_Class* element = boost::any_cast<MatML_Class*>(anyptr);
            MatML_ParentClass* elementParent = boost::any_cast<MatML_ParentClass*>(anyptrparent);

            std::pair<MatML_Class*, MatML_Class*> data(MatMLFindAndBumpDown(element, (elementParent->*cont_func)()));
            if (data.second)
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
void bellshire::MatML_Base_GUI::IndividualBumpDownStrongtype(boost::any& anyptr,
    boost::any& anyptrparent,
    TreeCtrlSorted* MatMLTreeCtrl,
    wxTreeItemId itemParentId,
    wxTreeItemId itemId,
    wxTreeItemId nextitemId
)
{
    try {
        if (anyptrparent.type() == typeid(MatML_ParentClass*)) {
            MatML_Class* element = boost::any_cast<MatML_Class*>(anyptr);
            MatML_ParentClass* elementParent = boost::any_cast<MatML_ParentClass*>(anyptrparent);

            std::pair<typename MatML_Class::value_type, typename MatML_Class::value_type> data(MatMLFindAndBumpDown(element->t, (elementParent->*cont_func)()));
            if (data.second)
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
void bellshire::MatML_Base_GUI::IndividualBumpDownHavingId(boost::any& anyptr,
    boost::any& anyptrparent,
    TreeCtrlSorted* MatMLTreeCtrl,
    wxTreeItemId itemParentId,
    wxTreeItemId itemId,
    wxTreeItemId nextitemId
)
{
    try {
        if (anyptrparent.type() == typeid(MatML_ParentClass*)) {
            MatML_Class* element = boost::any_cast<MatML_Class*>(anyptr);
            MatML_ParentClass* elementParent = boost::any_cast<MatML_ParentClass*>(anyptrparent);

            std::pair<MatML_Class*, MatML_Class*> data(MatMLFindAndBumpDownHavingId(element, (elementParent->*cont_func)()));
            if (data.second)
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
void bellshire::MatML_Base_GUI::IndividualBumpDownHavingOptionalId(boost::any& anyptr,
    boost::any& anyptrparent,
    TreeCtrlSorted* MatMLTreeCtrl,
    wxTreeItemId itemParentId,
    wxTreeItemId itemId,
    wxTreeItemId nextitemId
)
{
    try {
        if (anyptrparent.type() == typeid(MatML_ParentClass*)) {
            MatML_Class* element = boost::any_cast<MatML_Class*>(anyptr);
            MatML_ParentClass* elementParent = boost::any_cast<MatML_ParentClass*>(anyptrparent);

            std::pair<MatML_Class*, MatML_Class*> data(MatMLFindAndBumpDownHavingOptionalId(element, (elementParent->*cont_func)()));
            if (data.second)
                MatMLTreeCtrlBumpDown<MatML_GUI>(MatMLTreeCtrl, itemParentId, itemId, data.first, nextitemId, data.second);

            return;
        }
    }
    catch (const boost::bad_any_cast&) {};//do nothing
}
