#include "BT_MatML_GatherIDRefs.h"

using namespace bellshire;


GatherIDRefs::idref_ptrs bellshire::GatherIDRefs::IDRefs(Associate* element) {
    GatherIDRefs::idref_ptrs rtn;
    // none
    return rtn;
}

GatherIDRefs::idref_ptrs bellshire::GatherIDRefs::IDRefs(AssociationDetails* element) {
    GatherIDRefs::idref_ptrs rtn;

    if (element->Associate().present())
        for (auto i : IDRefs(&element->Associate().get())) rtn.push_back(i);

    if (element->Notes().present())
        for (auto i : IDRefs(&element->Notes().get())) rtn.push_back(i);

    return rtn;
}

GatherIDRefs::idref_ptrs bellshire::GatherIDRefs::IDRefs(BulkDetails* element)
{
    GatherIDRefs::idref_ptrs rtn;

    for (auto i : Sequence_IDRefs(element->Class())) rtn.push_back(i);

    for (auto i : Sequence_IDRefs(element->Subclass())) rtn.push_back(i);

    if (element->Characterization().present())
        for (auto i : IDRefs(&element->Characterization().get())) rtn.push_back(i);

    if (element->Source().present())
        for (auto i : IDRefs(&element->Source().get())) rtn.push_back(i);

    if (element->Form().present())
        for (auto i : IDRefs(&element->Form().get())) rtn.push_back(i);

    for (auto i : IDRefs(&element->Name())) rtn.push_back(i);

    for (auto i : Sequence_IDRefs(element->Specification())) rtn.push_back(i);

    for (auto i : Sequence_IDRefs(element->ProcessingDetails())) rtn.push_back(i);

    for (auto i : Sequence_IDRefs(element->PropertyData())) rtn.push_back(i);

    if (element->Notes().present())
        for (auto i : IDRefs(&element->Notes().get())) rtn.push_back(i);

    return rtn;
}

GatherIDRefs::idref_ptrs bellshire::GatherIDRefs::IDRefs(Characterization* element) {
    GatherIDRefs::idref_ptrs rtn;
    if (element->ChemicalComposition().present())
        for (auto i : IDRefs(&element->ChemicalComposition().get())) rtn.push_back(i);

    for (auto i : Sequence_IDRefs(element->DimensionalDetails())) rtn.push_back(i);

    for (auto i : IDRefs(&element->Formula())) rtn.push_back(i);

    for (auto i : Sequence_IDRefs(element->PhaseComposition())) rtn.push_back(i);

    if (element->Notes().present())
        for (auto i : IDRefs(&element->Notes().get())) rtn.push_back(i);

    return rtn;
};
GatherIDRefs::idref_ptrs bellshire::GatherIDRefs::IDRefs(ChemicalComposition* element) {
    GatherIDRefs::idref_ptrs rtn;

    for (auto i : Sequence_IDRefs(element->Compound())) rtn.push_back(i);

    for (auto i : Sequence_IDRefs(element->Element())) rtn.push_back(i);

    return rtn;
};

GatherIDRefs::idref_ptrs bellshire::GatherIDRefs::IDRefs(Class* element)
{
    GatherIDRefs::idref_ptrs rtn;


    if (element->Name().present())
        for (GatherIDRefs::idref_ptr i : IDRefs(&element->Name().get())) {
            rtn.push_back(i);
        }

    for (GatherIDRefs::idref_ptr i : Sequence_IDRefs(element->ParentMaterial())) {
        rtn.push_back(i); 
    }

    for (GatherIDRefs::idref_ptr i : Sequence_IDRefs(element->ParentSubClass())) {
        rtn.push_back(i);
    }

    return rtn;
}

GatherIDRefs::idref_ptrs bellshire::GatherIDRefs::IDRefs(ComponentDetails* element)
{
    GatherIDRefs::idref_ptrs rtn;

    for (auto i : IDRefs(&element->Name())) rtn.push_back(i);

    for (auto i : Sequence_IDRefs(element->AssociationDetails())) rtn.push_back(i);

    if (element->Characterization().present())
        for (auto i : IDRefs(&element->Characterization().get())) rtn.push_back(i);

    for (auto i : Sequence_IDRefs(element->Class())) rtn.push_back(i);

    for (auto i : Sequence_IDRefs(element->Subclass())) rtn.push_back(i);

    for (auto i : Sequence_IDRefs(element->ComponentDetails1())) rtn.push_back(i);

    if (element->Form().present())
        for (auto i : IDRefs(&element->Form().get())) rtn.push_back(i);

    for (auto i : Sequence_IDRefs(element->ProcessingDetails())) rtn.push_back(i);

    for (auto i : Sequence_IDRefs(element->PropertyData())) rtn.push_back(i);

    if (element->Source().present())
        for (auto i : IDRefs(&element->Source().get())) rtn.push_back(i);

    for (auto i : Sequence_IDRefs(element->Specification())) rtn.push_back(i);

    return rtn;
}

GatherIDRefs::idref_ptrs bellshire::GatherIDRefs::IDRefs(Compound* element) {
    GatherIDRefs::idref_ptrs rtn;

    if (element->Concentration().present())
        for (auto i : IDRefs(&element->Concentration().get())) rtn.push_back(i);

    for (auto i : Sequence_IDRefs(element->Element())) rtn.push_back(i);

    if (element->Notes().present())
        for (auto i : IDRefs(&element->Notes().get())) rtn.push_back(i);

    return rtn;
};
GatherIDRefs::idref_ptrs bellshire::GatherIDRefs::IDRefs(Concentration* element) {
    GatherIDRefs::idref_ptrs rtn;

    for (auto i : Sequence_IDRefs(element->Qualifier())) rtn.push_back(i);

    for (auto i : Sequence_IDRefs(element->Uncertainty())) rtn.push_back(i);

    for (auto i : IDRefs(&element->Units())) rtn.push_back(i);

    for (auto i : IDRefs(&element->Value())) rtn.push_back(i);

    if (element->Notes().present())
        for (auto i : IDRefs(&element->Notes().get())) rtn.push_back(i);

    return rtn;
};
GatherIDRefs::idref_ptrs bellshire::GatherIDRefs::IDRefs(DataFormat* element) {
    GatherIDRefs::idref_ptrs rtn;
    //none
    return rtn;
};
GatherIDRefs::idref_ptrs bellshire::GatherIDRefs::IDRefs(DimensionalDetails* element) {
    GatherIDRefs::idref_ptrs rtn;

    for (auto i : IDRefs(&element->Name())) rtn.push_back(i);

    if (element->Qualifier().present())
        for (auto i : IDRefs(&element->Qualifier().get())) rtn.push_back(i);

    for (auto i : Sequence_IDRefs(element->Uncertainty())) rtn.push_back(i);

    for (auto i : IDRefs(&element->Units())) rtn.push_back(i);

    for (auto i : IDRefs(&element->Value())) rtn.push_back(i);

    if (element->Notes().present())
        for (auto i : IDRefs(&element->Notes().get())) rtn.push_back(i);

    return rtn;
};
GatherIDRefs::idref_ptrs bellshire::GatherIDRefs::IDRefs(Element* element) {
    GatherIDRefs::idref_ptrs rtn;

    if (element->Concentration().present())
        for (auto i : IDRefs(&element->Concentration().get())) rtn.push_back(i);

    for (auto i : IDRefs(&element->Symbol())) rtn.push_back(i);

    if (element->Notes().present())
        for (auto i : IDRefs(&element->Notes().get())) rtn.push_back(i);

    return rtn;
};
GatherIDRefs::idref_ptrs bellshire::GatherIDRefs::IDRefs(Form* element) {
    GatherIDRefs::idref_ptrs rtn;

    for (auto i : IDRefs(&element->Description())) rtn.push_back(i);

    if (element->Geometry().present())
        for (auto i : IDRefs(&element->Geometry().get())) rtn.push_back(i);

    if (element->Notes().present())
        for (auto i : IDRefs(&element->Notes().get())) rtn.push_back(i);

    return rtn;
};
GatherIDRefs::idref_ptrs bellshire::GatherIDRefs::IDRefs(Formula* element) {
    GatherIDRefs::idref_ptrs rtn;
    //none
    return rtn;
};
GatherIDRefs::idref_ptrs bellshire::GatherIDRefs::IDRefs(Geometry* element) {
    GatherIDRefs::idref_ptrs rtn;

    if (element->Dimensions().present())
        for (auto i : IDRefs(&Dimensions(&element->Dimensions().get()))) rtn.push_back(i);

    if (element->Orientation().present())
        for (auto i : IDRefs(&Orientation(&element->Orientation().get()))) rtn.push_back(i);

    for (auto i : IDRefs(&Shape(&element->Shape()))) rtn.push_back(i);

    if (element->Notes().present())
        for (auto i : IDRefs(&element->Notes().get())) rtn.push_back(i);

    return rtn;
};
GatherIDRefs::idref_ptrs bellshire::GatherIDRefs::IDRefs(Glossary* element) {
    GatherIDRefs::idref_ptrs rtn;

    for (auto i : Sequence_IDRefs(element->Term())) rtn.push_back(i);

    return rtn;
};
GatherIDRefs::idref_ptrs bellshire::GatherIDRefs::IDRefs(GlossaryTerm* element) {
    GatherIDRefs::idref_ptrs rtn;

    for (auto i : IDRefs(&element->Name())) rtn.push_back(i);

    for (auto i : Sequence_IDRefs_Strongtype<GlossaryTerm::Abbreviation_sequence, Abbreviation>(element->Abbreviation())) rtn.push_back(i);

    for (auto i : IDRefs(&Definition(&element->Definition()))) rtn.push_back(i);

    for (auto i : Sequence_IDRefs_Strongtype<GlossaryTerm::Synonym_sequence, Synonym>(element->Synonym())) rtn.push_back(i);

    if (element->Notes().present())
        for (auto i : IDRefs(&element->Notes().get())) rtn.push_back(i);

    return rtn;
};
GatherIDRefs::idref_ptrs bellshire::GatherIDRefs::IDRefs(Graphs* element) {
    GatherIDRefs::idref_ptrs rtn;

    for (auto i : Sequence_IDRefs(element->Graph())) rtn.push_back(i);

    return rtn;
};

GatherIDRefs::idref_ptrs bellshire::GatherIDRefs::IDRefs(Material* element)
{
    GatherIDRefs::idref_ptrs rtn;

    for (auto i : IDRefs(&element->BulkDetails())) rtn.push_back(i);

    for (auto i : Sequence_IDRefs(element->ComponentDetails())) rtn.push_back(i);

    if (element->Glossary().present())
        for (auto i : IDRefs(&element->Glossary().get())) rtn.push_back(i);

    if (element->Graphs().present())
        for (auto i : IDRefs(&element->Graphs().get())) rtn.push_back(i);

    return rtn;
}

GatherIDRefs::idref_ptrs bellshire::GatherIDRefs::IDRefs(Metadata* element)
{
    GatherIDRefs::idref_ptrs rtn;

    for (auto i : Sequence_IDRefs(element->AuthorityDetails())) rtn.push_back(i);

    for (auto i : Sequence_IDRefs(element->DataSourceDetails())) rtn.push_back(i);

    for (auto i : Sequence_IDRefs(element->MeasurementTechniqueDetails())) rtn.push_back(i);

    for (auto i : Sequence_IDRefs(element->ParameterDetails())) rtn.push_back(i);

    for (auto i : Sequence_IDRefs(element->PropertyDetails())) rtn.push_back(i);

    for (auto i : Sequence_IDRefs(element->SourceDetails())) rtn.push_back(i);

    for (auto i : Sequence_IDRefs(element->SpecimenDetails())) rtn.push_back(i);

    for (auto i : Sequence_IDRefs(element->TestConditionDetails())) rtn.push_back(i);

    return rtn;
}

GatherIDRefs::idref_ptrs bellshire::GatherIDRefs::IDRefs(Name* element)
{
    GatherIDRefs::idref_ptrs rtn;

    if (element->authority().present())
        rtn.push_back(&element->authority().get());

    return rtn;
}

GatherIDRefs::idref_ptrs bellshire::GatherIDRefs::IDRefs(Notes* element) {
    GatherIDRefs::idref_ptrs rtn;
    //none
    return rtn;
};
GatherIDRefs::idref_ptrs bellshire::GatherIDRefs::IDRefs(ParameterValue* element) {
    GatherIDRefs::idref_ptrs rtn;

    rtn.push_back(&element->parameter());

    for (auto i : IDRefs(&element->Data())) rtn.push_back(i);

    for (auto i : Sequence_IDRefs(element->Qualifier())) rtn.push_back(i);

    for (auto i : Sequence_IDRefs(element->Uncertainty())) rtn.push_back(i);

    if (element->Notes().present())
        for (auto i : IDRefs(&element->Notes().get())) rtn.push_back(i);


    return rtn;
};
GatherIDRefs::idref_ptrs bellshire::GatherIDRefs::IDRefs(PhaseComposition* element) {
    GatherIDRefs::idref_ptrs rtn;

    for (auto i : IDRefs(&element->Name())) rtn.push_back(i);

    if (element->Concentration().present())
        for (auto i : IDRefs(&element->Concentration().get())) rtn.push_back(i);

    for (auto i : Sequence_IDRefs(element->PropertyData())) rtn.push_back(i);

    if (element->Notes().present())
        for (auto i : IDRefs(&element->Notes().get())) rtn.push_back(i);

    return rtn;
};
GatherIDRefs::idref_ptrs bellshire::GatherIDRefs::IDRefs(ProcessingDetails* element) {
    GatherIDRefs::idref_ptrs rtn;

    for (auto i : IDRefs(&element->Name())) rtn.push_back(i);

    if (element->Result().present())
        for (auto i : IDRefs(&Result(&element->Result().get()))) rtn.push_back(i);

    for (auto i : Sequence_IDRefs(element->ParameterValue())) rtn.push_back(i);

    if (element->Notes().present())
        for (auto i : IDRefs(&element->Notes().get())) rtn.push_back(i);

    return rtn;
};
GatherIDRefs::idref_ptrs bellshire::GatherIDRefs::IDRefs(PropertyData* element) {
    GatherIDRefs::idref_ptrs rtn;

    for (auto i : IDRefs(&element->Data())) rtn.push_back(i);

    for (auto i : Sequence_IDRefs(element->ParameterValue())) rtn.push_back(i);

    rtn.push_back(&element->property());

    for (auto i : Sequence_IDRefs(element->Qualifier())) rtn.push_back(i);

    if (element->source().present())
        rtn.push_back(&element->source().get());

    if (element->specimen().present())
        rtn.push_back(&element->specimen().get());

    if (element->technique().present())
        rtn.push_back(&element->technique().get());

    if (element->test().present())
        rtn.push_back(&element->test().get());

    for (auto i : Sequence_IDRefs(element->Uncertainty())) rtn.push_back(i);

    if (element->Notes().present())
        for (auto i : IDRefs(&element->Notes().get())) rtn.push_back(i);


    return rtn;
};
GatherIDRefs::idref_ptrs bellshire::GatherIDRefs::IDRefs(Qualifier* element) {
    GatherIDRefs::idref_ptrs rtn;
    //none
    return rtn;
};
GatherIDRefs::idref_ptrs bellshire::GatherIDRefs::IDRefs(Relationship* element) {
    GatherIDRefs::idref_ptrs rtn;
    //none
    return rtn;
};
GatherIDRefs::idref_ptrs bellshire::GatherIDRefs::IDRefs(Source* element) {
    GatherIDRefs::idref_ptrs rtn;

    if (element->source().present())
        rtn.push_back(&element->source().get());

    return rtn;
};
GatherIDRefs::idref_ptrs bellshire::GatherIDRefs::IDRefs(Specification* element) {
    GatherIDRefs::idref_ptrs rtn;

    if (element->authority().present())
        rtn.push_back(&element->authority().get());

    return rtn;
};
GatherIDRefs::idref_ptrs bellshire::GatherIDRefs::IDRefs(Uncertainty* element) {
    GatherIDRefs::idref_ptrs rtn;

    for (auto i : IDRefs(&element->Value())) rtn.push_back(i);

    if (element->Units().present())
        for (auto i : IDRefs(&element->Units().get())) rtn.push_back(i);

    if (element->Unitless().present())
        for (auto i : IDRefs(&element->Unitless().get())) rtn.push_back(i);

    if (element->Scale().present())
        for (auto i : IDRefs(&element->Scale().get())) rtn.push_back(i);

    if (element->Notes().present())
        for (auto i : IDRefs(&element->Notes().get())) rtn.push_back(i);

    return rtn;
};
GatherIDRefs::idref_ptrs bellshire::GatherIDRefs::IDRefs(Unit* element) {
    GatherIDRefs::idref_ptrs rtn;

    //Note Name is a string not a Name element.

    if (element->Currency().present())
        for (auto i : IDRefs(&element->Currency().get())) rtn.push_back(i);

    return rtn;
};
GatherIDRefs::idref_ptrs bellshire::GatherIDRefs::IDRefs(Unitless* element) {
    GatherIDRefs::idref_ptrs rtn;
    //none
    return rtn;
};
GatherIDRefs::idref_ptrs bellshire::GatherIDRefs::IDRefs(Units* element) {
    GatherIDRefs::idref_ptrs rtn;

    for (auto i : Sequence_IDRefs(element->Unit())) rtn.push_back(i);

    return rtn;
};
GatherIDRefs::idref_ptrs bellshire::GatherIDRefs::IDRefs(Value* element) {
    GatherIDRefs::idref_ptrs rtn;
    //none
    return rtn;
};

GatherIDRefs::idref_ptrs bellshire::GatherIDRefs::IDRefs(AuthorityDetails* element)
{
    GatherIDRefs::idref_ptrs rtn;

    for (auto i : IDRefs(&element->Name())) rtn.push_back(i);

    if (element->Notes().present())
        for (auto i : IDRefs(&element->Notes().get())) rtn.push_back(i);

    return rtn;
}

GatherIDRefs::idref_ptrs bellshire::GatherIDRefs::IDRefs(DataSourceDetails* element) {
    GatherIDRefs::idref_ptrs rtn;

    for (auto i : IDRefs(&element->Name())) rtn.push_back(i);

    if (element->Notes().present())
        for (auto i : IDRefs(&element->Notes().get())) rtn.push_back(i);

    return rtn;
};
GatherIDRefs::idref_ptrs bellshire::GatherIDRefs::IDRefs(MeasurementTechniqueDetails* element) {
    GatherIDRefs::idref_ptrs rtn;

    for (auto i : IDRefs(&element->Name())) rtn.push_back(i);

    if (element->Notes().present())
        for (auto i : IDRefs(&element->Notes().get())) rtn.push_back(i);

    return rtn;
};
GatherIDRefs::idref_ptrs bellshire::GatherIDRefs::IDRefs(ParameterDetails* element) {
    GatherIDRefs::idref_ptrs rtn;

    for (auto i : IDRefs(&element->Name())) rtn.push_back(i);

    if (element->Units().present())
        for (auto i : IDRefs(&element->Units().get())) rtn.push_back(i);

    if (element->Unitless().present())
        for (auto i : IDRefs(&element->Unitless().get())) rtn.push_back(i);

    if (element->Notes().present())
        for (auto i : IDRefs(&element->Notes().get())) rtn.push_back(i);

    return rtn;
};
GatherIDRefs::idref_ptrs bellshire::GatherIDRefs::IDRefs(PropertyDetails* element) {
    GatherIDRefs::idref_ptrs rtn;

    for (auto i : IDRefs(&element->Name())) rtn.push_back(i);

    if (element->Units().present())
        for (auto i : IDRefs(&element->Units().get())) rtn.push_back(i);

    if (element->Unitless().present())
        for (auto i : IDRefs(&element->Unitless().get())) rtn.push_back(i);

    if (element->Notes().present())
        for (auto i : IDRefs(&element->Notes().get())) rtn.push_back(i);

    return rtn;
};
GatherIDRefs::idref_ptrs bellshire::GatherIDRefs::IDRefs(SourceDetails* element) {
    GatherIDRefs::idref_ptrs rtn;

    for (auto i : IDRefs(&element->Name())) rtn.push_back(i);

    if (element->Notes().present())
        for (auto i : IDRefs(&element->Notes().get())) rtn.push_back(i);

    return rtn;
};
GatherIDRefs::idref_ptrs bellshire::GatherIDRefs::IDRefs(SpecimenDetails* element) {
    GatherIDRefs::idref_ptrs rtn;

    if (element->Name().present())
        for (auto i : IDRefs(&element->Name().get())) rtn.push_back(i);

    if (element->Geometry().present())
        for (auto i : IDRefs(&element->Geometry().get())) rtn.push_back(i);

    if (element->Notes().present())
        for (auto i : IDRefs(&element->Notes().get())) rtn.push_back(i);

    return rtn;
};
GatherIDRefs::idref_ptrs bellshire::GatherIDRefs::IDRefs(TestConditionDetails* element) {
    GatherIDRefs::idref_ptrs rtn;

    for (auto i : Sequence_IDRefs(element->ParameterValue())) rtn.push_back(i);

    if (element->Notes().present())
        for (auto i : IDRefs(&element->Notes().get())) rtn.push_back(i);

    return rtn;
};
GatherIDRefs::idref_ptrs bellshire::GatherIDRefs::IDRefs(ChemicalElementSymbol* element) {
    GatherIDRefs::idref_ptrs rtn;
    //none
    return rtn;
};
GatherIDRefs::idref_ptrs bellshire::GatherIDRefs::IDRefs(CurrencyCode* element) {
    GatherIDRefs::idref_ptrs rtn;
    //none
    return rtn;
};

GatherIDRefs::idref_ptrs bellshire::GatherIDRefs::IDRefs(MatML_Doc* matml_doc)
{
    GatherIDRefs::idref_ptrs rtn;

    for (auto i : Sequence_IDRefs(matml_doc->Material())) rtn.push_back(i);

    if (matml_doc->Metadata().present())
        for (auto i : IDRefs(&matml_doc->Metadata().get())) rtn.push_back(i);

    return rtn;
}

GatherIDRefs::idref_ptrs bellshire::GatherIDRefs::IDRefs(ParentMaterial* element)
{
    GatherIDRefs::idref_ptrs rtn;
    {
        ::xml_schema::idref& idref(element->id());
        //const Material& material(dynamic_cast<const Material&>(*idref));
        rtn.push_back(&idref);
    }
    return rtn;
}

GatherIDRefs::idref_ptrs bellshire::GatherIDRefs::IDRefs(Symbol* element) {
    GatherIDRefs::idref_ptrs rtn;
    //none
    return rtn;
};
GatherIDRefs::idref_ptrs bellshire::GatherIDRefs::IDRefs(Graph* element) {
    GatherIDRefs::idref_ptrs rtn;
    //none
    return rtn;
};
GatherIDRefs::idref_ptrs bellshire::GatherIDRefs::IDRefs(Data* element) {
    GatherIDRefs::idref_ptrs rtn;
    //none
    return rtn;
};
GatherIDRefs::idref_ptrs bellshire::GatherIDRefs::IDRefs(Data1* element) {
    GatherIDRefs::idref_ptrs rtn;
    //none
    return rtn;
};
GatherIDRefs::idref_ptrs bellshire::GatherIDRefs::IDRefs(delimiter* element) {
    //none
    GatherIDRefs::idref_ptrs rtn;
    return rtn;
};
GatherIDRefs::idref_ptrs bellshire::GatherIDRefs::IDRefs(Scale* element) {
    GatherIDRefs::idref_ptrs rtn;
    //none
    return rtn;
};

GatherIDRefs::idref_ptrs bellshire::GatherIDRefs::IDRefs(Definition* element) {
    GatherIDRefs::idref_ptrs rtn;
    //none
    return rtn;
};
GatherIDRefs::idref_ptrs bellshire::GatherIDRefs::IDRefs(Abbreviation* element) {
    GatherIDRefs::idref_ptrs rtn;
    //none
    return rtn;
};
GatherIDRefs::idref_ptrs bellshire::GatherIDRefs::IDRefs(Synonym* element) {
    GatherIDRefs::idref_ptrs rtn;
    //none
    return rtn;
};
GatherIDRefs::idref_ptrs bellshire::GatherIDRefs::IDRefs(Shape* element) {
    GatherIDRefs::idref_ptrs rtn;
    //none
    return rtn;
};
GatherIDRefs::idref_ptrs bellshire::GatherIDRefs::IDRefs(Dimensions* element) {
    GatherIDRefs::idref_ptrs rtn;
    //none
    return rtn;
};
GatherIDRefs::idref_ptrs bellshire::GatherIDRefs::IDRefs(Orientation* element) {
    GatherIDRefs::idref_ptrs rtn;
    //none
    return rtn;
};
GatherIDRefs::idref_ptrs bellshire::GatherIDRefs::IDRefs(Result* element) {
    GatherIDRefs::idref_ptrs rtn;
    //none
    return rtn;
};

GatherIDRefs::idref_ptrs bellshire::GatherIDRefs::IDRefs(ParentSubClass* element)
{
    GatherIDRefs::idref_ptrs rtn;

    for (auto i : Sequence_IDRefs(element->t->ParentMaterial())) rtn.push_back(i);

    for (auto i : Sequence_IDRefs(element->t->ParentSubClass())) rtn.push_back(i);

    return rtn;
}

GatherIDRefs::idref_ptrs bellshire::GatherIDRefs::IDRefs(Description* element) {
    GatherIDRefs::idref_ptrs rtn;
    //none
    return rtn;
};

GatherIDRefs::idref_ptrs bellshire::GatherIDRefs::IDRefs(Subclass* element)
{
    GatherIDRefs::idref_ptrs rtn;

    for (auto i : Sequence_IDRefs(element->t->ParentMaterial())) rtn.push_back(i);

    for (auto i : Sequence_IDRefs(element->t->ParentSubClass())) rtn.push_back(i);

    return rtn;
}

GatherIDRefs::idref_ptrs bellshire::GatherIDRefs::IDRefs(Subclass1* element)
{
    GatherIDRefs::idref_ptrs rtn;

    for (auto i : Sequence_IDRefs(element->t->ParentMaterial())) rtn.push_back(i);

    for (auto i : Sequence_IDRefs(element->t->ParentSubClass())) rtn.push_back(i);

    return rtn;
}
