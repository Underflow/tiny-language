#pragma once

#include <memory>

#include "../lexer/lexer.h"
#include "../ast/exp.h"
#include "context.h"

std::unique_ptr<Exp> ParseExp(Lexer& in, Context& ctx);

std::unique_ptr<Ast> Parse(Lexer& in);


