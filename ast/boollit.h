#pragma once

#include "ast.h"

class BoolLit : public Ast
{
    virtual void Pretty(std::ostream& strm) const;
};

