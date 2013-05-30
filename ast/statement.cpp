#include "statement.h"

void Statement::Pretty(std::ostream& strm) const
{
    oh_my_->Pretty(strm);
    strm << ";";
}

