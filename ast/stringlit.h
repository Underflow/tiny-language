#pragma once

#include "ast.h"

class StringLit : public Ast
{
    virtual void Pretty(std::ostream& strm) const;
};

