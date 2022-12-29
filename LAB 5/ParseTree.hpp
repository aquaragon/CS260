//
// Created by aiden on 4/28/2022.
//

#ifndef LAB_5_PARSETREE_HPP
#define LAB_5_PARSETREE_HPP
#include <string>

using std::string;

struct ParseNode
{
    char value;
    ParseNode * left;
    ParseNode * right;
    ParseNode(char value): value(value), left(nullptr), right(nullptr){};
    ~ParseNode() = default;

};

class ParseTree
{
private:
    ParseNode * root;
public:
    ParseTree(string expression);
    ~ParseTree();
    void recDelete(ParseNode * ptr);
    string preOrder();
    string recPreOrder(ParseNode * node);
    string inOrder();
    string recInOrder(ParseNode * node);
    string postOrder();
    string recPostOrder(ParseNode * node);
    ParseNode * doParse(string expression);
    bool isOperand(char letter);
    bool isOperator(char character);
    bool higherPrec(char next, char value);
    string display();
    void parseInOrder(string expression);
};


#endif //LAB_5_PARSETREE_HPP
