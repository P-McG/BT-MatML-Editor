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

#include "matml31.hxx"
#include "matml31_strongtypedef.h"

#include "BT_MatML_TreeCtrlSorted.h"
#include "BT_MatML_MatMLTreeItemData.h"

namespace bellshire {

	//Utility for std:string and wxString
#define _std2wx(var) wxString (var.c_str(),wxConvUTF8)
#define _wx2std(var) std::string(var.mb_str())

	/// Utility Functions
	/// <summary>
	/// </summary>
	class Utilities
	{
	public:
		static wxTreeItemId MatMLtoTreeCtrl(TreeCtrlSorted* MatMLTreeCtrl, Material* MatMLMaterial);/*!<Find the associated TreeCtrl*/
		static std::list< std::pair< Material*, xml_schema::string > > GetMaterialIDPair(::boost::shared_ptr<MatML_Doc> MatMLDoc, std::list<xml_schema::string> ClassFilters = std::list<xml_schema::string>());
		static bool InFilter(Material* material, std::list<xml_schema::string> Filter);
		static bool InFilter(Material* material, xml_schema::string* Filter);

		static std::list<Name*> GetMatMLDocClassNames(::boost::shared_ptr<MatML_Doc> MatMLDoc);
		static std::list<Name*> GetBulkDetailsClassNames(Material* material);
		static bool CompareName( Name*& first, Name*& second);
		static bool SameName(Name*& first, Name*& second);

		static ::std::string Label(::std::string name, ::std::string id);
		static ::std::string LabelToId(::std::string label);

		static std::list<xml_schema::string> wx2std(const wxArrayString& wxstr);
		static wxArrayString std2wx(const std::list<xml_schema::string>& stdstr);

		void CollectBranchMaterials(boost::shared_ptr<MatML_Doc> doc, Material* m, std::vector<Material*>& ms);
		void CollectBranchMaterialsBackwards(Material* m, std::vector<Material*>& ms);
		void CollectBranchMaterialsForewards(boost::shared_ptr<MatML_Doc> doc, Material* m, std::vector<Material*>& ms);

	};

};//namespace bellshire