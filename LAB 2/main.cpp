//
//  main.cpp
//  deque
//
//  Created by jim bailey on 4/8/21.
//

#include <iostream>
#include <stdexcept>
#include "Deque.hpp"

#define QUEUE_TEST
#define RESIZE_TEST
#define LIST_TEST
#define ADD_HEAD_TEST
#define REMOVE_TAIL_TEST
#define REV_QUEUE_TEST
#define MIX_TEST
#define THINK_TEST

int main()
{
    int num = 0;
#ifdef QUEUE_TEST
    const int NUM_QUEUE = 8;
    Deque queue;

    std::cout << "Testing basic queue, addTail, removeHead, isEmpty\n" << std::endl;

    std::cout << "Adding eight odd integers to FIFO" << std::endl;
    for (int i = 0; i < NUM_QUEUE; i++)
    {
        queue.addTail(2 * num + 1);
        num += 1;
    }

    std::cout << "Expected 1 3 5 7 9 11 13 15" << std::endl;
    std::cout << "Actually ";
    for (int i = 0; i < NUM_QUEUE; i++)
    {
        std::cout << queue.removeHead() << " ";
    }
    std::cout << std::endl;

    std::cout << "\nFIFO should be empty" << std::endl;
    std::cout << "FIFO " << (queue.isEmpty()?"is ":"is not ") << "empty" << std::endl;

    std::cout << "\nDone with basic test\n" << std::endl;
#endif // QUEUE_TEST

#ifdef RESIZE_TEST
    const int NUM_RESIZE = 8;
    const int NUM_RESIZE_EXTRA = 4;
    Deque resize(NUM_RESIZE);
    num = 0;

    std::cout << "Testing resizing queue, addTail, removeHead\n" << std::endl;

    std::cout << "Adding eight odd integers to FIFO" << std::endl;
    for (int i = 0; i < NUM_RESIZE; i++)
    {
        resize.addTail(2 * num + 1);
        num += 1;
    }
    std::cout << "Removing four to cause wrap" << std::endl;
    std::cout << "Expected 1 3 5 7" << std::endl;
    std::cout << "Actually ";
    for (int i = 0; i < NUM_RESIZE_EXTRA; i++)
    {
        std::cout << resize.removeHead() << " ";
    }
    std::cout << std::endl;

    std::cout << "\nAdding four more for wrapping" << std::endl;
    for (int i = 0; i < NUM_RESIZE_EXTRA; i++)
    {
        resize.addTail(2 * num + 1);
        num += 1;
    }

    std::cout << "Dumping the array " << std::endl;
    std::cout << "Expected 17 19 21 23 9 11 13 15" << std::endl;
    std::cout << "Actually " << resize.dumpArray() << std::endl;

    std::cout << "\nNow adding eight more" << std::endl;
    for (int i = 0; i < NUM_RESIZE; i++)
    {
        resize.addTail(2 * num + 1);
        num += 1;
    }
    std::cout << "Expected 9 11 13 15 17 19 21 23 25 27 29 31 33 35 37 39" << std::endl;
    std::cout << "Actually " << resize.dumpArray() << std::endl;

    std::cout << "\nDone with resize test\n" << std::endl;
#endif // RESIZE_TEST

#ifdef LIST_TEST
    const int NUM_LIST = 7;
    const int NUM_LIST_EXTRA = 5;
    Deque list(NUM_LIST+1);
    int listValues[NUM_LIST+NUM_LIST_EXTRA] = {1, 3, 6, 10, 15, 21, 28, 36, 45, 55, 66, 78};
    num = 0;

    std::cout << "Testing listQueue, addTail, removeHead\n" << std::endl;

    std::cout << "Adding seven values to FIFO" << std::endl;
    for (int i = 0; i < NUM_LIST; i++)
    {
        list.addTail(listValues[num]);
        num += 1;
    }

    std::cout << "Testing list" << std::endl;
    std::cout << "Expected 1 3 6 10 15 21 28" << std::endl;
    std::cout << "Actually " << list.listQueue() << std::endl;

    std::cout << "\nRemoving five to cause wrap" << std::endl;
    std::cout << "Expected 1 3 6 10 15" << std::endl;
    std::cout << "Actually ";
    for (int i = 0; i < NUM_LIST_EXTRA; i++)
    {
        std::cout << list.removeHead() << " ";
    }
    std::cout << std::endl;

    std::cout << "\nAdding five more for wrapping" << std::endl;
    for (int i = 0; i < NUM_LIST_EXTRA; i++)
    {
        list.addTail(listValues[num]);
        num += 1;
    }

    std::cout << "Testing list after wrap" << std::endl;
    std::cout << "Expected 21 28 36 45 55 66 78" << std::endl;
    std::cout << "Actually " << list.listQueue() << std::endl;

    std::cout << "\nDone with testing listQueue\n" << std::endl;

#endif // LIST_TEST

#ifdef ADD_HEAD_TEST
    const int NUM_HEAD = 7;
    Deque head;
    int headValues[NUM_HEAD] = {3, 5, 7, 11, 13, 17, 19};

    std::cout << "Testing addHead\n" << std::endl;

    std::cout << "Adding seven values to head" << std::endl;
    for (int i = 0; i < NUM_HEAD; i++)
    {
        head.addHead(headValues[i]);
    }

    std::cout << "Now removing from head" << std::endl;
    std::cout << "Expected 19 17 13 11 7 5 3" << std::endl;
    std::cout << "Actually ";
    for (int i = 0; i < NUM_HEAD; i++)
    {
        std::cout << head.removeHead() << " ";
    }
    std::cout << std::endl;

    std::cout << "\nDone with testing addHead\n" << std::endl;

#endif // ADD_HEAD_TEST

#ifdef REMOVE_TAIL_TEST
    const int NUM_TAIL = 6;
    Deque tail;
    int tailValues[NUM_TAIL] = {1, 2, 4, 8, 16, 32};

    std::cout << "Testing removeTail\n" << std::endl;

    std::cout << "Adding six values to tail" << std::endl;
    for (int i = 0; i < NUM_TAIL; i++)
    {
        tail.addTail(tailValues[i]);
    }

    std::cout << "Now removing from tail" << std::endl;
    std::cout << "Expected 32 16 8 4 2 1" << std::endl;
    std::cout << "Actually ";
    for (int i = 0; i < NUM_TAIL; i++)
    {
        std::cout << tail.removeTail() << " ";
    }
    std::cout << std::endl;

    std::cout << "\nDone with testing removeTail\n" << std::endl;
#endif // REMOVE_TAIL_TEST

#ifdef REV_QUEUE_TEST
    const int NUM_REV_QUEUE = 8;
    const int NUM_REV_ADD = 4;
    Deque revQueue(NUM_REV_QUEUE);
    num = 0;

    std::cout << "Testing reverse FIFO, addHead, removeTail, isEmpty\n" << std::endl;

    std::cout << "Adding eight even integers to FIFO" << std::endl;
    for (int i = 0; i < NUM_REV_QUEUE; i++)
    {
        revQueue.addHead(2 * num);
        num += 1;
    }

    std::cout << "Removing four before wrapping"<< std::endl;

    std::cout << "Expected 0 2 4 6" << std::endl;
    std::cout << "Actually ";
    for (int i = 0; i < NUM_REV_ADD; i++)
    {
        std::cout << revQueue.removeTail() << " ";
    }
    std::cout << std::endl;

    std::cout << "\nAdding four more to force wrap" << std::endl;
    for (int i = 0; i < NUM_REV_ADD; i++)
    {
        revQueue.addHead(2 * num);
        num += 1;
    }

    std::cout << "Now dumping array" << std::endl;
    std::cout << "Expected 14 12 10 8 22 20 18 16" << std::endl;
    std::cout << "Actually " << revQueue.dumpArray() << std::endl;

    std::cout << "\nNow adding eight more to force resize" << std::endl;
    for (int i = 0; i < NUM_REV_QUEUE; i++)
    {
        revQueue.addHead(2 * num);
        num += 1;
    }
    std::cout << "Now dumping array" << std::endl;
    std::cout << "Expected 22 20 18 16 14 12 10 8 38 36 34 32 30 28 26 24" << std::endl;
    std::cout << "Actually " << revQueue.dumpArray() << std::endl;

    std::cout << "\nNow using removeTail to empty array" << std::endl;
    std::cout << "Expected 8 10 12 14 16 18 20 22 24 26 28 30 32 34 36 38" << std::endl;
    std::cout << "Actually ";
    for (int i = 0; i < NUM_REV_QUEUE*2; i++)
    {
        std::cout << revQueue.removeTail() << " ";
    }
    std::cout << std::endl;

    std::cout << "\nFIFO should be empty" << std::endl;
    std::cout << "FIFO " << (revQueue.isEmpty()?"is ":"is not ") << "empty" << std::endl;

    std::cout << "\nDone with reverse FIFO tests\n" << std::endl;
#endif //REV_QUEUE_TEST

#ifdef MIX_TEST
    const int NUM_MIX = 3;
    Deque mixQueue(NUM_MIX * 2);
    num = 0;
    std::cout << "Testing reverse mix of adds and removes\n" << std::endl;

    std::cout << "Adding three odd integers to tail" << std::endl;
    for (int i = 0; i < NUM_MIX; i++)
    {
        mixQueue.addTail(2 * num + 1);
        num += 1;
    }
    std::cout << "Adding three even numbers to head" << std::endl;
    for (int i = 0; i < NUM_MIX; i++)
    {
        mixQueue.addHead(2 * num);
        num += 1;
    }
    std::cout << "Dumping array " << std::endl;
    std::cout << "Expected 1 3 5 10 8 6" << std::endl;
    std::cout << "Actually " << mixQueue.dumpArray() << std::endl;

    std::cout << "\nAdding three more to tail to force resize" << std::endl;
    for (int i = 0; i < NUM_MIX; i++)
    {
        mixQueue.addTail(2 * num + 1);
        num += 1;
    }
    std::cout << "Adding three more to head to fill array" << std::endl;
    for (int i = 0; i < NUM_MIX; i++)
    {
        mixQueue.addHead(2 * num);
        num += 1;
    }
    std::cout << "Dumping array " << std::endl;
    std::cout << "Expected 10 8 6 1 3 5 13 15 17 22 20 18" << std::endl;
    std::cout << "Actually " << mixQueue.dumpArray() << std::endl;

    std::cout << "\nNow removing from Tail " << std::endl;
    std::cout << "Expected 17 15 13 5 3 1" << std::endl;
    std::cout << "Actually ";
    for(int i = 0; i < NUM_MIX*2; i++)
    {
        std::cout << mixQueue.removeTail() << " ";
    }
    std::cout << std::endl;

    std::cout << "\nNow removing from Head " << std::endl;
    std::cout << "Expected 22 20 18 10 8 6" << std::endl;
    std::cout << "Actually ";
    for(int i = 0; i < NUM_MIX*2; i++)
    {
        std::cout << mixQueue.removeHead() << " ";
    }
    std::cout << std::endl;

    std::cout << "\nCalling removeHead from empty FIFO" << std::endl;
    try {
        mixQueue.removeHead();
        std::cout << "Failed to throw exception" << std::endl;
    }
    catch (std::out_of_range &ex) {
        std::cout << "Caught out_of_range with message " << ex.what() << std::endl;
    }
    catch ( ... ) {
        std::cout << "Caught something else " << std::endl;
    }
    std::cout << "\nCalling removeTail from empty FIFO" << std::endl;
    try {
        mixQueue.removeTail();
        std::cout << "Failed to throw exception" << std::endl;
    }
    catch (std::out_of_range &ex) {
        std::cout << "Caught out_of_range with message " << ex.what() << std::endl;
    }
    catch ( ... ) {
        std::cout << "Caught something else " << std::endl;
    }

    std::cout << "\nDone with mixed tests\n" << std::endl;
#endif // MIX_TEST

#ifdef THINK_TEST
    std::cout << "This location is for you to add your solution to the thinking problem" << std::endl;

    const int NUM_THINK = 5;
    int thinkValues[NUM_THINK] = {2, 3, 5, 7, 11};
    Deque think;

    for(int i = (NUM_THINK - 1); i >= 0; i--)
    {
        think.addTail(thinkValues[i]);
    }

    std::cout << "Values in reverse order should be 11 7 5 3 2" << std::endl;
    std::cout << "Values in reverse order really is " << think.listQueue() << std::endl;

    std::cout <<std::endl << "Done with thinking test" << std::endl << std::endl;


#endif //THINK_TEST

    return 0;
}