#include <iostream>
#include <fstream>
#include <string>
#include <random>
using namespace std;


int main(int argc,char *argv[])
{
	random_device rd{};
    mt19937 gen{rd()};
    normal_distribution<double> Random_Fidelity{0.8,0.1};
    double temp = Random_Fidelity(gen);
    cout << temp << endl;
    return 0;
}