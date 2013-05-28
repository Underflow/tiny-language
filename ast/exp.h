#pragma once

#include "ast.h"

class Exp : public Ast
{
public:
    virtual void Pretty(std::ostream& strm) const = 0;
    virtual void x86Gen(std::ostream& strm) const = 0;
};

