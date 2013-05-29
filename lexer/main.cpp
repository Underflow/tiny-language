#include <iostream>

#include "lexer.h"
#include "../parser/parser.h"

int main(int argc, char** argv)
{
    Type T0;
    Type T1;
    Type T2;
    Type T3;
    Type T4;
    Type T5;
    Type T6;

    T1.SetCastable(T0);
    T1.SetCastable(T2);
    T2.SetCastable(T3);
    T3.SetCastable(T5);
    T4.SetCastable(T5);
    T0.SetCastable(T6);

    std::cout << "T1 -> T2 : " << T1.IsCastable(T2) << std::endl;
    std::cout << "T1 -> T5 : " << T1.IsCastable(T5) << std::endl;
    std::cout << "T0 -> T5 : " << T0.IsCastable(T5) << std::endl;

    Lexer l(argv[1]);
    try {
        auto res = Parse(l);
        res->Pretty(std::cout);
    } catch (std::exception& e) {
        std::cerr << e.what();
    }
    return 0;
}
