//
//  display.cpp
//  ParseTree
//
//  Created by jim bailey on 4/28/22.
//

#include <string>
#include <sstream>
#include <iomanip>
#include <queue>

#include "ParseTree.hpp"

// display method for a binary tree
//   assumes that the values in a node are 3 chars or less
//   assumes that a node has a method to display its value as a string
std::string ParseTree::display()
{
    // arbitrary width of the display
    const int PAGE_WIDE = 64;
    
    // dummy placeholder for null leaves
    ParseNode * dummy = nullptr;
    
    // empty node output
    std::string emptyNode = ".";
    
    // define buffer to collect output
    std::stringstream buffer;
    
    // define queue (FIFO) to hold next layer's nodes
    std::queue<ParseNode *> theQueue;
    
    // boolean to keep track of when no nodes in layer
    bool more = true;
    
    // start with the root
    theQueue.push(root);
    
    // first layer has one node
    int curNodes = 1;
    
    // while there are nodes in the queue
    while (more)
    {
        more = false;
        
        // calculate the base offset
        int offset = PAGE_WIDE/(curNodes*2);

        // process the nodes in the layer
        for (int i = 0; i < curNodes; i++)
        {
            // get and remove front node
            ParseNode * ptr = theQueue.front();
            theQueue.pop();
            
            // all offsets after the first are doubled
            if (i == 1)
            {
                offset *= 2;
            }
                
            // if not a dummy node process it
            if (ptr != dummy)
            {
                // add contents to buffer
                buffer << std::setw(offset) << ptr->getValue();
                
                // if there is a left child, add to fifo
                if (ptr->getLeft())
                {
                    more = true;
                    theQueue.push(ptr->getLeft());
                }
                // no left child, add dummy in its place
                else
                {
                    theQueue.push(dummy);
                }
                
                // if right child, add to fifo
                if (ptr->getRight())
                {
                    more = true;
                    theQueue.push(ptr->getRight());
                }
                // no right child, add dummy in its place
                else
                {
                    theQueue.push(dummy);
                }
            }
            
            // this node was a dummy
            //  output the emptyNode symbol
            //  add two dummies to FIFO for children placeholders
            else
            {
                buffer << std::setw(offset) << emptyNode;
                theQueue.push(dummy);
                theQueue.push(dummy);
            }
        }
        curNodes *= 2;
        buffer << std::endl;
    }
           
    return buffer.str();
}
