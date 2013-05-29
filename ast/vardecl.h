#pragma once

#include <string>
#include <memory>

#include "ast.h"
#include "type.h"
#include "exp.h"
#include "statement.h"

class VarDecl : public Statement
{
private:
    std::string varname_;
    int type_;
    std::unique_ptr<Exp> val_;
    int stack_offset_;

public:
    VarDecl(int type, const std::string& name, std::unique_ptr<Exp>&& val);
    virtual void Pretty(std::ostream& strm) const;

    const std::string& varname() const { return varname_; }
    void stack_offset(int stack_offset) { stack_offset_ = stack_offset; }
    int stack_offset() const { return stack_offset_; }
};

