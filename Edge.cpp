#include <iostream>
#include <math.h>
using namespace std;

#include "env.h"
#include "Edge.h"
#include "Node.h"

Edge::Edge(){}
Edge::Edge(int in_id, Node *in_node1, Node *in_node2, double in_length)
{
    this->Edge_id = in_id;
    this->node1 = in_node1;
    this->node2 = in_node2;
    this->edge_length = in_length;
}
string Edge::toString()
{
    return "E#"+to_string(Edge_id)+" ("+to_string(node1->node_id)+","+to_string(node2->node_id)+") length: "+to_string(edge_length);
}
bool Edge::contains(Node *n)
{
    if(n == this->node1 || n == this->node2)
    {
        return true;
    }
    return false;
}
Node Edge::otherThan(Node *n)
{
    if(n == this->node1)
    {
        return *this->node2;
    }   
    else if(n == this->node2)
    {
        return *this->node1;
    }
}