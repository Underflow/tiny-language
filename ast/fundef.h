#pragma once

#include <string>
#include <vector>

#include "ast.h"
#include "block.h"
#include "vardecl.h"

class Fundef : public Ast
{
    std::string name_;
    int ret_type_;
    std::vector<std::unique_ptr<VarDecl>> args_;
    std::unique_ptr<Block> body_;

    Fundef(const Fundef&);

public:
    Fundef(const std::string& name, int ret_type,
        std::vector<std::unique_ptr<VarDecl>>&& args);
    virtual void Pretty(std::ostream& strm) const;

    void body(std::unique_ptr<Block>&& body) { body_ = std::move(body); }
};

