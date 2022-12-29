//
// Created by Aiden on 4/25/2022.
//

#include "ChainHash.hpp"
#include <string>

using std::string;

ChainLink::ChainLink(string value, ChainLink *next)
{
    this->value = value;
    this->next = next;
}

string ChainLink::getValue()
{
    return this->value;
}

ChainLink * ChainLink::getNext()
{
    return this->next;
}

void ChainLink::setNext(ChainLink * next)
{
    this->next = next;
}

///////////////////Chain Hash Functions///////////////////////////////////

ChainHash::ChainHash(int size)
{
    if(size > ADV_DEFAULT_SIZE)
    {
        adv_array_size = size;
        adv_array = new ChainLink*[adv_array_size];
        for(int i = 0; i < adv_array_size; i++)
        {
            adv_array[i] = nullptr;
        }
    }else
    {
        adv_array_size = ADV_DEFAULT_SIZE;
        adv_array = new ChainLink*[adv_array_size];
        for(int i = 0; i < adv_array_size; i++)
        {
            adv_array[i] = nullptr;
        }
    }
}

ChainHash::~ChainHash()
{
    for(int i = 0; i < adv_array_size; i++)
    {
        while(!isEmpty(i))
        {
            removeHead(i);
        }
    }
    delete [] adv_array;
}

bool ChainHash::isEmpty(int index)
{
    bool empty = true;
    if(adv_array[index] != nullptr)
    {
        empty = false;
    }
    return empty;
}

void ChainHash::removeHead(int index)
{
    if(adv_array != nullptr)
    {
        ChainLink * temp = adv_array[index];
        adv_array[index] = adv_array[index]->getNext();
        delete temp;
        count--;
    }
}

int ChainHash::hashFunc(string key)
{
    int hashValue = 0;
    for(int i = 0; i < key.length(); i++)
    {
        hashValue *= 128;
        hashValue += key[i];
        hashValue %= adv_array_size;
    }
    return hashValue;
}

void ChainHash::addItem(string value)
{
    if(count > adv_array_size*2)
    {
        resizeChain();
    }
    int index = hashFunc(value);
    ChainLink * temp = new ChainLink(value,adv_array[index]);
    adv_array[index] = temp;
    count++;
}

bool ChainHash::findItem(string value)
{
    int index = hashFunc(value);
    bool found = false;
    ChainLink * ptr = adv_array[index];
    while(ptr != nullptr && found == false)
    {
        if(ptr->getValue() == value)
        {
            found = true;
        }else
        {
            ptr = ptr->getNext();
        }
    }
    return found;
}

void ChainHash::removeItem(string value)
{
    bool remove_success = false;
    int index = hashFunc(value);
    if(adv_array[index]->getValue() == value)
    {
        removeHead(index);
    }else
    {
        ChainLink * ptr = adv_array[index]->getNext();
        ChainLink * prev = adv_array[index];
        while (ptr != nullptr && remove_success == false)
        {
            if(ptr->getValue() == value)
            {
                remove_success = true;
                prev->setNext(ptr->getNext());
                delete ptr;
                count--;
            }else
            {
                ptr = ptr->getNext();
                prev = prev->getNext();
            }
        }
    }
}

string ChainHash::displayTable()
{
    string table;
    for (int i = 0; i < adv_array_size; i++)
    {
        ChainLink * ptr = adv_array[i];
        if(ptr == nullptr)
        {
            table += EMPTY;
        }
        while(ptr != nullptr)
        {
            table += ptr->getValue() + " ";
            ptr = ptr->getNext();
        }
        table += '\n';
        delete ptr;
    }
    return table;
}

void ChainHash::resizeChain()
{
    int old_array_size = adv_array_size;
    if(adv_array_size > prime_nums[9])
    {
        adv_array_size *= 2;
    }else
    {
        for(int j = 0; j < 10; j++)
        {
            if(adv_array_size < prime_nums[j])
            {
                adv_array_size = prime_nums[j];
                j = 10;
            }
        }
    }
    ChainLink ** temp = new ChainLink*[adv_array_size];
    for(int i = 0; i < adv_array_size; i++)
    {
        temp[i] = nullptr;
    }
    string rehash [count];
    int index = 0;
    for(int i = 0; i < old_array_size; i++)
    {
        if(adv_array[i] != nullptr)
        {
            ChainLink * ptr = adv_array[i];
            while(ptr != nullptr)
            {
                rehash[index] = ptr->getValue();
                index++;
                ptr = ptr->getNext();
            }
        }
    }
    ChainLink ** junk = adv_array;
    adv_array = temp;
    delete [] junk;
    int end = count;
    count = 0 ;
    for(int i = 0; i < end; i++)
    {
        addItem(rehash[i]);
    }
}
