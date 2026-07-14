#ifndef NODE_H
#define NODE_H

#include <string>
#include <map>
#include <vector>

class Node;

struct UserFunction 
{
    std::vector<std::string> parametersNames;
    Node* funcBody;

    UserFunction() : funcBody(nullptr) {}

    UserFunction(std::vector<std::string> names, Node* body)
    {

        parametersNames = names;
        funcBody = body;
    }
};

class Node
{
    public:
        virtual double evaluate(std::map<std::string, double>& userSymbols, std::map<std::string, UserFunction>& userFunctions) = 0;

        virtual ~Node() = default;
};

class NumberNode : public Node
{
    private:
        double _number;
    
    public:
        NumberNode(double number);
        
        double evaluate(std::map<std::string, double>& userSymbols, std::map<std::string, UserFunction>& userFunctions) override;

        ~NumberNode() override;
};

class OperatorNode : public Node
{
    private:
        Node* _one;
        Node* _two;
        std::string _operator;

    public:
        OperatorNode(Node* one, Node* two, std::string oper);
        
        double evaluate(std::map<std::string, double>& userSymbols, std::map<std::string, UserFunction>& userFunctions) override;

        ~OperatorNode() override;
};

class VariableNode : public Node
{
    private: 
        std::string _name;
        Node* _valueExpression;

    public:
        VariableNode(std::string name, Node* valueExpression);

        double evaluate(std::map<std::string, double>& userSymbols, std::map<std::string, UserFunction>& userFunctions) override;

        ~VariableNode() override;
};

class VariableForUseNode : public Node 
{
    private: 
        std::string _name;

    public: 
        VariableForUseNode(std::string name);

        double evaluate(std::map<std::string, double>& userSymbols, std::map<std::string, UserFunction>& userFunctions) override;
        std::string get_name();

        ~VariableForUseNode() override = default; 
};

class FunctionNode : public Node
{
    private:
        std::string _type;
        std::vector<Node*> _arguments;
    
    public:
        FunctionNode(std::string type, std::vector<Node*> arguments);

        double evaluate(std::map<std::string, double>& userSymbols, std::map<std::string, UserFunction>& userFunctions) override;

        ~FunctionNode() override;
};

class DefFunctionNode : public Node
{
    private:
        std::string _name;
        std::vector<std::string> _parametersNames;
        Node* _funcBody;

    public:
        DefFunctionNode(std::string name, std::vector<std::string> parametersNames, Node* funcBody);

        double evaluate(std::map<std::string, double>& userSymbols, std::map<std::string, UserFunction>& userFunctions) override;

        ~DefFunctionNode() override;
};

class DefFunctionCallNode : public Node
{
    private:
        std::string _name;
        std::vector<Node*> _arguments;
    
    public:
        DefFunctionCallNode(std::string name, std::vector<Node*> arguments);

        double evaluate(std::map<std::string, double>& userSymbols, std::map<std::string, UserFunction>& userFunctions) override;

        ~DefFunctionCallNode() override;
};

#endif