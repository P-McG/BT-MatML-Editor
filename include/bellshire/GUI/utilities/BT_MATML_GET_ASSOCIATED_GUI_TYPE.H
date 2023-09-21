#pragma once
#include <math.h>
#include <type_traits>

#include "bellshire/matml31.hxx"
#include "bellshire/matml31_strongly_typed_def.h"

#include "bellshire/GUI/BT_MatML_GUI.h"

namespace bellshire::GUI
{
    class Intro_GUI;
    class MatML_Doc_GUI;
    class Material_GUI;
    class Associate_GUI;
    class AssociationDetails_GUI;
    class AuthorityDetails_GUI;
    class BulkDetails_GUI;
    class Characterization_GUI;
    class ChemicalComposition_GUI;
    class ChemicalElementSymbol_GUI;
    class Class_GUI;
    class Subclass_GUI;
    class Subclass1_GUI;
    class ParentMaterial_GUI;
    class ParentSubClass_GUI;
    class ComponentDetails_GUI;
    class Compound_GUI;
    class Concentration_GUI;
    class CurrencyCode_GUI;
    class DataSourceDetails_GUI;
    class DimensionalDetails_GUI;
    class Element_GUI;
    class Symbol_GUI;
    class Form_GUI;
    class Formula_GUI;
    class Geometry_GUI;
    class Shape_GUI;
    class Dimensions_GUI;
    class Orientation_GUI;
    class Glossary_GUI;
    class GlossaryTerm_GUI;
    class Definition_GUI;
    class Abbreviation_GUI;
    class Synonym_GUI;
    class Graphs_GUI;
    class Graph_GUI;
    class MeasurementTechniqueDetails_GUI;
    class Metadata_GUI;
    class Name_GUI;
    class Notes_GUI;
    class ParameterDetails_GUI;
    class ParameterValue_GUI;
    class Data_GUI;
    class PhaseComposition_GUI;
    class ProcessingDetails_GUI;
    class Result_GUI;
    class Relationship_GUI;
    class PropertyData_GUI;
    class Data1_GUI;
    class PropertyDetails_GUI;
    class Qualifier_GUI;
    class Source_GUI;
    class SourceDetails_GUI;
    class Specification_GUI;
    class SpecimenDetails_GUI;
    class TestConditionDetails_GUI;
    class Uncertainty_GUI;
    class Scale_GUI;
    class Unit_GUI;
    class Unitless_GUI;
    class Units_GUI;
    class Value_GUI;
    class DataFormat_GUI;
    class Description_GUI;
}

namespace bellshire::GUI::utilities{

#ifndef SET_GET_GUI
#define SET_GET_GUI( MATMLTYPE, GUITYPE) \
    template<> \
    class Get_Associated_GUI_type<MATMLTYPE> { \
    public: \
        using MatML_type = MATMLTYPE; \
        using MatML_GUI_type = GUITYPE; \
    private: \
        Get_Associated_GUI_type() {} \
    };
#endif

    template<class MatML>
    class Get_Associated_GUI_type {
    public:
        using MatML_type=MatML;
        using MatML_GUI_type=void;
    private:
        Get_Associated_GUI_type() {}
    };

    SET_GET_GUI(Associate, Associate_GUI);
    SET_GET_GUI(AssociationDetails, AssociationDetails_GUI);
    SET_GET_GUI(AuthorityDetails, AuthorityDetails_GUI);
    SET_GET_GUI(BulkDetails, BulkDetails_GUI);
    SET_GET_GUI(Characterization, Characterization_GUI);
    SET_GET_GUI(ChemicalComposition, ChemicalComposition_GUI);
    SET_GET_GUI(ChemicalElementSymbol, ChemicalElementSymbol_GUI);
    SET_GET_GUI(Class, Class_GUI);
    SET_GET_GUI(ComponentDetails, ComponentDetails_GUI);
    SET_GET_GUI(Compound, Compound_GUI);
    SET_GET_GUI(Concentration, Concentration_GUI);
    SET_GET_GUI(CurrencyCode, CurrencyCode_GUI);
    SET_GET_GUI(DataFormat, DataFormat_GUI);
    SET_GET_GUI(DataSourceDetails, DataSourceDetails_GUI);
    SET_GET_GUI(Description, Description_GUI);
    SET_GET_GUI(DimensionalDetails, DimensionalDetails_GUI);
    SET_GET_GUI(Element, Element_GUI);
    SET_GET_GUI(Form, Form_GUI);
    SET_GET_GUI(Formula, Formula_GUI);
    SET_GET_GUI(Geometry, Geometry_GUI);
    SET_GET_GUI(Glossary, Glossary_GUI);
    SET_GET_GUI(GlossaryTerm, GlossaryTerm_GUI);
    SET_GET_GUI(Graphs, Graphs_GUI);
    SET_GET_GUI(Material, Material_GUI);
    SET_GET_GUI(MatML_Doc, MatML_Doc_GUI);
    SET_GET_GUI(MeasurementTechniqueDetails, MeasurementTechniqueDetails_GUI);
    SET_GET_GUI(Metadata, Metadata_GUI);
    SET_GET_GUI(Name, Name_GUI);
    SET_GET_GUI(Notes, Notes_GUI);
    SET_GET_GUI(ParameterDetails, ParameterDetails_GUI);
    SET_GET_GUI(ParameterValue, ParameterValue_GUI);
    SET_GET_GUI(PhaseComposition, PhaseComposition_GUI);
    SET_GET_GUI(ProcessingDetails, ProcessingDetails_GUI);
    SET_GET_GUI(PropertyData, PropertyData_GUI);
    SET_GET_GUI(PropertyDetails, PropertyDetails_GUI);
    SET_GET_GUI(Qualifier, Qualifier_GUI);
    SET_GET_GUI(Relationship, Relationship_GUI);
    SET_GET_GUI(Source, Source_GUI);
    SET_GET_GUI(SourceDetails, SourceDetails_GUI);
    SET_GET_GUI(Specification, Specification_GUI);
    SET_GET_GUI(SpecimenDetails, SpecimenDetails_GUI);
    SET_GET_GUI(TestConditionDetails, TestConditionDetails_GUI);
    SET_GET_GUI(Uncertainty, Uncertainty_GUI);
    SET_GET_GUI(Unit, Unit_GUI);
    SET_GET_GUI(Unitless, Unitless_GUI);
    SET_GET_GUI(Units, Units_GUI);
    SET_GET_GUI(Value, Value_GUI);
    SET_GET_GUI(Definition, Definition_GUI);
    SET_GET_GUI(Abbreviation, Abbreviation_GUI);
    SET_GET_GUI(Synonym, Synonym_GUI);
    SET_GET_GUI(Shape, Shape_GUI);
    SET_GET_GUI(Dimensions, Dimensions_GUI);
    SET_GET_GUI(Orientation, Orientation_GUI);
    SET_GET_GUI(Result, Result_GUI);
    SET_GET_GUI(ParentSubClass, ParentSubClass_GUI);
    //SET_GET_GUI(Description, Description_GUI);
    SET_GET_GUI(Subclass, Subclass_GUI);
    SET_GET_GUI(Subclass1, Subclass1_GUI);
    SET_GET_GUI(ParentMaterial, ParentMaterial_GUI);
    SET_GET_GUI(Data, Data_GUI);
    SET_GET_GUI(Data1, Data1_GUI);
    SET_GET_GUI(Scale, Scale_GUI);
    SET_GET_GUI(Symbol, Symbol_GUI);
    SET_GET_GUI(Graph, Graph_GUI);

    
};//namespace bellshire

#include "bellshire/GUI/utilities/BT_MatML_Get_Associated_GUI_type.inl"
