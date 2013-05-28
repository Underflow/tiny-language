#pragma once

#include <iofwd>

class Ast
{
    public:
        virtual void Pretty(std::ostream& ostr) = 0;
};
