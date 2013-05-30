#include "fundef.h"

#include <string>
#include <memory>

#include "../ast/program.h"
#include "../ast/fundef.h"
#include "../ast/vardecl.h"
#include "../unique.h"

#include "parser.h"

std::unique_ptr<Fundef> ParseProto(Lexer& in, Context& ctx)
{
    if (in.Is<std::string>())
    {
        std::string ret_type = in.Get<std::string>();

        if (!in.Is<std::string>())
            throw std::runtime_error("expected function name after type '" + ret_type + "'");

        std::string name = in.Get<std::string>();

        if (!in.Is<Parenthesis>() || in.Get<Parenthesis>() != Parenthesis::LeftParenthesis)
            throw std::runtime_error("Expected '(' after function name");

        if (in.Is<Parenthesis>())
        {
            if (in.Get<Parenthesis>() == Parenthesis::LeftParenthesis)
                throw std::runtime_error("Invalid token '(' ");
            else
                return make_unique<Fundef>(name, ctx.TypeId(ret_type), std::vector<std::unique_ptr<VarDecl>>());
        }

        std::vector<std::unique_ptr<VarDecl>> args;
        std::string arg_type;
        std::string param_name;
        if (in.Is<std::string>())
        {
            arg_type = in.Get<std::string>();
            param_name = in.Get<std::string>();
            args.emplace_back(make_unique<VarDecl>(ctx.TypeId(arg_type), param_name, nullptr));
            ctx.DeclVar(param_name, args.back().get());
            while (in.Is<Comma>())
            {
                in.Get<Comma>();
                arg_type = in.Get<std::string>();
                param_name = in.Get<std::string>();
                args.emplace_back(make_unique<VarDecl>(ctx.TypeId(arg_type), param_name, nullptr));
                ctx.DeclVar(param_name, args.back().get());
            }

            if (!in.Is<Parenthesis>() || in.Get<Parenthesis>() != Parenthesis::RightParenthesis)
                throw std::runtime_error("Expected ')' in the end of arguments list");
        }
        return make_unique<Fundef>(name, ctx.TypeId(ret_type), std::move(args));
    }
}

std::unique_ptr<Fundef> FundeclOrDef(Lexer& in, Context& ctx)
{
    ctx.PushScope();
    auto proto = ParseProto(in, ctx);
    if (in.Is<Semicolon>())
    {
        in.Get<Semicolon>();
        ctx.PopScope();
        return std::move(proto);
    }
    else
    {
        Token<CurlyBracket>* brack = in.Peek<CurlyBracket>();
        //if (brack && brack->value() == CurlyBracket::LeftCurlyBracket)
        {
            auto body = ParseBlock(in, ctx);
            proto->body(std::move(body));
            ctx.PopScope();
            return proto;
        }
    }
    throw std::runtime_error("Lol error lol kestufoula?");
}

std::unique_ptr<Ast> ParseProgram(Lexer& in, Context& ctx)
{
    std::vector<std::unique_ptr<VarDecl>> vars;
    std::vector<std::unique_ptr<Fundef>> funs;

    while (!in.Is<TokEOF>())
    {
        auto is_fun = in.Peek<Parenthesis>(2);
        if (is_fun && is_fun->value() == Parenthesis::LeftParenthesis)
            funs.push_back(FundeclOrDef(in, ctx));
        else
            vars.push_back(ParseVarDecl(in, ctx));
    }
    return make_unique<Program>(std::move(vars), std::move(funs));
}

std::unique_ptr<Ast> Parse(Lexer& in)
{
    Context ctx;
    return ParseProgram(in, ctx);
}