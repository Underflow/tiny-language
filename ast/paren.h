#pragma once

#include "ast.h"

class Paren : public Ast
{
    virtual void Pretty(std::ostream& strm) const;
};

