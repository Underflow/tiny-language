#pragma once

#include "exp.h"
#include "vardecl.h"

class Var : public Exp
{
	const VarDecl* decl_;

public:
	Var(VarDecl* decl);
	virtual void Pretty(std::ostream& strm) const;
};