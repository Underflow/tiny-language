#include "block.h"

void Block::push_back(std::unique_ptr<Control>&& ctrl)
{
    stmts_.push_back(std::move(ctrl));
}

void Block::Pretty(std::ostream& strm) const
{
    strm << "{\n";
    for (auto& stmt : stmts_)
    {
        stmt->Pretty(strm);
        strm << "\n";
    }
    strm << "}\n";
}

