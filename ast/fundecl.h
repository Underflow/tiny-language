#pragma once

#include "ast.h"

class FunDecl : public Ast
{
    virtual void Pretty(std::ostream& strm) const;
};

