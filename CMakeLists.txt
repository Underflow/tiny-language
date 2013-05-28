PROJECT(Lanus CXX)

SET(sources
    ast/binop.cpp
    ast/neg.cpp
    ast/intlit.cpp

    lexer/main.cpp

    parser/exp.cpp
)

ADD_EXECUTABLE(lang ${sources})
