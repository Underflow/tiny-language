#pragma once

#include "ast.h"

class Program : public Ast
{
    std::vector<VarDecl> vars_;
    std::vector<FunDecl> fundec_;

    public:
    virtual void Pretty(std::ostream& strm);
};
