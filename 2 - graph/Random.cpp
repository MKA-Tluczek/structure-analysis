#include <stdlib.h>
#include <time.h>
#include "Random.h"
using namespace std;

void prepareSeed(){
	srand(time(0));
}

int rng(int min, int max){
	return (rand() % (max-min+1)) + min;
}
