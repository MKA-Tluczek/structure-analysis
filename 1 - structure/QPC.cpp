#include <iostream>
#include <windows.h>
#include "QPC.h"
using namespace std;

// Gotowy kod licznika skopiowany z ponizszej strony:
// https://stackoverflow.com/questions/1739259/how-to-use-queryperformancecounter
// Wprowadzono modyfikacje: Czestotliwosc komputera jest zbierana tylko jeden raz, przy uruchomieniu programu

static double PCFreq = 0.0;
static __int64 CounterStart = 0;

void prepareCounter(){
	LARGE_INTEGER li;
    if(!QueryPerformanceFrequency(&li))
    cout << "QueryPerformanceFrequency error!\nFunkcje eksperymentalne spowoduja crash aplikacji!\n";
    PCFreq = double(li.QuadPart)/1000.0;
}

void startCounter(){
	LARGE_INTEGER li;
	QueryPerformanceCounter(&li);
    CounterStart = li.QuadPart;
}

double getCounter(){
	LARGE_INTEGER li;
    QueryPerformanceCounter(&li);
    return double(li.QuadPart-CounterStart)/PCFreq;
}
