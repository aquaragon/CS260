//
// Created by aiden on 6/1/2022.
//

#include "WGraph.hpp"

#include <stdexcept>
#include <queue>
#include <stack>
#include <bits/stdc++.h>
#include <set>

using std::out_of_range, std::to_string, std::queue, std::stack, std::reverse, std::set;

WGraph::WGraph(int n)
{
    if (n < SIZE)
    {
        n = SIZE;
    }
    for(int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            adjacencyMatrix[i][j] = 0;
        }
    }
}

WGraph::~WGraph()
{
    for(int i = 0; i < numNodes; i++)
    {
        Edge * ptr = Nodelist[i]->adjacency;
        while(ptr != nullptr)
        {
            Edge * temp = ptr->next;
            delete ptr;
            ptr = temp;
        }
        delete Nodelist[i];
    }
}

void WGraph::addNode(char node_name)
{
    if(numNodes >= SIZE)
    {
        throw out_of_range("Graph array full");
    }
    Node * temp = new Node;
    temp->name = node_name;

    Nodelist[numNodes++] = temp;
}

int WGraph::findNode(char node_name)
{
    for (int index = 0; index < numNodes; index++)
    {
        if(Nodelist[index]->name == node_name)
        {
            return index;
        }
    }
    return -1;
}

void WGraph::addEdge(char node_start, char node_end, int weight)
{
    if(node_start == node_end)
    {
        return;
    }

    int starting = findNode(node_start);
    int ending = findNode(node_end);

    adjacencyMatrix[starting][ending] = weight;
    adjacencyMatrix[ending][starting] = weight;

    Edge * startEnd = new Edge;
    startEnd->weight = weight;
    startEnd->next = Nodelist[starting]->adjacency;
    startEnd->endIndex = ending;
    Nodelist[starting]->adjacency = startEnd;

    Edge * Endstart = new Edge;
    Endstart->weight = weight;
    Endstart->next = Nodelist[ending]->adjacency;
    Endstart->endIndex = starting;
    Nodelist[ending]->adjacency = Endstart;
}

string WGraph::listNodes()
{
    string list_of_nodes;
    for(int index = 0; index < numNodes; index++)
    {
        list_of_nodes += Nodelist[index]->name;
        list_of_nodes += " ";
    }
    return list_of_nodes;
}

string WGraph::displayAdjacency()
{
    string adjacency;

    for (int index = 0; index < numNodes; index++)
    {
        adjacency += Nodelist[index]->name;
        adjacency += ": ";

        Edge * ptr = Nodelist[index]->adjacency;
        while (ptr != nullptr)
        {
            adjacency += Nodelist[ptr->endIndex]->name;
            adjacency+= " ";
            ptr = ptr->next;
        }
        adjacency += '\n';
    }
    return adjacency;
}

string WGraph::displayMatrix()
{
    string matrix;
    matrix += "  ";
    for (int index = 0; index < numNodes; index++)
    {
        matrix += Nodelist[index]->name;
        matrix += "  ";
    }
    matrix += '\n';

    for(int index = 0; index < numNodes; index++)
    {
        matrix += Nodelist[index]->name;
        matrix += " ";
        for (int j = 0; j < numNodes; j++)
        {
            if(index == j)
            {
                matrix += "\\ ";
            }
            else if (adjacencyMatrix[index][j] > 0)
            {
                if(adjacencyMatrix[index][j] > 9)
                {
                    matrix += to_string(adjacencyMatrix[index][j]);
                }else
                {
                    matrix += to_string(adjacencyMatrix[index][j]);
                    matrix += " ";
                }

            }else
            {
                matrix += "X ";
            }
            matrix += " ";
        }
        matrix += '\n';
    }
    return matrix;
}

void WGraph::resetVisited()
{
    for (int index = 0; index < numNodes; index++)
    {
        Nodelist[index]->visited = false;
    }
}

string WGraph::unreachable()
{
    string unreach;
    unreach += "Unreached Node(s): ";
    for (int index = 0; index < numNodes; index++)
    {
        if(Nodelist[index]->visited == false)
        {
            unreach += Nodelist[index]->name;
            unreach += " ";
        }
    }
    resetVisited();
    return unreach;
}

string WGraph::breadthFirst(char node_name)
{
    string breadth;

    breadth += node_name;
    breadth += " ";

    queue<char> bf;
    int index = findNode(node_name);
    Nodelist[index]->visited = true;

    Edge * ptr = Nodelist[index]->adjacency;
    while(ptr != nullptr)
    {
        Nodelist[ptr->endIndex]->visited = true;
        bf.push(Nodelist[ptr->endIndex]->name);
        ptr = ptr->next;
    }

    while(!bf.empty())
    {
        char name = bf.front();
        index = findNode(name);
        breadth += name;
        breadth += " ";
        bf.pop();

        ptr = Nodelist[index]->adjacency;
        while (ptr != nullptr)
        {
            if (Nodelist[ptr->endIndex]->visited != true)
            {
                Nodelist[ptr->endIndex]->visited = true;
                bf.push(Nodelist[ptr->endIndex]->name);
            }
            ptr = ptr->next;
        }
    }
    breadth += unreachable();
    return breadth;
}

string WGraph::depthFirst(char node_name)
{
    string depth;

    int index = findNode(node_name);

    stack<char> df;
    df.push(node_name);

    Nodelist[index]->visited = true;

    Edge * ptr = Nodelist[index]->adjacency;
    while(!df.empty())
    {
        if(ptr != nullptr)
        {
            if(Nodelist[ptr->endIndex]->visited == false)
            {
                Nodelist[ptr->endIndex]->visited = true;
                df.push(Nodelist[ptr->endIndex]->name);
                ptr = Nodelist[ptr->endIndex]->adjacency;
            }
            else
            {
                ptr = ptr->next;
            }
        }else
        {
            ptr = Nodelist[findNode(df.top())]->adjacency;
            depth += df.top();
            depth += " ";
            df.pop();
        }
    }
    depth.resize(depth.length()-1);
    reverse(depth.begin(),depth.end());
    depth += " ";
    depth += unreachable();
    return depth;
}

string WGraph::minCostTree(char node_name)
{
    string mincost;
    mincost += node_name;
    mincost += ": ";

    int num_edge = 0;

    bool selected[numNodes];

    for(int i = 0; i < numNodes; i++)
    {
        selected[i] = false;
    }
    selected[findNode(node_name)] = true;

    while (num_edge < numNodes - 1)
    {
        int min = INT_MAX;
        int x = 0;
        int y = 0;
        for(int i = 0; i < numNodes; i++)
        {
            if(selected[i])
            {
                for(int j = 0; j < numNodes; j++)
                {
                    if(!selected[j] && adjacencyMatrix[i][j])
                    {
                        if (min > adjacencyMatrix[i][j])
                        {
                            min = adjacencyMatrix[i][j];
                            x = i;
                            y = j;
                        }
                    }
                }
            }
        }if(x != y)
        {
            mincost += Nodelist[x]->name;
            mincost += "-";
            mincost += Nodelist[y]->name;
            mincost += " ";
            selected[y] = true;
        }
        num_edge++;
    }
    mincost += "Unreached Node(s): ";
    for (int i = 0; i < numNodes; i++)
    {
        if(selected[i] == false)
        {
            mincost += Nodelist[i]->name;
            mincost += " ";
        }
    }
    return mincost;
}

int WGraph::minDis(int distance[], bool visited[])
{
    int minimum = INT_MAX, dist;

    for (int i = 0; i < numNodes; i++)
    {
        if(!visited[i] && distance[i] <= minimum)
        {
            minimum = distance[i];
            dist = i;
        }
    }
    return dist;
}

string WGraph::minCostPaths(char node_name)
{
    string minpath;

    bool visited[numNodes];
    int distance[numNodes];

    for (int i = 0; i < numNodes; i++)
    {
        distance[i] = INT_MAX;
        visited[i] = false;
    }

    distance[findNode(node_name)] = 0;

    for(int i = 0; i < numNodes; i++)
    {
        int min = minDis(distance,visited);
        visited[min] = true;
        for (int j = 0; j < numNodes; j++)
        {
            if(!visited[j] && adjacencyMatrix[min][j] && distance[min] != INT_MAX && distance[min] + adjacencyMatrix[min][j]<distance[j])
            {
                distance[j] = distance[min] +adjacencyMatrix[min][j];
            }
        }
    }
    for(int i = 0; i < numNodes; i++)
    {
        if(findNode(node_name) != i)
        {
            minpath += Nodelist[i]->name;
            minpath += "(";
            if(distance[i] == INT_MAX)
            {
                minpath += "inf";
            }
            else
            {
                minpath += to_string(distance[i]);
            }
            minpath += ") ";
        }
    }
    return minpath;
}