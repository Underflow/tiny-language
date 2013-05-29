#include <stdexcept>
#include <memory>

#include "../ast/statement.h"
#include "../ast/vardecl.h"
#include "../lexer/lexer.h"
#include "../ast/return.h"
#include "../ast/block.h"
#include "context.h"
#include "parser.h"

#include "../unique.h"

static std::unique_ptr<Block> ParseBlock(Lexer& in, Context& ctx);

std::unique_ptr<Statement> ParseVarDecl(Lexer& in, Context& ctx)
{
    auto ty = in.Get<std::string>();

    if (in.Is<std::string>())
    {
        auto id = in.Get<std::string>();

        std::unique_ptr<Exp> val(nullptr);
        if (in.Is<Affect>())
        {
            in.Get<Affect>();
            val = ParseExp(in, ctx);

            if (in.Is<Semicolon>())
                in.Get<Semicolon>();
            else
                throw std::runtime_error("expected ';'");
        }
        auto vd = make_unique<VarDecl>(ctx.TypeId(ty), id, std::move(val));
        ctx.DeclVar(id, vd.get());

        return std::move(vd);
    }
    else
        throw std::runtime_error("Expected identifier");
}

std::unique_ptr<Statement> Stmt(Lexer& in, Context& ctx)
{
    auto ty = in.Peek<std::string>();

    if (ty && ctx.TypeExists(ty->value()))
        return ParseVarDecl(in, ctx);

    std::unique_ptr<Statement> res(nullptr);

    if (in.Is<Keyword>() && in.Peek<Keyword>()->value() == Keyword::Return)
    {
        in.Get<Keyword>();
        res = make_unique<Return>(ParseExp(in, ctx));
    }
    else
        res = ParseExp(in, ctx);

    if (in.Is<Semicolon>())
        in.Get<Semicolon>();
    else
        throw std::runtime_error("expected ';'");

    return std::move(res);
}

std::unique_ptr<Ast> Parse(Lexer& in)
{
    Context ctx;
    return ParseBlock(in, ctx);
}

std::unique_ptr<Control> ParseIf(Lexer& in, Context& ctx)
{
    auto ifk = in.Peek<Keyword>();
    if (ifk && ifk->value() == Keyword::If)
    {
        in.Get<Keyword>();

        if (!in.Is<Parenthesis>() || in.Get<Parenthesis>() != Parenthesis::LeftParenthesis)
            throw std::runtime_error("expected '(' after if keyword");

        auto cond = ParseExp(in, ctx);

        if (!in.Is<Parenthesis>() || in.Get<Parenthesis>() != Parenthesis::RightParenthesis)
            throw std::runtime_error("expected ')' after if condition");

        auto if_block = ParseBlock(in, ctx);

        std::unique_ptr<Block> else_block(nullptr);

        ifk = in.Peek<Keyword>();

        if (ifk && ifk->value() == Keyword::Else)
        {
            in.Get<Keyword>();
            else_block = ParseBlock(in, ctx);
        }

        return make_unique<If>(cond, if_block, else_block);
    }
    throw std::runtime_error("Why the fuck is my parser in an 'if' rule ?");
}

std::unique_ptr<Control> ParseWhile(Lexer& in, Context& ctx)
{
    in.Get<Keyword>();

    if (in.Is<Parenthesis>()
        && in.Get<Parenthesis>() == Parenthesis::LeftParenthesis)
    {
        auto cond = ParseExp(in, ctx);

        if (!in.Is<Parenthesis>()
            && in.Get<Parenthesis>() != Parenthesis::RightParenthesis)
            throw std::runtime_error("expected ')' after while condition");

        auto loop = ParseBlock(in, ctx);

        return make_unique<While>(cond, loop);
    }
    else
        throw std::runtime_error("expected '(' after keyword 'while'");
}

std::unique_ptr<Control> ParseCompound(Lexer& in, Context& ctx)
{
    auto keyw = in.Peek<Keyword>();

    if (keyw && keyw->value() == Keyword::If)
        return ParseIf(in, ctx);
    if (keyw && keyw->value() == Keyword::While)
        return ParseWhile(in, ctx);
    return Stmt(in, ctx);
}

std::unique_ptr<Block> ParseBlock(Lexer& in, Context& ctx)
{
    std::unique_ptr<Block> b = make_unique<Block>();

    if (in.Is<CurlyBracket>()
            && in.Get<CurlyBracket>() == CurlyBracket::LeftCurlyBracket)
    {
        ctx.PushScope();
        while (!in.Is<CurlyBracket>())
            b->push_back(ParseCompound(in, ctx));
        ctx.PopScope();
    }
    else
    {
        ctx.PushScope();
        b->push_back(ParseCompound(in, ctx));
        ctx.PopScope();
    }
    return std::move(b);
}
