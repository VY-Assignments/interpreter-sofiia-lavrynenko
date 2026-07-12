#include <iostream>
#include <string>
#include <cmath>
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

VariableForUseNode::VariableForUseNode(std::string name)
{
    _name = name;
}

double VariableForUseNode::evaluate(std::map<std::string, double>& userSymbols)
{
    if (userSymbols.find(_name) != userSymbols.end())
    {
        return userSymbols[_name];
    }

    std::cout << "Variable was not found. \n";

    return 0;
}

FunctionNode::FunctionNode(std::string type, std::vector<Node*> arguments)
{
    _type = type;
    _arguments = arguments;
}

double FunctionNode::evaluate(std::map<std::string, double>& userSymbols)
{
    std::vector<double> argumentsValues;

    for(Node* argument : _arguments)
    {
        argumentsValues.push_back(argument -> evaluate(userSymbols));
    }

    if (_type == "pow")
    {
        if (argumentsValues.size() != 2)
        {
            std::cout << "Function pow expects 2 arguments. \n";
            return 0;
        }

        return std::pow(argumentsValues[0], argumentsValues[1]);
    }
    else if (_type == "abs")
    {
        if (argumentsValues.size() != 1)
        {
            std::cout << "Function abs expects 1 arguments. \n";
            return 0;
        }

        return std::abs(argumentsValues[0]);
    }
    else if (_type == "max")
    {
        if (argumentsValues.size() != 2)
        {
            std::cout << "Function max expects 2 arguments. \n";
            return 0;
        }

        return std::max(argumentsValues[0], argumentsValues[1]);
    }
    else if (_type == "min")
    {
        if (argumentsValues.size() != 2)
        {
            std::cout << "Function min expects 2 arguments. \n";
            return 0;
        }

        return std::min(argumentsValues[0], argumentsValues[1]);
    }
    else
    {
        std::cout << "Unknown function. \n";
        return 0;
    }
}

FunctionNode::~FunctionNode()
{
    for (Node* argument : _arguments)
    {
        delete argument;
    }
}