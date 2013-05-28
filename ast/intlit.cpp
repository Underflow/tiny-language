#include "intlit.h"

void IntLit::Pretty(std::ostream& strm) const
{
    strm << value_;
}

void IntLit::x86Gen(std::ostream& strm) const
{
    strm << "push " << value_ << "\n";
}

