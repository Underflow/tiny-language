#pragma once

#include "control.h"

class Statement : public Control
{
    std::unique_ptr<Statement> oh_my_;
public:
    Statement(){}
    Statement(std::unique_ptr<Statement>&& oh_my) : oh_my_(std::move(oh_my)) {}
    virtual void Pretty(std::ostream& strm) const;
};

