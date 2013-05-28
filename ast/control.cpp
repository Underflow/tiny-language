#include "control.h"
#include "block.h"

If::If(std::unique_ptr<Exp>&& cond, std::unique_ptr<Block> if_clause,
		std::unique_ptr<Block>&& else_clause)
		: cond_(std::move(cond)),
		if_(std::move(if_clause)),
		else_(std::move(else_clause))
{

}

void If::Pretty(std::ostream& strm) const
{
	strm << "if (";
	cond_->Pretty(strm);

	strm << ")\n\n{";
	if_->Pretty(strm);
	strm << "}";

	if (else_)
	{
		strm << "else {\n\n";
		else_->Pretty(strm);
		strm << "};\n";
	}
}

