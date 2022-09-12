#pragma once

/// <summary>
/// Takes a sequence and IDRefs calls the members of the container
/// </summary>
/// <typeparam name="sequence_type"></typeparam>
/// <param name="cont"></param>
/// <returns>Vector of IDRef pointers</returns>
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

/// <summary>
/// Same as GatherIDRefs, but with strongtype MatML Elements.
/// </summary>
/// <typeparam name="sequence_type"></typeparam>
/// <typeparam name="strongtype_type"></typeparam>
/// <param name="cont"></param>
/// <returns>vector of IDref pointers</returns>
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