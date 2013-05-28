#include "binop.h"

void Binop::Pretty(std::ostream& strm) const
{
    strm << "(";
    lhs_->Pretty(strm);
    strm << ") " << Show(op_) << " (";
    rhs_->Pretty(strm);
    strm << ")";
}

void Binop::x86Gen(std::ostream& strm) const
{
    lhs_->x86Gen(strm);
    rhs_->x86Gen(strm);
    strm <<
        "pop eax\n"
        "pop edx\n";
    switch (op_)
    {
    case Binop::Operator::Add:
        strm << "add eax, edx\n";
        break;
    case Binop::Operator::Sub:
        strm << "sub eax, edx\n";
        break;
    case Binop::Operator::Mul:
        strm << "mul edx\n";
        break;
    case Binop::Operator::Div:
        strm << "div eax, edx\n";
        break;
    case Binop::Operator::Mod:
        strm << "add eax, edx\n";
        break;
    case Binop::Operator::Equal:
        break;
    case Binop::Operator::Greater:
        break;
    case Binop::Operator::Less:
        break;
    case Binop::Operator::Leq:
        break;
    case Binop::Operator::Geq:
        break;
    default:
        break;
    }
    strm << "push eax\n";
}

Binop::Operator Binop::Convert(LowOperator op) const
{
    switch (op)
    {
        case LowOperator::Add:
            return Operator::Add;
        case LowOperator::Sub:
            return Operator::Sub;
    }
	return Operator::Add;
}

Binop::Operator Binop::Convert(HighOperator op) const
{
    switch (op)
    {
	case HighOperator::Multiply:
		return Operator::Mul;
	case HighOperator::Modulo:
		return Operator::Mod;
	case HighOperator::Divide:
		return Operator::Div;
    }
	return Operator::Add;
}

Binop::Operator Binop::Convert(CompOperator op) const
{
	switch (op)
	{
	case CompOperator::Equal:
		return Operator::Equal;
	case CompOperator::Greater:
		return Operator::Greater;
	case CompOperator::Less:
		return Operator::Less;
	case CompOperator::GreaterOrEqual:
		return Operator::Geq;
	case CompOperator::LessOrEqual:
		return Operator::Leq;
	}
	return Operator::Add;
}

std::string Binop::Show(Binop::Operator op) const
{
	switch (op)
	{
	case Binop::Operator::Add:
		return "+";
	case Binop::Operator::Sub:
		return "-";
	case Binop::Operator::Mul:
		return "*";
	case Binop::Operator::Div:
		return "/";
	case Binop::Operator::Mod:
		return "%";
	}
	return "ERR";
}