//
// Created by Aiden on 4/3/2022.
//
#include <stdexcept>
#include "ArrayInt.hpp"
using std::out_of_range, std::string, std::to_string;

int ArrayInt::getSize() //Gets size of array
{
    return array_size;
}

void ArrayInt::append(int array_value) //Appends values into array, resizes if array is too small, increments count when appends
{
    if (array_size <= count)
    {
        resize(array_size * 2);
        project_array[count] = array_value;
        count++;
    }else
    {
        project_array[count] = array_value;
        count++;
    }
}

int ArrayInt::getLast() //Returns last index array value
{
    if (count <= 0 )
    {
        throw out_of_range("Array is empty. - getLast");
    }
    int last = project_array[count - 1];
    return last;
}

void ArrayInt::deleteLast() //Deletes last index array value, decrements count
{
    if(count <= 0)
    {
        throw out_of_range("Array is empty. - deleteLast");
    }
    count--;
}

void ArrayInt::resize(int new_size) //Creates a new array of twice of previous array size, copies all previous contents into new array, sets pointer to new array, deletes old array
{
    if(new_size > array_size)
    {
        int *new_array= new int [new_size];
        for(int i = 0; i < count; i++)
        {
            new_array[i] = project_array[i];
        }
        array_size = new_size;
        delete [] project_array;
        project_array = new_array;
    }
}

string ArrayInt::listElements() //Inputs all elements of array into a string, returns string
{
    string numbers_list;

    if(count == 0)
    {
        numbers_list = "Empty Array";
    }
    for(int i = 0; i < count; i++)
    {
        if(i == (count - 1))
        {
            numbers_list += to_string(project_array[i]);
        }else
        {
            numbers_list += to_string(project_array[i]) + ", ";
        }
    }
    return numbers_list;
}

void ArrayInt::insertAt(int location, int insert_value) //Inserts a value at given location of array, pulls all array values after insert to the left, increments count
{
    if(location < 0 || location > count || location > array_size)
    {
        throw out_of_range("Out of range of the array - insertAt");
    }
    if(count >= array_size)
    {
        resize(array_size * 2);
    }
    for (int i = count; i > location; i--)
    {
        project_array[i] = project_array[i-1];
    }
    project_array[location] = insert_value;
    count++;
}

int ArrayInt::removeAt(int location) //Removes value of array at given location, decrements count
{
    if (location < 0 || location > count || location > array_size || count <= 0)
    {
        throw out_of_range ("Out of range of the array - removeAt");
    }
    int saved_value = 0;
    saved_value = project_array[location];
    for (int i = location; i < count; i++)
    {
        project_array[i] = project_array[i+1];
    }
    count--;
    return saved_value;
}

bool ArrayInt::find(int seeked_value) //Linear searches array for given value, returns true or false
{
    bool found_value = false;
    for (int i = 0;i < count && i != seeked_value; i++)
    {
        if (project_array[i] == seeked_value)
        {
            found_value = true;
        }
    }
    return found_value;
}

bool ArrayInt::findRemove(int seeked_value) //Removes given value if found
{
    bool removed_value = false;
    for (int i = 0;i < count && i != seeked_value; i++)
    {
        if (project_array[i] == seeked_value)
        {
            removed_value = true;
            removeAt(i);
        }
    }
    return removed_value;
}

int ArrayInt::findLargest() // Linear searches array for largest value, returns largest
{
    if (count == 0)
    {
        throw out_of_range ("Array empty - findLargest");
    }
    int largest_value = project_array[0];
    for (int i =0; i < count; i++)
    {
        if (project_array[i] > largest_value)
        {
            largest_value = project_array[i];
        }
    }
    return largest_value;
}

void ArrayInt::removeLargest() //Removes largest value from array
{
    if (count == 0)
    {
        throw out_of_range ("Array empty - removeLargest");
    }
    int largest_value = 0;
    int location = 0;
    for (int i = 0; i < count; i++)
    {
        if (project_array[i] > project_array[location])
        {
            location = i;
        }
    }
    removeAt(location);
}

void ArrayInt::setAt(int index, int value) //Sets a given location in memory to a given value, if the given location is passed count, count is set to location + 1
{
    if (index < 0 || index >= array_size)
    {
        throw out_of_range ("Out of range - setAt");
    }
    project_array[index] = value;
    if(index > count)
    {
        count = index + 1;
    }
}

int ArrayInt::getAt(int index) // Returns value at a given memory location
{
    if (index < 0 || index >= array_size)
    {
        throw out_of_range ("Out of range - getAt");
    }
    int get = 0;
    get = project_array[index];
    return get;
}