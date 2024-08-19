#include <iostream>
#include "Random.h"
#include "MatrixGraph.h"
#include "ListGraph.h"
#include "Dijkstra.h"
using namespace std;

const int MAXINT = 2147483647;

void DijkstraMatrix(MatrixGraph* target, int start, int end, bool output){
	//szybszy dostep
	int vertexNo = (target->vertexNo);
	int* values = (target->values);
	
	int distance[vertexNo]; //odleglosc do tego wierzcholka
	int previous[vertexNo]; //poprzedni wierzcholek na sciezce
	bool checked[vertexNo]; //czy juz zostal rozpatrzony
	
	for(int i = 0; i < vertexNo; i++){
		distance[i] = MAXINT;
		previous[i] = -1;
		checked[i] = false;
	}
	distance[start] = 0;
	
	int nextDistance, nextID;
	while(1){
		nextDistance = MAXINT, nextID = -1;
		
		//znajdz nastepny wierzcholek do rozpatrzenia
		for(int i = 0; i < vertexNo; i++){
			if(!checked[i]){
				if(distance[i] < nextDistance){
					nextDistance = distance[i];
					nextID = i;
				}
			}
		}
		
		//sprawdz czy dotarlismy do konca, albo czy wyczerpaly nam sie wierzcholki
		if(nextID == end || nextID == -1) break;
		
		//przejdz przez krawedzie wychodzace
		for(int i = 0; i < vertexNo; i++){
			if(values[nextID*vertexNo + i] != -1){
				if(distance[nextID] + values[nextID*vertexNo + i] < distance[i]){
					distance[i] = distance[nextID] + values[nextID*vertexNo + i];
					previous[i] = nextID;
				}
			}
		}
		
		checked[nextID] = true;
	}
	
	if(output){
		if(previous[end] == -1 && start != end){
			cout << "Algorytm Dijkstry, na macierzy, od " << start << " do " << end << "\nDlugosc drogi: ND\nDroga: Nie istnieje\n";
			return;
		}
		
		cout << "Algorytm Dijkstry, na macierzy, od " << start << " do " << end << "\nDlugosc drogi: " << distance[end] << "\nDroga: " << nextID;
		nextID = previous[nextID];
		while(nextID != -1){
			cout << "<-" << nextID;
			nextID = previous[nextID];
		}
		cout << "\n";
	}
}

void DijkstraList(ListGraph* target, int start, int end, bool output){
	//szybszy dostep
	int vertexNo = (target->vertexNo);
	int* outEdges = (target->outEdges);
	int** values = (target->values);
	
	int distance[vertexNo]; //odleglosc do tego wierzcholka
	int previous[vertexNo]; //poprzedni wierzcholek na sciezce
	bool checked[vertexNo]; //czy juz zostal rozpatrzony
	
	for(int i = 0; i < vertexNo; i++){
		distance[i] = MAXINT;
		previous[i] = -1;
		checked[i] = false;
	}
	distance[start] = 0;
	
	int nextDistance, nextID;
	while(1){
		nextDistance = MAXINT, nextID = -1;
		
		//znajdz nastepny wierzcholek do rozpatrzenia
		for(int i = 0; i < vertexNo; i++){
			if(!checked[i]){
				if(distance[i] < nextDistance){
					nextDistance = distance[i];
					nextID = i;
				}
			}
		}
		
		//sprawdz czy dotarlismy do konca, albo czy wyczerpaly nam sie wierzcholki
		if(nextID == end || nextID == -1) break;
		
		//przejdz przez krawedzie wychodzace
		for(int i = 0; i < outEdges[nextID]*2; i += 2){
			if(distance[nextID] + values[nextID][i+1] < distance[values[nextID][i]]){
				distance[values[nextID][i]] = distance[nextID] + values[nextID][i+1];
				previous[values[nextID][i]] = nextID;
			}
		}
		
		checked[nextID] = true;
	}
	
	if(output){
		if(previous[end] == -1 && start != end){
			cout << "Algorytm Dijkstry, na liscie, od " << start << " do " << end << "\nDlugosc drogi: ND\nDroga: Nie istnieje\n";
			return;
		}
		
		cout << "Algorytm Dijkstry, na liscie, od " << start << " do " << end << "\nDlugosc drogi: " << distance[end] << "\nDroga: " << nextID;
		nextID = previous[nextID];
		while(nextID != -1){
			cout << "<-" << nextID;
			nextID = previous[nextID];
		}
		cout << "\n";
	}
}
