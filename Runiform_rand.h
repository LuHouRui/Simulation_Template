#ifndef RUNIFORM_RAND_H
#define RUNIFORM_RAND_H

#define PMMLCG_A 630360016
#define PMMLCG_M 2147483647

class PMMLCG {
private:
	long long seed;

public:
	PMMLCG(long long seed_in = 123);
	void setSeed(long long seed_in);
	double rand();
};

class uniform_rand
{

private:
	PMMLCG uni_rand;
	double upper_bound, lower_bound;

public:
	uniform_rand(long long seed_in, double lower_in, double upper_in);
	// uniform_rand(long long seed_in, int lower_in, int upper_in);
	double rand();

};
#endif