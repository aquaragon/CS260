//
// Created by aiden on 4/21/2022.
//
#include <string>
using std::string;

#include "StringHash.hpp"

StringHash::StringHash(int size)
{
    if(size > DEFAULT_SIZE)
    {
        array_size = size;
        this->string_hash = new string[size];
        for(int i = 0; i < array_size; i++)
        {
            string_hash[i] = EMPTY;
        }
    }else
    {
        array_size = DEFAULT_SIZE;
        this->string_hash = new string[DEFAULT_SIZE];
        for(int i = 0; i < array_size; i++)
        {
            string_hash[i] = EMPTY;
        }
    }
}

StringHash::~StringHash()
{
    delete [] string_hash;
}

int StringHash::hashFunc(string key)
{
    int hashValue = 0;
    for(int i = 0; i < key.length(); i++)
    {
        hashValue *= 128;
        hashValue += key[i];
        hashValue %= array_size;
    }
    return hashValue;
}

void StringHash::resize()
{
    array_size *= 2;
    string * temp = new string[array_size];
    for(int i = 0; i < array_size; i++)
    {
        temp[i] = EMPTY;
    }
    for(int i = 0; i < (array_size/2); i++)
    {
        if(string_hash[i] != EMPTY && string_hash[i] != DELETED)
        {
            if(temp[hashFunc(string_hash[i])] != EMPTY)
            {
                int index = hashFunc(string_hash[i]);
                while(temp[index] != EMPTY)
                {
                    index += 1;
                    if (index >= array_size)
                    {
                        index = 0;
                    }
                }
                temp[index] = string_hash[i];
            }else
            {
                temp[hashFunc(string_hash[i])] = string_hash[i];
            }
        }
    }
    string * junk = string_hash;
    string_hash = temp;
    delete [] junk;
}

void StringHash::addItem(string value)
{
    if(count >= array_size/2)
    {
        resize();
    }
    int index = hashFunc(value);
    while((string_hash[index] != EMPTY))
    {
        index += 1;
        if (index >= array_size)
        {
            index = 0;
        }
    }
    count += 1;
    string_hash[index] = value;
}

bool StringHash::findItem(string value)
{
    int index = hashFunc(value);
    bool found = false;
    while(string_hash[index] != EMPTY && !found)
    {
        if (string_hash[index] == value)
        {
            found = true;
        }else
        {
            index += 1;
            if (index >= array_size)
            {
                index = 0;
            }
        }
    }
    return found;
}

bool StringHash::removeItem(string value)
{
    int index = hashFunc(value);
    bool found = false;
    while(string_hash[index] != EMPTY && !found)
    {
        if(string_hash[index] == value)
        {
            string_hash[index] = DELETED;
            count--;
            found = true;
        }else
        {
            index+= 1;
            if(index >= array_size)
            {
                index = 0;
            }
        }
    }
    return found;
}

string StringHash::displayTable()
{
    string table;
    int index = 0;
    while (index < array_size)
    {
        table += string_hash[index] + '\n';
        index++;
    }
    return table;
}
