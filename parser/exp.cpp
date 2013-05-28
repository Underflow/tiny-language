#pragma once

#include "../lexer/lexer.h"
#include "../ast/exp.h"
#include "../ast/neg.h"
#include "../ast/binop.h"
#include "../ast/intlit.h"
#include "../unique.h"
#include "parser.h"

static std::unique_ptr<Exp> LowExp(Lexer& in);
std::unique_ptr<Exp> CompExp(Lexer& in);
std::unique_ptr<Exp> HighExp(Lexer& in);

std::unique_ptr<Exp> Term(Lexer& in)
{
    if (in.Is<int>())
    {
        return make_unique<IntLit>(in.Get<int>());
    }
	throw std::exception("invalid token");
}


std::unique_ptr<Exp> LowExp(Lexer& in)
{
    std::unique_ptr<Exp> lhs = HighExp(in);

    while (in.Is<LowOperator>())
    {
        LowOperator op = in.Get<LowOperator>();

        std::unique_ptr<Exp> rhs = HighExp(in);

        lhs = make_unique<Binop>(std::move(lhs), op, std::move(rhs));
    }

    return lhs;
}

std::unique_ptr<Exp> CompExp(Lexer& in)
{
    std::unique_ptr<Exp> lhs = LowExp(in);

    while (in.Is<CompOperator>())
    {
        CompOperator op = in.Get<CompOperator>();

        std::unique_ptr<Exp> rhs = LowExp(in);

        lhs = make_unique<Binop>(std::move(lhs), op, std::move(rhs));
    }

    return lhs;
}

std::unique_ptr<Exp> Parse(Lexer& in)
{
	return LowExp(in);
}

std::unique_ptr<Exp> Paren(Lexer& in)
{
    if (in.Is<LowOperator>())
    {
		if (in.Get<LowOperator>() == LowOperator::Sub)
            return make_unique<Neg>(LowExp(in));
    }
    if (in.Is<Parenthesis>())
    {
        if (in.Get<Parenthesis>() == Parenthesis::LeftParenthesis)
        {
			auto res = LowExp(in);
            if (in.Is<Parenthesis>()
                    && in.Get<Parenthesis>() == Parenthesis::RightParenthesis)
                return res;
        }
    }
    return Term(in);
}

std::unique_ptr<Exp> HighExp(Lexer& in)
{
    std::unique_ptr<Exp> lhs = Paren(in);

    while (in.Is<HighOperator>())
    {
        HighOperator op = in.Get<HighOperator>();

        std::unique_ptr<Exp> rhs = Paren(in);

        lhs = make_unique<Binop>(std::move(lhs), op, std::move(rhs));
    }

    return lhs;
}
