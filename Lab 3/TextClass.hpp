//
// Created by aiden on 4/14/2022.
//
#include <string>
using std::string;

#ifndef LAB_3_TEXTCLASS_HPP
#define LAB_3_TEXTCLASS_HPP

class Link{
private:
    char value;
    Link * next;
    Link * prev;

public:
    Link(char value, Link * next = nullptr, Link * prev = nullptr);
    char getValue();
    Link * getNext();
    Link * getPrev();
    void setNext(Link * next);
    void setPrev(Link * prev);
};

class TextClass{
private:
    Link * head;
    Link * tail;
    Link * dupe_location = nullptr;
    char last_found = '\0';

public:
    TextClass();
    ~TextClass();
    void addHead(char value);
    void addTail(char value);
    char getHead();
    char getTail();
    void removeHead();
    void removeTail();
    bool find(char value);
    bool findRemove(char value);
    string displayList();
    bool isEmpty();
    void append(TextClass const & other_list);
    bool findNext(char value);
    void removeLast();
    void insertLast(char value);

};




#endif //LAB_3_TEXTCLASS_HPP
