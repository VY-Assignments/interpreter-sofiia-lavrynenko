#include <iostream>
#include <string>

int main()
{
    std::string input;

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
    }

    return 0;
}