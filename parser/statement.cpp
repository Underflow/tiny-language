#pragma once

#include <memory>

#include "../ast/statement.h"
#include "../ast/vardecl.h"
#include "../ast/return.h"
#include "../lexer/lexer.h"
#include "context.h"
#include "parser.h"

#include "../unique.h"

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
				throw std::exception("expected ';'");
		}
		auto vd = make_unique<VarDecl>(ctx.TypeId(ty), id, std::move(val));
		ctx.DeclVar(id, vd.get());

		return std::move(vd);
	}
	else
		throw std::exception("Expected identifier");
}

std::unique_ptr<Statement> Stmt(Lexer& in, Context& ctx)
{
	auto ty = in.Peek<std::string>();

	if (ty && ctx.TypeExists(ty->value()))
		return ParseVarDecl(in, ctx);

	std::unique_ptr<Statement> res(nullptr);

	if (ty && ty->value() == "return")
	{
		in.Get<std::string>();
		res = make_unique<Return>(ParseExp(in, ctx));
	}
	else
		res = ParseExp(in, ctx);

	if (in.Is<Semicolon>())
		in.Get<Semicolon>();
	else
		throw std::exception("expected ';'");

	return std::move(res);
}

std::unique_ptr<Ast> Parse(Lexer& in)
{
	Context ctx;
	return Stmt(in, ctx);
}

std::unique_ptr<Ast> ParseCompound(Lexer& in, Context& ctx)
{
	{
		auto ifParser = ParseIf(in, ctx);
	}
}

std::unique_ptr<Ast> ParseIf(Lexer& in, Context& ctx)
{
}
std::unique_ptr<Ast> ParseCompound(Lexer& in, Context& ctx)