#include <iostream>
#include "Random.h"
#include "MatrixGraph.h"
#include "ListGraph.h"
#include "Kruskal.h"
using namespace std;

void quicksortEdges(int* array, int first, int last){
	if(first >= last) return;
	
	int swap;
	int a = first*3 + 2, b = last*3 + 2, pivot = array[rng(first, last)*3 + 2];
	
	while(1){
		if(array[a] < pivot){
			a += 3;
			if(a == b){
				a -= 3;
				break;
			}
		}
		else{
			if(array[b] > pivot){
				b -= 3;
				if(a == b){
					b += 3;
					break;
				}
			}
			else{
				swap = array[a-2];
				array[a-2] = array[b-2];
				array[b-2] = swap;
				
				swap = array[a-1];
				array[a-1] = array[b-1];
				array[b-1] = swap;
				
				swap = array[a];
				array[a] = array[b];
				array[b] = swap;
				
				if(array[a] < pivot){
					a += 3;
					if(a == b){
						a -= 3;
						break;
					}
				}
				else{
					b -= 3;
					if(a == b){
						b += 3;
						break;
					}
				}
			}
		}
	}
	
	quicksortEdges(array, first, (a-2)/3);
	quicksortEdges(array, (b-2)/3, last);
}

void KruskalMatrix(MatrixGraph* target, bool output){
	//szybszy dostep
	int vertexNo = (target->vertexNo);
	int* values = (target->values);
	
	//Krok 1 - przygotowanie kazdego wierzcholka jako poczatkowo osobne drzewo
	int treeID[vertexNo]; //wierzcholek n jest czescia drzewa numer treeID[n]
	for(int i = 0; i < vertexNo; i++) treeID[i] = i;
	
	//Krok 2 - przygotowanie listy wszystkich krawedzi
	int edgeNo = 0;
	int* queue = (int*) malloc(0);
	for(int from = 0; from < vertexNo; from++){
		for(int to = from+1; to < vertexNo; to++){
			if(values[from*vertexNo + to] != -1){
				edgeNo++;
				queue = (int*) realloc(queue, edgeNo*3*sizeof(int));
				queue[edgeNo*3 - 3] = from;
				queue[edgeNo*3 - 2] = to;
				queue[edgeNo*3 - 1] = values[from*vertexNo + to];
			}
		}
	}
	
	//Krok 3 - sortowanie listy
	quicksortEdges(queue, 0, edgeNo-1);
	
	//Krok 4 - rozpatrujemy krawedzie
	int a, b, w, newTree, oldTree;
	
	int answerSize = 0; //ile krawedzi juz jest w odpowiedzi
	int answerTotal = 0; //suma wag w drzewie
	int* answer = (int*) malloc(0); //kazda para liczb to krawedz od a do b
	
	for(int i = 0; i < edgeNo*3; i += 3){
		a = queue[i];
		b = queue[i+1];
		if(treeID[a] != treeID[b]){ //Krawedz laczy dwa rozne drzewa
			
			newTree = min(treeID[a], treeID[b]);
			oldTree = max(treeID[a], treeID[b]);
			for(int i = 0; i < vertexNo; i++){
				if(treeID[i] == oldTree) treeID[i] = newTree;
			}
			
			answerSize++;
			answerTotal += queue[i+2];
			answer = (int*) realloc(answer, answerSize*2*sizeof(int));
			answer[answerSize*2 - 2] = a;
			answer[answerSize*2 - 1] = b;
		}
	}
	
	if(output){
		cout << "Algorytm Kruskala, na macierzy\nWynik: " << answerTotal << "\n";
		for(int i = 0; i < answerSize*2; i += 2){
			cout << answer[i] << "-" << answer[i+1] << ", ";
		}
		cout << "\n";
	}
	
	free(answer);
	free(queue);
}

void KruskalList(ListGraph* target, bool output){
	//szybszy dostep
	int vertexNo = (target->vertexNo);
	int* outEdges = (target->outEdges);
	int** values = (target->values);
	
	//Krok 1 - przygotowanie kazdego wierzcholka jako poczatkowo osobne drzewo
	int treeID[vertexNo]; //wierzcholek n jest czescia drzewa numer treeID[n]
	for(int i = 0; i < vertexNo; i++) treeID[i] = i;
	
	//Krok 2 - przygotowanie listy wszystkich krawedzi
	int edgeNo = 0;
	int* queue = (int*) malloc(0);
	for(int from = 0; from < vertexNo; from++){
		for(int i = 0; i < 2*outEdges[from]; i += 2){
			if(values[from][i] > from){ //rozpatrujemy tylko krawedzie idacy do wiekszego wierzcholka, aby nie liczyc krawedzi dwa razy
				edgeNo++;
				queue = (int*) realloc(queue, edgeNo*3*sizeof(int));
				queue[edgeNo*3 - 3] = from;
				queue[edgeNo*3 - 2] = values[from][i];
				queue[edgeNo*3 - 1] = values[from][i+1];
			}
		}
	}
	
	//Krok 3 - sortowanie listy
	quicksortEdges(queue, 0, edgeNo-1);
	
	//Krok 4 - rozpatrujemy krawedzie
	int a, b, w, newTree, oldTree;
	
	int answerSize = 0; //ile krawedzi juz jest w odpowiedzi
	int answerTotal = 0; //suma wag w drzewie
	int* answer = (int*) malloc(0); //kazda para liczb to krawedz od a do b
	
	for(int i = 0; i < edgeNo*3; i += 3){
		a = queue[i];
		b = queue[i+1];
		if(treeID[a] != treeID[b]){ //Krawedz laczy dwa rozne drzewa
			
			newTree = min(treeID[a], treeID[b]);
			oldTree = max(treeID[a], treeID[b]);
			for(int i = 0; i < vertexNo; i++){
				if(treeID[i] == oldTree) treeID[i] = newTree;
			}
			
			answerSize++;
			answerTotal += queue[i+2];
			answer = (int*) realloc(answer, answerSize*2*sizeof(int));
			answer[answerSize*2 - 2] = a;
			answer[answerSize*2 - 1] = b;
		}
	}
	
	if(output){
		cout << "Algorytm Kruskala, na liscie\nWynik: " << answerTotal << "\n";
		for(int i = 0; i < answerSize*2; i += 2){
			cout << answer[i] << "-" << answer[i+1] << ", ";
		}
		cout << "\n";
	}
	
	free(answer);
	free(queue);
}
