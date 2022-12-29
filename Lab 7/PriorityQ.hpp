//
// Created by Aiden on 5/17/2022.
//

#ifndef MAIN_CPP_PRIORITYQ_HPP
#define MAIN_CPP_PRIORITYQ_HPP
#include "Heap.hpp"

class PriorityQ {
private:
    static const int DEF_ARRAY_SIZE = 10;
    Heap * PQHeap;

public:
    PriorityQ(int n = DEF_ARRAY_SIZE);
    ~PriorityQ();
    void addItem(int item);
    int getItem();

};


#endif //MAIN_CPP_PRIORITYQ_HPP
