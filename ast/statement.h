#pragma once

#include "control.h"

class Statement : public Control
{
public:
	virtual void Pretty(std::ostream& strm) const = 0;
};

