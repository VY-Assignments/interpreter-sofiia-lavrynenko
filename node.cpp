#include <iostream>
#include <string>
#include <cmath>
#include "node.h"

NumberNode::NumberNode(double number)
{
    _number = number;
}

double NumberNode::evaluate(std::map<std::string, double>& userSymbols, std::map<std::string, UserFunction>& userFunctions)
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

double OperatorNode::evaluate(std::map<std::string, double>& userSymbols, std::map<std::string, UserFunction>& userFunctions)
{
    double oneValue = _one -> evaluate(userSymbols, userFunctions);
    double twoValue = _two -> evaluate(userSymbols, userFunctions);

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

double VariableNode::evaluate(std::map<std::string, double>& userSymbols, std::map<std::string, UserFunction>& userFunctions)
{
    if (userSymbols.find(_name) != userSymbols.end())
    {
        std::cout << "Variable already exists. \n";
        return userSymbols[_name];
    }
    
    double val = _valueExpression -> evaluate(userSymbols, userFunctions);
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

double VariableForUseNode::evaluate(std::map<std::string, double>& userSymbols, std::map<std::string, UserFunction>& userFunctions)
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

double FunctionNode::evaluate(std::map<std::string, double>& userSymbols, std::map<std::string, UserFunction>& userFunctions)
{
    std::vector<double> argumentsValues;

    for(Node* argument : _arguments)
    {
        argumentsValues.push_back(argument -> evaluate(userSymbols, userFunctions));
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

DefFunctionNode::DefFunctionNode(std::string name, std::vector<std::string> parametersNames, Node* funcBody)
{
    _name = name;
    _parametersNames = parametersNames;
    _funcBody = funcBody;
}

double DefFunctionNode::evaluate(std::map<std::string, double>& userSymbols, std::map<std::string, UserFunction>& userFunctions)
{
    if (userFunctions.find(_name) != userFunctions.end())
    {
        delete userFunctions[_name].funcBody;
    }

    userFunctions[_name] = {_parametersNames, _funcBody};

    return 0;
}

DefFunctionNode::~DefFunctionNode() {}

DefFunctionCallNode::DefFunctionCallNode(std::string name, std::vector<Node*> arguments)
{
    _name = name;
    _arguments = arguments;
}

double DefFunctionCallNode::evaluate(std::map<std::string, double>& userSymbols, std::map<std::string, UserFunction>& userFunctions)
{
    if (userFunctions.find(_name) == userFunctions.end())
    {
        std::cout << "Function wasn't found. \n";
        return 0;
    }

    UserFunction function = userFunctions[_name];

    if (_arguments.size() != function.parametersNames.size())
    {
        std::cout << "Wrong parameters amount. \n";
        return 0;
    }

    std::vector<double> evaluated;

    for (Node* argument : _arguments)
    {
        evaluated.push_back(argument -> evaluate(userSymbols, userFunctions));
    }

    std::map<std::string, double> oldV;
    std::vector<std::string> erase;

    for (int i = 0; i < function.parametersNames.size(); i++)
    {
        std::string paramN = function.parametersNames[i];

        if (userSymbols.find(paramN) != userSymbols.end())
        {
            oldV[paramN] = userSymbols[paramN];
        }
        else
        {
            erase.push_back(paramN);
        }


        userSymbols[paramN] = evaluated[i];
    }

    double res = function.funcBody -> evaluate(userSymbols, userFunctions);

    for (auto& pair : oldV)
    {
        userSymbols[pair.first] = pair.second;
    }

    for (std::string& name : erase)
    {
        userSymbols.erase(name);
    }

    return res;
}

DefFunctionCallNode::~DefFunctionCallNode()
{
    for (Node* argument: _arguments)
    {
        delete argument;
    }
}