#pragma once

#include "ast.h"

class Block : public Ast
{
    virtual void Pretty(std::ostream& strm) const;
};

