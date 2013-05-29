#include "return.h"


Return::Return(std::unique_ptr<Exp>&& val)
    : val_(std::move(val))
{
}

void Return::Pretty(std::ostream& strm) const
{
    strm << "return ";
    val_->Pretty(strm);
    strm << ";";
}
