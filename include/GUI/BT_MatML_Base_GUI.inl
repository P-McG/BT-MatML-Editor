#pragma once



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
    temp1.id(xml_schema::id(string("BT-TEMP-ID")));

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
        temp1.id(xml_schema::id(string("BT-TEMP-ID")));
    }

    *matml0 = temp1;
    *matml1 = temp0;

    //Replace the temp id with the previous one
    if (temp1.id().present())
        matml0->id().set(tempid);
}

template<class MatML_Class, class MatML_ContClass>
std::pair<typename  MatML_Class*, typename MatML_Class*>
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

template<class MatML_Class, class MatML_ContClass>
std::pair<typename  MatML_Class*, typename MatML_Class*>
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
std::pair<typename  MatML_Class*, typename MatML_Class*>
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
std::pair<typename  MatML_Class*, typename MatML_Class*>
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
std::pair<typename  MatML_Class*, typename MatML_Class*>
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
std::pair<typename  MatML_Class*, typename MatML_Class*>
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

            std::pair<MatML_Class::value_type, MatML_Class::value_type> data(MatMLFindAndBumpUp(element->t, (elementParent->*cont_func)()));
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

            std::pair<MatML_Class::value_type, MatML_Class::value_type> data(MatMLFindAndBumpDown(element->t, (elementParent->*cont_func)()));
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