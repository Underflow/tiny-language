#pragma once

#include <memory>

#include "../lexer/lexer.h"
#include "../ast/exp.h"
#include "context.h"

std::unique_ptr<Exp> ParseExp(Lexer& in, Context& ctx);
std::unique_ptr<Ast> Parse(Lexer& in);
std::unique_ptr<Block> ParseBlock(Lexer& in, Context& ctx);
std::unique_ptr<Statement> ParseVarDecl(Lexer& in, Context& ctx);