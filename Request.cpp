#include <iostream>
#include <math.h>
using namespace std;

#include "Request.h"

Request::Request(){}

Request::Request(int in_id, int in_source, int in_destinaiton, int in_capacity_demand,double in_fidelity_demand, int in_weight)
{
    this->Request_id = in_id;
    this->source = in_source;
    this->destination = in_destinaiton;
    this->capacity_demand = in_capacity_demand;
    this->fidelity_demand = in_fidelity_demand;
    this->weight = in_weight;
}

string Request::toString()
{
    return "R#"+to_string(Request_id) + " ("+to_string(source)+","+to_string(destination)+") "+ " C:"+to_string(capacity_demand)+" F:"+to_string(fidelity_demand)+" W:"
                    + to_string(weight);
}
