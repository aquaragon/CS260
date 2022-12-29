//
// Created by Aiden on 5/17/2022.
//

#ifndef MAIN_CPP_HEAP_HPP
#define MAIN_CPP_HEAP_HPP


class Heap {
private:
    static const int DEF_ARR_SIZE = 10;
    int * heap_array = nullptr;
    int count = 0;
    int array_size = 0;

    void resize();
    void BubbleUp(int child);
    void trickleDown(int root);

public:

    Heap(int n = DEF_ARR_SIZE);
    ~Heap();
    void addItem(int item);
    int getItem();
};


#endif //MAIN_CPP_HEAP_HPP
