#pragma once

#include <vector>
#include <memory>

#include "ast.h"

class Program : public Ast
{
    std::vector<std::unique_ptr<Ast>> decls_;

public:
    virtual void Pretty(std::ostream& strm) const;
    Program(std::vector<std::unique_ptr<Ast>>&& decls)
        : decls_(std::move(decls))
    {
    }
};
