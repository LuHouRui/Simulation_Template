#include <iostream>
#include "Runiform_rand.h"
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <cmath>
#include <string.h>
#include <vector>
#include <unistd.h>
#include <algorithm>

using namespace std;
string file_path;
int main(int argc,char *argv[])
{
    if(argc == 2){
		file_path = argv[1];
	}
    ifstream file;
	file.open(file_path,ios::in);
    double value = 0;
    double temp = 0;
    int count = 0;
    while(!file.eof()){
        file >> temp;
        if(temp > 0){
            value += temp;
            count++;
        }
    }
    value = value/count;
    cout << "Average:" << endl;
    cout << value << endl;
}