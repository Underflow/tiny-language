#pragma once

#include "ast.h"

class HighExp : public Ast
{
    virtual void Pretty(std::ostream& strm) const;
};

