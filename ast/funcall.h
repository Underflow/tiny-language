#pragma once

#include "ast.h"

class Funcall : public Ast
{
    virtual void Pretty(std::ostream& strm) const;
};

