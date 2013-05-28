#pragma once

#include "ast.h"
#include "statement.h"

class Exp : public Statement
{
public:
    virtual void Pretty(std::ostream& strm) const = 0;
};

