#ifndef NODE_H
#define NODE_H

#include "Link.h"
#include <vector>
class Link;

class Node
{
    public:
        Node();
        Node(int in_id,int in_x,int in_y,int in_num_Qubits);
        bool attemptSwapping(Link *link1,Link *link2);
        string toString();
        bool operator==(const Node &)const;
        vector<Link>Links;
        vector<pair<Link,Link>>internalLinks;
        vector<Node> neighbors;
        int remainingQubit;
        int node_id;
        int position_x;
        int position_y;
        int Qubits_num;
};

#endif