//
// Created by Aiden on 4/12/2022.
//

#include "Deque.hpp"
#include <stdexcept>

using std::out_of_range,std::to_string;

Deque::Deque(int n) //creates an array of passed in value, creates a default sized array if no value is passed in
{
    if(n < MIN_SIZE)
    {
        array_size = DEFAULT_SIZE;
        this->deque_array = new int [array_size];
    }else
    {
        array_size = n;
        this->deque_array = new int [array_size];
    }
}

Deque::~Deque() //deletes memory allocated for array
{
    delete [] deque_array;
}

void Deque::addTail(int value) //resizes if array is full, increments count, sets tail location of array to value, increments tail, wraps tail to start of array if it reaches the end
{
    if(count >= array_size)
    {
        resize();
    }
    count++;
    deque_array[tail] = value;
    tail++;
    if (tail >= array_size)
    {
        tail = 0;
    }
}

void Deque::resize()//creates new array, copies values from smaller array over, realigns head and tail to their respected queue positions, deletes old array
{
    int * doubled_array = new int [array_size * 2];
    for(int i = 0; i < count; i++)
    {
        head++;
        if(head >= array_size)
        {
            head = 0;
        }
        doubled_array[i] = deque_array[head];
    }
    tail = count;
    head = -1;
    array_size *= 2;
    delete [] deque_array;
    deque_array = doubled_array;
}

int Deque::removeHead() //throws exception for reaching into empty array, decrements count, moves head to next position in array and retrieves value there, if head reaches end of array function sets it back to the start of the array, wrapping
{
    if (count <= 0) {
        throw out_of_range("Queue is empty - removeHead");
    }
    count--;
    head++;
    if(head >= array_size)
    {
        head = 0;
    }
    return deque_array[head];
}

bool Deque::isEmpty() //checks to see if array is empty
{
    bool empty = false;
    if(count <= 0 )
    {
        empty = true;
    }
    return empty;
}

string Deque::dumpArray()//returns a string that is fed numbers from the array
{
    string dumped_array;
    for(int i = 0; i < array_size; i++)
    {

        if(i == (array_size - 1))
        {
            dumped_array += to_string(deque_array[i]);
        }else
        {
            dumped_array += to_string(deque_array[i]) + " ";
        }
    }
    return dumped_array;
}

string Deque::listQueue() //starts at head location and feeds into a string numbers until it hits the value of tail -1
{
    string list_queue;
    int temp_track = head;
    while(temp_track != (tail - 1))
    {
        temp_track++;
        if(temp_track == (tail - 1))
        {
            list_queue += to_string(deque_array[temp_track]);
        }else
        {
            list_queue += to_string(deque_array[temp_track]) + " ";
        }
        if(temp_track == (array_size - 1))
        {
            temp_track = -1;
        }
    }
    return list_queue;
}

void Deque::addHead(int value) //Like add tail but to head in order to have a functioning DEqueue, resizes if need be, goes down array and wraps to top
{
    if(count >= array_size)
    {
        resize();
    }
    count++;
    if (head < 0)
    {
        head = array_size - 1;
    }
    deque_array[head] = value;
    head--;
}

int Deque::removeTail() //Like remove head but to tail for DEqueue, climbs down the array, wraps tail to top of array when at end
{
    if (count <= 0) {
        throw out_of_range("Queue is empty - removeTail");
    }
    count--; //switch this
    if(tail <= 0)
    {
        tail = array_size;
    }
    tail--;
    return deque_array[tail];
}

