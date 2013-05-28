#pragma once

#include <iostream>

class Ast
{
    public:
        virtual void Pretty(std::ostream& ostr) const = 0;
};
