#pragma once

#include <string>
#include <memory>

#include "ast.h"
#include "exp.h"
#include "statement.h"

class VarDecl : public Statement
{
    std::string varname_;
    int type_;
	std::unique_ptr<Exp> val_;

    public:
		VarDecl(int ty, const std::string& name, std::unique_ptr<Exp>&& val);
        virtual void Pretty(std::ostream& strm) const;

		const std::string varname() const { return varname_; }
};

