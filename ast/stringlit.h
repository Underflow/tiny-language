#pragma once

#include "ast.h"

class StringLit : public Ast
{
    std::string value_;
    public:
        virtual void Pretty(std::ostream& strm) const;
};

