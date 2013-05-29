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
    ast/affect.cpp
    ast/vardecl.cpp
    ast/control.cpp
    ast/funcall.cpp
    ast/statement.cpp

    lexer/main.cpp

    parser/exp.cpp
    parser/context.cpp
    parser/statement.cpp




    ast/neg.h
    ast/var.h
    ast/binop.h
    ast/block.h
    ast/intlit.h
    ast/return.h
    ast/affect.h
    ast/vardecl.h
    ast/control.h
    ast/funcall.h
    ast/statement.h

    lexer/lexer.h

    parser/context.h
)

ADD_EXECUTABLE(lang ${sources})
