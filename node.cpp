#include <iostream>
#include <string>
#include "node.h"

NumberNode::NumberNode(double number)
{
    _number = number;
}

double NumberNode::evaluate()
{
    return _number;
}

void NumberNode::print()
{
    std::cout << _number << "\n";
}

OperatorNode::OperatorNode(Node* one, Node* two, std::string oper)
{
    _one = one;
    _two = two;
    _operator = oper;
}

double OperatorNode::evaluate()
{
    double oneValue = _one -> evaluate();
    double twoValue = _two -> evaluate();

    if (_operator == "+")
    {
        return oneValue + twoValue;
    }
    else if (_operator == "-")
    {
        return oneValue - twoValue;
    }
    else if (_operator == "*")
    {
        return oneValue * twoValue;
    }
    else if (_operator == "/")
    {
        if (twoValue == 0)
        {
            std::cout << "You cannot divide by zero. \n";
            return 0;
        }

        return oneValue / twoValue;
    }

    return 0;
}

void OperatorNode::print()
{
    std::cout << _operator << "\n";
}