#pragma once

#include <vector>
#include <memory>

#include "ast.h"
#include "control.h"

class Block : public Ast
{
    std::vector<std::unique_ptr<Control>> stmts_;

    public:
        virtual void Pretty(std::ostream& strm) const;
        void push_back(std::unique_ptr<Control>&& ctrl);
};

