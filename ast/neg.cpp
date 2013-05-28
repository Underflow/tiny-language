#include "neg.h"

void Neg::Pretty(std::ostream& strm) const
{
    strm << "-(";
    exp_->Pretty(strm);
    strm << ")";
}

void Neg::x86Gen(std::ostream& strm) const
{
    exp_->x86Gen(strm);
    strm <<
        "pop eax\n"
        "neg eax\n"
        "push eax\n";
}