#ifndef NODE_H
#define NODE_H

#include <string>

class Node
{
    public:
        virtual double evaluate() = 0;
        virtual void print() = 0;

        virtual ~Node() = default;
};

class NumberNode : public Node
{
    private:
        double _number;
    
    public:
        NumberNode(double number);
        
        double evaluate() override;
        void print() override;
};

class OperatorNode : public Node
{
    private:
        Node* _one;
        Node* _two;
        std::string _operator;

    public:
        OperatorNode(Node* one, Node* two, std::string oper);
        
        double evaluate() override;
        void print() override;
};

#endif