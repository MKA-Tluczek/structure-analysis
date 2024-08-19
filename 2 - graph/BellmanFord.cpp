#include <iostream>
#include "Random.h"
#include "MatrixGraph.h"
#include "ListGraph.h"
#include "BellmanFord.h"
using namespace std;

const int MAXINT = 2147483647;

void BellmanFordMatrix(MatrixGraph* target, int start, int end, bool output){
	//szybszy dostep
	int vertexNo = (target->vertexNo);
	int* values = (target->values);
	
	//Krok 1 - przygotowac liste krawedzi
	int edgeNo = 0;
	int* edge = (int*) malloc (0);
	for(int from = 0; from < vertexNo; from++){
		for(int to = 0; to < vertexNo; to++){
			if(values[from*vertexNo + to] != -1){
				edgeNo++;
				edge = (int*) realloc(edge, edgeNo*3*sizeof(int));
				edge[edgeNo*3 - 3] = from;
				edge[edgeNo*3 - 2] = to;
				edge[edgeNo*3 - 1] = values[from*vertexNo + to];
			}
		}
	}
	
	//Krok 2 - iteracje krawedzi
	int distance[vertexNo];
	int previous[vertexNo];
	for(int i = 0; i < vertexNo; i++){
		distance[i] = MAXINT;
		previous[i] = -1;
	}
	distance[start] = 0;
	
	int a, b, w;
	for(int n = 0; n < vertexNo-1; n++){
		for(int i = 0; i < edgeNo*3; i += 3){
			a = edge[i];
			b = edge[i+1];
			w = edge[i+2];
			if(distance[a] < distance[b] - w){
				distance[b] = distance[a] + w;
				previous[b] = a;
			}
		}
	}
	
	if(output){
		if(previous[end] == -1 && start != end){
			cout << "Algorytm Bellmana-Forda, na macierzy, od " << start << " do " << end << "\nDlugosc drogi: ND\nDroga: Nie istnieje\n";
			return;
		}
		
		cout << "Algorytm Bellmana-Forda, na macierzy, od " << start << " do " << end << "\nDlugosc drogi: " << distance[end] << "\nDroga: " << end;
		end = previous[end];
		while(end != -1){
			cout << "<-" << end;
			end = previous[end];
		}
		cout << "\n";
	}
}

void BellmanFordList(ListGraph* target, int start, int end, bool output){
	//szybszy dostep
	int vertexNo = (target->vertexNo);
	int* outEdges = (target->outEdges);
	int** values = (target->values);
	
	//Krok 1 - przygotowac liste krawedzi
	int edgeNo = 0;
	int* edge = (int*) malloc (0);
	for(int from = 0; from < vertexNo; from++){
		for(int i = 0; i < outEdges[from]*2; i += 2){
			edgeNo++;
			edge = (int*) realloc(edge, edgeNo*3*sizeof(int));
			edge[edgeNo*3 - 3] = from;
			edge[edgeNo*3 - 2] = values[from][i];
			edge[edgeNo*3 - 1] = values[from][i+1];
		}
	}
	
	//Krok 2 - iteracje krawedzi
	int distance[vertexNo];
	int previous[vertexNo];
	for(int i = 0; i < vertexNo; i++){
		distance[i] = MAXINT;
		previous[i] = -1;
	}
	distance[start] = 0;
	
	int a, b, w;
	for(int n = 0; n < vertexNo-1; n++){
		for(int i = 0; i < edgeNo*3; i += 3){
			a = edge[i];
			b = edge[i+1];
			w = edge[i+2];
			if(distance[a] < distance[b] - w){
				distance[b] = distance[a] + w;
				previous[b] = a;
			}
		}
	}
	
	if(output){
		if(previous[end] == -1 && start != end){
			cout << "Algorytm Bellmana-Forda, na liscie, od " << start << " do " << end << "\nDlugosc drogi: ND\nDroga: Nie istnieje\n";
			return;
		}
		
		cout << "Algorytm Bellmana-Forda, na liscie, od " << start << " do " << end << "\nDlugosc drogi: " << distance[end] << "\nDroga: " << end;
		end = previous[end];
		while(end != -1){
			cout << "<-" << end;
			end = previous[end];
		}
		cout << "\n";
	}
}
