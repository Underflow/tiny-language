#pragma once

#include "ast.h"

class Fundef : public Ast
{
    virtual void Pretty(std::ostream& strm) const;
};

