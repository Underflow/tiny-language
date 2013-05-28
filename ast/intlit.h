#pragma once

#include "exp.h"

class IntLit : public Exp
{
    int value_;

    public:
        IntLit(int v) : value_(v) {}
        virtual void Pretty(std::ostream& strm) const;
};

