#include "affect.h"

void Affect::Pretty(std::ostream& strm) const
{
    strm << var_->varname() << " = ";
    exp_->Pretty(strm);
}

Affect::Affect(VarDecl* var, std::unique_ptr<Exp>&& exp)
    : var_(var), exp_(std::move(exp))
{
}