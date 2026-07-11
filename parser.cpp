#include <vector>
#include <string>
#include <iostream>
#include "node.h"
#include "lexer.h"
#include "parser.h"

Parser::Parser(std::vector<Token> tokens)
{
    _tokens = tokens;
    _position = 0;
}

Token Parser::peek() const
{
    if (_position >= _tokens.size())
    {
        return _tokens.back();
    }

    return _tokens[_position];
}

Token Parser::move_forward()
{
    if (_position >= _tokens.size())
    {
        return _tokens.back();
    }

    Token toReturn = _tokens[_position];

    _position++;

    return toReturn;
}

bool Parser::match(TokenType type)
{
    if (peek().type == type)
    {
        move_forward();

        return true;
    }

    return false;
}

Node* Parser::parse_factor()
{
    Token curr = peek();

    if (match(TokenType::number))
    {
        double val = std::stod(curr.value);
        return new NumberNode(val);
    }

    if (match(TokenType::lparent))
    {
        Node* expression = parse_plus_minus();

        if (!match(TokenType::rparent))
        {
            std::cout << "No rigth parenthesis was found. \n";
        }

        return expression;
    }

    return nullptr;
}

Node* Parser::parse_multipl_divis()
{
    Node* one = parse_factor();

    while (peek().type == TokenType::star || peek().type == TokenType::slash)
    {
        Token operatToken = move_forward();
        Node* two = parse_factor();

        one = new OperatorNode(one, two, operatToken.value);
    }

    return one;
}

Node* Parser::parse_plus_minus()
{
    Node* one = parse_multipl_divis();

    while (peek().type == TokenType::plus || peek().type == TokenType::minus)
    {
        Token operatToken = move_forward();
        Node* two = parse_multipl_divis();

        one = new OperatorNode(one, two, operatToken.value);
    }

    return one;
}

Node* Parser::parse()
{
    return parse_plus_minus();
}