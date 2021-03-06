#pragma once

#include "ast.h"

class FloatLit : public Ast
{
    float value_;

    public:
        virtual void Pretty(std::ostream& strm) const;
};

