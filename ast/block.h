#pragma once

#include "ast.h"

class Block : public Ast
{
    std::vector<std::unique_ptr<CompoundExp>> stmts_;

    public:
        virtual void Pretty(std::ostream& strm) const;
};

