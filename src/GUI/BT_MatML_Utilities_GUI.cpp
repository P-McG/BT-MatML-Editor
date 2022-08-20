#include "BT_MatML_Utilities_GUI.h"


using namespace bellshire;

/// <summary>
/// Searches the TreeCtrl to find the MatML Element
/// </summary>
/// <param name="MatMLTreeCtrl"></param>
/// <param name="material"></param>
/// <returns>Matching TreeCtrlId</returns>
wxTreeItemId Utilities::MatMLtoTreeCtrl(TreeCtrlSorted* MatMLTreeCtrl, Material* material)
{
	//When using this need to check the return value to see if :IsOk
	wxTreeItemIdValue cookie;
	wxTreeItemId MaterialItemId(MatMLTreeCtrl->GetFirstChild(MatMLTreeCtrl->GetRootItem(), cookie));

	do {
		MatMLTreeItemData* MaterialItem = (MatMLTreeItemData*)(MatMLTreeCtrl->GetItemData(MaterialItemId));
		try {
			Material* const TreeMaterial = boost::any_cast<Material* const>(MaterialItem->GetAnyMatMLDataPointer());
			//			if(TreeMaterial->id().get()==MatMLMaterial->id().get()){
			if (TreeMaterial->id() == material->id()) {
				return MaterialItemId; //found
			}
		}
		catch (const boost::bad_any_cast&) {}//do nothing

		MaterialItemId = MatMLTreeCtrl->GetNextSibling(MaterialItemId);
	} while (MaterialItemId.IsOk());
	return MaterialItemId;
}

/// <summary>
/// Gather Material* and Material->ID paired together in a list.
/// </summary>
/// <param name="MatMLDoc"></param>
/// <param name="ClassFilters"></param>
/// <returns>MaterialIDPair</returns>
std::list< std::pair< Material*, xml_schema::string > > Utilities::GetMaterialIDPair(::boost::shared_ptr<MatML_Doc> MatMLDoc, std::list<xml_schema::string> ClassFilters)
{
	std::list< std::pair< Material*, xml_schema::string > > MaterialIDPair;

	MatML_Doc::Material_sequence& cont(MatMLDoc->Material());
	MatML_Doc::Material_iterator iter(cont.begin());
	if (!cont.empty()) {

		for (; iter != cont.end(); ++iter) {
			if (iter->id().present()) {

				bool addToList = true;

				//Filter
				if (!ClassFilters.empty()) {

					//trial

					for (std::list<xml_schema::string>::iterator iterClassFilters(ClassFilters.begin()); iterClassFilters != ClassFilters.end(); ++iterClassFilters)
					{
						if (!iterClassFilters->empty()) {

							bool inFilter = InFilter(&*iter, &*iterClassFilters);

							if (!inFilter) {
								addToList = false;
								break;
							}
						}
					}
				}

				if (addToList) {
					std::pair< Material*, xml_schema::string> pair ( &*iter, iter->id().get());
					MaterialIDPair.push_back(pair);
				}
			}
		}
	}
	return MaterialIDPair;
}


/// <summary>
/// Determines if the Material has a Class->Name for each of the ClassFilter strings
/// If the filter is empty then the default is true.
/// </summary>
/// <param name="material"></param>
/// <param name="ClassFilters"></param>
/// <returns></returns>
bool Utilities::InFilter(Material* material, std::list<xml_schema::string> Filter)
{
	bool inFilter = true; //default to true when there is NO Filter
	if (!Filter.empty()) {

		for (std::list<xml_schema::string>::iterator iterFilter(Filter.begin()); iterFilter != Filter.end(); ++iterFilter)
		{
			if (!iterFilter->empty()) {

				inFilter = InFilter(material, &*iterFilter);

				if (!inFilter) break; //if false exit
			}
		}
	}
	return inFilter;
}

/// <summary>
/// Determines if the Material has a Class->Name that matches the ClassFilter string
/// </summary>
/// <param name="material"></param>
/// <param name="ClassFilter"></param>
/// <returns></returns>
bool Utilities::InFilter(Material* material, xml_schema::string* Filter)
{
	bool inFilter = true; // default to true if ClassFilter is empty.
	if (!Filter->empty()) {

		inFilter = false; // default to false if no class->name present.
		if (!material->BulkDetails().Class().empty()) {

			BulkDetails::Class_sequence& contClass(material->BulkDetails().Class());
			BulkDetails::Class_iterator iterClass(contClass.begin());
			for (; iterClass != contClass.end(); ++iterClass) {//Iterate over the class
				if (iterClass->Name().present() && !Filter->empty() && iterClass->Name().get().compare(*Filter) == 0) {
					inFilter = true; // One of the class->name is the filter.
					break; //Don't need to check anymore
				}
			}
		}
	}
	return inFilter;
}

/// <summary>
/// Gathers within the MatMLDoc all of the materials->BulkDetails->Class->Name
/// </summary>
/// <param name="MatMLDoc"></param>
/// <returns></returns>
std::list<Name*> Utilities::GetMatMLDocClassNames(::boost::shared_ptr<MatML_Doc> MatMLDoc)
{
	std::list<Name*> names;

	MatML_Doc::Material_sequence& cont(MatMLDoc->Material());
	MatML_Doc::Material_iterator iter(cont.begin());
	if (!cont.empty()) {

		for (; iter != cont.end(); ++iter) {
			names.merge(GetBulkDetailsClassNames(&*iter), CompareName);

			//Sort list and remove duplicates
			names.sort(CompareName);
			names.unique(SameName);
		}
	}

	//Sort list and remove duplicates
	names.sort(CompareName);
	names.unique(SameName);

	return names;
}

/// <summary>
/// Get the Materials BulkDetails->Class->Names
/// </summary>
/// <param name="material"></param>
/// <returns></returns>
std::list<Name*> Utilities::GetBulkDetailsClassNames(Material* material)
{
	std::list<Name*> names;

	if (!material->BulkDetails().Class().empty()) {

		BulkDetails::Class_sequence& contClass(material->BulkDetails().Class());
		BulkDetails::Class_iterator iterClass(contClass.begin());
		for (; iterClass != contClass.end(); ++iterClass)//Iterate over the class
			if (iterClass->Name().present())
				names.push_back((Name*)&iterClass->Name().get());
	}

	names.sort(CompareName);
	names.unique(SameName);

	return names;
}

/// <summary>
/// Comparision of the First Name to the Second Name
/// </summary>
/// <param name="first"></param>
/// <param name="second"></param>
/// <returns></returns>
bool Utilities::CompareName( Name*& first,  Name*& second)
{
	return ((*first) < (*second));
}

/// <summary>
/// Compare if the First Name and Second Name are the same
/// a binary predicate implemented as a function
/// </summary>
/// <param name="first"></param>
/// <param name="second"></param>
/// <returns></returns>
bool Utilities::SameName(Name*& first, Name*& second)
{
	return ((*first) == (*second));
}

/// <summary>
/// Creates a string of the Labels used in wxWidgets displays
/// </summary>
::std::string Utilities::Label(::std::string name, ::std::string id)
{
	::std::string label;
	if (!name.empty()) label.append(name);
	if (!name.empty() && !id.empty()) label.append(" :");
	if (!id.empty()) label.append(id);
	return label;
}

///<summary>
/// Takes the Label, used in wxWidgets displays, and pulls out the Id
/// </summary>
::std::string Utilities::LabelToId(::std::string label)
{
	::std::list<::std::string> result;
	return boost::split(result, label, boost::is_any_of(":")).back();
}

/// <summary>
/// Converts wxArrayString to std::list of xml_schema::string
/// </summary>
/// <param name="wxstr"></param>
/// <returns></returns>
std::list<xml_schema::string> Utilities::wx2std(const wxArrayString& wxstr)
{
	std::list<xml_schema::string> stdstr;

	for (wxArrayString::const_iterator itor(wxstr.begin()); itor != wxstr.end(); ++itor) {
		xml_schema::string str = _wx2std((*itor));
		stdstr.push_back(str);

	}
	return stdstr;
}

/// <summary>
/// Converts list of xml_schema::string to wxArrayString
/// </summary>
/// <param name="stdstr"></param>
/// <returns></returns>
wxArrayString Utilities::std2wx(const std::list<xml_schema::string>& stdstr)
{
	wxArrayString wxstr;

	for (std::list<xml_schema::string>::const_iterator itor(stdstr.begin()); itor != stdstr.end(); ++itor)
		wxstr.push_back(_std2wx((*itor)));

	return wxstr;
}


/// <summary>
/// Collect Branch of Materials
/// </summary>
/// <param name="m"></param>
/// <param name="ms"></param>
void Utilities::CollectBranchMaterials(boost::shared_ptr<MatML_Doc> doc, Material* m, std::vector<Material*>& ms)
{
	CollectBranchMaterialsBackwards(m, ms);
	CollectBranchMaterialsForewards(doc, m, ms);
}

/// <summary>
/// Collect Branch of Materials in the Backwards direction
/// </summary>
/// <param name="m"></param>
/// <param name="ms"></param>
void Utilities::CollectBranchMaterialsBackwards(Material* m, std::vector<Material*>& ms)
{

	if (!m->ComponentDetails().empty()) {
		Material::ComponentDetails_sequence& cs(m->ComponentDetails());
		for (Material::ComponentDetails_iterator ci = cs.begin(); ci != cs.end(); ci++) {
			if (ci->Class().empty()) continue;
			ComponentDetails::Class_sequence& classcont(ci->Class());
			for (ComponentDetails::Class_iterator classiter = classcont.begin(); classiter != classcont.end(); ++classiter) {
				if (classiter->ParentMaterial().empty()) continue;
				Material* parentmaterial(dynamic_cast<Material*>(&*classiter->ParentMaterial().front().id()));
				if (parentmaterial == NULL || parentmaterial == m) continue;

				//check for duplicates
				bool dupl = false;
				for (std::vector<Material*>::iterator mi = ms.begin(); mi != ms.end(); mi++) {//duplicate check loop
					if (*mi == parentmaterial) {
						dupl = true;

						break;//get out of duplicate check loop
					}
				}
				if (!dupl) CollectBranchMaterialsBackwards(parentmaterial, ms);
			}
		}
	}
	//components go first then this material
	ms.push_back(m);
}

/// <summary>
/// Collect Branch of Materials in the Forwards direction
/// </summary>
/// <param name="m"></param>
/// <param name="ms"></param>
void Utilities::CollectBranchMaterialsForewards(boost::shared_ptr<MatML_Doc> doc, Material* m, std::vector<Material*>& ms)
{
	//check to see if pointer m occurs in any material->ComponentDetails->Class->ParentMaterial->idref

	MatML_Doc::Material_sequence& docms(doc->Material());
	for (MatML_Doc::Material_iterator docmi = docms.begin(); docmi != docms.end(); docmi++) {

		if (!docmi->ComponentDetails().empty()) {
			Material::ComponentDetails_sequence& cs(docmi->ComponentDetails());
			for (Material::ComponentDetails_iterator ci = cs.begin(); ci != cs.end(); ci++) {
				if (ci->Class().empty()) continue;
				ComponentDetails::Class_sequence& classcont(ci->Class());
				for (ComponentDetails::Class_iterator classiter = classcont.begin(); classiter != classcont.end(); ++classiter) {
					if (classiter->ParentMaterial().empty()) continue;
					Material* parentmaterial(dynamic_cast<Material*>(&*classiter->ParentMaterial().front().id()));
					if (parentmaterial != m) continue;

					//check for duplicates.
					bool dupl = false;
					for (std::vector<Material*>::iterator mi = ms.begin(); mi != ms.end(); mi++) {//duplicate check loop
						if (*mi == &*docmi) {//see if they have the same memory location
							dupl = true;
							break;//get out of duplicate check loop
						}
					}
					if (!dupl) {
						//this material goes first then the materials with this as a component.
						ms.push_back(&(*docmi));
						CollectBranchMaterialsForewards(doc ,&(*docmi), ms);
					}
				}
			}
		}
	}
}
