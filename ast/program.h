#pragma once

#include <vector>
#include <memory>

#include "ast.h"
#include "fundef.h"
#include "vardecl.h"

class Program : public Ast
{
    std::vector<std::unique_ptr<VarDecl>> vars_;
    std::vector<std::unique_ptr<Fundef>> funs_;

public:
    virtual void Pretty(std::ostream& strm) const;
    Program(std::vector<std::unique_ptr<VarDecl>>&& vars,
        std::vector<std::unique_ptr<Fundef>>&& funs)
        : vars_(std::move(vars)), funs_(std::move(funs))
    {
    }
};
