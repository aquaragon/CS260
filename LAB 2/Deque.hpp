//
// Created by Aiden on 4/12/2022.
//
#include <string>
using std::string;
#ifndef LAB_2_DEQUE_HPP

class Deque
{
private:
    static const int DEFAULT_SIZE = 20;
    static const int MIN_SIZE = 1;

    int array_size = 0;
    int count = 0;
    int * deque_array;
    int tail = 0;
    int head = -1;

public:
    Deque(int n = DEFAULT_SIZE);
    ~Deque();
    void addTail(int value);
    void resize();
    int removeHead();
    bool isEmpty();
    string dumpArray();
    string listQueue();
    void addHead(int value);
    int removeTail();
};


#define LAB_2_DEQUE_HPP

#endif //LAB_2_DEQUE_HPP
