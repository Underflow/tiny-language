#include "funcall.h"

Funcall::Funcall(const std::string& fun,
        std::vector<std::unique_ptr<Exp>>&& args)
        : fun_(fun), args_(std::move(args))
{
}
void Funcall::Pretty(std::ostream& strm) const
{
    strm << fun_ << "(";
    for (const auto& arg : args_)
    {
        arg->Pretty(strm);
        strm << ", ";
    }
    strm << ")";
}

