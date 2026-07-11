#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include <string>
#include "node.h"
#include "lexer.h"

class Parser
{
    private:
        std::vector<Token> _tokens;
        int _position;

        Token peek() const;
        Token move_forward();
        bool match (TokenType type);

        Node* parse_user_variables();

        Node* parse_plus_minus();
        Node* parse_multipl_divis();
        Node* parse_factor();

    public:
        Parser(std::vector<Token> tokens);

        Node* parse();
};

#endif