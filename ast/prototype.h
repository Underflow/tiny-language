#pragma once

#include "ast.h"

class Prototype : public Ast
{
    virtual void Pretty(std::ostream& strm) const;
};

