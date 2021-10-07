#include <iostream>
#include <math.h>
using namespace std;

#include "env.h"
#include "Link.h"
#include "Node.h"

Link::Link(){}
Link::Link(Link *in_link)
{
    this->Link_id = in_link->Link_id;
    this->node1 = in_link->node1;
    this->node2 = in_link->node2;
    this->link_length = in_link->link_length;
    this->fidelity = in_link->fidelity;
    this->capacity = in_link->capacity;
    this->external_probability = in_link->external_probability;
}
Link::Link(int in_id,Node *in_node1,Node *in_node2,double in_length,double in_fidelity)
{
    this->Link_id = in_id;
    this->node1 = in_node1;
    this->node2 = in_node2;
    this->link_length = in_length;
    this->fidelity = in_fidelity;
    external_probability = exp(-ALPHA * in_length);
}

Node Link::theOtherEndOf(Node *n)
{
    if(n == node1){
        return *node1;
    }
    else{
        return *node2;
    }
}

bool Link::contains(Node *n)
{
    return (node1 == n || node2 == n);
}

bool Link::swappedAt(Node *n)
{
    return (node1 == n && state_of_node1 || node2 == n && state_of_node2);
}

bool Link::swappedAtTheOtherEndOf(Node *n)
{
    return (node1 == n && state_of_node2 || node2 == n && state_of_node1);
}

bool Link::swapped()
{
    return (state_of_node1 || state_of_node2);
}

bool Link::notSwapped()
{
    return !swapped();
}

int Link::GetId()
{
    return Link_id;
}

bool Link::operator==(const Link &right)const
{
    if(&right == NULL)
        return false;
    if(right.Link_id==Link_id)
        return true;
    return false;
}

bool Link::assignQubits(){
    this->assigned = true;
}

bool Link::tryEntanglement()
{
    double Random_value = Get_Random_double();
    entangled = assigned && external_probability >= Random_value;
    // cout << "此次生成機率: " << Random_value << endl;
    return entangled;
}

void Link::clearEntanglement()
{
    assigned = false;
    entangled = false;
}

string Link::toString()
{
    string state =entangled?"✓":"✗";
    string assigned_state = to_string(node1->node_id)+","+to_string(node2->node_id);
    if(assigned)
    {
        assigned_state = "["+assigned_state+"]";
    }
    else
    {
        assigned_state = "("+assigned_state+")";
    }
    return "L#"+to_string(Link_id)+state+assigned_state+" C:"+to_string(capacity)+" "+to_string(link_length)+"km P:"
                    + to_string(external_probability) + "";
}

bool Link::assignable(){
    return (!assigned && node1->remainingQubit>0&&node2->remainingQubit>0);
}