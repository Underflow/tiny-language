#pragma once

#include "ast.h"

class Statement : public Ast
{
public:
	virtual void Pretty(std::ostream& strm) const = 0;
};

