//
//  main.cpp
//  ArrayInt
//
//  Created by Jim Bailey on 3/31/2021.
//  This work by Jim Bailey is licensed under a Creative
//  Commons Attribution 4.0 International License.
//

#include <iostream>
#include <iomanip>
#include <stdexcept>
#include "ArrayInt.hpp"


#define TEST_CONSTRUCTOR
#define TEST_APPEND
#define TEST_MAKE_ROOM
#define TEST_INSERT_REMOVE
#define TEST_FIND
#define TEST_FIND_LARGEST
#define TEST_SET_GET
#define TEST_MIX
#define TEST_THINK


int main(int argc, const char * argv[])
{
#ifdef TEST_CONSTRUCTOR
    const int DEFAULT = 10;
    const int OVERLOAD = 15;
    std::cout << "Testing default and overloaded constructors." << std::endl;
    std::cout << "Also uses getSize" << std::endl << std::endl;

    ArrayInt defaultSize;
    ArrayInt defineSize(OVERLOAD);

    std::cout << "Default size should be " << DEFAULT << " and is " << defaultSize.getSize() << std::endl;
    std::cout << "Overload size should be " << OVERLOAD << " and is " << defineSize.getSize() << std::endl;
    std::cout << std::endl << std::endl;
#endif // TEST_CONSTRUCTOR

#ifdef TEST_APPEND
    std::cout << "Testing append, getLast, and removeLast" << std::endl << std::endl;

    ArrayInt appends;
    const int NUM_APPENDS = 5;
    int primes[NUM_APPENDS] = {2, 3, 5, 7, 11};


    for(int i = 0; i < NUM_APPENDS; i++)
    {
        appends.append(primes[i]);
    }

    std::cout << "The array should be: 11, 7, 5, 3, 2" << std::endl;
    std::cout << "The array really is: ";
    try {
        for(int i = 0; i < NUM_APPENDS - 1; i++)
        {
            std::cout << appends.getLast() << ", ";
            appends.deleteLast();
        }
        std::cout << appends.getLast() << std::endl;
        appends.deleteLast();
    }
    catch ( ... ) {
        std::cout << "Problem with appending and deleting" << std::endl;
    }

    std::cout << "Trying getLast on empty array, should throw exception" << std::endl;
    try {
        std::cout << appends.getLast() << std::endl;
    }
    catch (std::out_of_range &ex) {
        std::cout << "Caught out of range with message: " << ex.what() << std::endl;
    }
    catch ( ... ) {
        std::cout << "Caught something weird " << std::endl;
    }

    std::cout << "Trying to delete from empty array, should throw exception" << std::endl;
    try {
        appends.deleteLast();
    }
    catch (std::out_of_range &ex) {
        std::cout << "Caught out of range with message: " << ex.what() << std::endl;
    }
    catch ( ... ) {
        std::cout << "Caught something weird " << std::endl;
    }

    std::cout << std::endl << std::endl;
#endif // TEST_APPEND

#ifdef TEST_MAKE_ROOM
    const int START = 7;
    const int UPDATE = 12;
    std::cout << "Testing setSize and auto expansion on appends" << std::endl;
    std::cout << "Also tests listElements" << std::endl << std::endl;

    ArrayInt room(START);
    std::cout << "Starting size should be " << START << " and is " << room.getSize() << std::endl;
    room.resize(UPDATE);
    std::cout << "After resize, size should be " << UPDATE << " and is " << room.getSize() << std::endl;

    std::cout << std::endl << "Now going to fill array and see if expands" << std::endl;
    for(int i = 0; i < UPDATE; i++)
    {
        room.append(2 * i + 1);
    }
    std::cout << "Filled with 12 values, no problem" << std::endl;
    std::cout << "Size should still be " << UPDATE << " and is " << room.getSize() << std::endl;
    std::cout << std::endl << "Adding one more" << std::endl;
    room.append(25);
    std::cout << "Size should now be " << 2 * UPDATE << " and is " << room.getSize() << std::endl;

    std::cout << std::endl << "Should show: 1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25 " << std::endl;
    std::cout << "Array returns: " << room.listElements() << " ";

    std::cout << std::endl << std::endl;
#endif // TEST_MAKE_ROOM

#ifdef TEST_INSERT_REMOVE
    const int BEGIN = 10;
    std::cout << "Testing insert and remove " << std::endl << std::endl;

    ArrayInt insertRemove;
    for(int i = 0; i < BEGIN; i++)
    {
        insertRemove.append(2*i);
    }

    std::cout << "Array starting with: ";
    std::cout << insertRemove.listElements();

    std::cout << std::endl << "Size should be " << BEGIN << " and is " << insertRemove.getSize() << std::endl;

    std::cout << std::endl << "Now inserting the numbers 5, 9, and 13" << std::endl;
    insertRemove.insertAt(7, 13);
    insertRemove.insertAt(5, 9);
    insertRemove.insertAt(3, 5);
    std::cout << "Size should be " << 2 * BEGIN << " and is " << insertRemove.getSize() << std::endl;
    std::cout << "The values should be:  0, 2, 4, 5, 6, 8, 9, 10, 12, 13, 14, 16, 18" << std::endl;
    std::cout << "The values really are: ";
    std::cout << insertRemove.listElements();

    std::cout << std::endl << std::endl << "Now trying to remove the values 12, 8, 0 -- removed:  ";
    std::cout << insertRemove.removeAt(8) << ", ";
    std::cout << insertRemove.removeAt(5) << ", ";
    std::cout << insertRemove.removeAt(0) << std::endl;

    std::cout << "The array should be: 2, 4, 5, 6, 9, 10, 13, 14, 16, 18 " << std::endl;
    std::cout << "The array really is: ";
    std::cout << insertRemove.listElements();

    std::cout << std::endl << std::endl << "Now testing illegal inserts and removes " << std::endl;
    std::cout << std::endl << "Testing invalid insertAt at index larger than array size" << std::endl;
    try {
        insertRemove.insertAt(BEGIN*3, -1);
        std::cout << "Should have thrown an exception inserting at " << BEGIN*3 << std::endl;
    }
    catch (std::out_of_range &ex) {
        std::cout << "Caught out of range with message: " << ex.what() << std::endl;
    }
    catch ( ... ) {
        std::cout << "Caught something weird " << std::endl;
    }

    std::cout << std::endl << "Testing invalid insertAt at negative index" << std::endl;
    try {
        insertRemove.insertAt(-1, 500);
        std::cout << "Should have thrown an exception inserting at -1" << std::endl;
    }
    catch (std::out_of_range &ex) {
        std::cout << "Caught out of range with message: " << ex.what() << std::endl;
    }
    catch ( ... ) {
        std::cout << "Caught something weird " << std::endl;
    }

    std::cout << std::endl << "Emptying the array, expecting: 18 16 14 13 10 9 6 5 4 2 ";
    std::cout << std::endl << "Actually removed the values  : ";
    for(int i = 0; i < BEGIN; i++)
    {
        std::cout << insertRemove.getLast() << " ";
        insertRemove.deleteLast();
    }
    std::cout << std::endl;

    std::cout << std::endl << "Now testing removeAt on empty array" << std::endl;
    try {
        insertRemove.removeAt(0);
        std::cout << "Should have thrown an exception" << std::endl;
    }
    catch (std::out_of_range &ex) {
        std::cout << "Caught out of range with message: " << ex.what() << std::endl;
    }
    catch ( ... ) {
        std::cout << "Caught something weird " << std::endl;
    }
    std::cout << std::endl << std::endl;
#endif // TEST_INSERT_REMOVE

#ifdef TEST_FIND
    const int FIND_COUNT = 10;
    std::cout << "Testing find and findRemove " << std::endl << std::endl;

    ArrayInt findRemove;
    int primes2[FIND_COUNT] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
    for(int i = 0; i < FIND_COUNT; i++)
    {
        findRemove.append(primes2[i]);
    }

    std::cout << "Array contains " << findRemove.listElements() << std::endl;

    std::cout << "Testing find on 4 and 7.  4 should not be found, 7 should be found." << std::endl;
    std::cout << 4 << (findRemove.find(4)?" was ":" was not " ) << "found" << std::endl;
    std::cout << 7 << (findRemove.find(7)?" was ":" was not " ) << "found" << std::endl;

    std::cout << "Testing findRemove on 4 and 7.  4 should not be removed, 7 should be removed." << std::endl;
    std::cout << 4 << (findRemove.findRemove(4)?" was ":" was not " ) << "removed" << std::endl;
    std::cout << 7 << (findRemove.findRemove(7)?" was ":" was not " ) << "removed" << std::endl;

    std::cout << "After the remove" << std::endl;
    std::cout << " expected: 2, 3, 5, 11, 13, 17, 19, 23, 29" << std::endl;
    std::cout << " actually: " << findRemove.listElements() << std::endl;

    std::cout << "Using findRemove on final element, 29" << std::endl;
    std::cout << 29 << (findRemove.findRemove(29)?" was ":" was not " ) << "removed" << std::endl;

    std::cout << "Using find to look for 29 after removal.  Should not find" << std::endl;
    std::cout << 29 << (findRemove.find(29)?" was ":" was not " ) << "found" << std::endl;

    int last = findRemove.getLast();
    std::cout << "Testing find after deleteLast.  Should not find." << std::endl;
    findRemove.deleteLast();
    std::cout << last << (findRemove.find(last)?" was ":" was not " ) << "found" << std::endl;

    std::cout << "Ending array" << std::endl;
    std::cout << " expected: 2, 3, 5, 11, 13, 17, 19" << std::endl;
    std::cout << " actually: " << findRemove.listElements() << std::endl;

    std::cout << std::endl << std::endl;
#endif // TEST_FIND

#ifdef TEST_FIND_LARGEST
    const int LARGE_COUNT = 8;
    std::cout << "Testing find and findRemove " << std::endl << std::endl;

    ArrayInt findLarge;
    int large[LARGE_COUNT] = {3, 11, 19, 7, 5, 2, 13, 23};
    for(int i = 0; i < LARGE_COUNT; i++)
    {
        findLarge.append(large[i]);
    }

    std::cout << "Array contains " << findLarge.listElements() << std::endl;

    std::cout << "Largest should be 23 and is " << findLarge.findLargest() << std::endl;

    findLarge.removeLargest();
    findLarge.removeLargest();
    std::cout << "After removing two Largest " << std::endl;
    std::cout << "should be 3, 11, 7, 5, 2, 13" << std::endl;
    std::cout << "actually  " << findLarge.listElements() << std::endl;

    std::cout << "Emptying array" << std::endl;
    for(int i = 0; i < LARGE_COUNT - 2; i++)
    {
        findLarge.deleteLast();
    }

    std::cout << std::endl << "Now testing findLargest on empty array" << std::endl;
    try {
        findLarge.findLargest();
        std::cout << "Should have thrown an exception" << std::endl;
    }
    catch (std::out_of_range &ex) {
        std::cout << "Caught out of range with message: " << ex.what() << std::endl;
    }
    catch ( ... ) {
        std::cout << "Caught something weird " << std::endl;
    }

    std::cout << std::endl << "Now testing removeLargest on empty array" << std::endl;
    try {
        findLarge.removeLargest();
        std::cout << "Should have thrown an exception" << std::endl;
    }
    catch (std::out_of_range &ex) {
        std::cout << "Caught out of range with message: " << ex.what() << std::endl;
    }
    catch ( ... ) {
        std::cout << "Caught something weird " << std::endl;
    }

    std::cout << std::endl << std::endl;
#endif // TEST_FIND_LARGEST

#ifdef TEST_SET_GET
    std::cout << "Testing setting values and reading them back" << std::endl << std::endl;
    
    const int SET_COUNT = 12;
    ArrayInt setGet(SET_COUNT);
    std::cout << "Testing invalid setAt index storing -1 outside of array" << std::endl;
    try {
        setGet.setAt(-1, 12);
        std::cout << "Should have thrown an exception" << std::endl;
    }
    catch (std::out_of_range &ex) {
        std::cout << "Caught out of range with message: " << ex.what() << std::endl;
    }
    catch ( ... ) {
        std::cout << "Caught something weird " << std::endl;
    }
    
    std::cout << std::endl << "Now loading some values and displaying them" << std::endl;
    setGet.setAt(0, 3);
    setGet.setAt(2, 7);
    setGet.setAt(1, 5);
    setGet.setAt(4, 13);
    setGet.setAt(3, 11);
    setGet.setAt(6, 17);
    int maxSet = 6;

    std::cout << "The values should be:  3, 5, 7, 11, 13, unknown, 17" << std::endl;
    std::cout << "The values really are: ";
    for(int i = 0; i < maxSet; i++)
        std::cout << setGet.getAt(i) << ", ";
    std::cout << setGet.getAt(maxSet) << std::endl;
    
    std::cout << std::endl << "Testing invalid getAt index that is larger than array size" << std::endl;
    try {
        setGet.getAt(SET_COUNT + 1);
        std::cout << "Should have thrown an exception" << std::endl;
    }
    catch (std::out_of_range &ex) {
        std::cout << "Caught out of range with message: " << ex.what() << std::endl;
    }
    catch ( ... ) {
        std::cout << "Caught something weird " << std::endl;
    }
    
    std::cout << std::endl << "Now testing mixed sets and appends" << std::endl;
    std::cout << setGet.listElements() << std::endl; //AD
    setGet.append(27);
    std::cout << setGet.listElements() << std::endl; //AD
    setGet.setAt(maxSet+3, -1);
    std::cout << setGet.listElements() << std::endl;
    setGet.append(42);
    std::cout << setGet.listElements() << std::endl;
    std::cout << "After appends and sets " << std::endl;
    std::cout << " should be 3, 5, 7, 11, 13, unknown, 17, 27, unknown, -1, 42" << std::endl;
    std::cout << " actually  " << setGet.listElements() << std::endl;
    
    std::cout << std::endl << std::endl;
#endif  // TEST_SET_GET

#ifdef TEST_MIX
    std::cout << "Testing a mixture of appends, inserts, sets, and removes" << std::endl;
    
    ArrayInt mixed;
    
    mixed.append(2);
    mixed.append(4);
    mixed.append(6);
    mixed.setAt(5, 16);
    mixed.append(32);
    mixed.deleteLast();
    mixed.insertAt(4, 19);
    mixed.insertAt(4, INT_MAX);
    mixed.setAt(1, 7);
    mixed.append(64);
    mixed.append(256);
    mixed.removeAt(1);
    mixed.insertAt(1, 4);
    mixed.removeLargest();
    mixed.insertAt(5, 88);
    
    std::cout << "Displaying the results" << std::endl;
    std::cout << " Should be 2, 4, 6, unknown, 19, 88, unknown, 16, 64, 256" << std::endl;
    std::cout << " Really is " << mixed.listElements() << std::endl;
    
    std::cout << std::endl << "Done testing mixed " << std::endl << std::endl;
#endif //TEST_MIX

#ifdef TEST_THINK
    std::cout << "This location is for you to add your solution to the thinking problem" << std::endl;
    
    const int NUM_THINK = 10;
    int thinkValues[NUM_THINK] = {1, 3, 22, 18, 95, -1, 7, 0, 99, 4};

    ArrayInt Think;

    for(int i = 0; i < NUM_THINK; i++)
    {
        Think.append(thinkValues[i]);
    }
    
    std::cout << "Values in order should be 99, 95, 22, 18, 7, 4, 3, 1, 0, -1" << std::endl;

    std::cout << "Values actually are       ";

    for(int i = 0; i < NUM_THINK; i++)
    {
        int largest = Think.findLargest();
        Think.removeLargest();
        if (i == 9)
        {
            std::cout << largest;
        }else
        {
            std::cout << largest << ", ";
        }
    }

    std::cout << std::endl;
    
    std::cout <<std::endl << "Done with thinking test" << std::endl << std::endl;

#endif // TEST_THINK

    return 0;
}
