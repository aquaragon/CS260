//
// Created by Aiden on 5/9/2022.
//

#include "Tree.hpp"
//
// Created by aiden on 4/28/2022.
//

#include <string>
#include <iostream>

using std::string, std::to_string, std::stoi;

Tree::Tree()
{
    this->root = nullptr;
}

Tree::~Tree()
{
    recDelete(root);
}

void Tree::recDelete(Node *ptr)
{
    if(ptr != nullptr)
    {
        recDelete(ptr->left);
        recDelete(ptr->right);
        delete ptr;
    }
}

void Tree::insertValue(int value)
{
    bool climb = true;
    if(root == nullptr)
    {
        root = new Node(value);
    }else
    {
        Node * ptr = root;
        while(climb == true)
        {
            if(value >= ptr->value && ptr->right != nullptr)
            {
                ptr = ptr->right;
            }
            else if(value < ptr->value && ptr->left != nullptr)
            {
                ptr = ptr->left;
            }
            else
            {
                climb = false;
            }
        }
        if(value == ptr->value && ptr->present == false)
        {
            ptr->present = true;
        }
        else if(value >= ptr->value)
        {
            ptr->right = new Node(value);
        }else
        {
            ptr->left = new Node(value);
        }
    }
}

bool Tree::findValue(int value)
{
    return recFindvalue(value,root);
}

bool Tree::recFindvalue(int value, Node * ptr)
{
    bool found = false;
    if(ptr == nullptr)
    {
        return found;
    }else if(ptr->value == value && ptr->present == true)
    {
        found = true;
        remove_location = ptr;
        return found;
    }else if(value > ptr->value)
    {
        return recFindvalue(value, ptr->right);
    }else
    {
        return recFindvalue(value,ptr->left);
    }
}

string Tree::inOrder()
{
    return recInOrder(root);
}

string Tree::recInOrder(Node * ptr)
{
    string in_order = "";

    if (ptr == nullptr)
    {
        return in_order;
    }
    else
    {
        in_order += recInOrder(ptr->left);
        if(ptr->present == false)
        {
            in_order += to_string(ptr->value) + "D ";
        }else
        {
            in_order += to_string(ptr->value) + " ";
        }
        in_order += recInOrder(ptr->right);
    }
    return in_order;
}

string Tree::preOrder()
{
    return recPreOrder(root);
}

string Tree::recPreOrder(Node * ptr)
{
    string pre_order = "";

    if (ptr == nullptr)
    {
        return pre_order;
    }else
    {
        if(ptr->present == false)
        {
            pre_order += "D ";
        }else
        {
            pre_order += to_string(ptr->value) + " ";
        }
        pre_order += recPreOrder(ptr->left);
        pre_order += recPreOrder(ptr->right);
    }
    return pre_order;
}

string Tree::postOrder()
{
    return recPostOrder(root);
}

string Tree::recPostOrder(Node * ptr)
{
    string post_order = "";

    if(ptr == nullptr)
    {
        return post_order;
    }else
    {
        post_order += recPostOrder(ptr->left);
        post_order += recPostOrder(ptr->right);
        if(ptr->present == false)
        {
            post_order += "D ";
        }
        else
        {
            post_order += to_string(ptr->value) + " ";
        }
    }
    return post_order;
}

bool Tree::removeValue(int value)
{
    bool found_remove = recFindvalue(value,root);
    if (found_remove == true)
    {
        remove_location->present = false;
        remove_location = nullptr;
    }
    return found_remove;
}

int Tree::findLarger(int value)
{
    bool found_first = recFindvalue(value,root);
    int larger = -1;
    if(found_first == true)
    {
        larger = value;
    }
    Node * ptr = root;
    while(larger == -1 && ptr != nullptr && found_first == false)
    {
        if(value < ptr->value)
        {
            if(ptr->left == nullptr)
            {
                larger = ptr->value;
                remove_location = ptr;
            }else if(value > ptr->left->value)
            {
                if(ptr->left->right != nullptr && value < ptr->left->right->value)
                {
                    ptr = ptr->left->right;
                }else
                {
                    larger = ptr->value;
                    remove_location = ptr;
                }
            }
            else
            {
                ptr = ptr->left;
            }
        }else if (value > ptr->value)
        {
            ptr = ptr->right;
        }
    }
    return larger;
}

int Tree::removeLarger(int value)
{
    int larger = findLarger(value);
    if(larger != -1)
    {
        remove_location->present = false;
    }
    return larger;
}


