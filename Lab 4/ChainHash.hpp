//
// Created by Aiden on 4/25/2022.
//

#ifndef LAB_4_CHAINHASH_HPP
#define LAB_4_CHAINHASH_HPP

#include <string>

using std::string;

class ChainLink {
private:
    string value = "";
    ChainLink * next;

public:
    ChainLink(string value, ChainLink * next = nullptr);
    string getValue();
    ChainLink * getNext();
    void setNext(ChainLink * next);
};

class ChainHash {
private:
    static const int ADV_DEFAULT_SIZE = 7;
    const string EMPTY = "_empty_";
    int prime_nums [10] = {13,29,59,127,257,521,1049,2099,4201,7919};

    int adv_array_size = 0;
    ChainLink ** adv_array;
    int count = 0;

public:
    ChainHash(int size = ADV_DEFAULT_SIZE);
    ~ChainHash();
    bool isEmpty(int index);
    void removeHead(int index);
    int hashFunc(string key);
    void addItem(string value);
    bool findItem(string value);
    void removeItem(string value);
    string displayTable();
    void resizeChain();
};




#endif //LAB_4_CHAINHASH_HPP
