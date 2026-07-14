#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <vector>

enum class TokenType
{
    var, 
    name,
    number, 
    plus,
    minus,
    star,
    slash,
    assign,
    lparent,
    rparent,
    function,
    comma,
    def,
    lcurl,
    rcurl,
    end
};

struct Token
{
    TokenType type;
    std::string value;
};

class Lexer 
{
    private:
        std::string _input;
        int _position;

        char move_forward();
        char peek();

    public:
        Lexer(std::string input);

        std::vector<Token> tokenize();
};

#endif