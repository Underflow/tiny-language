#pragma once

#include "ast.h"

class Affect : public Ast
{
    std::string id_;
    std::unique_ptr<Exp> exp_;

    public:
        virtual void Pretty(std::ostream& strm) const;
};

