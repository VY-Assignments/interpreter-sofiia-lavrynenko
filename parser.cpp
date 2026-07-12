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

Node* Parser::parse_user_variables()
{
    if (match(TokenType::var))
    {
        Token nameT = peek();

        if (!match(TokenType::name))
        {
            std::cout << "You need to give a name for the variable. \n";
            return nullptr;
        }

        if (!match(TokenType::assign))
        {
            std::cout << "You need to type a '=' after the name. \n";
            return nullptr;
        }

        Node* valueExpression = parse_plus_minus();

        return new VariableNode(nameT.value, valueExpression);
    }

    return parse_plus_minus();
}

Node* Parser::parse_factor()
{
    Token curr = peek();
    
    if (match(TokenType::minus))
    {
        Node* withZero = new NumberNode(0);

        Node* expression = parse_factor();

        return new OperatorNode(withZero, expression, "-");
    }

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

    if (match(TokenType::name))
    {
        return new VariableForUseNode(curr.value);
    }

    if (match(TokenType::function))
    {
        std::string functionType = curr.value;

        if (!match(TokenType::lparent))
        {
            std::cout << "There must be a '(' after the function name. \n";
            return nullptr;
        }

        std::vector<Node*> arguments;

        if (peek().type != TokenType::rparent)
        {
            while (true)
            {
                arguments.push_back(parse_plus_minus());

                if (match(TokenType::comma))
                {
                    continue;
                }

                break;
            }
        }

        if (!match(TokenType::rparent))
        {
            std::cout << "There must be a ')' after the function arguments. \n";
            return nullptr;
        }

        return new FunctionNode(functionType, arguments);
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
    return parse_user_variables();
}