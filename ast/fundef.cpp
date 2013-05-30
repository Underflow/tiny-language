#include "fundef.h"

void Fundef::Pretty(std::ostream& strm) const
{
    strm << ret_type_ << " " << name_ << "(";
    auto arg = args_.begin();
    (*arg)->Pretty(strm);
    ++arg;

    for (; arg != args_.end(); ++arg)
    {
        strm << ", ";
        (*arg)->Pretty(strm);
    }
    strm << ")\n";
    body_->Pretty(strm);
}

Fundef::Fundef(const std::string& name, int ret_type,
       std::vector<std::unique_ptr<VarDecl>>&& args)
    : name_(name), ret_type_(ret_type), args_(std::move(args))
{
}