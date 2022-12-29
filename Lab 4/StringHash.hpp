//
// Created by aiden on 4/21/2022.
//
#include <string>

using std::string;

#ifndef LAB_4_STRINGHASH_HPP
#define LAB_4_STRINGHASH_HPP




class StringHash {
private:
    static const int DEFAULT_SIZE = 11;
    const string EMPTY = "_empty_";
    const string DELETED = "_deleted_";

    int array_size = 0;
    string * string_hash = nullptr;
    int count = 0;


public:
    StringHash(int size = DEFAULT_SIZE);
    ~StringHash();
    int hashFunc(string key);
    void addItem(string value);
    bool findItem(string value);
    bool removeItem(string value);
    string displayTable();
    void resize();
};


#endif //LAB_4_STRINGHASH_HPP
