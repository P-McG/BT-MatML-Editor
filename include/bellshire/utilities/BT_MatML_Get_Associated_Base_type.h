#pragma once
#include "bellshire/matml31.hxx"
#include "bellshire/matml31_strongly_typed_def.h"
#include "bellshire/BT_MatML.h"

#ifndef SET_GET_BASE
#define SET_GET_BASE(TYPE) \
    template<> \
    class Get_Associated_Base_type<TYPE> { \
    public: \
        using MatML_type = TYPE; \
        using MatML_Base_type = TYPE##_Base; \
    private: \
        Get_Associated_Base_type() {} \
    };
#endif

namespace bellshire::utilities
{
    template<class MatML>
    class Get_Associated_Base_type {
    public:
        using MatML_type = MatML;
        using MatML_Base_type = void;
    private:
        Get_Associated_Base_type() {}
    };

    SET_GET_BASE(Associate);
    SET_GET_BASE(AssociationDetails);
    SET_GET_BASE(AuthorityDetails);
    SET_GET_BASE(BulkDetails);
    SET_GET_BASE(Characterization);
    SET_GET_BASE(ChemicalComposition);
    SET_GET_BASE(ChemicalElementSymbol);
    SET_GET_BASE(Class);
    SET_GET_BASE(ComponentDetails);
    SET_GET_BASE(Compound);
    SET_GET_BASE(Concentration);
    SET_GET_BASE(CurrencyCode);
    SET_GET_BASE(DataFormat);
    SET_GET_BASE(DataSourceDetails);
    SET_GET_BASE(DimensionalDetails);
    SET_GET_BASE(Element);
    SET_GET_BASE(Form);
    SET_GET_BASE(Formula);
    SET_GET_BASE(Geometry);
    SET_GET_BASE(Glossary);
    SET_GET_BASE(GlossaryTerm);
    SET_GET_BASE(Graphs);
    SET_GET_BASE(Material);
    SET_GET_BASE(MatML_Doc);
    SET_GET_BASE(MeasurementTechniqueDetails);
    SET_GET_BASE(Metadata);
    SET_GET_BASE(Name);
    SET_GET_BASE(Notes);
    SET_GET_BASE(ParameterDetails);
    SET_GET_BASE(ParameterValue);
    SET_GET_BASE(PhaseComposition);
    SET_GET_BASE(ProcessingDetails);
    SET_GET_BASE(PropertyData);
    SET_GET_BASE(PropertyDetails);
    SET_GET_BASE(Qualifier);
    SET_GET_BASE(Relationship);
    SET_GET_BASE(Source);
    SET_GET_BASE(SourceDetails);
    SET_GET_BASE(Specification);
    SET_GET_BASE(SpecimenDetails);
    SET_GET_BASE(TestConditionDetails);
    SET_GET_BASE(Uncertainty);
    SET_GET_BASE(Unit);
    SET_GET_BASE(Unitless);
    SET_GET_BASE(Units);
    SET_GET_BASE(Value);
    SET_GET_BASE(Definition);
    SET_GET_BASE(Abbreviation);
    SET_GET_BASE(Synonym);
    SET_GET_BASE(Shape);
    SET_GET_BASE(Dimensions);
    SET_GET_BASE(Orientation);
    SET_GET_BASE(Result);
    SET_GET_BASE(ParentSubClass);
    //SET_GET_BASE(Description);
    SET_GET_BASE(Subclass);
    SET_GET_BASE(Subclass1);
    SET_GET_BASE(ParentMaterial);
    SET_GET_BASE(Data);
    SET_GET_BASE(Data1);
    SET_GET_BASE(Scale);
    SET_GET_BASE(Symbol);
    SET_GET_BASE(Graph);
    
};//namespace bellshire

#include "bellshire/utilities/BT_MatML_Get_Associated_Base_type.inl"
