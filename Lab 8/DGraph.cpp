//
// Created by Aiden on 5/26/2022.
//

#include "DGraph.hpp"
#include <stdexcept>
#include <queue>
#include <string>

using std::out_of_range, std::queue, std::string;

DGraph::~DGraph()
{
    for (int index = 0; index < num_Nodes; index++)
    {
        Edge * ptr = nodeList[index]->adjacency;
        while(ptr != nullptr)
        {
            Edge * temp = ptr->next;
            delete ptr;
            ptr = temp;
        }
        delete nodeList[index];
    }
}

void DGraph::addNode(char name)
{
    if(num_Nodes >= SIZE)
    {
        throw out_of_range("Graph size exceeded");
    }

    Node * temp = new Node;
    temp->name = name;
    temp->visited = false;
    temp->adjacency = nullptr;

    nodeList[num_Nodes++] = temp;

}

bool DGraph::addEdge(char starts, char ends)
{
    if (starts == ends)
    {
        return false;
    }

    int startIndex = findNode(starts);
    int endIndex = findNode(ends);

    if (startIndex == -1 || endIndex == -1)
    {
        return false;
    }

    adjacencyMatrix[startIndex][endIndex] = true;


    Edge * startEnd = new Edge;
    startEnd->endIndex = endIndex;
    startEnd->next = nodeList[startIndex]->adjacency;
    nodeList[startIndex]->adjacency = startEnd;

    return true;
}

int DGraph::findNode(char name)
{
    for (int index = 0; index < num_Nodes; index++)
    {
        if(nodeList[index]->name == name)
        {
            return index;
        }
    }
    return -1;
}

string DGraph::listNodes()
{
    string theList = "The Nodes are: ";
    for (int index = 0; index < num_Nodes; index++)
    {
        theList += nodeList[index]->name;
        theList += " ";
    }
    return theList;
}

string DGraph::displayAdjacency()
{
    string buffer;
    buffer = "The Adjacency List is: \n";

    for (int index = 0; index < num_Nodes; index++)
    {
        buffer += nodeList[index]->name;
        buffer += ": ";

        Edge * ptr = nodeList[index]->adjacency;
        while (ptr != nullptr)
        {
            buffer += nodeList[ptr->endIndex]->name;
            buffer+= " ";
            ptr = ptr->next;
        }
        buffer += '\n';
    }
    return buffer;
}

string DGraph::displayMatrix()
{
    string buffer;
    buffer += "  ";
    for (int index = 0; index <num_Nodes; index++)
    {
        buffer += nodeList[index]->name;
        buffer += " ";
    }
    buffer += '\n';

    for(int index = 0; index < num_Nodes; index++)
    {
        buffer += nodeList[index]->name;
        buffer += " ";
        for (int j = 0; j < num_Nodes; j++)
        {
            if (adjacencyMatrix[index][j] == true)
            {
                buffer += "1";
            }else
            {
                buffer += "0";
            }
            buffer += " ";
        }
        buffer += '\n';
    }
    return buffer;
}

void DGraph::resetVisited()
{
    for (int index = 0; index < num_Nodes; index++)
    {
        nodeList[index]->visited = false;
    }
}

string DGraph::bF(char value, string breadth)
{
    breadth += value;
    breadth += ": ";

    queue<char> list;
    int index = findNode(value);
    nodeList[index]->visited = true;

    Edge * ptr = nodeList[index]->adjacency;
    while(ptr != nullptr)
    {
        nodeList[ptr->endIndex]->visited= true;
        list.push(nodeList[ptr->endIndex]->name);
        ptr = ptr->next;
    }

    while (!list.empty())
    {
        char name = list.front();
        index = findNode(name);
        breadth += name;
        breadth += " ";
        list.pop();

        ptr = nodeList[index]->adjacency;
        while(ptr != nullptr)
        {
            if(nodeList[ptr->endIndex]->visited != true)
            {
                nodeList[ptr->endIndex]->visited = true;
                list.push(nodeList[ptr->endIndex]->name);
            }
            ptr = ptr->next;
        }
    }

    return breadth;
}

string DGraph::breadthFirst(char value)
{
    string breadth;
    breadth = bF(value, breadth);
    breadth += unreachable(value);
    resetVisited();
    return breadth;
}

string DGraph::recDF(char name, string depth)
{

    nodeList[findNode(name)]->visited = true;
    depth += name;
    depth += " ";

    Edge * ptr = nodeList[findNode(name)]->adjacency;
    while (ptr != nullptr)
    {
        if(nodeList[ptr->endIndex]->visited == false)
        {
            depth = recDF(nodeList[ptr->endIndex]->name, depth);
        }
        ptr = ptr->next;
    }
    return depth;
}

string DGraph::depthFirst(char name)
{
    string depth;
    depth = recDF(name,depth);
    depth.insert(1, ":");
    depth += unreachable(name);
    resetVisited();
    return depth;
}

string DGraph::unreachable(char value)
{
    string unreachable;

    unreachable += "with ";

    int i = findNode(value) + 1;
    if(i > num_Nodes - 1)
    {
        i = 0;
    }
    while(i != findNode(value))
    {
        bool reached = false;
        int j = 0;
        while (reached == false && j < num_Nodes)
        {
            if(adjacencyMatrix[j][i] == true)
            {
                reached = true;
            }else
            {
                j++;
            }
        }
        if (reached == false)
        {
            unreachable += nodeList[i]->name;
            unreachable += " ";
        }
        i++;
        if(i > num_Nodes-1)
        {
            i = 0;
        }
    }

    unreachable += "unreachable";
    return unreachable;
}

string DGraph::minTree(char start)
{
    string mintree;
    string depth;
    depth = recDF(start, mintree);
    int edge = 0;
    int min_span = depth.size()/2;
    int node_location = 0;
    char node = start;
    char connect = depth[node_location+2];
    bool connects = false;
    while (edge < min_span - 1)
    {
        mintree += node;
        mintree += "-";
        Edge * ptr = nodeList[findNode(node)]->adjacency;
        while(ptr != nullptr && connects == false)
        {
            if(nodeList[ptr->endIndex]->name == connect)
            {
                connects = true;
                mintree += connect;
                mintree += " ";
                node_location += 2;
                node = depth[node_location];
                edge++;
                connect = depth[node_location+2];
            }else
            {
                ptr = ptr->next;
            }
        }
        if (connects == false)
        {
            node = depth[node_location -2];
            mintree = mintree.substr(0, mintree.length()-2);
        }
        connects = false;
    }
    string pre;
    pre = start;
    pre += ": ";
    mintree.insert(0,pre);
    resetVisited();
    return mintree;
}

string DGraph::connectTable()
{
    string table;
    for (int i = 0; i < num_Nodes; i++)
    {
        string list;
        list = bF(nodeList[i]->name, list);
        resetVisited();
        table += list;
        table += '\n';
    }
    return table;
}
