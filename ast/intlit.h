#pragma once

#include "ast.h"

class IntLit : public Ast
{
    virtual void Pretty(std::ostream& strm) const;
};

