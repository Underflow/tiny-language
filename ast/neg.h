#pragma once

#include <memory>

#include "exp.h"

class Neg : public Exp
{
    std::unique_ptr<Exp> exp_;

    public:
		Neg(std::unique_ptr<Exp>&& exp)
			: exp_(std::move(exp))
		{
		}

        void Pretty(std::ostream& strm) const;
};
