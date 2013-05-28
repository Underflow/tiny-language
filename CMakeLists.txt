PROJECT(Lanus CXX)

SET(sources
    ast/neg.cpp
    ast/var.cpp
    ast/binop.cpp
    ast/block.cpp
    ast/intlit.cpp
    ast/return.cpp
    ast/vardecl.cpp
    ast/control.cpp
    ast/statement.cpp

    lexer/main.cpp

    parser/exp.cpp
    parser/context.cpp
    parser/statement.cpp
)

ADD_EXECUTABLE(lang ${sources})
