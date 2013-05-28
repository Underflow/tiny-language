#pragma once

class AbstractToken {};

template <class T>
class Token
{
    T value_;
    public:
        Token(T val) : value_(val) {}
        T value() { return value_; }
};
