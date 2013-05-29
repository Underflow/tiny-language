#pragma once

#include <memory>

#include "exp.h"
#include "vardecl.h"

class Affect : public Exp
{
    VarDecl* var_;
    std::unique_ptr<Exp> exp_;

    public:
        Affect(VarDecl* var, std::unique_ptr<Exp>&& exp);
        virtual void Pretty(std::ostream& strm) const;
};

