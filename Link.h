#ifndef LINK_H
#define LINK_H

#include "Node.h"
class Node;

class Link
{
    public:
        Link();
        Link(Link *in_link);
        Link(int in_id, Node *in_node1, Node *in_node2, double in_length,double fidelity);
        Node theOtherEndOf(Node *n);
        bool contains(Node *n);
        bool swappedAt(Node *n);
        bool swappedAtTheOtherEndOf(Node *n);
        bool swapped();
        bool notSwapped();
        int GetId();
        bool operator==(const Link &)const;
        bool assignQubits();
        bool tryEntanglement();
        void clearEntanglement();
        string toString();
        bool assignable();
        Node *node1;
        Node *node2;
        bool state_of_node1 = false;
        bool state_of_node2 = false;
        int Link_id;
        int capacity=0;   //共有幾條link建立成功
        double fidelity;
        double link_length;
        bool entangled = false;
        bool assigned = false;
        double external_probability;
};

#endif