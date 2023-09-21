/////////////////////////////////////////////////////////////////////////////
// Name:        MatMLTreeItemData.h
// Purpose:     MatML Version of the wxTreeItemData.
// Author:      Paul McGrath
// Modified by:
// Created:
// Copyright:   (c) Paul McGrath
// Licence:     CC licence
/////////////////////////////////////////////////////////////////////////////
#pragma once

#include "wx/treebase.h"
#include "wx/clntdata.h"

#include <boost/any.hpp>
#include <wx/string.h>

#include "bellshire/matml31.hxx"
#include "bellshire/matml31_strongly_typed_def.h"

namespace bellshire::GUI{

	//template <typename T, typename U>
	//inline bool is_equal(const observer_ptr<T>& t, const observer_ptr<U>& u)
	//{
	//	return !t.owner_before(u) && !u.owner_before(t);
	//}

/// MatMLTreeItemData
///  Allows for the storage of MatML Data as a void pointer.
/// <summary>
/// This allows MatML data to be pulled from the wxTreeCtrl 
/// selection and boost::any_cast back into MatML Data pointer.
/// </summary>
	class MatMLTreeItemData : public wxTreeItemData
	{
		boost::any m_AnyMatMLData;
		wxString m_desc;
		size_t size;
		observer_ptr<void> voidptr;

	public:
		MatMLTreeItemData() : m_AnyMatMLData(nullptr), voidptr(observer_ptr<void>()), size(sizeof(nullptr)) {}
		MatMLTreeItemData(observer_ptr<Associate> MatMLData, const wxString& desc = wxT("Associate")) : m_AnyMatMLData(MatMLData), m_desc(desc), voidptr(observer_ptr<void>(MatMLData)), size(sizeof(MatMLData)) { }
		MatMLTreeItemData(observer_ptr<AssociationDetails> MatMLData, const wxString& desc = wxT("AssociationDetails")) : m_AnyMatMLData(MatMLData), m_desc(desc), voidptr(observer_ptr<void>(MatMLData)), size(sizeof(MatMLData)) { }
		MatMLTreeItemData(observer_ptr<AuthorityDetails> MatMLData, const wxString& desc = wxT("AuthorityDetails")) : m_AnyMatMLData(MatMLData), m_desc(desc), voidptr(observer_ptr<void>(MatMLData)), size(sizeof(MatMLData)) { }
		MatMLTreeItemData(observer_ptr<BulkDetails> MatMLData, const wxString& desc = wxT("BulkDetails")) : m_AnyMatMLData(MatMLData), m_desc(desc), voidptr(observer_ptr<void>(MatMLData)), size(sizeof(MatMLData)) { }
		MatMLTreeItemData(observer_ptr<Characterization> MatMLData, const wxString& desc = wxT("Characterization")) : m_AnyMatMLData(MatMLData), m_desc(desc), voidptr(observer_ptr<void>(MatMLData)), size(sizeof(MatMLData)) { }
		MatMLTreeItemData(observer_ptr<ChemicalComposition> MatMLData, const wxString& desc = wxT("ChemicalComposition")) : m_AnyMatMLData(MatMLData), m_desc(desc), voidptr(observer_ptr<void>(MatMLData)), size(sizeof(MatMLData)) { }
		//MatMLTreeItemData(observer_ptr<ChemicalElementSymbol> MatMLData, const wxString& desc = wxT("ChemicalElementSymbol")) : m_AnyMatMLData(MatMLData), m_desc(desc), voidptr(observer_ptr<void>(MatMLData)), size(sizeof(MatMLData)) { }
		MatMLTreeItemData(observer_ptr<Class> MatMLData, const wxString& desc = wxT("Class")) : m_AnyMatMLData(MatMLData), m_desc(desc), voidptr(observer_ptr<void>(MatMLData)), size(sizeof(MatMLData)) { }
		MatMLTreeItemData(observer_ptr<Subclass> MatMLData, const wxString& desc = wxT("Subclass")) : m_AnyMatMLData(MatMLData), m_desc(desc), voidptr(observer_ptr<void>(MatMLData)), size(sizeof(MatMLData)) { }
		MatMLTreeItemData(observer_ptr<Subclass1> MatMLData, const wxString& desc = wxT("Subclass1")) : m_AnyMatMLData(MatMLData), m_desc(desc), voidptr(observer_ptr<void>(MatMLData)), size(sizeof(MatMLData)) { }
		MatMLTreeItemData(observer_ptr<ParentMaterial> MatMLData, const wxString& desc = wxT("ParentMaterial")) : m_AnyMatMLData(MatMLData), m_desc(desc), voidptr(observer_ptr<void>(MatMLData)), size(sizeof(MatMLData)) { }
		MatMLTreeItemData(observer_ptr<ParentSubClass> MatMLData, const wxString& desc = wxT("ParentSubClass")) : m_AnyMatMLData(MatMLData), m_desc(desc), voidptr(observer_ptr<void>(MatMLData)), size(sizeof(MatMLData)) { }
		MatMLTreeItemData(observer_ptr<ComponentDetails> MatMLData, const wxString& desc = wxT("ComponentDetails")) : m_AnyMatMLData(MatMLData), m_desc(desc), voidptr(observer_ptr<void>(MatMLData)), size(sizeof(MatMLData)) { }
		MatMLTreeItemData(observer_ptr<Compound> MatMLData, const wxString& desc = wxT("Compound")) : m_AnyMatMLData(MatMLData), m_desc(desc), voidptr(observer_ptr<void>(MatMLData)), size(sizeof(MatMLData)) { }
		MatMLTreeItemData(observer_ptr<Concentration> MatMLData, const wxString& desc = wxT("Concentration")) : m_AnyMatMLData(MatMLData), m_desc(desc), voidptr(observer_ptr<void>(MatMLData)), size(sizeof(MatMLData)) { }
		MatMLTreeItemData(observer_ptr<CurrencyCode> MatMLData, const wxString& desc = wxT("CurrencyCode")) : m_AnyMatMLData(MatMLData), m_desc(desc), voidptr(observer_ptr<void>(MatMLData)), size(sizeof(MatMLData)) { }
		MatMLTreeItemData(observer_ptr<DataFormat> MatMLData, const wxString& desc = wxT("DataFormat")) : m_AnyMatMLData(MatMLData), m_desc(desc), voidptr(observer_ptr<void>(MatMLData)), size(sizeof(MatMLData)) { }
		MatMLTreeItemData(observer_ptr<DataSourceDetails> MatMLData, const wxString& desc = wxT("DataSourceDetails")) : m_AnyMatMLData(MatMLData), m_desc(desc), voidptr(observer_ptr<void>(MatMLData)), size(sizeof(MatMLData)) { }
		MatMLTreeItemData(observer_ptr<DimensionalDetails> MatMLData, const wxString& desc = wxT("DimensionalDetails")) : m_AnyMatMLData(MatMLData), m_desc(desc), voidptr(observer_ptr<void>(MatMLData)), size(sizeof(MatMLData)) { }
		MatMLTreeItemData(observer_ptr<Description> MatMLData, const wxString& desc = wxT("Description")) : m_AnyMatMLData(MatMLData), m_desc(desc), voidptr(observer_ptr<void>(MatMLData)), size(sizeof(MatMLData)) { }
		MatMLTreeItemData(observer_ptr<Element> MatMLData, const wxString& desc = wxT("Element")) : m_AnyMatMLData(MatMLData), m_desc(desc), voidptr(observer_ptr<void>(MatMLData)), size(sizeof(MatMLData)) { }
		MatMLTreeItemData(observer_ptr<Symbol> MatMLData, const wxString& desc = wxT("Symbol")) : m_AnyMatMLData(MatMLData), m_desc(desc), voidptr(observer_ptr<void>(MatMLData)), size(sizeof(MatMLData)) { }
		MatMLTreeItemData(observer_ptr<Form> MatMLData, const wxString& desc = wxT("Form")) : m_AnyMatMLData(MatMLData), m_desc(desc), voidptr(observer_ptr<void>(MatMLData)), size(sizeof(MatMLData)) { }
		MatMLTreeItemData(observer_ptr<Formula> MatMLData, const wxString& desc = wxT("Formula")) : m_AnyMatMLData(MatMLData), m_desc(desc), voidptr(observer_ptr<void>(MatMLData)), size(sizeof(MatMLData)) { }
		MatMLTreeItemData(observer_ptr<Geometry> MatMLData, const wxString& desc = wxT("Geometry")) : m_AnyMatMLData(MatMLData), m_desc(desc), voidptr(observer_ptr<void>(MatMLData)), size(sizeof(MatMLData)) { }
		MatMLTreeItemData(observer_ptr<Shape> MatMLData, const wxString& desc = wxT("Shape")) : m_AnyMatMLData(MatMLData), m_desc(desc), voidptr(observer_ptr<void>(MatMLData)), size(sizeof(MatMLData)) { }
		MatMLTreeItemData(observer_ptr<Dimensions> MatMLData, const wxString& desc = wxT("Dimensions")) : m_AnyMatMLData(MatMLData), m_desc(desc), voidptr(observer_ptr<void>(MatMLData)), size(sizeof(MatMLData)) { }
		MatMLTreeItemData(observer_ptr<Orientation> MatMLData, const wxString& desc = wxT("Orientation")) : m_AnyMatMLData(MatMLData), m_desc(desc), voidptr(observer_ptr<void>(MatMLData)), size(sizeof(MatMLData)) { }
		MatMLTreeItemData(observer_ptr<Glossary> MatMLData, const wxString& desc = wxT("Glossary")) : m_AnyMatMLData(MatMLData), m_desc(desc), voidptr(observer_ptr<void>(MatMLData)), size(sizeof(MatMLData)) { }
		MatMLTreeItemData(observer_ptr<GlossaryTerm> MatMLData, const wxString& desc = wxT("GlossaryTerm")) : m_AnyMatMLData(MatMLData), m_desc(desc), voidptr(observer_ptr<void>(MatMLData)), size(sizeof(MatMLData)) { }
		MatMLTreeItemData(observer_ptr<Definition> MatMLData, const wxString& desc = wxT("Definition")) : m_AnyMatMLData(MatMLData), m_desc(desc), voidptr(observer_ptr<void>(MatMLData)), size(sizeof(MatMLData)) { }
		MatMLTreeItemData(observer_ptr<Abbreviation> MatMLData, const wxString& desc = wxT("Abbreviation")) : m_AnyMatMLData(MatMLData), m_desc(desc), voidptr(observer_ptr<void>(MatMLData)), size(sizeof(MatMLData)) { }
		MatMLTreeItemData(observer_ptr<Synonym> MatMLData, const wxString& desc = wxT("Synonym")) : m_AnyMatMLData(MatMLData), m_desc(desc), voidptr(observer_ptr<void>(MatMLData)), size(sizeof(MatMLData)) { }
		//	This is the same as xml_schema::string MatMLTreeItemData(GlossaryTerm::Synonym_type*  MatMLData,const wxString& desc=wxT("Synonym")) : m_AnyMatMLData(MatMLData), m_desc(desc) { }
		//	MatMLTreeItemData(xml_schema::string*  MatMLData,const wxString& desc=wxT("String")) : m_AnyMatMLData(MatMLData), m_desc(desc), voidptr(observer_ptr<void>(MatMLData)) { }
		MatMLTreeItemData(observer_ptr<Graphs> MatMLData, const wxString& desc = wxT("Graphs")) : m_AnyMatMLData(MatMLData), m_desc(desc), voidptr(observer_ptr<void>(MatMLData)), size(sizeof(MatMLData)) { }
		MatMLTreeItemData(observer_ptr<Graph> MatMLData, const wxString& desc = wxT("Graph")) : m_AnyMatMLData(MatMLData), m_desc(desc), voidptr(observer_ptr<void>(MatMLData)), size(sizeof(MatMLData)) { }
		MatMLTreeItemData(observer_ptr<Material> MatMLData, const wxString& desc = wxT("Material")) : m_AnyMatMLData(MatMLData), m_desc(desc), voidptr(observer_ptr<void>(MatMLData)), size(sizeof(MatMLData)) { }
		MatMLTreeItemData(observer_ptr<MatML_Doc> MatMLData, const wxString& desc = wxT("MatML_Doc")) : m_AnyMatMLData(MatMLData), m_desc(desc), voidptr(observer_ptr<void>(MatMLData)), size(sizeof(MatMLData)) { }
		MatMLTreeItemData(observer_ptr<MeasurementTechniqueDetails> MatMLData, const wxString& desc = wxT("MeasurementTechniqueDetails")) : m_AnyMatMLData(MatMLData), m_desc(desc), voidptr(observer_ptr<void>(MatMLData)), size(sizeof(MatMLData)) { }
		MatMLTreeItemData(observer_ptr<Metadata> MatMLData, const wxString& desc = wxT("Metadata")) : m_AnyMatMLData(MatMLData), m_desc(desc), voidptr(observer_ptr<void>(MatMLData)), size(sizeof(MatMLData)) { }
		MatMLTreeItemData(observer_ptr<Name> MatMLData, const wxString& desc = wxT("Name")) : m_AnyMatMLData(MatMLData), m_desc(desc), voidptr(observer_ptr<void>(MatMLData)), size(sizeof(MatMLData)) { }
		MatMLTreeItemData(observer_ptr<Notes> MatMLData, const wxString& desc = wxT("Notes")) : m_AnyMatMLData(MatMLData), m_desc(desc), voidptr(observer_ptr<void>(MatMLData)), size(sizeof(MatMLData)) { }
		MatMLTreeItemData(observer_ptr<ParameterDetails> MatMLData, const wxString& desc = wxT("ParameterDetails")) : m_AnyMatMLData(MatMLData), m_desc(desc), voidptr(observer_ptr<void>(MatMLData)), size(sizeof(MatMLData)) { }
		MatMLTreeItemData(observer_ptr<ParameterValue> MatMLData, const wxString& desc = wxT("ParameterValue")) : m_AnyMatMLData(MatMLData), m_desc(desc), voidptr(observer_ptr<void>(MatMLData)), size(sizeof(MatMLData)) { }
		MatMLTreeItemData(observer_ptr<Data> MatMLData, const wxString& desc = wxT("Data")) : m_AnyMatMLData(MatMLData), m_desc(desc), voidptr(observer_ptr<void>(MatMLData)), size(sizeof(MatMLData)) { }
		MatMLTreeItemData(observer_ptr<PhaseComposition> MatMLData, const wxString& desc = wxT("PhaseComposition")) : m_AnyMatMLData(MatMLData), m_desc(desc), voidptr(observer_ptr<void>(MatMLData)), size(sizeof(MatMLData)) { }
		MatMLTreeItemData(observer_ptr<ProcessingDetails> MatMLData, const wxString& desc = wxT("ProcessingDetails")) : m_AnyMatMLData(MatMLData), m_desc(desc), voidptr(observer_ptr<void>(MatMLData)), size(sizeof(MatMLData)) { }
		MatMLTreeItemData(observer_ptr<Result> MatMLData, const wxString& desc = wxT("Result")) : m_AnyMatMLData(MatMLData), m_desc(desc), voidptr(observer_ptr<void>(MatMLData)), size(sizeof(MatMLData)) { }
		MatMLTreeItemData(observer_ptr<PropertyData> MatMLData, const wxString& desc = wxT("PropertyData")) : m_AnyMatMLData(MatMLData), m_desc(desc), voidptr(observer_ptr<void>(MatMLData)), size(sizeof(MatMLData)) { }
		MatMLTreeItemData(observer_ptr<delimiter> MatMLData, const wxString& desc = wxT("delimiter")) : m_AnyMatMLData(MatMLData), m_desc(desc), voidptr(observer_ptr<void>(MatMLData)), size(sizeof(MatMLData)) { }
		MatMLTreeItemData(observer_ptr<PropertyDetails> MatMLData, const wxString& desc = wxT("PropertyDetails")) : m_AnyMatMLData(MatMLData), m_desc(desc), voidptr(observer_ptr<void>(MatMLData)), size(sizeof(MatMLData)) { }
		MatMLTreeItemData(observer_ptr<Data1> MatMLData, const wxString& desc = wxT("Data")) : m_AnyMatMLData(MatMLData), m_desc(desc), voidptr(observer_ptr<void>(MatMLData)), size(sizeof(MatMLData)) { }
		MatMLTreeItemData(observer_ptr<Qualifier> MatMLData, const wxString& desc = wxT("Qualifier")) : m_AnyMatMLData(MatMLData), m_desc(desc), voidptr(observer_ptr<void>(MatMLData)), size(sizeof(MatMLData)) { }
		MatMLTreeItemData(observer_ptr<Relationship> MatMLData, const wxString& desc = wxT("Relationship")) : m_AnyMatMLData(MatMLData), m_desc(desc), voidptr(observer_ptr<void>(MatMLData)), size(sizeof(MatMLData)) { }
		MatMLTreeItemData(observer_ptr<Source> MatMLData, const wxString& desc = wxT("Source")) : m_AnyMatMLData(MatMLData), m_desc(desc), voidptr(observer_ptr<void>(MatMLData)), size(sizeof(MatMLData)) { }
		MatMLTreeItemData(observer_ptr<SourceDetails> MatMLData, const wxString& desc = wxT("SourceDetails")) : m_AnyMatMLData(MatMLData), m_desc(desc), voidptr(observer_ptr<void>(MatMLData)), size(sizeof(MatMLData)) { }
		MatMLTreeItemData(observer_ptr<Specification> MatMLData, const wxString& desc = wxT("Specification")) : m_AnyMatMLData(MatMLData), m_desc(desc), voidptr(observer_ptr<void>(MatMLData)), size(sizeof(MatMLData)) { }
		MatMLTreeItemData(observer_ptr<SpecimenDetails> MatMLData, const wxString& desc = wxT("SpecimenDetails")) : m_AnyMatMLData(MatMLData), m_desc(desc), voidptr(observer_ptr<void>(MatMLData)), size(sizeof(MatMLData)) { }
		MatMLTreeItemData(observer_ptr<TestConditionDetails> MatMLData, const wxString& desc = wxT("TestConditionDetails")) : m_AnyMatMLData(MatMLData), m_desc(desc), voidptr(observer_ptr<void>(MatMLData)), size(sizeof(MatMLData)) { }
		MatMLTreeItemData(observer_ptr<Uncertainty> MatMLData, const wxString& desc = wxT("Uncertainty")) : m_AnyMatMLData(MatMLData), m_desc(desc), voidptr(observer_ptr<void>(MatMLData)), size(sizeof(MatMLData)) { }
		MatMLTreeItemData(observer_ptr<Scale> MatMLData, const wxString& desc = wxT("Scale")) : m_AnyMatMLData(MatMLData), m_desc(desc), voidptr(observer_ptr<void>(MatMLData)), size(sizeof(MatMLData)) { }
		MatMLTreeItemData(observer_ptr<Unit> MatMLData, const wxString& desc = wxT("Unit")) : m_AnyMatMLData(MatMLData), m_desc(desc), voidptr(observer_ptr<void>(MatMLData)), size(sizeof(MatMLData)) { }
		MatMLTreeItemData(observer_ptr<Unitless> MatMLData, const wxString& desc = wxT("Unitless")) : m_AnyMatMLData(MatMLData), m_desc(desc), voidptr(observer_ptr<void>(MatMLData)), size(sizeof(MatMLData)) { }
		MatMLTreeItemData(observer_ptr<Units> MatMLData, const wxString& desc = wxT("Units")) : m_AnyMatMLData(MatMLData), m_desc(desc), voidptr(observer_ptr<void>(MatMLData)), size(sizeof(MatMLData)) { }
		MatMLTreeItemData(observer_ptr<Value> MatMLData, const wxString& desc = wxT("Value")) : m_AnyMatMLData(MatMLData), m_desc(desc), voidptr(observer_ptr<void>(MatMLData)), size(sizeof(MatMLData)) { }

		virtual ~MatMLTreeItemData() {
			DeleteStrongType< Definition>();
			DeleteStrongType< Abbreviation>();
			DeleteStrongType< Synonym>();
			DeleteStrongType< Shape>();
			DeleteStrongType< Dimensions>();
			DeleteStrongType< Orientation>();
			DeleteStrongType< Result>();
			DeleteStrongType< ParentSubClass>();
			DeleteStrongType< Description>();
			DeleteStrongType< Subclass>();
			DeleteStrongType< Subclass1>();
		}

		template<class T>
		void DeleteStrongType() {

			//if (!m_AnyMatMLData.empty()) {
			//	if (m_AnyMatMLData.type() == typeid(T*)) {
			//		T* strongtype = boost::any_cast<T*>(m_AnyMatMLData);
			//		delete strongtype;
			//	}
			//}
		}


		const boost::any GetAnyMatMLDataPointer() const { return m_AnyMatMLData; }
		decltype(auto) GetVoidMatMLDataPointer() const { return voidptr; }
		size_t GetDataSize() { return size; }

		template<class T>
		void SetAnyMatMLDataPointer(T MatMLData)
		{
			this->m_AnyMatMLData = MatMLData;
			this->voidptr = observer_ptr<void> (MatMLData);
			this->size = sizeof(MatMLData);
		}

		void NullAnyMatMLDataPointer()
		{
			this->m_AnyMatMLData = nullptr;
			this->voidptr=observer_ptr<void>();
			this->size = sizeof(nullptr);
		}

		const wxChar* GetDesc() const { return m_desc.c_str(); }



		const bool operator==(const MatMLTreeItemData& in) { return in.voidptr==voidptr; }

	};
}//namespace bellshire





