#include "neg.h"

void Neg::Pretty(std::ostream& strm) const
{
    strm << "-(";
    exp_->Pretty(strm);
    strm << ")";
}
