#include <iostream>
#include <limits.h>
#include <string.h>
#include <random>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;

#include "Node.h"
#include "Edge.h"
#include "Link.h"
#include "Request.h"
#include "env.h"

#define Node_FILENAME "Node_Topolist.txt"
#define Edge_FILENAME "Edge_Topolist.txt"
#define Request_FILENAME "Request_Topolist.txt"

string Node_path;
string Edge_path;
string Request_path;
string setup_path;

//Read Setup parameters
int Max_Qubits,Min_Qubits,Max_Weight,Min_Weight,Max_Capacity,Min_Capacity;
double edge_alpha,edge_beta,Max_edge_distance,f_avg,f_std,R_f_avg,R_f_std;

int node_num;
int edge_num;
int request_num;

Node *Nodes;       //Input Nodes
Edge *Edges;       //Input Edges
Request *Requests; //Input requests

vector<vector<int>> Graph; //儲存著各點與各點間的Edge_id

vector<vector<int>> Get_adjacent_matrix(Edge *In_Edges)
{
    vector<int> row;
    row.assign(node_num, -1); //配置一個 row 的大小
    vector<vector<int>> Edge_table;
    Edge_table.assign(node_num, row); //配置2維
    for (int i = 0; i < edge_num; i++)
    {
        Edge *cur_edge = &In_Edges[i];
        Node *cur_node1 = cur_edge->node1;
        Node *cur_node2 = cur_edge->node2;
        Edge_table[cur_node1->node_id][cur_node2->node_id] = cur_edge->Edge_id;
        Edge_table[cur_node2->node_id][cur_node1->node_id] = cur_edge->Edge_id;
    }
    return Edge_table;
}

bool bfs(vector<vector<int>> rGraph, int s, int t, int parent[])
{
    // Create a visited array and mark all vertices as not visited
    bool visited[node_num];
    memset(visited, 0, sizeof(visited));

    // Create a queue, enqueue source vertex and mark source vertex
    // as visited
    vector<int> q;
    q.push_back(s);
    visited[s] = true;
    parent[s] = -1;

    // Standard BFS Loop
    while (!q.empty())
    {
        int u = q.front();
        q.erase(q.begin());

        for (int v = 0; v < node_num; v++)
        {
            if (visited[v] == false && rGraph[u][v] > 0)
            {
                q.push_back(v);
                parent[v] = u;
                visited[v] = true;
            }
        }
    }

    // If we reached sink in BFS starting from source, then return
    // true, else false
    return (visited[t] == true);
}

bool Initialization()
{
    ifstream node_fin, edge_fin, request_fin,setup_fin;
    node_fin.open(Node_path, ios::in);
    edge_fin.open(Edge_path, ios::in);
    request_fin.open(Request_path, ios::in);
    setup_fin.open(setup_path, ios::in);
    if (!edge_fin || !node_fin || !request_fin || !setup_fin)
    {
        cout << "Read Files Error." << endl;
    }
    setup_fin >> edge_alpha >> edge_beta;
	setup_fin >> Max_edge_distance;
	setup_fin >> Max_Qubits >> Min_Qubits;
	setup_fin >> f_avg >> f_std;
	setup_fin >> R_f_avg >> R_f_std;
	setup_fin >> Max_Weight >> Min_Weight;
	setup_fin >> Max_Capacity >> Min_Capacity;
	setup_fin.close();
    node_fin >> node_num;
    edge_fin >> edge_num;
    request_fin >> request_num;
    Nodes = new Node[node_num];
    Edges = new Edge[edge_num];
    Requests = new Request[request_num];
    for (int i = 0; i < node_num; i++)
    {
        node_fin >> Nodes[i].node_id >> Nodes[i].position_x >> Nodes[i].position_y >> Nodes[i].Qubits_num >> Nodes[i].remainingQubit;
    }
    for (int i = 0; i < edge_num; i++)
    {
        int node1_id, node2_id;
        edge_fin >> Edges[i].Edge_id >> node1_id >> node2_id >> Edges[i].edge_length;
        Edges[i].node1 = &Nodes[node1_id];
        Edges[i].node2 = &Nodes[node2_id];
    }
    for (int i = 0; i < request_num; i++)
    {
        request_fin >> Requests[i].Request_id >> Requests[i].source >> Requests[i].destination >> Requests[i].capacity_demand >> Requests[i].fidelity_demand >> Requests[i].weight;
    }
    node_fin.close();
    edge_fin.close();
    request_fin.close();

    vector<int> row;
    row.assign(node_num, -1);    //配置一個 row 的大小
    Graph.assign(node_num, row); //配置2維
    for (int i = 0; i < edge_num; i++)
    {
        Edge *cur_edge = &Edges[i];
        Node *cur_node1 = cur_edge->node1;
        Node *cur_node2 = cur_edge->node2;
        Graph[cur_node1->node_id][cur_node2->node_id] = cur_edge->Edge_id;
        Graph[cur_node2->node_id][cur_node1->node_id] = cur_edge->Edge_id;
    }

    // for (int i = 0; i < Graph.size(); i++)
    // {
    //   for (int j = 0; j < Graph[i].size(); j++)
    //   {
    //     cout << setw(4) << Graph[i][j] << "\t";
    //   }
    //   cout << endl;
    // }

    return true;
}

int main(int argc, char *argv[])
{
    if (argc == 5)
    {
        Node_path = argv[1];
        Edge_path = argv[2];
        Request_path = argv[3];
        setup_path = argv[4];
    }
    else
    {
        cout << "You need to input [# of Nodes] [# of Requests] [Size of Area] [Date]";
    }

    if (!Initialization())
    {
        return 1;
    }
    //將Request根據wight由大到小排序
    sort(Requests, Requests + request_num, [](Request a, Request b)
         { return a.weight > b.weight; });
    // cout << endl << "============================== Weight ==============================" << endl;
    // for (int i = 0; i < request_num; i++)
    // {
    //   cout << Requests[i].toString() << endl;
    // }

    vector<vector<int>> paths_of_the_requests_vec;
    vector<int> row;
    paths_of_the_requests_vec.assign(request_num, row);
    int num_success = 0;
    vector<int> remainingQubits;
    for (int i = 0; i < node_num; i++)
    {
        remainingQubits.push_back(Nodes[i].remainingQubit);
    }
    // for (int i = 0; i < remainingQubits.size(); i++)
    // {
    //     cout << remainingQubits[i] << "\t";
    // }
    // cout << endl;

    for (int request_index = 0; request_index < request_num; request_index++)
    {

        // cout << endl << "============================== Routing Init ==============================" << endl;
        Request *cur_request = &Requests[request_index];
        int cur_source = cur_request->source;
        int cur_destination = cur_request->destination;
        // // print information of the cur_request
        // cout << cur_request->toString() << endl;
        //	開始為request進行routing，並記錄所有可能的path
        vector<vector<int>> rGraph = Get_adjacent_matrix(Edges);
        int max_flow = 0;
        int parent[node_num];
        vector<vector<int>> path_vec;
        // cout << endl << "============================== Routing ==============================" << endl;


        //======================================================================//
        //  Routing for the request
        //======================================================================//
        //Reference https://www.geeksforgeeks.org/find-edge-disjoint-paths-two-vertices/
        while (bfs(rGraph, cur_source, cur_destination, parent))
        {
            // Find minimum residual capacity of the edges along the
            // path filled by BFS. Or we can say find the maximum flow
            // through the path found.
            int path_flow = INT_MAX;
            vector<int> cur_path;
            for (int v = cur_destination; v != cur_source; v = parent[v])
            {
                int u = parent[v];
                // cout << v << "\t";
                cur_path.push_back(v);
                path_flow = min(path_flow, rGraph[u][v]);
            }
            cur_path.push_back(cur_source);
            // cout << cur_source << endl;
            // update residual capacities of the edges and reverse edges
            // along the path
            for (int v = cur_destination; v != cur_source; v = parent[v])
            {
                int u = parent[v];
                rGraph[u][v] -= path_flow;
                rGraph[v][u] += path_flow;
            }
            // Add path flow to overall flow
            max_flow += path_flow;
            path_vec.push_back(cur_path);
        }
        // cout << "# of paths: " << to_string(path_vec.size()) << endl;
        //======================================================================//
        //  Check the Qubits of node along the path can satisfy the demand of request.
        //======================================================================//
        //檢查是否有path存在可以滿足request
        if (path_vec.size() > 0)
        {
            //Assign path to the cur_request
            // 依路徑長度做升序排列，以便從最短路徑開始檢查。
            sort(path_vec.begin(), path_vec.end(), [](vector<int> a, vector<int> b)
                 { return a.size() < b.size(); });
            // cout << "Check demand of request " << request_index << endl;
            for (int path_index = 0; path_index < path_vec.size(); path_index++)
            {
                //遍尋path上的所有節點找出最小的qubits數量。
                int path_min_capacity = INT_MAX;
                for (int i = 0; i < path_vec[path_index].size(); i++)
                {
                    int cur_node_id = path_vec[path_index][i];
                    if(path_min_capacity > remainingQubits[cur_node_id])
                    {
                        path_min_capacity = remainingQubits[cur_node_id];
                    }
                }
                // cout << "Request's capcaity: " << cur_request->capacity_demand << " Path's capacity: " << path_min_capacity << endl;
                
                //path上的最小qubit數量是否大於等於request的capacity's demand，是則將此條path作為request的main path。
                if(path_min_capacity >= cur_request->capacity_demand && path_min_capacity != INT_MAX)
                {
                    paths_of_the_requests_vec[cur_request->Request_id] = path_vec[path_index];
                    // for (int i = 0; i < path_vec[path_index].size(); i++)
                    // {
                    //     cout << path_vec[path_index][i] << "\t";
                    // }
                    // cout << endl;
                    for (int i = 0; i < path_vec[path_index].size(); i++)
                    {
                        int cur_node_id = path_vec[path_index][i];
                        remainingQubits[cur_node_id] = remainingQubits[cur_node_id] - cur_request->capacity_demand;
                    }
                    num_success++;
                    break;
                }
            }
            // for (int i = 0; i < remainingQubits.size(); i++)
            // {
            //     cout << remainingQubits[i] << "\t";
            // }
            // cout << endl;
        }
    }
    //======================================================================//
    //  After all,generate entanglemnet and check the capacity of edge along 
    //  the path can satisfy the request
    //======================================================================//
    //Setup random object for generate requests
	random_device rd{};
    mt19937 gen{621};
    normal_distribution<double> Random_Fidelity{f_avg,f_std};
    vector<Link>Links;
    //generate entanglement
    for (int i = 0; i < edge_num; i++)
    {
        Edge *cur_edge = &Edges[i];
        Link cur_link = Link(cur_edge->Edge_id,cur_edge->node1,cur_edge->node2,cur_edge->edge_length,Random_Fidelity(gen));
        int gen_times = min(cur_edge->node1->Qubits_num,cur_edge->node2->Qubits_num);
        cur_link.assignQubits();
        for (int i = 0; i < gen_times; i++)
        {
            if(cur_link.tryEntanglement())
            {
                cur_link.capacity++;
                cur_link.node1->remainingQubit--;
                cur_link.node1->remainingQubit--;
            }
        }
        
        Links.push_back(cur_link);
    }
    
    vector<vector<int>>Link_table;
    vector<int>assigned_capacity;
    row.assign(node_num,-1);
    Link_table.assign(node_num,row);
    for (int i = 0; i < Links.size(); i++)
    {
        Link *cur_link = &Links[i];
        assigned_capacity.push_back(cur_link->capacity);
        Link_table[cur_link->node1->node_id][cur_link->node2->node_id] = i;
        Link_table[cur_link->node2->node_id][cur_link->node1->node_id] = i;
    }
    // cout << num_success << endl;
    int total_weight = 0;
    num_success = 0;
    for (int i = 0; i < request_num; i++)
    {
        Request *cur_request = &Requests[i];
        vector<int> cur_path = paths_of_the_requests_vec[cur_request->Request_id];
        // cout << "==============================================================================================================" << endl;
        // cout << cur_request->toString() << endl;
        if(cur_path.size() > 0)
        {
            int index = -1;
            int previous_node_id,cur_node_id,cur_link_id;
            // cout << cur_request->toString() << endl;
            for (index = 1; index < cur_path.size(); index++)
            {
                previous_node_id = cur_path[index-1];
                cur_node_id = cur_path[index];
                cur_link_id = Link_table[previous_node_id][cur_node_id];
                if(assigned_capacity[cur_link_id] < cur_request->capacity_demand || Links[cur_link_id].fidelity < cur_request->fidelity_demand)
                {
                    // cout << "Failed. capacity " << assigned_capacity[cur_link_id] << " fidelity " << Links[cur_link_id].fidelity << endl;
                    break;
                }
            }
            // cout << "path: " << previous_node_id << "   " << cur_node_id << "   " << Links[cur_link_id].capacity << endl;
            // cout << "request: " << Links[cur_link_id].node1->node_id << "   "  << Links[cur_link_id].node2->node_id;
            // cout << "   " << cur_request->capacity_demand << endl;
            if(index == cur_path.size()){
                num_success++;
                total_weight += cur_request->weight;
            }
        }
        // cout << "==============================================================================================================" << endl;
    }
    

    // cout << endl << "============================== Result ==============================" << endl;
    // cout << "(" << to_string(num_success) << "/" << to_string(request_num) << ")" << endl;
    cout << num_success << endl;
    // cout << total_weight << endl;
    return 0;
}