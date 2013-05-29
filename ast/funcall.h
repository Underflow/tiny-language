#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <string>

#include "ast.h"
#include "exp.h"

class Funcall : public Exp
{
    std::string fun_;
    std::vector<std::unique_ptr<Exp>> args_;

public:
    Funcall(const std::string& fun,
        std::vector<std::unique_ptr<Exp>>&& args);
    virtual void Pretty(std::ostream& strm) const;
};

