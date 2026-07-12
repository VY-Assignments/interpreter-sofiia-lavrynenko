#include <string>
#include <vector>
#include "lexer.h"

Lexer::Lexer(std::string input)
{
    _input = input;

    _position = 0;
}

char Lexer::move_forward()
{
    if (_position >= _input.length())
    {
        return '\0';
    }

    char toReturn = _input[_position];

    _position++;

    return toReturn;
}

char Lexer::peek()
{
    if (_position >= _input.length())
    {
        return '\0';
    }

    return _input[_position];
}

std::vector<Token> Lexer::tokenize()
{
    std::vector<Token> tokens;

    while (peek() != '\0')
    {
        char curr = peek();

        if (curr == ' ' || curr == '\t')
        {
            move_forward();
        }

        else if (curr == '+')
        {
            tokens.push_back({TokenType::plus, "+"});
            move_forward();
        }

        else if (curr == '-')
        {
            tokens.push_back({TokenType::minus, "-"});
            move_forward();
        }

        else if (curr == '*')
        {
            tokens.push_back({TokenType::star, "*"});
            move_forward();
        }

        else if (curr == '/')
        {
            tokens.push_back({TokenType::slash, "/"});
            move_forward();
        }

        else if (curr == '(')
        {
            tokens.push_back({TokenType::lparent, "("});
            move_forward();
        }

        else if (curr == ')')
        {
            tokens.push_back({TokenType::rparent, ")"});
            move_forward();
        }

        else if (curr == '=')
        {
            tokens.push_back({TokenType::assign, "="});
            move_forward();
        }

        else if (curr == ',')
        {
            tokens.push_back({TokenType::comma, ","});
            move_forward();
        }

        else if (std::isalpha(curr))
        {
            std::string word = "";

            while (std::isalpha(peek()))
            {
                word += move_forward();
            }

            if (word == "var")
            {
                tokens.push_back({TokenType::var, "var"});
            }
            else if (word == "pow" || word == "abs" || word == "max" || word == "min")
            {
                tokens.push_back({TokenType::function, word});
            }
            else
            {
                tokens.push_back({TokenType::name, word});
            }
        }

        else if (std::isdigit(curr))
        {
            std::string num = "";

            while (std::isdigit(peek()) || peek() == '.')
            {
                num += move_forward();
            }

            tokens.push_back({TokenType::number, num});
        }

        else
        {
            move_forward();
        }
    }

    tokens.push_back({TokenType::end, ""});

    return tokens;
}