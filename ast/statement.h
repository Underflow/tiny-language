#pragma once

#include "ast.h"

class Statement : public Ast
{
    virtual void Pretty(std::ostream& strm) const;
};

