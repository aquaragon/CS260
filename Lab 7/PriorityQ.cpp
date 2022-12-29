//
// Created by Aiden on 5/17/2022.
//

#include "PriorityQ.hpp"
#include <stdexcept>

PriorityQ::PriorityQ(int n)
{
    PQHeap = new Heap(n);
}

PriorityQ::~PriorityQ()
{
    delete PQHeap;
}

void PriorityQ::addItem(int item)
{
    PQHeap->addItem(item);
}

int PriorityQ::getItem()
{
    return PQHeap->getItem();
}