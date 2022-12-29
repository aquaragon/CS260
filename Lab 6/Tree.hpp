//
// Created by Aiden on 5/9/2022.
//

#ifndef LAB_6_TREE_HPP
#define LAB_6_TREE_HPP

//
// Created by aiden on 4/28/2022.
//

#ifndef LAB_5_PARSETREE_HPP
#define LAB_5_PARSETREE_HPP

#include <string>

using std::string;

struct Node
{
    int value;
    Node * left;
    Node * right;
    bool present;
    Node(int value): value(value), left(nullptr), right(nullptr), present(true){};
    ~Node() = default;
};

class Tree
{
private:
    Node * remove_location = nullptr;
    Node * root;
    void recDelete(Node * ptr);
    bool recFindvalue(int value, Node * ptr);
    string recInOrder(Node * ptr);
    string recPreOrder(Node * ptr);
    string recPostOrder(Node * ptr);
public:
    Tree();
    ~Tree();
    void insertValue(int value);
    bool findValue(int value);
    string inOrder();
    string preOrder();
    string postOrder();
    bool removeValue(int value);
    int findLarger(int value);
    int removeLarger(int value);
};


#endif //LAB_5_PARSETREE_HPP


#endif //LAB_6_TREE_HPP
