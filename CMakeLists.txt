PROJECT(Lanus CXX)

SET(CMAKE_CXX_FLAGS "-std=c++0x")

SET(sources
    ast/neg.cpp
    ast/var.cpp
    ast/type.cpp
    ast/binop.cpp
    ast/block.cpp
    ast/intlit.cpp
    ast/return.cpp
    ast/fundef.cpp
    ast/affect.cpp
    ast/vardecl.cpp
    ast/control.cpp
    ast/funcall.cpp
    ast/program.cpp
    ast/statement.cpp

    lexer/main.cpp

    parser/exp.cpp
    parser/context.cpp
    parser/statement.cpp
    parser/fundef.cpp
    parser/fundef.h


    ast/neg.h
    ast/var.h
    ast/binop.h
    ast/block.h
    ast/intlit.h
    ast/fundef.h
    ast/return.h
    ast/affect.h
    ast/vardecl.h
    ast/control.h
    ast/funcall.h
    ast/program.h
    ast/statement.h

    lexer/lexer.h

    parser/context.h
)

ADD_EXECUTABLE(lang ${sources})
