#ifndef NODE_H
#define NODE_H

#include <string>
#include <map>

class Node
{
    public:
        virtual double evaluate(std::map<std::string, double>& userSymbols) = 0;

        virtual ~Node() = default;
};

class NumberNode : public Node
{
    private:
        double _number;
    
    public:
        NumberNode(double number);
        
        double evaluate(std::map<std::string, double>& userSymbols) override;

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
        
        double evaluate(std::map<std::string, double>& userSymbols) override;

        ~OperatorNode() override;
};

class VariableNode : public Node
{
    private: 
        std::string _name;
        Node* _valueExpression;

    public:
        VariableNode(std::string name, Node* valueExpression);

        double evaluate(std::map<std::string, double>& userSymbols) override;

        ~VariableNode() override;
};

class VariableForUseNode : public Node 
{
    private: 
        std::string _name;

    public: 
        VariableForUseNode(std::string name);

        double evaluate(std::map<std::string, double>& userSymbols) override;

        ~VariableForUseNode() override = default; 
};

class FunctionNode : public Node
{
    private:
        std::string _type;
        std::vector<Node*> _arguments;
    
    public:
        FunctionNode(std::string type, std::vector<Node*> arguments);

        double evaluate(std::map<std::string, double>& userSymbols) override;

        ~FunctionNode() override;
};

#endif