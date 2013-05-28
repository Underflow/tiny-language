#pragma once

#include <memory>

#include "ast.h"
#include "exp.h"
#include "../lexer/lexer.h"

class Binop : public Exp
{
public:
        virtual void Pretty(std::ostream& strm) const;
        void x86Gen(std::ostream& strm) const;

        enum class Operator
        {
            Add, Sub, Mul, Div, Mod,
			Equal, Greater, Less, Leq, Geq
        };

		template <class Op>
		Binop(std::unique_ptr<Exp>&& lhs, Op op,
			std::unique_ptr<Exp>&& rhs)
			: lhs_(std::move(lhs)), op_(Convert(op)), rhs_(std::move(rhs))
		{
		}


    private:
        Operator Convert(LowOperator op) const;
        Operator Convert(HighOperator op) const;
        Operator Convert(CompOperator op) const;
		std::string Show(Operator op) const;
        std::unique_ptr<Exp> lhs_;
        Operator op_;
        std::unique_ptr<Exp> rhs_;
};