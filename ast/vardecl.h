#pragma once

#include "ast.h"

class VarDecl : public Ast
{
    virtual void Pretty(std::ostream& strm) const;
};

