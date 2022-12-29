//
// Created by aiden on 6/1/2022.
//

#ifndef LAB_9_WGRAPH_HPP
#define LAB_9_WGRAPH_HPP

#include <string>

using std::string;

struct Edge{
    int startIndex;
    int endIndex;

    int weight;

    Edge * next = nullptr;
};

struct Node{
    char name;
    Edge * adjacency = nullptr;
    bool visited = false;

};

class WGraph {
private:
    static const int SIZE = 10;
    int numNodes = 0;
    Node * Nodelist[SIZE];
    int adjacencyMatrix[SIZE][SIZE];

    int findNode(char node_name);
    string unreachable();
    void resetVisited();
    int minDis(int distance[], bool visited[]);

public:
    WGraph(int n = SIZE);
    ~WGraph();
    void addNode(char node_name);
    void addEdge(char node_start, char node_end, int weight);
    string listNodes();
    string displayAdjacency();
    string displayMatrix();
    string breadthFirst(char node_name);
    string depthFirst(char node_name);
    string minCostTree(char node_name);
    string minCostPaths(char node_name);


};


#endif //LAB_9_WGRAPH_HPP
