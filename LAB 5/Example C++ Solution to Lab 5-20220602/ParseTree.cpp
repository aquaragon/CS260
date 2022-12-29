#include "ParseTree.hpp"
#include <stack>
#include <cctype>
#include <iostream>
#include <sstream>
#include <queue>
#include <iomanip>

// constants for parsing
const char PLUS = '+';
const char MINUS = '-';
const char MULT = '*';
const char DIV = '/';
const char MOD = '%';
const char SPACE = ' ';
const char LPAREN = '(';
const char RPAREN = ')';


ParseTree::ParseTree(std::string input)
{
    if (input == "" )
    {
        root = nullptr;
    }
    else
    {
        root = doParse(input);
    }
}

ParseTree::~ParseTree()
{
    recDelete(root);
}

void ParseTree::recDelete(ParseNode * ptr)
{
    if ( ptr!= nullptr )
    {
        recDelete(ptr->getLeft());
        recDelete(ptr->getRight());
        delete ptr;
    }
}

std::string ParseTree::preOrder()
{
    return recPreOrder(root);
}

std::string ParseTree::postOrder()
{
    return recPostOrder(root);
}

std::string ParseTree::inOrder()
{
    return recInOrder(root);
}

std::string ParseTree::recPreOrder(ParseNode *ptr)
{
    if ( ptr != nullptr )
    {
        std::string buffer = "";
        buffer += ptr->getValue();
        buffer += recPreOrder(ptr->getLeft());
        buffer += recPreOrder(ptr->getRight());
        return buffer;
    }
    return "";
}

std::string ParseTree::recPostOrder(ParseNode *ptr)
{
    if ( ptr != nullptr )
    {
        std::string buffer = "";
        buffer += recPostOrder(ptr->getLeft());
        buffer += recPostOrder(ptr->getRight());
        buffer += ptr->getValue();
        return buffer;
    }
    return "";
}

//#define FULL_PARENS
//#define SOME_PARENS
#define REMOVE_PARENS

#ifdef FULL_PARENS
std::string ParseTree::recInOrder(ParseNode *ptr, bool paren)
{
    if ( ptr != nullptr )
    {
        std::string buffer = "";

        buffer += "(";

        buffer += recInOrder(ptr->getLeft(), true);
        buffer += ptr->getValue();
        buffer += recInOrder(ptr->getRight(), true);
        
        buffer += ")";

        return buffer;
    }
    return "";
}
#endif // FULL_PARENS

#ifdef SOME_PARENS
std::string ParseTree::recInOrder(ParseNode *ptr, bool paren)
{
    if ( ptr != nullptr )
    {
        std::string buffer = "";

        if (ptr->getLeft())
        {
            buffer += "(";
        }

        buffer += recInOrder(ptr->getLeft(), true);
        buffer += ptr->getValue();
        buffer += recInOrder(ptr->getRight(), true);
        
        if (ptr->getLeft())
        {
            buffer += ")";
        }

        return buffer;
    }
    return "";
}
#endif // SOME_PARENS

#ifdef REMOVE_PARENS
std::string ParseTree::recInOrder(ParseNode *ptr, bool paren)
{
    if ( ptr != nullptr )
    {
        std::string buffer = "";
        if (paren)
        {
            buffer += "(";
        }
        
        if ( ptr->getLeft() != nullptr and isOperator(ptr->getLeft()->getValue()) )
        {
            if (higherPrec(ptr->getValue(), ptr->getLeft()->getValue()))
            {
                // left paren due to higher prec
                buffer += recInOrder(ptr->getLeft(), true);
            }
            else
            {
                buffer += recInOrder(ptr->getLeft(), false);
            }
        }
        else
        {
            buffer += recInOrder(ptr->getLeft(), false);
        }

        buffer += ptr->getValue();
        
        if ( ptr->getRight() != nullptr and isOperator(ptr->getRight()->getValue()) )
        {
            if ( higherPrec(ptr->getValue(),ptr->getRight()->getValue()) )
            {
                // right paren due to higher prec
                buffer += recInOrder(ptr->getRight(), true);
            }
            else if ( getPrec(ptr->getValue()) == getPrec(ptr->getRight()->getValue()) and
                    ( ptr->getValue() == DIV or ptr->getValue() == MINUS or ptr->getValue() == MOD ) )
            {
                // right paren due to same prec and DIV, MINUS, or MOD
                buffer += recInOrder(ptr->getRight(), true);
            }
            else
            {
                buffer += recInOrder(ptr->getRight(), false);
            }
        }
        else
        {
            buffer += recInOrder(ptr->getRight(), false);
        }
        
        if (paren)
        {
            buffer += ")";
        }

        return buffer;
    }
    return "";
}
#endif // REMOVE_PARENS

// This assumes the input is a properly formed postFix expression
// that contains only single letter operands and operators
ParseNode * ParseTree::doParse(std::string input)
{
    // Get next char
    // if char is letter, push
    // if char is operator, pop to right, pop to left, push
    std::stack <ParseNode*> theStack;
    for(int i = 0; i < static_cast<int>(input.length()); i++)
    {
        char letter = input[i];

        if ( isalpha(letter) )
        {
            theStack.push(new ParseNode(letter));
        }
        else
        {
            ParseNode * temp = new ParseNode(letter);
            temp->setRight(theStack.top());
            theStack.pop();
            temp->setLeft(theStack.top());
            theStack.pop();
            theStack.push(temp);
        }

    }
    return theStack.top();

}

/*
 * helper function
 *    return true for operators
 *    false otherwise
 */
bool ParseTree::isOperator(char value)
{
    
    switch(value)
    {
        case PLUS:
        case MINUS:
        case MULT:
        case DIV:
        case MOD:
            return true;
        default:
            return false;
    }
}

/*
 * helper function
 *    return true for operands
 *    false otherwise
 */
bool ParseTree::isOperand(char value)
{
    return isalnum(value);
}

/*
 * helper function
 *
 * return true if operator1 higher precedence than operator2
 *
 */
bool ParseTree::higherPrec(char oper1, char oper2)
{
    return getPrec(oper1) > getPrec(oper2);
}

/*
 * helper function for higherPrec
 *
 * return weight of operator
 */
int ParseTree::getPrec(char oper)
{
    int prec = -1;
    switch (oper)
    {
        case PLUS:
        case MINUS:
            prec = 1;
            break;
        case MULT:
        case DIV:
        case MOD:
            prec = 2;
    }
    return prec;
}

// converts a proper in order expression to postfix
std::string ParseTree::inOrder2PostOrder(std::string input)
{
    // define stack for storing values
    // buffer for saving converted string
    std::stack<char> theStack;
    std::string buffer = "";
    
    for(int i = 0; i < static_cast<int>(input.length()); i++ )
    {
        char next = input[i];
        
        // output all operands
        if ( isOperand(next) )
        {
            buffer += next;
        }
        // push opening parens
        else if ( next == LPAREN )
        {
            theStack.push(next);
        }
        // closing paren
        // pop and output until matching opening paren
        else if ( next == RPAREN )
        {
            bool isPopping = true;
            while ( !theStack.empty()  and isPopping)
            {
                char value = theStack.top();
                theStack.pop();
                if ( value == LPAREN )
                {
                    isPopping = false;
                }
                else
                {
                    buffer += value;
                }
            }
        }
        // operator
        // pop and output anything on stack
        //   until opening paren or higher precedence
        // push this one on stack
        else if ( isOperator(next) )
        {
            bool isPopping = true;
            while ( !theStack.empty() and isPopping )
            {
                char value = theStack.top();
                theStack.pop();
                if ( value == LPAREN )
                {
                    theStack.push(value);
                    isPopping = false;;
                }
                else
                {
                    if ( higherPrec(next, value))
                    {
                        theStack.push(value);
                        isPopping = false;
                    }
                    else
                    {
                        buffer += value;
                    }
                }
            }
            theStack.push(next);
        }
    }
    
    // get any remaining operators on stack
    while ( !theStack.empty() )
    {
        buffer += theStack.top();
        theStack.pop();
    }
    
    // return the result
    return buffer;
}

void ParseTree::parseInOrder(std::string input)
{
    recDelete(root);
    
    root = doParse(inOrder2PostOrder(input));
}

/*
// display method for a binary tree
//   assumes that the values in a node are 3 chars or less
//   assumes that a node has a method to display its value as a string
std::string ParseTree::display()
{
    // arbitrary width of the display
    const int PAGE_WIDE = 64;
    
    // dummy placeholder for null leaves
    ParseNode * dummy = nullptr;
    
    std::stringstream buffer;
    std::queue<ParseNode *> theQueue;
    
    bool more = true;
    theQueue.push(root);
    
    int curNodes = 1;
    
    while (more)
    {
        more = false;
        
        int offset = PAGE_WIDE/(curNodes*2);

        for (int i = 0; i < curNodes; i++)
        {
            ParseNode * ptr = theQueue.front();
            theQueue.pop();
            if (i == 1)
            {
                offset *= 2;
            }
                
            
            if (ptr != dummy)
            {
                buffer << std::setw(offset) << ptr->displayNode();
                if (ptr->getLeft())
                {
                    more = true;
                    theQueue.push(ptr->getLeft());
                }
                else
                {
                    theQueue.push(dummy);
                }
                if (ptr->getRight())
                {
                    more = true;
                    theQueue.push(ptr->getRight());
                }
                else
                {
                    theQueue.push(dummy);
                }
            }
            else
            {
                buffer << std::setw(offset) << ".";
                theQueue.push(dummy);
                theQueue.push(dummy);
            }
        }
        curNodes *= 2;
        buffer << std::endl;
    }
           
    return buffer.str();
}
*/
