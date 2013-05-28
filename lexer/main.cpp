#include "stdio.h"
#include "lexer.h"

int main()
{
    Lexer lex("test.tl");

    Token<int> *tok3 = lex.Peek<int>(2);
    printf("Token : %d\n", tok3->value());
    return 0;
}
