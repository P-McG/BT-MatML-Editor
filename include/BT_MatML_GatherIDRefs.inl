#pragma once


template<typename sequence_type>
bellshire::GatherIDRefs::idref_ptrs bellshire::GatherIDRefs::Sequence_IDRefs(sequence_type& cont)
{
    idref_ptrs rtn;

    //Loop through all the elements within the sequence.
    if (!cont.empty())
        for (auto& matml_class : cont) {
            for (idref_ptr i : IDRefs(&matml_class)) {
                rtn.push_back(i);
            }
        }

    return rtn;
}

template<typename sequence_type, typename strongtype_type>
bellshire::GatherIDRefs::idref_ptrs bellshire::GatherIDRefs::Sequence_IDRefs_Strongtype(sequence_type& cont)
{
    idref_ptrs rtn;

    //Loop through all the elements within the sequence.
    if (!cont.empty())
        for (auto& matml_class : cont)
            for (idref_ptr  i : IDRefs(&strongtype_type(&matml_class)))
                rtn.push_back(i);

    return rtn;
}