#pragma once

#include "ast.h"

class Type : public Ast
{
    virtual void Pretty(std::ostream& strm) const;
};

