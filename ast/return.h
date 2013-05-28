#pragma once

#include <memory>

#include "statement.h"
#include "exp.h"

class Return : public Statement
{
    std::unique_ptr<Exp> val_;

    public:
        Return(std::unique_ptr<Exp>&& val);
        virtual void Pretty(std::ostream& strm) const;
};
