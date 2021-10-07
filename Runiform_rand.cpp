#include"Runiform_rand.h"


//using namespace std;

void PMMLCG::setSeed(long long seed_in)
{
	this->seed = seed_in;
};

PMMLCG::PMMLCG(long long seed_in)
{
	this->seed = seed_in;
}

double PMMLCG::rand()
{
	this->seed = (this->seed*PMMLCG_A) % PMMLCG_M;

	return ((double)(this->seed) / PMMLCG_M);
};

// uniform_rand::uniform_rand(long long seed_in, double in)
// {
// 	this->uni_rand.setSeed(seed_in);
// 	this->value = in;
// }

uniform_rand::uniform_rand(long long seed_in, double lower_in, double upper_in)
{
	this->uni_rand.setSeed(seed_in);
	this->lower_bound = lower_in;
	this->upper_bound = upper_in;
}

double uniform_rand::rand()
{
	double R = this->uni_rand.rand();
	return (this->lower_bound + (this->upper_bound - this->lower_bound)*R);
}
// uniform_rand::uniform_rand(long long seed_in, int lower_in, int upper_in)
// {
// 	this->uni_rand.setSeed(seed_in);
// 	this->lower_bound = lower_in;
// 	this->upper_bound = upper_in;
// }
/*
int main()
{
	PMMLCG myclass;
	myclass.setSeed(587);
	for(int i=0;i<5;i++)
		cout<<myclass.rand()<<endl;

	system("PAUSE");
	return 1;
};*/