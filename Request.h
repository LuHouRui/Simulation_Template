#ifndef REQUEST_H
#define REQUEST_H

class Request
{
    public:
        Request();
        Request(int in_id, int source, int destinaiton, int capacity_demand,double fidelity_demand, int weight);
        string toString();
        int Request_id;
        int source;
        int destination;
        int capacity_demand;
        double fidelity_demand;
        int weight;
};

#endif