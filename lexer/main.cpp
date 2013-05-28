#include <iostream>

#include "lexer.h"
#include "../parser/parser.h"

int main(int argc, char** argv)
{
    Lexer l(argv[1]);
    try {
        auto res = Parse(l);
        std::ofstream out("out.S");
        out <<
            "extern printf" << std::endl << 
            "section .data" << std::endl <<
            "fmt: db 'res: %d', 10, 0" << std::endl <<
            "section .text" << std::endl <<
            "global main" << std::endl <<
            "main:" << std::endl;
        res->x86Gen(out);
        out <<
            "push fmt" << std::endl <<
            "call printf" << std::endl <<
            "add esp, 8" << std::endl <<
            "ret" << std::endl;
    } catch (std::exception& e) {
        std::cerr << e.what();
    }
    return 0;
}
