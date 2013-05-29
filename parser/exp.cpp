#include <stdexcept>

#include "parser.h"
#include "context.h"
#include "../unique.h"
#include "../ast/exp.h"
#include "../ast/var.h"
#include "../ast/neg.h"
#include "../ast/binop.h"
#include "../ast/affect.h"
#include "../ast/intlit.h"
#include "../lexer/lexer.h"

static std::unique_ptr<Exp> LowExp(Lexer& in, Context& ctx);
static std::unique_ptr<Exp> CompExp(Lexer& in, Context& ctx);
static std::unique_ptr<Exp> HighExp(Lexer& in, Context& ctx);
static std::unique_ptr<Exp> LogicExp(Lexer& in, Context& ctx);

std::unique_ptr<Exp> Term(Lexer& in, Context& ctx)
{
    if (in.Is<int>())
        return make_unique<IntLit>(in.Get<int>());
    if (in.Is<std::string>())
    {
        std::string var = in.Get<std::string>();
        auto par = in.Peek<Parenthesis>();
        /*
           if (par && par->value() == Parenthesis::LeftParenthesis)
           return make_unique<Funcall>(var, ParseArgs(in, ctx));
           */
        VarDecl* vd = ctx.GetVar(var);
        if (!vd)
            throw std::runtime_error("invalid identifier");
        return make_unique<Var>(vd);
    }

    throw std::runtime_error("invalid token");
}


std::unique_ptr<Exp> LowExp(Lexer& in, Context& ctx)
{
    std::unique_ptr<Exp> lhs = HighExp(in, ctx);

    while (in.Is<LowOperator>())
    {
        LowOperator op = in.Get<LowOperator>();

        std::unique_ptr<Exp> rhs = HighExp(in, ctx);

        lhs = make_unique<Binop>(std::move(lhs), op, std::move(rhs));
    }

    return lhs;
}

std::unique_ptr<Exp> ParseExp(Lexer& in, Context& ctx)
{
    return AffectExp(in, ctx);
}

std::unique_ptr<Exp> Paren(Lexer& in, Context& ctx)
{
    if (in.Is<LowOperator>())
    {
        if (in.Get<LowOperator>() == LowOperator::Sub)
            return make_unique<Neg>(LowExp(in, ctx));
    }
    if (in.Is<Parenthesis>())
    {
        if (in.Get<Parenthesis>() == Parenthesis::LeftParenthesis)
        {
            auto res = LowExp(in, ctx);
            if (in.Is<Parenthesis>()
                    && in.Get<Parenthesis>() == Parenthesis::RightParenthesis)
                return res;
        }
    }
    return Term(in, ctx);
}

std::unique_ptr<Exp> HighExp(Lexer& in, Context& ctx)
{
    std::unique_ptr<Exp> lhs = Paren(in, ctx);

    while (in.Is<HighOperator>())
    {
        HighOperator op = in.Get<HighOperator>();

        std::unique_ptr<Exp> rhs = Paren(in, ctx);

        lhs = make_unique<Binop>(std::move(lhs), op, std::move(rhs));
    }

    return lhs;
}

std::unique_ptr<Exp> CompExp(Lexer& in, Context& ctx)
{
    std::unique_ptr<Exp> lhs = LowExp(in, ctx);

    if (in.Is<CompOperator>())
    {
        CompOperator op = in.Get<CompOperator>();

        std::unique_ptr<Exp> rhs = LowExp(in, ctx);

        lhs = make_unique<Binop>(std::move(lhs), op, std::move(rhs));
    }

    return lhs;
}

std::unique_ptr<Exp> LogicExp(Lexer& in, Context& ctx)
{
    std::unique_ptr<Exp> lhs = CompExp(in, ctx);

    while (in.Is<LogicOperator>())
    {
        LogicOperator op = in.Get<LogicOperator>();

        std::unique_ptr<Exp> rhs = LowExp(in, ctx);

        lhs = make_unique<Binop>(std::move(lhs), op, std::move(rhs));
    }

    return lhs;
}

std::unique_ptr<Exp> AffectExp(Lexer& in, Context& ctx)
{
    if (in.Peek<std::string>() && in.Peek<AffectOp>(1))
    {
        std::string name = in.Get<std::string>();
        VarDecl* var = ctx.GetVar(name);
        in.Get<AffectOp>();
        auto val = LogicExp(in, ctx);
        return make_unique<Affect>(var, val);
    }
    else
        return LogicExp(in, ctx);
}