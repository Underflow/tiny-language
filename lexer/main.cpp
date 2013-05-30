#include <iostream>

#include "lexer.h"
#include "../parser/parser.h"

int main(int argc, char** argv)
{
    Lexer l(argv[1]);
    try {
        auto res = Parse(l);
        res->Pretty(std::cout);
    } catch (std::exception& e) {
        std::cerr << e.what();
    }
    return 0;
}
