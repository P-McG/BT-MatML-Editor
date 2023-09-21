/////////////////////////////////////////////////////////////////////////////
// Name:        BT_MatML_Utilities_GUI.h
// Purpose:     Classes of Utilities_GUI Base and Derived Misc. 
//				fn used in other classes.
// Author:      Paul McGrath
// Modified by:
// Created:
// Copyright:   (c) Paul McGrath
// Licence:     CC licence
/////////////////////////////////////////////////////////////////////////////
#pragma once

#include <boost/shared_ptr.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/classification.hpp>

#include <wx/treebase.h>

#include <list>
#include <vector>

#include "bellshire/matml31.hxx"
#include "bellshire/matml31_strongly_typed_def.h"

#include "bellshire/GUI/BT_MatML_TreeCtrlSorted.h"
#include "bellshire/GUI/BT_MatML_MatMLTreeItemData.h"

namespace bellshire::GUI {

	//Utility for std:string and wxString
#define _std2wx(var) wxString (var.c_str(),wxConvUTF8)
#define _wx2std(var) ::std::string(var.mb_str())

	/// Utility Functions
	/// <summary>
	/// </summary>
	class Utilities
	{
	public:
		static wxTreeItemId MatMLtoTreeCtrl(TreeCtrlSorted* MatMLTreeCtrl, observer_ptr<Material> MatMLMaterial);/*!<Find the associated TreeCtrl*/
		static std::list< std::pair< observer_ptr<Material>, xml_schema::string > > GetMaterialIDPair(observer_ptr<MatML_Doc> MatMLDoc, std::list<xml_schema::string> ClassFilters = std::list<xml_schema::string>());
		static bool InFilter(observer_ptr<Material> material, std::list<xml_schema::string> Filter);
		static bool InFilter(observer_ptr<Material> material, xml_schema::string* Filter);

		static std::list<Name*> GetMatMLDocClassNames(observer_ptr<MatML_Doc> matml_doc);
		static std::list<Name*> GetBulkDetailsClassNames(Material* material);
		static bool CompareName( Name*& first, Name*& second);
		static bool SameName(Name*& first, Name*& second);

		static ::std::string Label(::std::string name, ::std::string id);
		static ::std::string LabelToId(::std::string label);

		static std::list<xml_schema::string> wx2std(const wxArrayString& wxstr);
		static wxArrayString std2wx(const std::list<xml_schema::string>& stdstr);

		void CollectBranchMaterials(observer_ptr<MatML_Doc> doc, observer_ptr<Material> m, std::vector<observer_ptr<Material>>& ms);
		void CollectBranchMaterialsBackwards(observer_ptr<Material> m, std::vector<observer_ptr<Material>>& ms);
		void CollectBranchMaterialsForewards(observer_ptr<MatML_Doc> doc, observer_ptr<Material> m, std::vector<observer_ptr<Material>>& ms);

	};

};//namespace bellshire