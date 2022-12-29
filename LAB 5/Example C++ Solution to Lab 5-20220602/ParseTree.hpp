#ifndef PARSETREE_H
#define PARSETREE_H

#include <string>
class ParseNode
{
private:
        char value;
        ParseNode * left;
        ParseNode * right;
public:
    ParseNode(char value) : value(value), right(nullptr), left(nullptr) {}
    
    void setLeft(ParseNode * left) {this->left = left;}
    void setRight(ParseNode * right) {this->right = right;}
    
    char getValue() {return this->value;}
    ParseNode * getLeft() {return this->left;}
    ParseNode * getRight() {return this->right;}
    
    std::string displayNode() const {return std::string(1, value);}
};

class ParseTree
{
    public:
        ParseTree(std::string input);
        ~ParseTree();
        std::string preOrder();
        std::string postOrder();
        std::string inOrder();
        void parseInOrder(std::string input);
    
        // display method
        std::string display();

    private:
        ParseNode * root;
    
            // recursive traversals
        std::string recPreOrder(ParseNode *ptr);
        std::string recPostOrder(ParseNode *ptr);
        std::string recInOrder(ParseNode *ptr, bool paren = false);
            // recursive delete method
        void recDelete(ParseNode * ptr);
    
        ParseNode * doParse(std::string input);
        std::string inOrder2PostOrder(std::string input);
    
            // helper functions for inOrder2PostOrder
        bool higherPrec(char oper1, char oper2);
        int getPrec(char oper);
        bool isOperand(char value);
        bool isOperator(char value);
};

#endif // PARSETREE_H
