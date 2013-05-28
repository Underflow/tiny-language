#pragma once
#include <memory>

class AbstractToken
{
    public:
        virtual ~AbstractToken() {}
};

template <class T>
class Token : public AbstractToken
{
    T value_;
    public:
        Token(T val) : value_(val) {}
        T value() { return value_; }
};

template <class T, class... Args>
std::unique_ptr<AbstractToken> make_token(Args... args)
{
    return std::unique_ptr<AbstractToken>(new T(args...));
}
