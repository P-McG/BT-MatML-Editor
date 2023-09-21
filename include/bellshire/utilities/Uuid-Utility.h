/////////////////////////////////////////////////////////////////////////////
// Name:        Uuid-Utility.h
// Purpose:     Utilities for the generation of the Uuids.
// Author:      Paul McGrath
// Modified by:
// Created:
// Copyright:   (c) Paul McGrath
// Licence:     CC licence
/////////////////////////////////////////////////////////////////////////////
#pragma once

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>


//creating a uuid class that
// initializes the uuid in the constructor
// using a defined mechanism

namespace bellshire::utilities{

class uuid_class : public boost::uuids::uuid
{
public:
    uuid_class()
        : boost::uuids::uuid(boost::uuids::random_generator()())
    {}

    explicit uuid_class(boost::uuids::uuid const& u)
        : boost::uuids::uuid(u)
    {}

    operator boost::uuids::uuid() {
        return static_cast<boost::uuids::uuid&>(*this);
    }

    operator boost::uuids::uuid() const {
        return static_cast<boost::uuids::uuid const&>(*this);
    }
};

// Usage
// uuid_class u1;
// uuid_class u2;
//
// assert(u1 != u2);

}//namespace bellshire
