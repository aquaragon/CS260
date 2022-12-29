//
// Created by Aiden on 5/26/2022.
//

#ifndef LAB_8_DGRAPH_HPP
#define LAB_8_DGRAPH_HPP

#include <string>

using std::string;

struct Edge{
    int endIndex;
    Edge * next = nullptr;
}
;

struct Node{
    char name;
    bool visited;
    Edge * adjacency = nullptr;
};

class DGraph {
private:
    static const int SIZE = 20;
    int num_Nodes = 0;
    Node * nodeList[SIZE];
    bool adjacencyMatrix[SIZE][SIZE];

    int findNode(char name);
    void resetVisited();
    string recDF(char name, string depth);
    string bF(char name, string breadth);
    string unreachable(char value);


public:
    ~DGraph();
    void addNode(char name);
    bool addEdge(char starts, char ends);
    string listNodes();
    string displayAdjacency();
    string displayMatrix();
    string breadthFirst(char name);
    string depthFirst(char name);
    string minTree(char start);
    string connectTable();

};


#endif //LAB_8_DGRAPH_HPP
