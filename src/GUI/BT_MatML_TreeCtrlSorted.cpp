/**
 * @file TreeCtrlSorted.cpp
 *
 * @brief
 *
 * @author Paul McGrath
 * Contact:
 *
 */
#include "BT_MatML_TreeCtrlSorted.h"
#include "BT_MatML_MatMLTreeItemData.h"
#include <wx/object.h>
#include <wx/config.h>
#include <boost/any.hpp>
#include <list>

using boost::any_cast;
typedef std::list<boost::any> many;
using namespace bellshire;

IMPLEMENT_DYNAMIC_CLASS(TreeCtrlSorted, wxTreeCtrl)

/**
 * Implementation OnCompareItems
 *
 * Comparison test for ordering of the TreeCtrl
 * 
 * Sorts the Metadata to the end of the list
 * Sorts the Material as per its Class->Name
 * Sorts the Material as per its position
 *
 */
int TreeCtrlSorted::OnCompareItems(const wxTreeItemId& item1, const wxTreeItemId& item2)
{
	//Get the current MatML data pointer

    MatMLTreeItemData* item1_MatML_Data((MatMLTreeItemData *)(this->GetItemData(item1)));
	MatMLTreeItemData* item2_MatML_Data((MatMLTreeItemData *)(this->GetItemData(item2)));

	boost::any temp1 = item1_MatML_Data->GetAnyMatMLDataPointer();
	boost::any temp2 = item2_MatML_Data->GetAnyMatMLDataPointer();

	//MetaData elements is always placed at the end.
	try{
		if(temp1.type() == typeid(Metadata*))
			return +1;
	}
	catch(const boost::bad_any_cast &){}//do nothing

	try{
		if (temp2.type() == typeid(Metadata*))
		return -1;
	}
	catch(const boost::bad_any_cast &){}//do nothing

	//Testing the Material elements
	try{
		if (temp1.type() == typeid(Material*) && temp2.type() == typeid(Material*)) {
			Material* material1 = any_cast<Material*>(temp1);
			Material* material2 = any_cast<Material*>(temp2);

			if (!material1->BulkDetails().Class().empty() && material2->BulkDetails().Class().empty()) return -1;

			else if (material1->BulkDetails().Class().empty() && !material2->BulkDetails().Class().empty()) return +1;

			else if (!material1->BulkDetails().Class().empty() && !material2->BulkDetails().Class().empty()) {

				BulkDetails::Class_sequence& cont1(material1->BulkDetails().Class());
				BulkDetails::Class_iterator iter1(cont1.begin());
				BulkDetails::Class_sequence& cont2(material2->BulkDetails().Class());
				BulkDetails::Class_iterator iter2(cont2.begin());
				for (;;) {

					//Test the Class order
					int classorder1 = ClassOrder(*iter1), classorder2 = ClassOrder(*iter2);

					//If one of the preordered classes
					if (classorder1 < classorder2)return -1;
					else if (classorder1 > classorder2) return +1;

					//If not one of the preordered classes
					else if (classorder1 == INT_MAX && classorder2 == INT_MAX) {
						std::string str1;
						if (iter1->Name().present()) {
							str1 = iter1->Name()->c_str();
						}
						else if (!iter1->ParentMaterial().empty()) {
							str1 = iter1->ParentMaterial().front().id().c_str();
						}
						std::string str2;
						if (iter2->Name().present()) {
							str2 = iter2->Name()->c_str();
						}
						else if (!iter2->ParentMaterial().empty()) {
							str2 = iter2->ParentMaterial().front().id().c_str();
						}
						int cmp = str1.compare(str2);
						if (cmp < 0) return -1;
						else if (cmp > 0) return +1;
					}

					++iter1; ++iter2;

					//If one or both run run out of Classes to compare
					if (iter1 == cont1.end() && iter2 != cont2.end()) return -1;
					else if (iter1 != cont1.end() && iter2 == cont2.end()) return +1;
					else if (iter1 == cont1.end() && iter2 == cont2.end()) return -1;
				}
			}
		}
	}
	catch(const boost::bad_any_cast &){}//do nothing

	//If not a Class then use the position for ordering
	try{
		if (temp1.type() == typeid(Class*) && temp2.type() == typeid(Class*)) {

			Class* class1 = any_cast<Class*>(temp1);
			Class* class2 = any_cast<Class*>(temp2);

			if (this->GetItemParent(item1) == this->GetItemParent(item2)) {

				MatMLTreeItemData* parent_MatML_Data((MatMLTreeItemData*)(this->GetItemData(this->GetItemParent(item1))));
				boost::any parentanyptr = parent_MatML_Data->GetAnyMatMLDataPointer();

				if (parentanyptr.type() == typeid(BulkDetails*)) {

					BulkDetails* parent = any_cast<BulkDetails*>(parentanyptr);

					int pos1 = PositionOrder(parent, class1), pos2 = PositionOrder(parent, class2);
					if (pos1 < pos2) return -1;
					else if (pos1 > pos2) return +1;
					else return 0; //this should never occur
				}
			}
		}
	}
	catch(const boost::bad_any_cast &){}//do nothing

	return 0;
}

wxArrayString TreeCtrlSorted::GetSortClasses()
{
	unsigned i(0);
	bool b(true);
	wxString str;
	wxArrayString arraystr;
	wxConfig config(wxT("BTMatML"));

	do {
		str.Empty();
		b = config.Read(wxT("/General/ClassSortOrder/") + wxString::Format(wxT("%i"), i), &str);
		if (b) {
			arraystr.push_back(str);
			i++;
		}
	} while (b);

	return arraystr;
}
/**
 * Implementation ClassOrder
 *
 * Returns int value based on the hardcoding of the class order.
 *
 */
int TreeCtrlSorted::ClassOrder(Class& item)
{
	wxArrayString arraystr(GetSortClasses());

	int i=0;
	if(item.Name().present()){
		for(i;i<arraystr.GetCount(); i++)
			if(item.Name()->compare(arraystr[i]) == 0) return i;

	}
	return INT_MAX;
}

int TreeCtrlSorted::PositionOrder(Material* element)
{
	 int pos=1;

	MatMLTreeItemData* item_MatML_Data((MatMLTreeItemData *)(this->GetItemData(this->GetRootItem())));
	boost::any anyptr = item_MatML_Data->GetAnyMatMLDataPointer();

	try{
		if (anyptr.type() == typeid(MatML_Doc*)) {
			MatML_Doc* doc = any_cast<MatML_Doc*>(anyptr);

			MatML_Doc::Material_sequence& cont(doc->Material());
			MatML_Doc::Material_iterator iter(cont.begin());
			if (!cont.empty())
				for (; iter != cont.end(); ++iter, ++pos)
					if (element->id() == iter->id())
						break;
		}
	}
   	catch(const boost::bad_any_cast &){}//do nothing
	return INT_MAX;
}

int TreeCtrlSorted::PositionOrder(BulkDetails* parent, Class* element)
{
	 int pos=1;

	 BulkDetails::Class_sequence& cont(parent->Class());
	 if(!cont.empty()){
		 pos=1;
		 BulkDetails::Class_iterator iter(cont.begin());
		  for (; iter!=cont.end ();++iter,++pos)
			  if(element==static_cast<Class*>(&*iter)){
				  return pos;
			  }

			  //if(element->Name().present() && iter->Name().present())
				 // if(element->Name().get()==iter->Name().get()) return pos;
	 }

	return INT_MAX;
}

//void TreeCtrlSorted::Delete()
//{
//    //No New statements so no deletes required.
//    wxTreeCtrl::Delete(); //Call the parent delete function.
//}
//
//void TreeCtrlSorted::Delete(wxTreeItemId& itemid)
//{
//    //No New statements so no deletes required.
//    wxTreeCtrl::Delete(itemid); //Call the parent delete function.
//}
//
////void TreeCtrlSorted::Delete(wxTreeItemId itemid)
////{
//    //No New statements so no deletes required.
////    wxTreeCtrl::Delete(itemid); //Call the parent delete function.
////}
