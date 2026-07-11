#include <iostream>
#include <string>
#include "node.h"

NumberNode::NumberNode(double number)
{
    _number = number;
}

double NumberNode::evaluate(std::map<std::string, double>& userSymbols)
{
    return _number;
}

NumberNode::~NumberNode() {}

OperatorNode::OperatorNode(Node* one, Node* two, std::string oper)
{
    _one = one;
    _two = two;
    _operator = oper;
}

double OperatorNode::evaluate(std::map<std::string, double>& userSymbols)
{
    double oneValue = _one -> evaluate(userSymbols);
    double twoValue = _two -> evaluate(userSymbols);

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

OperatorNode::~OperatorNode() 
{
    delete _one;
    delete _two;
}

VariableNode::VariableNode(std::string name, Node* valueExpression)
{
    _name = name;
    _valueExpression = valueExpression;
}

double VariableNode::evaluate(std::map<std::string, double>& userSymbols)
{
    if (userSymbols.find(_name) != userSymbols.end())
    {
        std::cout << "Variable already exists. \n";
        return userSymbols[_name];
    }
    
    double val = _valueExpression -> evaluate(userSymbols);
    userSymbols[_name] = val;
    return val;
}

VariableNode::~VariableNode()
{
    delete _valueExpression;
}