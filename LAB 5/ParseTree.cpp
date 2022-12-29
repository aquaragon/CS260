//
// Created by aiden on 4/28/2022.
//

#include "ParseTree.hpp"
#include <stack>
#include <string>
#include <queue>
#include <iomanip>

using std::stack, std::string, std::queue;

ParseTree::ParseTree(string expression)
{
    if(expression == "")
    {
        root = nullptr;
    }else
    {
        root = doParse(expression);
    }
}

ParseTree::~ParseTree()
{
    recDelete(root);
}

void ParseTree::recDelete(ParseNode *ptr)
{
    if(ptr != nullptr)
    {
        recDelete(ptr->left);
        recDelete(ptr->right);
        delete ptr;
    }
}

string ParseTree::preOrder()
{
    return recPreOrder(root);
}

string ParseTree::recPreOrder(ParseNode * node)
{
    string buffer = "";

    if (node == nullptr)
    {
        return buffer;
    }else
    {
        buffer += node->value;
        buffer += recPreOrder(node->left);
        buffer += recPreOrder(node->right);
    }
    return buffer;
}


string ParseTree::inOrder()
{
    return recInOrder(root);
}

/*string ParseTree::recInOrder(ParseNode * node)
{
    string buffer = "";
    int need_right_paren = 0;
    bool need_right = false;

    if (node == nullptr)
    {
        return buffer;
    }
    else
    {
        buffer += recInOrder(node->left);
        if(node->value == '+' || node->value == '-')
        {
            int size = buffer.length();
            char temp = buffer[size-1];
            buffer[size-1] = '(';
            buffer += temp;
            need_right = true;
        }
        buffer += node->value;
        if(need_right == true)
        {
            if(need_right_paren % 2 == 1)
            {
                buffer += ")";
                need_right = false;
                need_right_paren++;
            }else
            {
                need_right_paren++;
            }

        }
        buffer += recInOrder(node->right);
    }
    return buffer;
} */

//////^^^^^Recursive in order after thinking problem^^^^^^^^/////////

string ParseTree::recInOrder(ParseNode * node)
{
    string buffer = "";

    if (node == nullptr)
    {
        return buffer;
    }
    else
    {
        buffer += "(";
        buffer += recInOrder(node->left);
        buffer += node->value;
        buffer += recInOrder(node->right);
        buffer += ")";
    }
    return buffer;
}

//////^^^^^Recursive in order before thinking problem^^^^^^^^/////////

string ParseTree::postOrder()
{
    return recPostOrder(root);
}

string ParseTree::recPostOrder(ParseNode * node)
{
    string buffer = "";

    if(node == nullptr)
    {
        return buffer;
    }else
    {
        buffer += recPostOrder(node->left);
        buffer += recPostOrder(node->right);
        buffer += node->value;
    }
    return buffer;
}

ParseNode * ParseTree::doParse(string expression)
{
    stack<ParseNode*> stack1;
    for(int i = 0; i<expression.length(); i++)
    {
        char letter = expression[i];
        if(letter != ' ')
        {
            if(isOperand(letter))
            {
                stack1.push(new ParseNode(letter));
            }
            else
            {
                ParseNode * temp = new ParseNode(letter);
                temp->right = stack1.top();
                stack1.pop();
                temp->left = stack1.top();
                stack1.pop();
                stack1.push(temp);
            }
        }
    }
    return stack1.top();
}

bool ParseTree::isOperand(char letter)
{
    bool operand = true;
    if(letter == '*' || letter == '+' || letter == '-' || letter == '/' || letter == '%' || letter == '(' || letter == ')')
    {
        operand = false;
    }
    return operand;
}

bool ParseTree::isOperator(char character)
{
    bool op = false;
    if(character == '+' || character == '-' || character == '*'|| character == '/' || character == '%')
    {
        op = true;
    }
    return op;
}

bool ParseTree::higherPrec(char next, char value)
{
    bool prec = false;
    if(next == '/' || next == '*')
    {
        prec = true;
    }
    return prec;
}

std::string ParseTree::display()
{
    // arbitrary width of the display
    const int PAGE_WIDE = 64;

    // dummy placeholder for null leaves
    ParseNode * dummy = nullptr;

    // empty node output
    std::string emptyNode = ".";

    // define buffer to collect output
    std::stringstream buffer;

    // define queue (FIFO) to hold next layer's nodes
    std::queue<ParseNode *> theQueue;

    // boolean to keep track of when no nodes in layer
    bool more = true;

    // start with the root
    theQueue.push(root);

    // first layer has one node
    int curNodes = 1;

    // while there are nodes in the queue
    while (more)
    {
        more = false;

        // calculate the base offset
        int offset = PAGE_WIDE/(curNodes*2);
        // process the nodes in the layer
        for (int i = 0; i < curNodes; i++)
        {
            // get and remove front node
            ParseNode * ptr = theQueue.front();
            theQueue.pop();

            // all offsets after the first are doubled
            if (i == 1)
            {
                offset *= 2;
            }

            // if not a dummy node process it
            if (ptr != dummy)
            {
                // add contents to buffer
                buffer << std::setw(offset) << ptr->value;

                // if there is a left child, add to fifo
                if (ptr->left)
                {
                    more = true;
                    theQueue.push(ptr->left);
                }
                    // no left child, add dummy in its place
                else
                {
                    theQueue.push(dummy);
                }

                // if right child, add to fifo
                if (ptr->right)
                {
                    more = true;
                    theQueue.push(ptr->right);
                }
                    // no right child, add dummy in its place
                else
                {
                    theQueue.push(dummy);
                }
            }

                // this node was a dummy
                // output the emptyNode symbol
                // add two dummies to FIFO for children placeholders
            else
            {
                buffer << std::setw(offset) << emptyNode;
                theQueue.push(dummy);
                theQueue.push(dummy);
            }
        }
        curNodes *= 2;
        buffer << std::endl;
    }

    return buffer.str();
}

void ParseTree::parseInOrder(string expression)
{
    stack<char> stack2;
    string output = "";

    for (int i = 0; i < expression.length(); i++)
    {
        char value = expression[i];

        if (isOperand(value))
        {
            output += value;
        }
        else if(value == '(')
        {
            stack2.push(value);
        }
        else if(value == ')')
        {
            bool isPopping = true;
            while (!stack2.empty() && isPopping)
            {
                char value = stack2.top();
                stack2.pop();

                if(value == '(')
                {
                    isPopping = false;
                }else
                {
                    output += value;
                }
            }
        }
        else if (isOperator(value))
        {
            bool isPopping = true;

            while(!stack2.empty() && isPopping)
            {
                char next = stack2.top();
                stack2.pop();

                if(higherPrec(next,value))
                {
                    output += next;
                }else
                {
                    stack2.push(next);
                    isPopping = false;
                }
            }
            stack2.push(value);
        }
    }
    while(!stack2.empty())
    {
        output += stack2.top();
        stack2.pop();
    }
    root = doParse(output);
}
