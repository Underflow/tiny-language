#pragma once

#include "ast.h"

class Term : public Ast
{
    virtual void Pretty(std::ostream& strm) const;
};

