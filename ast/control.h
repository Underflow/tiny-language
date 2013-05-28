#pragma once

#include <memory>

#include "ast.h"

class Block;
class Exp;

class Control : public Ast
{
};

class If : public Control
{
	std::unique_ptr<Exp> cond_;
	std::unique_ptr<Block> if_;
	std::unique_ptr<Block> else_;

public:
	If(std::unique_ptr<Exp>&& cond, std::unique_ptr<Block> if_clause,
		std::unique_ptr<Block>&& else_clause = nullptr);
	virtual void Pretty(std::ostream& in) const;
};