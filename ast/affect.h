#pragma once

#include "ast.h"

class Affect : public Ast
{
    virtual void Pretty(std::ostream& strm) const;
};

