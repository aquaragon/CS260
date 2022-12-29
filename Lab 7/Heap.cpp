//
// Created by Aiden on 5/17/2022.
//

#include "Heap.hpp"
#include <stdexcept>

Heap::Heap(int n)
{
    if (n > DEF_ARR_SIZE)
    {
        heap_array = new int [n];
        array_size = n;
    }
    else
    {
        heap_array = new int [DEF_ARR_SIZE];
        array_size = DEF_ARR_SIZE;
    }
}

Heap::~Heap()
{
    delete [] heap_array;
}

void Heap::resize()
{
    int * doubled_array = new int [array_size * 2];
    for(int i = 0; i < array_size; i++)
    {
        doubled_array[i] = heap_array[i];
    }
    delete [] heap_array;
    heap_array = doubled_array;
    array_size *= 2;
}

void Heap::BubbleUp(int child)
{
    int parent = (child - 1)/2;
    while(child > 0 && heap_array[parent] > heap_array[child])
    {
        int temp = heap_array[parent];
        heap_array[parent] = heap_array[child];
        heap_array[child] = temp;
        child = parent;
        parent = (child -1)/2;
    }
}

void Heap::addItem(int item)
{
    if(count >= array_size)
    {
        resize();
    }
    heap_array[count] = item;
    count++;
    if(count - 1 != 0)
    {
        BubbleUp(count - 1);
    }
}

void Heap::trickleDown(int root)
{
    do{
       int j = -1;
       int right = 2*root + 2;
       if(right < count && heap_array[right] < heap_array[root])
       {
           int left = 2*root + 1;
           if(heap_array[left] < heap_array[right])
           {
               j = left;
           }else
           {
               j = right;
           }
       }else
       {
           int left = 2*root +1;
           if(left < count && heap_array[left] < heap_array[root])
           {
               j = left;
           }
       }
       if(j >= 0)
       {
           int temp = heap_array[root];
           heap_array[root] = heap_array[j];
           heap_array[j] = temp;
       }
       root = j;
    }while(root >= 0);
}

int Heap::getItem()
{
    if (count == 0)
    {
        throw std::out_of_range("Empty Array");
    }
    int smallest = heap_array[0];
    heap_array [0] = heap_array[--count];
    trickleDown(0);
    return smallest;
}

