#pragma once
#include "bellshire/matml31.hxx"
#include "bellshire/matml31_strongly_typed_def.h"
#include "bellshire/Lib/matml31_lib.hxx"

/*
* There are two types of the same MatML elements. One included in matmlXX.hxx and one included in matmlXX_lib.hxx
* The compiler differentiates between the two because of the different namespace. It is recommended that
* The specialization should be coded for the ::MatML_Class and NOT bellshire::Lib::MatML_Class. This will
* allow for ease of use.
*/
#ifndef SET_GET_LIB
#define SET_GET_LIB(TYPE) \
    template<> \
    class Get_Associated_Lib_type<::##TYPE> { \
    public: \
        using MatML_type =::##TYPE; \
        using MatML_lib_type = bellshire::Lib::##TYPE##_lib; \
    private: \
        Get_Associated_Lib_type() {} \
    };
#endif

namespace bellshire::Lib::utilities
{


    template<class MatML>
    class Get_Associated_Lib_type {
    public:
        using MatML_type = MatML;
        using MatML_lib_type = void;
    private:
        Get_Associated_Lib_type() {}
    };

    SET_GET_LIB(Associate);
    SET_GET_LIB(AssociationDetails);
    SET_GET_LIB(AuthorityDetails);
    SET_GET_LIB(BulkDetails);
    SET_GET_LIB(Characterization);
    SET_GET_LIB(ChemicalComposition);
    SET_GET_LIB(ChemicalElementSymbol);
    SET_GET_LIB(Class);
    SET_GET_LIB(ComponentDetails);
    SET_GET_LIB(Compound);
    SET_GET_LIB(Concentration);
    SET_GET_LIB(CurrencyCode);
    SET_GET_LIB(DataFormat);
    SET_GET_LIB(DataSourceDetails);
    SET_GET_LIB(DimensionalDetails);
    SET_GET_LIB(Element);
    SET_GET_LIB(Form);
    SET_GET_LIB(Formula);
    SET_GET_LIB(Geometry);
    SET_GET_LIB(Glossary);
    SET_GET_LIB(GlossaryTerm);
    SET_GET_LIB(Graphs);
    SET_GET_LIB(Material);
    //SET_GET_LIB(MatML_Doc);//'MatML_Doc': is not a member of 'bellshire::lib' defined in matml31_lib.hxx
    SET_GET_LIB(MeasurementTechniqueDetails);
    SET_GET_LIB(Metadata);
    SET_GET_LIB(Name);
    SET_GET_LIB(Notes);
    SET_GET_LIB(ParameterDetails);
    SET_GET_LIB(ParameterValue);
    SET_GET_LIB(PhaseComposition);
    SET_GET_LIB(ProcessingDetails);
    SET_GET_LIB(PropertyData);
    SET_GET_LIB(PropertyDetails);
    SET_GET_LIB(Qualifier);
    SET_GET_LIB(Relationship);
    SET_GET_LIB(Source);
    SET_GET_LIB(SourceDetails);
    SET_GET_LIB(Specification);
    SET_GET_LIB(SpecimenDetails);
    SET_GET_LIB(TestConditionDetails);
    SET_GET_LIB(Uncertainty);
    SET_GET_LIB(Unit);
    SET_GET_LIB(Unitless);
    SET_GET_LIB(Units);
    SET_GET_LIB(Value);
    //SET_GET_LIB(Definition);
    //SET_GET_LIB(Abbreviation);
    //SET_GET_LIB(Synonym);
    //SET_GET_LIB(Shape);
    //SET_GET_LIB(Dimensions);
    //SET_GET_LIB(Orientation);
    //SET_GET_LIB(Result);
    //SET_GET_LIB(ParentSubClass);
    //SET_GET_LIB(Description);
    //SET_GET_LIB(Subclass);
    //SET_GET_LIB(Subclass1);
    //SET_GET_LIB(ParentMaterial);
    //SET_GET_LIB(Data);
    //SET_GET_LIB(Data1);
    //SET_GET_LIB(Scale);
    //SET_GET_LIB(Symbol);
    //SET_GET_LIB(Graph);

    ParentMaterial;
    
};//namespace bellshire

#include "bellshire/Lib/utilities/BT_MatML_Get_Associated_Lib_type.inl"
