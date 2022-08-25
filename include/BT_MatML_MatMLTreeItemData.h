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

#include "matml31.hxx"
#include "matml31_strongtypedef.h"

namespace bellshire{

/// MatMLTreeItemData
///  Allows for the storage of MatML Data as a void pointer.
/// <summary>
/// This allows MatML data to be pulled from the wxTreeCtrl 
/// selection and boost::any_cast back into MatML Data pointer.
/// </summary>
class MatMLTreeItemData : public wxTreeItemData
{
public:
	MatMLTreeItemData() : m_AnyMatMLData(nullptr), voidptr(nullptr) {}
	MatMLTreeItemData(Associate*  MatMLData, const wxString& desc=wxT("Associate")) : m_AnyMatMLData(MatMLData), m_desc(desc), voidptr((void*)MatMLData) { }
	MatMLTreeItemData(AssociationDetails*  MatMLData, const wxString& desc=wxT("AssociationDetails")) : m_AnyMatMLData(MatMLData), m_desc(desc), voidptr((void*)MatMLData) { }
	MatMLTreeItemData(AuthorityDetails*  MatMLData,const wxString& desc=wxT("AuthorityDetails")) : m_AnyMatMLData(MatMLData), m_desc(desc), voidptr((void*)MatMLData) { }
	MatMLTreeItemData(BulkDetails*  MatMLData,const wxString& desc=wxT("BulkDetails")) : m_AnyMatMLData(MatMLData), m_desc(desc), voidptr((void*)MatMLData) { }
	MatMLTreeItemData(Characterization*  MatMLData,const wxString& desc=wxT("Characterization")) : m_AnyMatMLData(MatMLData), m_desc(desc), voidptr((void*)MatMLData) { }
	MatMLTreeItemData(ChemicalComposition*  MatMLData,const wxString& desc=wxT("ChemicalComposition")) : m_AnyMatMLData(MatMLData), m_desc(desc), voidptr((void*)MatMLData) { }
	MatMLTreeItemData(ChemicalElementSymbol*  MatMLData,const wxString& desc=wxT("ChemicalElementSymbol")) : m_AnyMatMLData(MatMLData), m_desc(desc), voidptr((void*)MatMLData) { }
	MatMLTreeItemData(Class*  MatMLData,const wxString& desc=wxT("Class")) : m_AnyMatMLData(MatMLData), m_desc(desc), voidptr((void*)MatMLData) { }
	MatMLTreeItemData(Subclass*  MatMLData,const wxString& desc=wxT("Subclass")) : m_AnyMatMLData(MatMLData), m_desc(desc), voidptr((void*)MatMLData) { }
	MatMLTreeItemData(Subclass1*  MatMLData,const wxString& desc=wxT("Subclass1")) : m_AnyMatMLData(MatMLData), m_desc(desc), voidptr((void*)MatMLData) { }
	MatMLTreeItemData(ParentMaterial*  MatMLData,const wxString& desc=wxT("ParentMaterial")) : m_AnyMatMLData(MatMLData), m_desc(desc), voidptr((void*)MatMLData) { }
	MatMLTreeItemData(ParentSubClass*  MatMLData,const wxString& desc=wxT("ParentSubClass")) : m_AnyMatMLData(MatMLData), m_desc(desc), voidptr((void*)MatMLData) { }
	MatMLTreeItemData(ComponentDetails*  MatMLData,const wxString& desc=wxT("ComponentDetails")) : m_AnyMatMLData(MatMLData), m_desc(desc), voidptr((void*)MatMLData) { }
	MatMLTreeItemData(Compound*  MatMLData,const wxString& desc=wxT("Compound")) : m_AnyMatMLData(MatMLData), m_desc(desc), voidptr((void*)MatMLData) { }
	MatMLTreeItemData(Concentration*  MatMLData,const wxString& desc=wxT("Concentration")) : m_AnyMatMLData(MatMLData), m_desc(desc), voidptr((void*)MatMLData) { }
	MatMLTreeItemData(CurrencyCode*  MatMLData,const wxString& desc=wxT("CurrencyCode")) : m_AnyMatMLData(MatMLData), m_desc(desc), voidptr((void*)MatMLData) { }
	MatMLTreeItemData(DataFormat*  MatMLData,const wxString& desc=wxT("DataFormat")) : m_AnyMatMLData(MatMLData), m_desc(desc), voidptr((void*)MatMLData) { }
	MatMLTreeItemData(DataSourceDetails*  MatMLData,const wxString& desc=wxT("DataSourceDetails")) : m_AnyMatMLData(MatMLData), m_desc(desc), voidptr((void*)MatMLData) { }
	MatMLTreeItemData(DimensionalDetails*  MatMLData,const wxString& desc=wxT("DimensionalDetails")) : m_AnyMatMLData(MatMLData), m_desc(desc), voidptr((void*)MatMLData) { }
	MatMLTreeItemData(Element*  MatMLData,const wxString& desc=wxT("Element")) : m_AnyMatMLData(MatMLData), m_desc(desc), voidptr((void*)MatMLData) { }
	MatMLTreeItemData(Symbol*  MatMLData,const wxString& desc=wxT("Symbol")) : m_AnyMatMLData(MatMLData), m_desc(desc), voidptr((void*)MatMLData) { }
	MatMLTreeItemData(Form*  MatMLData,const wxString& desc=wxT("Form")) : m_AnyMatMLData(MatMLData), m_desc(desc), voidptr((void*)MatMLData) { }
	MatMLTreeItemData(Formula*  MatMLData,const wxString& desc=wxT("Formula")) : m_AnyMatMLData(MatMLData), m_desc(desc), voidptr((void*)MatMLData) { }
	MatMLTreeItemData(Geometry*  MatMLData,const wxString& desc=wxT("Geometry")) : m_AnyMatMLData(MatMLData), m_desc(desc), voidptr((void*)MatMLData) { }
	MatMLTreeItemData(Shape*  MatMLData,const wxString& desc=wxT("Shape")) : m_AnyMatMLData(MatMLData), m_desc(desc), voidptr((void*)MatMLData) { }
	MatMLTreeItemData(Dimensions*  MatMLData,const wxString& desc=wxT("Dimensions")) : m_AnyMatMLData(MatMLData), m_desc(desc), voidptr((void*)MatMLData) { }
	MatMLTreeItemData(Orientation*  MatMLData,const wxString& desc=wxT("Orientation")) : m_AnyMatMLData(MatMLData), m_desc(desc), voidptr((void*)MatMLData) { }
	MatMLTreeItemData(Glossary*  MatMLData,const wxString& desc=wxT("Glossary")) : m_AnyMatMLData(MatMLData), m_desc(desc) , voidptr((void*)MatMLData) { }
	MatMLTreeItemData(GlossaryTerm*  MatMLData,const wxString& desc=wxT("GlossaryTerm")) : m_AnyMatMLData(MatMLData), m_desc(desc), voidptr((void*)MatMLData) { }
    MatMLTreeItemData(Definition*  MatMLData,const wxString& desc=wxT("Definition")) : m_AnyMatMLData(MatMLData), m_desc(desc), voidptr((void*)MatMLData) { }
    MatMLTreeItemData(Abbreviation*  MatMLData,const wxString& desc=wxT("Abbreviation")) : m_AnyMatMLData(MatMLData), m_desc(desc), voidptr((void*)MatMLData) { }
    MatMLTreeItemData(Synonym*  MatMLData,const wxString& desc=wxT("Synonym")) : m_AnyMatMLData(MatMLData), m_desc(desc), voidptr((void*)MatMLData) { }
//	This is the same as xml_schema::string MatMLTreeItemData(GlossaryTerm::Synonym_type*  MatMLData,const wxString& desc=wxT("Synonym")) : m_AnyMatMLData(MatMLData), m_desc(desc) { }
//	MatMLTreeItemData(xml_schema::string*  MatMLData,const wxString& desc=wxT("String")) : m_AnyMatMLData(MatMLData), m_desc(desc), voidptr((void*)MatMLData) { }
	MatMLTreeItemData(Graphs*  MatMLData,const wxString& desc=wxT("Graphs")) : m_AnyMatMLData(MatMLData), m_desc(desc), voidptr((void*)MatMLData) { }
	MatMLTreeItemData(Graph*  MatMLData,const wxString& desc=wxT("Graph")) : m_AnyMatMLData(MatMLData), m_desc(desc), voidptr((void*)MatMLData) { }
	MatMLTreeItemData(Material*  MatMLData,const wxString& desc=wxT("Material")) : m_AnyMatMLData(MatMLData), m_desc(desc), voidptr((void*)MatMLData) { }
	MatMLTreeItemData(MatML_Doc*  MatMLData,const wxString& desc=wxT("MatML_Doc")) : m_AnyMatMLData(MatMLData), m_desc(desc), voidptr((void*)MatMLData) { }
	MatMLTreeItemData(MeasurementTechniqueDetails*  MatMLData,const wxString& desc=wxT("MeasurementTechniqueDetails")) : m_AnyMatMLData(MatMLData), m_desc(desc), voidptr((void*)MatMLData) { }
	MatMLTreeItemData(Metadata*  MatMLData,const wxString& desc=wxT("Metadata")) : m_AnyMatMLData(MatMLData), m_desc(desc), voidptr((void*)MatMLData) { }
	MatMLTreeItemData(Name*  MatMLData,const wxString& desc=wxT("Name")) : m_AnyMatMLData(MatMLData), m_desc(desc), voidptr((void*)MatMLData) { }
	MatMLTreeItemData(Notes*  MatMLData,const wxString& desc=wxT("Notes")) : m_AnyMatMLData(MatMLData), m_desc(desc), voidptr((void*)MatMLData) { }
	MatMLTreeItemData(ParameterDetails*  MatMLData,const wxString& desc=wxT("ParameterDetails")) : m_AnyMatMLData(MatMLData), m_desc(desc), voidptr((void*)MatMLData) { }
	MatMLTreeItemData(ParameterValue*  MatMLData,const wxString& desc=wxT("ParameterValue")) : m_AnyMatMLData(MatMLData), m_desc(desc), voidptr((void*)MatMLData) { }
	MatMLTreeItemData(Data*  MatMLData,const wxString& desc=wxT("Data")) : m_AnyMatMLData(MatMLData), m_desc(desc), voidptr((void*)MatMLData) { }
	MatMLTreeItemData(PhaseComposition*  MatMLData,const wxString& desc=wxT("PhaseComposition")) : m_AnyMatMLData(MatMLData), m_desc(desc), voidptr((void*)MatMLData) { }
	MatMLTreeItemData(ProcessingDetails*  MatMLData,const wxString& desc=wxT("ProcessingDetails")) : m_AnyMatMLData(MatMLData), m_desc(desc), voidptr((void*)MatMLData) { }
	MatMLTreeItemData(Result*  MatMLData,const wxString& desc=wxT("Result")) : m_AnyMatMLData(MatMLData), m_desc(desc), voidptr((void*)MatMLData) { }
	MatMLTreeItemData(PropertyData*  MatMLData,const wxString& desc=wxT("PropertyData")) : m_AnyMatMLData(MatMLData), m_desc(desc), voidptr((void*)MatMLData) { }
	MatMLTreeItemData(delimiter*  MatMLData,const wxString& desc=wxT("delimiter")) : m_AnyMatMLData(MatMLData), m_desc(desc), voidptr((void*)MatMLData) { }
	MatMLTreeItemData(PropertyDetails*  MatMLData,const wxString& desc=wxT("PropertyDetails")) : m_AnyMatMLData(MatMLData), m_desc(desc), voidptr((void*)MatMLData) { }
	MatMLTreeItemData(Data1*  MatMLData,const wxString& desc=wxT("Data")) : m_AnyMatMLData(MatMLData), m_desc(desc) , voidptr((void*)MatMLData) { }
	MatMLTreeItemData(Qualifier*  MatMLData,const wxString& desc=wxT("Qualifier")) : m_AnyMatMLData(MatMLData), m_desc(desc), voidptr((void*)MatMLData) { }
	MatMLTreeItemData(Relationship*  MatMLData,const wxString& desc=wxT("Relationship")) : m_AnyMatMLData(MatMLData), m_desc(desc), voidptr((void*)MatMLData) { }
	MatMLTreeItemData(Source*  MatMLData,const wxString& desc=wxT("Source")) : m_AnyMatMLData(MatMLData), m_desc(desc), voidptr((void*)MatMLData) { }
	MatMLTreeItemData(SourceDetails*  MatMLData,const wxString& desc=wxT("SourceDetails")) : m_AnyMatMLData(MatMLData), m_desc(desc), voidptr((void*)MatMLData) { }
	MatMLTreeItemData(Specification*  MatMLData,const wxString& desc=wxT("Specification")) : m_AnyMatMLData(MatMLData), m_desc(desc), voidptr((void*)MatMLData) { }
	MatMLTreeItemData(SpecimenDetails*  MatMLData,const wxString& desc=wxT("SpecimenDetails")) : m_AnyMatMLData(MatMLData), m_desc(desc), voidptr((void*)MatMLData) { }
	MatMLTreeItemData(TestConditionDetails*  MatMLData,const wxString& desc=wxT("TestConditionDetails")) : m_AnyMatMLData(MatMLData), m_desc(desc), voidptr((void*)MatMLData) { }
	MatMLTreeItemData(Uncertainty*  MatMLData,const wxString& desc=wxT("Uncertainty")) : m_AnyMatMLData(MatMLData), m_desc(desc), voidptr((void*)MatMLData) { }
	MatMLTreeItemData(Scale*  MatMLData,const wxString& desc=wxT("Scale")) : m_AnyMatMLData(MatMLData), m_desc(desc), voidptr((void*)MatMLData) { }
	MatMLTreeItemData(Unit*  MatMLData,const wxString& desc=wxT("Unit")) : m_AnyMatMLData(MatMLData), m_desc(desc), voidptr((void*)MatMLData) { }
	MatMLTreeItemData(Unitless*  MatMLData,const wxString& desc=wxT("Unitless")) : m_AnyMatMLData(MatMLData), m_desc(desc), voidptr((void*)MatMLData) { }
	MatMLTreeItemData(Units*  MatMLData,const wxString& desc=wxT("Units")) : m_AnyMatMLData(MatMLData), m_desc(desc), voidptr((void*)MatMLData) { }
	MatMLTreeItemData(Value*  MatMLData,const wxString& desc=wxT("Value")) : m_AnyMatMLData(MatMLData), m_desc(desc), voidptr((void*)MatMLData) { }

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
	};

	template<class T>
	void DeleteStrongType() {

		if (!m_AnyMatMLData.empty()) {
			if (m_AnyMatMLData.type() == typeid(T*)) {
				T* strongtype = boost::any_cast<T*>(m_AnyMatMLData);
				delete strongtype;
			}
		}
	}

	const boost::any GetAnyMatMLDataPointer() const { return m_AnyMatMLData; }

	template<class T>
	void SetAnyMatMLDataPointer(T* MatMLData)
	{
		this->m_AnyMatMLData=MatMLData;
		this->voidptr=(void*)MatMLData;
	}

	void NullAnyMatMLDataPointer()
	{
		this->m_AnyMatMLData=nullptr;
		this->voidptr=(void*)nullptr;
	}

    const wxChar *GetDesc() const { return m_desc.c_str(); }
//	const bool operator==(MatMLTreeItemData& in) {return (in.voidptr==voidptr);}
	const bool operator==(const MatMLTreeItemData& in) {return (in.voidptr==voidptr);}

private:
	boost::any m_AnyMatMLData;
    wxString m_desc;
	void* voidptr;

};
}//namespace bellshire





