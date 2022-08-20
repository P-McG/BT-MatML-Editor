/////////////////////////////////////////////////////////////////////////////
// Name:        BT_MatML_Default.h
// Purpose:     Defaults for the MatML Classes.
// Author:      Paul McGrath
// Modified by:
// Created:
// Copyright:   (c) Paul McGrath
// Licence:     CC licence
/////////////////////////////////////////////////////////////////////////////
#ifndef CLASSDEFAULT_H
#define CLASSDEFAULT_H

#include "matml31.hxx"
#include "BT_MatML_MatMLTreeItemData.h"

using namespace bellshire;

template<class T>
class Default:public T
{
	public:
		Default<T>():T("REPLACE"){};
};

template<>
class Default<Associate>:public Associate
{
	public:
		Default<Associate>():Associate("REPLACE"){};
};

template<>
class Default<AssociationDetails>:public AssociationDetails
{
	public:
		Default(){};
};

template<>
class Default<Name>:public Name
{
public:
	Default<Name>():Name("REPLACE"){};
};

template<>
class Default<BulkDetails>:public BulkDetails
{
public:
	Default<BulkDetails>():BulkDetails(Default<::Name>()){};
};

template<>
class Default<Formula>:public Formula
{
public:
	Default<Formula>():Formula("REPLACE"){};
};

template<>
class Default<Characterization>:public Characterization
{
public:
	Default<Characterization>():Characterization(Default<::Formula>()){};
};

template<>
class Default<ChemicalComposition>:public ChemicalComposition
{
public:
	Default<ChemicalComposition>(){};
};

template<>
class Default<ChemicalElementSymbol>:public ChemicalElementSymbol
{
public:
	Default<ChemicalElementSymbol>():ChemicalElementSymbol("C"){};
};

template<>
class Default<Class>:public Class
{
public:
	Default<Class>(){};
};

template<>
class Default<ParentMaterial>:public ParentMaterial
{
public:
	Default<ParentMaterial>():ParentMaterial(xml_schema::id("REPLACE")){};
};

template<>
class Default<ParentSubClass>:public Class::ParentSubClass_type
{
public:
	Default<bellshire::ParentSubClass>(){};
};

template<>
class Default<ComponentDetails>:public ComponentDetails
{
public:
	Default<ComponentDetails>():ComponentDetails(Default<::Name>()){};
};

template<>
class Default<Compound>:public Compound
{
public:
	Default<Compound>(){};
};

template<>
class Default<Value>:public Value
{
public:
	Default<Value>():Value("0.0",format_type::float_){};
};

template<>
class Default<Unit>:public Unit
{
public:
	  Default<Unit>(){this->Name("REPLACE");};
};

template<>
class Default<Units>:public Units
{
public:
	Default<Units>():Units(){this->Unit().push_back(Default<::Unit>());};
};

template<>
class Default<Concentration>:public Concentration
{
public:
	Default<Concentration>():Concentration(Default<::Value>(),Default<::Units>()){};
};

template<>
class Default<CurrencyCode>:public CurrencyCode
{
public:
	Default<CurrencyCode>():CurrencyCode("CAD"){};
};

template<>
class Default<DataFormat>:public DataFormat
{
public:
	Default<DataFormat>():DataFormat(DataFormat::float_){};
};

template<>
class Default<DimensionalDetails>:public DimensionalDetails
{
public:
	Default<DimensionalDetails>():DimensionalDetails(Default<::Name>(),Default<::Value>(),Default<::Units>()){};
};

template<>
class Default<Symbol>:public Symbol
{
public:
	Default<Symbol>():Symbol(ChemicalElementSymbol("C")){};
};

template<>
class Default<Element>:public Element
{
public:
	Default<Element>():Element(Default<::Symbol>()){};
};

//template<>
//class Default<Description>:public Form::Description_type
//{
//public:
//	Default<Description>():Form::Description_type(Default<::Name>()){};
//};

template<>
class Default<Form>:public Form
{
public:
	Default<Form>():Form(Default<::Name>()){};
};

template<>
class Default<Dimensions>:public Geometry::Dimensions_type
{
public:
	Default<Dimensions>():Geometry::Dimensions_type("REPLACE") {};
};

template<>
class Default<Orientation>:public Geometry::Orientation_type
{
public:
	Default<Orientation>():Geometry::Orientation_type("REPLACE"){};
};

template<>
class Default<Shape>:public Geometry::Shape_type
{
public:
	Default<Shape>():Geometry::Shape_type("REPLACE") {};
};

template<>
class Default<Geometry>:public Geometry
{
public:
	Default<Geometry>():Geometry(Default<::Shape>()) {};
};

template<>
class Default<Glossary>:public Glossary
{
public:
	  Default<Glossary>():Glossary() {};

};

template<>
class Default<Definition>:public GlossaryTerm::Definition_type
{
public:
	Default<Definition>():GlossaryTerm::Definition_type(){};
};

template<>
class Default<GlossaryTerm>:public GlossaryTerm
{
public:
	Default<GlossaryTerm>():GlossaryTerm(Default<::Name>(),"REPLACE"){};
};

template<>
class Default<Abbreviation>:public GlossaryTerm::Abbreviation_type
{
public:
	Default<Abbreviation>():GlossaryTerm::Abbreviation_type("REPLACE"){};
};

template<>
class Default<Synonym>:public GlossaryTerm::Synonym_type
{
public:
	Default<Synonym>():GlossaryTerm::Synonym_type("REPLACE"){};
};

template<>
class Default<Graph>:public Graphs::Graph_type
{
public:
	Default<Graph>():Graphs::Graph_type() {};
};

template<>
class Default<Graphs>:public Graphs
{
public:
	Default<Graphs>() :Graphs() { this->Graph().push_back(Default<::Graph>()); };
};

template<>
class Default<Material>:public Material
{
public:
	Default<Material>():Material(Default<::BulkDetails>()){};
};

template<>
class Default<Metadata>:public Metadata
{
public:
	  Default<Metadata>(){};
};

template<>
class Default<Notes>:public Notes
{
public:
	Default<Notes>():Notes("REPLACE"){};
};

template<>
class Default<ParameterValue>:public ParameterValue
{
public:
	Default<ParameterValue>():ParameterValue(ParameterValue::Data_type("0.0"),
		 ParameterValue::parameter_type("0"),
		 Default<::DataFormat>()){};
};

template<>
class Default<PhaseComposition>:public PhaseComposition
{
public:
	Default<PhaseComposition>():PhaseComposition(Default<::Name>()){};
};

template<>
class Default<ProcessingDetails>:public ProcessingDetails
{
public:
	Default<ProcessingDetails>():ProcessingDetails(Default<::Name>()){};
};

template<>
class Default<Result>:public ProcessingDetails::Result_type
{
public:
	Default<Result>():ProcessingDetails::Result_type("REPLACE") {};
};

template<>
class Default<PropertyData>:public PropertyData
{
public:
	Default<PropertyData>():PropertyData(Data1("0.0",Default<::DataFormat>()),
		 PropertyData::property_type("REPLACE")){};
};

template<>
class Default<Qualifier>:public Qualifier
{
public:
	Default<Qualifier>():Qualifier("REPLACE"){};
};

template<>
class Default<Relationship>:public Relationship
{
public:
	Default<Relationship>():Relationship("REPLACE"){};
};

template<>
class Default<Source>:public Source
{
public:
	  Default<Source>(){};
};

template<>
class Default<Specification>:public Specification
{
public:
	Default<Specification>():Specification("REPLACE"){};
};

template<>
class Default<Uncertainty>:public Uncertainty
{
public:
	Default<Uncertainty>():Uncertainty(Default<::Value>()){
		Uncertainty::Units_optional& cont(this->Units());
		cont.set(Default<::Units>());
	};
};

template<>
class Default<Scale> :public Scale
{
public:
	Default<Scale>() :Scale("Linear") {};
};

template<>
class Default<Unitless>:public Unitless
{
public:
	  Default<Unitless>(){};
};

template<>
class Default<AuthorityDetails>:public AuthorityDetails
{
public:
	Default<AuthorityDetails>():AuthorityDetails(Default<::Name>(),xml_schema::id("REPLACE")){};
};

template<>
class Default<DataSourceDetails>:public DataSourceDetails
{
public:
	Default<DataSourceDetails>():DataSourceDetails(Default<::Name>(),xml_schema::id("REPLACE")){};
};

template<>
class Default<MeasurementTechniqueDetails>:public MeasurementTechniqueDetails
{
public:
	Default<MeasurementTechniqueDetails>():MeasurementTechniqueDetails(Default<::Name>(),xml_schema::id("REPLACE")){};
};

template<>
class Default<ParameterDetails>:public ParameterDetails
{
public:
	Default<ParameterDetails>():ParameterDetails(Default<::Name>(),xml_schema::id("REPLACE")){};
};

template<>
class Default<PropertyDetails>:public PropertyDetails
{
public:
	Default<PropertyDetails>():PropertyDetails(Default<::Name>(),xml_schema::id("REPLACE")){
		PropertyDetails::Units_optional& cont(this->Units());
		cont.set(Default<::Units>());
	};
};

template<>
class Default<SourceDetails>:public SourceDetails
{
public:
	Default<SourceDetails>():SourceDetails(Default<::Name>(),xml_schema::id("REPLACE")){};
};

template<>
class Default<SpecimenDetails>:public SpecimenDetails
{
public:
	Default<SpecimenDetails>():SpecimenDetails(xml_schema::id("REPLACE")){};
};

template<>
class Default<TestConditionDetails>:public TestConditionDetails
{
public:
	Default<TestConditionDetails>():TestConditionDetails(xml_schema::id("REPLACE")){};
};

template<>
class Default<MatML_Doc>:public MatML_Doc
{
public:
	Default<MatML_Doc>():MatML_Doc(){
		this->Material().push_back(Default<::Material>());
		this->Metadata().set(Default<::Metadata>());
	}
};


#endif
