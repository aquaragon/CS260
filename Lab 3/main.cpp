//
//  main.cpp
//  TextClass
//
//  Created by jim bailey on 4/14/21.
//

#include <iostream>
#include "TextClass.hpp"

// basic tests
#define TEST_HEAD
#define TEST_TAIL
#define TEST_QUEUE
#define TEST_DISPLAY
#define TEST_FIND
#define TEST_FIND_REMOVE

// advanced tests
#define TEST_APPEND
#define TEST_FIND_NEXT
#define TEST_REMOVE_LAST
#define TEST_INSERT_LAST
#define TEST_MIXED

// thinking test
#define THINK_TEST

int main() {

// basic tests
#ifdef TEST_HEAD
    std::cout << "Testing adding and removing from head\n" << std::endl;
    const int ADD_HEAD = 5;
    char heads[ADD_HEAD] = {'a','b','c','d','e'};
    
    TextClass head;
    std::cout << "Adding five letters to head of list" << std::endl;
    for (int i = 0; i < ADD_HEAD; i++)
    {
        head.addHead(heads[i]);
    }
    std::cout << " removing and displaying them" << std::endl;
    std::cout << " expected e d c b a" << std::endl;
    std::cout << " actually ";
    for (int i = 0; i < ADD_HEAD; i++)
    {
        std::cout << head.getHead() << " ";
        head.removeHead();
    }
    std::cout << "\n" << std::endl;
    
    std::cout << "Now reading an extra value " << std::endl;
    try {
        head.getHead();
        std::cout << " should have thrown an exception" << std::endl;
    }
    catch (std::out_of_range &ex) {
        std::cout << "Caught out_of_range saying " << ex.what() << std::endl;
    }
    catch ( ... ) {
        std::cout << "Caught something unexpected" << std::endl;
    }
    
    std::cout << "Done testing adding and removing from head\n" << std::endl;
#endif // TEST_HEAD

#ifdef TEST_TAIL
    std::cout << "Testing adding and removing from tail\n" << std::endl;
    const int ADD_TAIL = 5;
    char tails[ADD_TAIL] = {'z','y','x','w','v'};
    
    TextClass tail;
    std::cout << "Adding five letters to tail of list" << std::endl;
    for (int i = 0; i < ADD_TAIL; i++)
    {
        tail.addTail(tails[i]);
    }
    std::cout << " removing and displaying them" << std::endl;
    std::cout << " expected v w x y z" << std::endl;
    std::cout << " actually ";
    for (int i = 0; i < ADD_TAIL; i++)
    {
        std::cout << tail.getTail() << " ";
        tail.removeTail();
    }
    std::cout << "\n" << std::endl;
    
    std::cout << "Now getting an extra value " << std::endl;
    try {
        tail.getTail();
        std::cout << " should have thrown an exception" << std::endl;
    }
    catch (std::out_of_range &ex) {
        std::cout << "Caught out_of_range saying " << ex.what() << std::endl;
    }
    catch ( ... ) {
        std::cout << "Caught something unexpected" << std::endl;
    }
    
    std::cout << "Done testing adding and removing from tail\n" << std::endl;
#endif // TEST_TAIL

#ifdef TEST_QUEUE
    std::cout << "Testing queue both ways\n" << std::endl;
    const int FIFO = 5;
    char headFifo[FIFO] = {'A', 'C', 'E', 'G', 'I'};
    char tailFifo[FIFO] = {'M', 'N', 'O', 'P', 'Q'};
    
    TextClass fifo1;
    std::cout << "Adding five letters to tail of list" << std::endl;
    for (int i = 0; i < FIFO; i++)
    {
        fifo1.addTail(headFifo[i]);
    }
    std::cout << " removing from head and displaying them" << std::endl;
    std::cout << " expected A C E G I" << std::endl;
    std::cout << " actually ";
    for (int i = 0; i < FIFO; i++)
    {
        std::cout << fifo1.getHead() << " ";
        fifo1.removeHead();
    }
    std::cout << "\n" << std::endl;
    
    TextClass fifo2;
    std::cout << "Adding five letters to head of list" << std::endl;
    for (int i = 0; i < FIFO; i++)
    {
        fifo2.addHead(tailFifo[i]);
    }
    std::cout << " removing from tail and displaying them" << std::endl;
    std::cout << " expected M N O P Q" << std::endl;
    std::cout << " actually ";
    for (int i = 0; i < FIFO; i++)
    {
        std::cout << fifo2.getTail() << " ";
        fifo2.removeTail();
    }
    std::cout << "\n" << std::endl;
    
    std::cout << "Done testing queue both ways\n" << std::endl;
#endif //  TEST_QUEUE

#ifdef TEST_DISPLAY
    std::cout << "Testing display list\n" << std::endl;
    const int DISPLAY = 6;
    char displays[DISPLAY] = {'s', 'p', 'r', 'u', 'c', 'e'};

    
    TextClass display;
    std::cout << "Adding six letters to tail of list" << std::endl;
    for (int i = 0; i < DISPLAY; i++)
    {
        display.addTail(displays[i]);
    }
    std::cout << " displaying them head to tail" << std::endl;
    std::cout << " expected s p r u c e" << std::endl;
    std::cout << " actually " << display.displayList() << "\n" << std::endl;
    
    std::cout << "Done testing display list\n" << std::endl;
#endif // TEST_DISPLAY

#ifdef TEST_FIND
    std::cout << "Testing find\n" << std::endl;
    const int FIND = 5;
    char vowels[FIND] = {'a', 'e', 'i', 'o', 'u'};

    TextClass findTail;
    std::cout << "Adding five vowels to tail of a list" << std::endl;
    for (int i = 0; i < FIND; i++)
    {
        findTail.addTail(vowels[i]);
    }
    std::cout << " displaying them" << std::endl;
    std::cout << " expected a e i o u" << std::endl;
    std::cout << " actually " << findTail.displayList() << std::endl;
    
    std::cout << "  e " << (findTail.find('e')?"is":"is not") << " there" << std::endl;
    std::cout << "  x " << (findTail.find('x')?"is":"is not") << " there" << std::endl << std::endl;
    
    TextClass findHead;
    std::cout << "Adding five vowels to head of a list" << std::endl;
    for (int i = 0; i < FIND; i++)
    {
        findHead.addHead(vowels[i]);
    }
    std::cout << " displaying them" << std::endl;
    std::cout << " expected u o i e a" << std::endl;
    std::cout << " actually " << findHead.displayList() << std::endl;
    
    std::cout << "  a " << (findHead.find('a')?"is":"is not") << " there" << std::endl;
    std::cout << "  r " << (findHead.find('r')?"is":"is not") << " there" << std::endl << std::endl;
    
    std::cout << "Done testing find\n" << std::endl;
#endif // TEST_FIND

#ifdef TEST_FIND_REMOVE
    std::cout << "Testing find and remove\n" << std::endl;
    const int FIND_REM = 5;
    char digits[FIND_REM] = {'1', '3', '5', '7', '9'};

    TextClass findRem;
    std::cout << "Adding five digits to tail of a list" << std::endl;
    for (int i = 0; i < FIND_REM; i++)
    {
        findRem.addTail(digits[i]);
    }
    std::cout << " displaying them" << std::endl;
    std::cout << " expected 1 3 5 7 9" << std::endl;
    std::cout << " actually " << findRem.displayList() << std::endl;
    
    std::cout << "  3 " << (findRem.findRemove('3')?"is":"is not") << " there" << std::endl;
    std::cout << "  6 " << (findRem.findRemove('6')?"is":"is not") << " there" << std::endl;
    
    std::cout << " displaying them after remove" << std::endl;
    std::cout << " expected 1 5 7 9" << std::endl;
    std::cout << " actually " << findRem.displayList() << std::endl << std::endl;
    
    std::cout << "Now testing find/remove head and tail" << std::endl;
    std::cout << "  1 " << (findRem.findRemove('1')?"is":"is not") << " there" << std::endl;
    std::cout << "  9 " << (findRem.findRemove('9')?"is":"is not") << " there" << std::endl;
    std::cout << " displaying them after remove" << std::endl;
    std::cout << " expected 5 7" << std::endl;
    std::cout << " actually " << findRem.displayList() << std::endl << std::endl;
    
    std::cout << "Done testing find and remove\n" << std::endl;
#endif // TEST_FIND_REMOVE

// advanced tests
#ifdef TEST_APPEND
    std::cout << "Testing appending a list\n" << std::endl;
    const int APPEND1 = 6;
    const int APPEND2 = 7;
    int counter = 0;
    char appendVals[APPEND1 + APPEND2] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm'};
    
    TextClass first;
    for (int i = 0; i < APPEND1; i++)
    {
        first.addTail(appendVals[counter]);
        counter++;
    }
    TextClass second;
    for (int i = 0; i < APPEND2; i++)
    {
        second.addTail(appendVals[counter]);
        counter++;
    }
    
    std::cout << "First list is " << first.displayList() << std::endl;
    std::cout << "Second list is " << second.displayList() << std::endl;
    
    first.append(second);
    std::cout << "First should now be a b c d e f g h i j k l m" << std::endl;
    std::cout << " and it actually is " << first.displayList() << std::endl;
    
    std::cout << "Done appending a list\n" << std::endl;
#endif // TEST_APPEND

#ifdef TEST_FIND_NEXT
    std::cout << "Testing find next\n" << std::endl;
    const int FIND_NEXT = 5;
    char nextVals[FIND_NEXT] = {'a', 'p', 'p', 'l', 'e'};
    
    TextClass nextFind;
    for (int i = 0; i < FIND_NEXT; i++)
    {
        nextFind.addTail(nextVals[i]);
    }
    
    std::cout << "List contains " << nextFind.displayList() << std::endl;
    std::cout << "Looking for a, e, p, p, k, a" << std::endl;
    std::cout << " a " << (nextFind.findNext('a')?"found":"not found") << std::endl;
    std::cout << " e " << (nextFind.findNext('e')?"found":"not found") << std::endl;
    std::cout << " p " << (nextFind.findNext('p')?"found":"not found") << std::endl;
    std::cout << " p " << (nextFind.findNext('p')?"found":"not found") << std::endl;
    std::cout << " k " << (nextFind.findNext('k')?"found":"not found") << std::endl;
    std::cout << " a " << (nextFind.findNext('a')?"found":"not found") << std::endl;
    
    std::cout << "Done testing find next\n" << std::endl;
#endif // TEST_FIND_NEXT

#ifdef TEST_REMOVE_LAST
    std::cout << "Testing remove last\n" << std::endl;
    const int REM_LAST = 7;
    char removeVals[REM_LAST] = {'b','e','a','r','d','e','d'};
    
    TextClass remLast;
    for (int i = 0; i < REM_LAST; i++)
    {
        remLast.addTail(removeVals[i]);
    }
    
    std::cout << "List contains " << remLast.displayList() << std::endl;
    std::cout << "Looking to remove first d after wrapping" << std::endl;
    std::cout << " first d " << (remLast.findNext('d')?"found":"not found") << std::endl;
    std::cout << " second d " << (remLast.findNext('d')?"found":"not found") << std::endl;
    std::cout << " first d again " << (remLast.findNext('d')?"found":"not found") << std::endl;
    remLast.removeLast();
    std::cout << "List should now be b e a r e d" << std::endl;
    std::cout << " and it is " << remLast.displayList() << std::endl;
    std::cout << "Looking to remove second e" << std::endl;
    std::cout << " e " << (remLast.findNext('e')?"found":"not found") << std::endl;
    std::cout << " e " << (remLast.findNext('e')?"found":"not found") << std::endl;
    remLast.removeLast();
    std::cout << "Doing an extra remove, should do nothing" << std::endl;
    remLast.removeLast();
    std::cout << "Displaying after removes" << std::endl;
    std::cout << " expected b e a r d" << std::endl;
    std::cout << " actually " << remLast.displayList() << std::endl << std::endl;
    
    std::cout << "Done testing remove last\n" << std::endl;
#endif // TEST_REMOVE_LAST

#ifdef TEST_INSERT_LAST
    std::cout << "Testing insert last\n" << std::endl;
    const int INSERT_LAST = 4;
    char insertVals[INSERT_LAST] = {'1', '3', '7', '9'};
    
    TextClass insLast;
    for (int i = 0; i < INSERT_LAST; i++)
    {
        insLast.addTail(insertVals[i]);
    }
    
    std::cout << "List contains " << insLast.displayList() << std::endl;
    std::cout << "Looking to insert 4, 5, and 6 in sequence" << std::endl;
    std::cout << " first finding 7 " << (insLast.findNext('7')?"found":"not found") << std::endl;
    insLast.insertLast('5');
    insLast.insertLast('6');
    std::cout << " now finding 5 "<< (insLast.findNext('5')?"found":"not found") << std::endl;
    insLast.insertLast('4');
    std::cout << " displaying result, expected 1 3 4 5 6 7 9" << std::endl;
    std::cout << " actually have " << insLast.displayList() << std::endl << std::endl;
    
    std::cout << "Done testing insert last\n" << std::endl;
#endif // TEST_INSERT_LAST

#ifdef TEST_MIXED
    std::cout << "Testing mixed inserts and deletes\n" << std::endl;
    const int MIX = 3;
    const int MIXED = 4;
    char mixLetters[MIX] = {'c', 'a', 'w'};
    
    TextClass mixed;
    for (int i = 0; i < MIX; i++)
    {
        mixed.addTail(mixLetters[i]);
    }
    
    std::cout << "List starts with " << mixed.displayList() << std::endl;
    std::cout << " replacing a with o and adding r" << std::endl;
    mixed.findNext('a');
    mixed.insertLast('o');
    mixed.removeLast();
    mixed.findNext('o');
    mixed.insertLast('r');
    std::cout << " caw should now be crow " << std::endl;
    std::cout << " and it is ";
    for(int i = 0; i < MIXED; i++)
    {
        std::cout << mixed.getHead();
        mixed.removeHead();
    }
    std::cout << "\n" << std::endl;
    
    std::cout << "Done testing mixed insers and deletes\n" << std::endl;
#endif // TEST_MIXED

// thinking test
#ifdef THINK_TEST
    std::cout << "Testing thinking solution\n" << std::endl;
    const int CAT = 13;
    const int DOG = 13;
    char catLetters[CAT] = {'T','h','i','s',' ','i','s',' ','a',' ','c','a','t'};
    char dogLetters[DOG] = {'T','h','i','s',' ','i','s',' ','a',' ','d','o','g'};
    
    // create two TextClass objects, one with catLetters and one with dogLetters
    // append the dogLetters list to the catLetters list and edit the result
    // when done display the two lists
    TextClass cat;
    TextClass dog;

    for (int i = 0; i < CAT; i++)
    {
        cat.addTail(catLetters[i]);
    }

    for (int i = 0; i < DOG; i++)
    {
        dog.addTail(dogLetters[i]);
    }

    std::cout << std::endl;

    cat.append(dog);

    cat.findNext('T');
    cat.findNext('T');
    cat.insertLast(' ');
    cat.insertLast('a');
    cat.insertLast('n');
    cat.insertLast('d');
    cat.insertLast(' ');
    cat.insertLast('t');
    cat.removeLast();

    cat.findNext('s');
    cat.findNext('s');
    cat.findNext('s');
    cat.insertLast('t');
    cat.removeLast();

    cat.findNext('i');
    cat.findNext('i');
    cat.findNext('i');
    cat.insertLast('a');
    cat.removeLast();
    
    std::cout << "Expected catList output: This is a cat and that is a dog" << std::endl;

    std::cout << "Actual catList output:   ";

    while(!cat.isEmpty())
    {
        std::cout << cat.getHead();
        cat.removeHead();
    }

    std::cout << std::endl;

    std::cout << "Expected dogList output: This is a dog" << std::endl;

    std::cout << "Actual dogList output:   ";

    while(!dog.isEmpty())
    {
        std::cout << dog.getHead();
        dog.removeHead();
    }

    std::cout << std::endl;
    
    std::cout << "Done testing thinking solution\n" << std::endl;
#endif // THINK_TEST

    return 0;
}