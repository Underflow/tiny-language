#pragma once

#include "ast.h"

class FloatLit : public Ast
{
    virtual void Pretty(std::ostream& strm) const;
};

