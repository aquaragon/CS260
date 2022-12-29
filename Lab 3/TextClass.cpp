//
// Created by aiden on 4/14/2022.
//


#include "TextClass.hpp"
#include <stdexcept>
#include <string>

using std::out_of_range, std::to_string;

Link::Link(char value, Link * next, Link * prev) //Default constrcutor, creates a new link class with a char value, next and prev pointers
{
    this->value = value;
    this->next = next;
    this->prev = prev;
}

char Link::getValue() //returns the char value of Link class
{
    return this->value;
}

Link * Link::getNext() //returns the next pointer of the Link class
{
    return this->next;
}

Link * Link::getPrev() //returns the prev pointer of the Link class
{
    return this->prev;
}

void Link::setNext(Link * next) //sets the next pointer to the passed in pointer
{
    this->next = next;
}

void Link::setPrev(Link * prev) // sets the prev pointer to the passed in pointer
{
    this->prev = prev;
}

////////////TEXTCLASS CLASS/////////////////////////////

TextClass::TextClass() //default constructor, creates head and tail pointers intialized to zero
{
    head = nullptr;
    tail = nullptr;
}

TextClass::~TextClass() //destructor, deletes links
{
    while (!isEmpty())
    {
        removeHead();
    }
}

void TextClass::addHead(char value) //Creates a new link at head that the head pointer points to, new link points to old head pointer
{

    if(head == nullptr)
    {
        head = tail = new Link(value);
    }else
    {
        Link * temp = new Link(value, head, nullptr); //Am I setting temp correctly here
        head->setPrev(temp);
        head = temp;
    }
}

void TextClass::addTail(char value) //Creates a new link at tail that points to nullptr, tail points to new link, previous link points next into this new link
{
    if (tail == nullptr)
    {
        head = tail = new Link(value);
    }else
    {
        Link * temp = new Link(value,nullptr,tail);
        tail->setNext(temp);
        tail = temp;
    }
}

char TextClass::getHead() //returns value of the Link that head points to, throws out of range
{
    if(head == nullptr)
    {
        throw out_of_range("Empty List - getHead");
    }
    char head_value = head->getValue();
    return head_value;
}

char TextClass::getTail() //returns value of the Link that tail points to, throws out of range
{
    if(head == nullptr)
    {
        throw out_of_range("Empty List - getTail");
    }
    char tail_value = tail->getValue();
    return tail_value;
}

void TextClass::removeHead() //removes Link that head points to, second link is now first which head now points to, deletes pointer to removed link, throws out of range
{
    if (head == nullptr)
    {
        throw out_of_range("Empty List - removeHead");
    }
    Link * temp = head;
    head = head->getNext();
    if (head == nullptr)
    {
        tail = nullptr;
    }else
    {
        head->setPrev(nullptr);
    }
    delete temp;
}

void TextClass::removeTail() //removes Link that tail points to, second to last link is now the last link, deletes pointer to removed link, throws out of range
{
    if (tail == nullptr)
    {
        throw out_of_range("List is Empty - removeTail");
    }
    Link * temp = tail;
    tail = tail->getPrev();
    if(tail == nullptr)
    {
        head = nullptr;
    }else
    {
        tail->setNext(nullptr);
    }
    delete temp;
}
bool TextClass::find(char value) //binary search of Linked list that starts at head until found or pointer through the link list ends up at end(nullptr)
{
    bool found = false;
    Link * ptr = head;
    while(ptr != nullptr)
    {
        if(value == ptr->getValue())
        {
            found = true;
            ptr = nullptr;
        }else
        {
            ptr = ptr->getNext();
        }
    }
    return found;
}
bool TextClass::findRemove(char value) //binary search that also removes Link that holds seeked value and deletes pointer to removed link
{
    Link * ptr = head;
    while(ptr != nullptr)
    {
        if(ptr->getValue() == value)
        {
            if (ptr == head)
            {
                removeHead();
                return true;
            }
            if (ptr == tail)
            {
                removeTail();
                return true;
            }
            ptr->getPrev()->setNext(ptr->getNext());
            ptr->getNext()->setPrev(ptr->getPrev());
            delete ptr;
            return true;
        }else
        {
            ptr = ptr->getNext();
        }
    }
    return false;
}

string TextClass::displayList() //creates a string that is inputted values of the Linked list down to tai
{
    string list;
    Link * ptr = head;
    while (ptr != nullptr)
    {
        list += ptr->getValue();
        list += " ";
        ptr = ptr->getNext();
    }
    return list;
}

bool TextClass::isEmpty()//checks if head is equal to nullptr
{
    return (head == nullptr);
}

void TextClass::append(TextClass const & other_list) //attaches to linked list together, adds to tail of the first list from head values of the second list, does not touch second list
{
    Link * ptr = other_list.head;

    while(ptr != nullptr)
    {
        addTail(ptr->getValue());
        ptr = ptr->getNext();
    }
}

bool TextClass::findNext(char value) //finds a passed in value but checks to see if it has been seeked before based off of a restricted pointer to a link, if so seeks passed that location again or until nullptr
{
    bool found = false;
    Link * ptr = head;
    if(last_found == value)
    {
        if(dupe_location == tail)
        {
            ptr = head;
        }else
        {
            ptr = dupe_location->getNext();
        }
        while(ptr != dupe_location && found == false)
        {
            if(ptr->getValue() == value)
            {
                found = true;
                last_found = ptr->getValue();
                dupe_location = ptr;
            }else
            {
                if(ptr == tail)
                {
                    ptr = head;
                }else
                {
                    ptr = ptr->getNext();
                }
            }
        }
    }else
    {
        while(ptr != nullptr && found == false)
        {
            if(ptr->getValue() == value)
            {
                found = true;
                last_found = ptr->getValue();
                dupe_location = ptr;
            }else
            {
                ptr = ptr->getNext();
            }
        }
    }
    return found;
}

void TextClass::removeLast() //removes the Link of the last seeked value at the restricted location assigned to dupe_location pointer
{
    if(dupe_location == tail)
    {
        removeTail();
        dupe_location = nullptr;
    }
    if(dupe_location == head)
    {
        removeHead();
        dupe_location = nullptr;
    }
    if(dupe_location != nullptr)
    {
        dupe_location->getPrev()->setNext(dupe_location->getNext());
        dupe_location->getNext()->setPrev(dupe_location->getPrev());
        delete dupe_location;
        dupe_location = nullptr;
    }
}

void TextClass::insertLast(char value) //creates a new link before the restricted location, sets the old link before dupe_location to point next to this new link and the dupe_location link to point back to this new link
{
    if(dupe_location == head)
    {
        Link * temp = new Link(value,dupe_location, nullptr);
        head->setPrev(temp);
        head = temp;
    }
    if(dupe_location != nullptr)
    {
        Link * temp = new Link(value,dupe_location,dupe_location->getPrev());
        (dupe_location->getPrev())->setNext(temp);
        dupe_location->setPrev(temp);
    }
}















