#include "var.h"

Var::Var(VarDecl* decl)
    : decl_(decl)
{
}

void Var::Pretty(std::ostream& strm) const
{
    strm << decl_->varname();
}
