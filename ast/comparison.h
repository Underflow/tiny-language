#pragma once

#include "ast.h"

class Comparison : public Ast
{
    virtual void Pretty(std::ostream& strm) const;
};

