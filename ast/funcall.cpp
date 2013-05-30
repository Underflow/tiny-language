#include "funcall.h"

Funcall::Funcall(const std::string& fun,
        std::vector<std::unique_ptr<Exp>>&& args, bool distr)
        : fun_(fun), args_(std::move(args)), distributed_(distr)
{
}
void Funcall::Pretty(std::ostream& strm) const
{
    if (!distributed_)
    {
        strm << fun_ << "(";
        auto arg = args_.begin();
        (*arg)->Pretty(strm);
        ++arg;
        for (; arg != args_.end(); ++arg)
        {
            strm << ", ";
            (*arg)->Pretty(strm);
        }
        strm << ")";
    }
    else
    {
        strm << "distributed_call(\"" << fun_ << "\"";

        for (int i = 0; i < args_.size(); ++i)
        {
            strm << ", ";
            args_[i]->Pretty(strm);
        }

        strm << ")\n";
    }
}

