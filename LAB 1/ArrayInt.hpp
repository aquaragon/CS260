//
// Created by Aiden on 4/3/2022.
//
#include <string>
using std::string;
#ifndef ARRAYINT_HPP_ARRAYINT_HPP
#define ARRAYINT_HPP_ARRAYINT_HPP



class ArrayInt {
private:
    static const int DEFAULTSIZE = 10;
    static const int MINSIZE = 1;

    int * project_array;
    int array_size = 0;
    int count = 0;

public:
    ArrayInt(int n = DEFAULTSIZE)
    {
        if (n < MINSIZE)
        {
            array_size = DEFAULTSIZE;
            this->project_array = new int [array_size];
        }else
        {
            array_size = n;
            this->project_array = new int [array_size];
        }
    };
    ~ArrayInt()
    {
        delete [] project_array;
    }
    int getSize();
    void append(int array_value);
    int getLast();
    void deleteLast();
    void resize(int new_size);
    string listElements();
    void insertAt(int a, int b);
    int removeAt(int location);
    bool find(int seeked_value);
    bool findRemove(int seeked_value);
    int findLargest();
    void removeLargest();
    void setAt(int index, int value);
    int getAt(int index);
};






#endif //ARRAYINT_HPP_ARRAYINT_HPP
