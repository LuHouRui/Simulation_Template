#include "env.h"
#include <iostream>
#include <cstdlib> /* 亂數相關函數 */
#include <ctime>   /* 時間相關函數 */
using namespace std;

double Get_Random_double()
{
    int min = 0;
    int max = 1;
    return (max - min) * rand() / (RAND_MAX + 1.0) + min;
}