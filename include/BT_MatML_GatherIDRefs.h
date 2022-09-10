#pragma once
#include "matml31.hxx"
#include "matml31_strongtypedef.h"
#include <vector>

namespace bellshire {

    /// <summary>
    /// Moves through the MatML Tree and scrapes pointers to
    /// xml_schema::idref.
    /// </summary>
    class GatherIDRefs {
    public:

        GatherIDRefs() {};
        virtual ~GatherIDRefs() {};

        typedef xml_schema::idref* idref_ptr;
        typedef std::vector< idref_ptr> idref_ptrs;

        template<typename sequence_type>
        idref_ptrs Sequence_IDRefs(sequence_type& cont);

        template<typename sequence_type, typename strongtype_type>
        idref_ptrs Sequence_IDRefs_Strongtype(sequence_type& cont);

        idref_ptrs IDRefs(Associate* element);
        idref_ptrs IDRefs(AssociationDetails* element);
        idref_ptrs IDRefs(BulkDetails* element);
        idref_ptrs IDRefs(Characterization* element);
        idref_ptrs IDRefs(ChemicalComposition* element);
        idref_ptrs IDRefs(Class* element);
        idref_ptrs IDRefs(ComponentDetails* element);
        idref_ptrs IDRefs(Compound* element);
        idref_ptrs IDRefs(Concentration* element);
        idref_ptrs IDRefs(DataFormat* element);
        idref_ptrs IDRefs(DimensionalDetails* element);
        idref_ptrs IDRefs(Element* element);
        idref_ptrs IDRefs(Form* element);
        idref_ptrs IDRefs(Formula* element);
        idref_ptrs IDRefs(Geometry* element);
        idref_ptrs IDRefs(Glossary* element);
        idref_ptrs IDRefs(GlossaryTerm* element);
        idref_ptrs IDRefs(Graphs* element);
        idref_ptrs IDRefs(Material* element);
        idref_ptrs IDRefs(Metadata* element);
        idref_ptrs IDRefs(Name* element);
        idref_ptrs IDRefs(Notes* element);
        idref_ptrs IDRefs(ParameterValue* element);
        idref_ptrs IDRefs(PhaseComposition* element);
        idref_ptrs IDRefs(ProcessingDetails* element);
        idref_ptrs IDRefs(PropertyData* element);
        idref_ptrs IDRefs(Qualifier* element);
        idref_ptrs IDRefs(Relationship* element);
        idref_ptrs IDRefs(Source* element);
        idref_ptrs IDRefs(Specification* element);
        idref_ptrs IDRefs(Uncertainty* element);
        idref_ptrs IDRefs(Unit* element);
        idref_ptrs IDRefs(Unitless* element);
        idref_ptrs IDRefs(Units* element);
        idref_ptrs IDRefs(Value* element);
        idref_ptrs IDRefs(AuthorityDetails* element);
        idref_ptrs IDRefs(DataSourceDetails* element);
        idref_ptrs IDRefs(MeasurementTechniqueDetails* element);
        idref_ptrs IDRefs(ParameterDetails* element);
        idref_ptrs IDRefs(PropertyDetails* element);
        idref_ptrs IDRefs(SourceDetails* element);
        idref_ptrs IDRefs(SpecimenDetails* element);
        idref_ptrs IDRefs(TestConditionDetails* element);
        idref_ptrs IDRefs(ChemicalElementSymbol* element);
        idref_ptrs IDRefs(CurrencyCode* element);
        idref_ptrs IDRefs(MatML_Doc* element);
        idref_ptrs IDRefs(ParentMaterial* element);
        idref_ptrs IDRefs(Symbol* element);
        idref_ptrs IDRefs(Graph* element);
        idref_ptrs IDRefs(Data* element);
        idref_ptrs IDRefs(Data1* element);
        idref_ptrs IDRefs(delimiter* element);
        idref_ptrs IDRefs(Scale* element);

        idref_ptrs IDRefs(Definition* element);
        idref_ptrs IDRefs(Abbreviation* element);
        idref_ptrs IDRefs(Synonym* element);
        idref_ptrs IDRefs(Shape* element);
        idref_ptrs IDRefs(Dimensions* element);
        idref_ptrs IDRefs(Orientation* element);
        idref_ptrs IDRefs(Result* element);
        idref_ptrs IDRefs(ParentSubClass* element);
        idref_ptrs IDRefs(Description* element);
        idref_ptrs IDRefs(Subclass* element);
        idref_ptrs IDRefs(Subclass1* element);    
    };
}//Namespace bellshire

#include "BT_MatML_GatherIDRefs.inl"
