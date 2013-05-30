#include "vardecl.h"

#include <iostream>

VarDecl::VarDecl(int ty, const std::string& name, std::unique_ptr<Exp>&& val)
    : type_(ty), varname_(name), val_(std::move(val)), stack_offset_(-1)
{
}

void VarDecl::Pretty(std::ostream& strm) const
{
    strm << (type_ ? "float" : "int") << " " << varname_;
    if (val_)
    {
        strm << " = ";
        val_->Pretty(strm);
    }
}

