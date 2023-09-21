#pragma once

/// <summary>
/// This is to allows people to mark pointers as non-owning.
/// 
/// Use mainly to refer to the MatML element which are
/// owned by the MatML tree.
/// </summary>
/// <typeparam name="T"></typeparam>
template<typename T> using observer_ptr = T*;
