#pragma once

#include "ast.h"

class CompoundExp : public Ast
{
    virtual void Pretty(std::ostream& strm) const;
};

