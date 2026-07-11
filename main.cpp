#include <iostream>
#include <string>
#include <vector>
#include <map>

#include "node.h"
#include "lexer.h"
#include "parser.h"

int main()
{
    std::map<std::string, double> userSymbols;

    std::string input;

    std::cout << "Welcome! \n";
    std::cout << "Enter your expression or exit/quit to stop:\n";

    while (std::getline(std::cin, input))
    {
        if (input == "exit" || input == "quit")
        {
            break;
        }

        if (input.empty())
        {
            continue;
        }

        Lexer lexer(input);
        std::vector<Token> tokens = lexer.tokenize();

        Parser parser(tokens);
        Node* root = parser.parse();

        if (root != nullptr)
        {
            double res = root -> evaluate();
            std::cout << "Your result: " << res << "\n";

            delete root;
        }
        else
        {
            std::cout << "Cannot parse the expression. \n";
        }
    }

    return 0;
}