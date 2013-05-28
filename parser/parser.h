#pragma once

#include <memory>
#include "../lexer/lexer.h"

#include "../ast/exp.h"

std::unique_ptr<Exp> Parse(Lexer& in);


