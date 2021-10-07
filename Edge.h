#ifndef EDGE_H
#define EDGE_H

#include "Node.h"
class Node;

class Edge
{
    public:
        Edge();
        Edge(int in_id, Node *in_node1, Node *in_node2, double in_length);
        string toString();
        bool contains(Node *n);
        Node otherThan(Node *n);
        int Edge_id;
        Node *node1;
        Node *node2;
        double edge_length;
        
};
#endif