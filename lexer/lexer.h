#include <memory>
#include <fstream>
#include <deque>
#include "token.h"

enum class LowOperator
{
    Add,
    Sub
};

enum class HighOperator
{
    Multiply,
    Divide,
    Modulo
};

class Affect {};

class If {};

class Else {};

class Return {};

enum class CompOperator
{
    Equal,
    Greater,
    Less,
    GreaterOrEqual,
    LessOrEqual,
};

enum class Bracket
{
    LeftBracket,
    RightBracket
};

enum class CurlyBracket
{
    LeftCurlyBracket,
    RightCurlyBracket
};

enum class Parenthesis
{
    LeftParenthesis,
    RightParenthesis
};

class Lexer
{
private:
    std::ifstream strm_;
    std::deque<std::unique_ptr<AbstractToken>> tokens_;

    bool IsBlank()
    {
        char current = strm_.peek();

        return (current == ' ')
            || (current == '\t')
            || (current == '\r')
            || (current == '\n');
    }

    void Clean()
    {
        while (IsBlank())
            strm_.get();
    }

    bool IsAlpha()
    {
        char current = strm_.peek();
        return ('a' <= current && current <= 'z')
            || ('A' <= current && current <= 'Z');
    }

    void GetAlpha()
    {
        std::string id;

        while (IsAlpha())
            id += strm_.get();

        Clean();
        tokens_.push_back(make_token<Token<std::string>>(id));
    }

    bool IsNumeric()
    {
        char current = strm_.peek();
        return ('0' <= current && current <= '9');
    }

    void GetNumeric()
    {
        std::string num;
        while(IsNumeric())
            num += strm_.get();

        Clean();
        tokens_.push_back(make_token<Token<int>>(std::stoi(num)));
    }

    bool IsLowOp()
    {
        char current = strm_.peek();
        return (current == '+')
            || (current == '-');
    }

    void GetLowOp()
    {
        char current = strm_.peek();
        if(current == '+')
            tokens_.push_back(make_token<Token<LowOperator>>(LowOperator::Add));
        if(current == '-')
            tokens_.push_back(make_token<Token<LowOperator>>(LowOperator::Sub));
    }

    bool IsHighOp()
    {
        char current = strm_.peek();
        return (current == '/')
            || (current == '*')
            || (current == '%');
    }

    void GetHighOp()
    {
        char current = strm_.peek();
        if(current == '/')
            tokens_.push_back(make_token<Token<HighOperator>>(HighOperator::Divide));
        if(current == '*')
            tokens_.push_back(make_token<Token<HighOperator>>(HighOperator::Multiply));
        if(current == '%')
            tokens_.push_back(make_token<Token<HighOperator>>(HighOperator::Modulo));
    }

    bool IsComparator()
    {
        std::string op;
        op += strm_.get();
        if(op == ">" || op == "<")
            return true;

        op += strm_.peek();
        strm_.unget();
        return (op == "==") || (op == "<=") || (op == ">=");
    }

    void GetComparator()
    {
        std::string op;
        op += strm_.get();
        if(op == ">")
            tokens_.push_back(make_token<Token<CompOperator>>(CompOperator::Greater));
        if(op == "<")
            tokens_.push_back(make_token<Token<CompOperator>>(CompOperator::Less));

        op += strm_.get();

        if(op == "<=")
            tokens_.push_back(make_token<Token<CompOperator>>(CompOperator::LessOrEqual));
        if(op == ">=")
            tokens_.push_back(make_token<Token<CompOperator>>(CompOperator::GreaterOrEqual));
        if(op == "==")
            tokens_.push_back(make_token<Token<CompOperator>>(CompOperator::Equal));
    }
    bool IsLeftParenthesis()
    {
        return strm_.peek() == '(';
    }

    bool IsRightParenthesis()
    {
        return strm_.peek() == ')';
    }

    bool IsParenthesis()
    {
        return IsLeftParenthesis() || IsRightParenthesis();
    }

    bool IsLeftBracket()
    {
        return strm_.peek() == '[';
    }

    bool IsRightBracket()
    {
        return strm_.peek() == ']';
    }

    bool IsLeftCurlyBracket()
    {
        return strm_.peek() == '{';
    }

    bool IsRightCurlyBracket()
    {
        return strm_.peek() == '}';
    }

    void GetToken()
    {
        if(IsAlpha())
            GetAlpha();
        else if(IsNumeric())
            GetNumeric();
        else if(IsLowOp())
            GetLowOp();
        else if(IsHighOp())
            GetHighOp();
        else if(IsComparator())
            GetComparator();
        else if(IsLeftParenthesis())
            tokens_.push_back(make_token<Token<Parenthesis>>(Parenthesis::LeftParenthesis));
        else if(IsRightParenthesis())
            tokens_.push_back(make_token<Token<Parenthesis>>(Parenthesis::RightParenthesis));
        else if(IsLeftBracket())
            tokens_.push_back(make_token<Token<Bracket>>(Bracket::LeftBracket));
        else if(IsRightBracket())
            tokens_.push_back(make_token<Token<Bracket>>(Bracket::RightBracket));
        else if(IsLeftCurlyBracket())
            tokens_.push_back(make_token<Token<CurlyBracket>>(CurlyBracket::LeftCurlyBracket));
        else if(IsRightCurlyBracket())
            tokens_.push_back(make_token<Token<CurlyBracket>>(CurlyBracket::RightCurlyBracket));
    }

public:
    Lexer(const std::string& filename)
        : strm_(filename)
    {

    }

    template <class T>
        bool Is()
        {
            return dynamic_cast<Token<T>*>(tokens_.front().get())
                != nullptr;
        }

    template <class Tok>
        void TakeBack(Tok tok)
        {
            tokens_.push_front(make_token<Tok>(tok));
        }

    template <class TokenType>
        Token<TokenType> Get()
        {
            if(tokens_.empty())
                GetToken();
            Token<TokenType> tok = *dynamic_cast<Token<TokenType>*>(tokens_.front().get());
            tokens_.pop_front();
            return tok;
        }
    template <class TokenType>
        Token<TokenType>* Peek(int lookahead = 1)
        {
            int late = lookahead - tokens_.size() + 1;
            while(late)
            {
                GetToken();
                --late;
            }
            return dynamic_cast<Token<TokenType>*>(tokens_[lookahead].get());
        }
};
