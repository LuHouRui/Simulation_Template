#include <iostream>
#include <vector>
using namespace std;

#include "env.h"
#include "Node.h"
#include "Link.h"

Node::Node(){}

Node::Node(int in_id,int in_x,int in_y,int in_num_Qubits){
    this->node_id = in_id;
    this->position_x = in_x;
    this->position_y = in_y;
    this->Qubits_num = in_num_Qubits;
    this->remainingQubit = in_num_Qubits;
    vector<Link>Links = vector<Link>();
    vector<pair<Link,Link>>internalLinks = vector<pair<Link,Link>>();
    vector<Node> neighbors = vector<Node>();
}

bool Node::operator==(const Node &right) const
{
    if(this->node_id != right.node_id)
        return false;
    return true;
}

bool Node::attemptSwapping(Link *link1,Link *link2){
    if(link1->node1 == this)
    {
        link1->state_of_node1=true;
    }
    else
    {
        link1->state_of_node2=true;
    }
    if(link2->node1 == this)
    {
        link2->state_of_node1=true;
    }
    else
    {
        link2->state_of_node2=true;
    }
    bool output = Get_Random_double() > internal_probability;
    if(output){
        pair<Link,Link>pair(*link1,*link2);
        internalLinks.push_back(pair);
    }  
    return output;
}

string Node::toString(){
    return "N#"+to_string(node_id)+"["
        +to_string(remainingQubit)+"/"+to_string(Qubits_num)+"]"
        +" @("+to_string(position_x)+","+to_string(position_y)+")";
}

