#pragma once

#include "ast.h"

class LowExp : public Ast
{
    virtual void Pretty(std::ostream& strm) const;
};

