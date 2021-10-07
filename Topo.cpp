#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <iomanip>
#include <unistd.h>
#include <algorithm>
using namespace std;

#include "Node.h"
#include "Edge.h"
#include "Request.h"
#include "Runiform_rand.h"
#define Node_FILENAME "Node_Topolist.txt"
#define Edge_FILENAME "Edge_Topolist.txt"
#define Request_FILENAME "Request_Topolist.txt"
vector<vector<int>> Get_adjacent_matrix(vector<Edge> Edge_vec,int node_num)
{
	vector<int> row;
	row.assign(node_num,-1);//配置一個 row 的大小
	vector<vector<int>> Edge_table;
	Edge_table.assign(node_num,row);//配置2維
	for (int i = 0; i < Edge_vec.size(); i++)
	{
		Edge cur_edge = Edge_vec[i];
		Node *cur_node1 = Edge_vec[i].node1;
		Node *cur_node2 = Edge_vec[i].node2;
		Edge_table[cur_node1->node_id][cur_node2->node_id] = cur_edge.Edge_id;
		Edge_table[cur_node2->node_id][cur_node1->node_id] = cur_edge.Edge_id;
	}
  return Edge_table;
}

bool Is_connectivity(vector<vector<int>> Edge_table)
{
	int node_num = Edge_table.size();
	int visited[node_num]={0};
	vector<int> queue;
	queue.push_back(0);
	visited[0] = -1;

	int cur_node;
	while(queue.size() != 0)
	{
		cur_node = queue.front();
		// cout << "目前節點是 " << cur_node << endl;
		queue.erase(queue.begin());
		visited[cur_node] = 1;
		for (int i = 0; i < node_num; i++)
		{
			if( i == cur_node)
			{
				continue;
			}
			if(Edge_table[cur_node][i] != -1 && visited[i] == 0)
			{
				// cout << "發現鄰居 " << i << endl;
				queue.push_back(i);
				visited[i] = -1;
			}
		}
		// for (int i = 0; i < queue.size(); i++)
		// {
		//   cout << queue[i] << "\t";
		// }
		// cout << endl;
	}
	int output = 1;
	for (int i = 0; i < node_num; i++)
	{
		// cout << visited[i] << "\t";
		output = output * visited[i];
	}
	return output;
}

int main(int argc,char *argv[])
{
	srand(time(NULL));
	//Read parameters
    char* node_num_char = NULL;
    char* reqeust_num_char = NULL;
    char* area_char = NULL;
	if (argc == 4) 
    {
		node_num_char = argv[1];
		reqeust_num_char = argv[2];
		area_char = argv[3];
	}
	int node_num = atoi(node_num_char);
	int request_num = atoi(reqeust_num_char);
	float area = atof(area_char);
	area = area*1000;

	//Read Setup parameters
	int Max_Qubits,Min_Qubits,Max_Weight,Min_Weight,Max_Capacity,Min_Capacity;
	double edge_alpha,edge_beta,Max_edge_distance,f_avg,f_std,R_f_avg,R_f_std;
	ifstream setup_fin;
	setup_fin.open("setup.txt",ios::in);
	if(!setup_fin){
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



	//Setup random object for generate nodes
	Node *pt;
	unsigned seed;
	seed = (unsigned)time(NULL);
	uniform_rand positionrand(seed, 0, area);
	uniform_rand qubitrand(seed,Min_Qubits,Max_Qubits);
	//Setup random object for generate edges
	int edge_num = 0;
	vector<Edge>Edge_vec;
	vector<vector<int>> Edge_table;
	bool connectivity = false;

	while(!connectivity){
		//Generate Nodes
		pt = new Node[node_num];
		for (int i = 0; i < node_num; i++)
		{
			Node n = Node(i,positionrand.rand(),positionrand.rand(),qubitrand.rand());
			pt[i] = n;
		}

		//Generate Edges
		for (int  i = 0; i < node_num; i++)
		{
			for(int j = i+1; j < node_num; j++)
			{
				double distance = sqrt(pow(abs(pt[i].position_x-pt[j].position_x),2)+pow(abs(pt[i].position_y-pt[j].position_y),2))/1000;
				double edge_probability = edge_beta*exp(-distance/Max_edge_distance*edge_alpha);
				if(edge_probability >= rand() / (RAND_MAX + 1.0)){
					Edge edge = Edge(edge_num, &pt[i], &pt[j], distance);
					Edge_vec.push_back(edge);
					edge_num++;
				}
			}
		}

		//Get adjency matrix of edges
		Edge_table = Get_adjacent_matrix(Edge_vec,node_num);
		connectivity = Is_connectivity(Edge_table);
		if(!connectivity)
		{
			Edge_vec.clear();
			edge_num=0;
		}
	}
	//Print adjency matrix of edges
	for (int i = 0; i < node_num; i++)
	{
		for (int j = 0; j < node_num; j++)
		{
			cout << Edge_table[i][j] << "\t";
		}
		cout << endl;
	}

	//根據兩點間的距離排序 Edges
	sort(Edge_vec.begin(), Edge_vec.end(), [](Edge a, Edge b){
        return a.edge_length < b.edge_length; // 升序排列
    });
	//印出糾纏紀錄表
	cout << endl << "==============================Edge between any two nodes==============================" << endl;
	for (int i = 0; i < Edge_vec.size(); i++)
	{
		cout << Edge_vec[i].toString() << endl;
	}
	cout << endl << "==========================================================================================" << endl;
	//Output nodes information
	FILE *oPtr;
	oPtr = fopen(Node_FILENAME, "w");
	if (oPtr) {
		fprintf(oPtr, "%d\n", (node_num));
		for (int i = 0; i < node_num; i++)
		{
			fprintf(oPtr,"%d\t",(pt[i].node_id));
			fprintf(oPtr, "%d\t", (pt[i].position_x));
			fprintf(oPtr, "%d\t", (pt[i].position_y));
			fprintf(oPtr, "%d\t", (pt[i].Qubits_num));
			fprintf(oPtr, "%d\n", (pt[i].remainingQubit));
		}
		fclose(oPtr);
	}
	//Output edges information
	oPtr = NULL;
    oPtr = fopen(Edge_FILENAME, "w");
	if (oPtr) {
		fprintf(oPtr, "%d\n", (edge_num));
		for (int i = 0; i < edge_num; i++)
		{
			fprintf(oPtr,"%d\t",(Edge_vec[i].Edge_id));
			fprintf(oPtr,"%d\t",(Edge_vec[i].node1->node_id));
			fprintf(oPtr,"%d\t",(Edge_vec[i].node2->node_id));
			fprintf(oPtr,"%f\n",(Edge_vec[i].edge_length));
		}
        fclose(oPtr);
    }

	//Setup random object for generate requests
	random_device rd{};
    mt19937 gen{rd()};
    normal_distribution<double> Random_Request_Fidelity{R_f_avg,R_f_std};
	//Generate requests
	vector<Request*>Request_vec;
	for (int i = 0; i < request_num; i++)
	{
		Request *req = new Request();
		req->Request_id = i;
		req->source = rand()%node_num;
		req->destination = rand()%node_num;
		while(req->source == req->destination){
			req->destination = rand()%node_num;
		}
		req->fidelity_demand = Random_Request_Fidelity(gen);
		req->weight = rand()%(Max_Weight-Min_Weight)+Min_Weight;
		req->capacity_demand = rand()%(Max_Capacity-Min_Capacity)+Min_Capacity;
		Request_vec.push_back(req);
	}
	//Output requests information
	oPtr = NULL;
    oPtr = fopen(Request_FILENAME, "w");
	if (oPtr) {
		fprintf(oPtr, "%d\n", (request_num));
		for (int i = 0; i < request_num; i++)
		{
			fprintf(oPtr,"%d\t",(Request_vec[i]->Request_id));
			fprintf(oPtr,"%d\t",(Request_vec[i]->source));
			fprintf(oPtr,"%d\t",(Request_vec[i]->destination));
			fprintf(oPtr,"%d\t",(Request_vec[i]->capacity_demand));
			fprintf(oPtr,"%f\t",(Request_vec[i]->fidelity_demand));
			fprintf(oPtr,"%d\n",(Request_vec[i]->weight));
		}
        fclose(oPtr);
    }

	//Clean memory
	delete[] pt;
	Request_vec.clear();
	Edge_vec.clear();
	oPtr = NULL;

    return 0;
}