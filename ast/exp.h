#pragma once

#include "ast.h"

class Exp : public Ast
{
    virtual void Pretty(std::ostream& strm) const;
};

