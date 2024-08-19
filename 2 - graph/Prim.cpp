#include <iostream>
#include "Random.h"
#include "MatrixGraph.h"
#include "ListGraph.h"
#include "Prim.h"
using namespace std;

const int MAXINT = 2147483647;

void PrimMatrix(MatrixGraph* target, bool output){
	//szybszy dostep
	int vertexNo = (target->vertexNo);
	int* values = (target->values);
	
	int costOfAdding[vertexNo];
	bool partOfTree[vertexNo];
	for(int i = 0; i < vertexNo; i++){
		partOfTree[i] = false;
	}
	
	//Krok 1 - zainicjalizuj pierwszy wierzcholek
	int startingPoint = rng(0, vertexNo-1);
	partOfTree[startingPoint] = true;
	
	for(int i = 0; i < vertexNo; i++){
		//poczatkowy koszt dodania to sasiedzi startowego wierzcholka
		costOfAdding[i] = values[startingPoint*vertexNo + i];
		if(costOfAdding[i] == -1) costOfAdding[i] = MAXINT;
	}
	
	//Krok 2 - petla dodawania kolejnych wierzcholkow
	int answerSize = 0; //ile krawedzi juz jest w odpowiedzi
	int answerTotal = 0; //suma wag w drzewie
	int* answer = (int*) malloc(0); //kazda para liczb to krawedz od a do b
	
	int cheapestVertex, cheapestAdd;
	
	while(1){
		cheapestAdd = MAXINT;
		
		//A - znajdz najtanszy wierzcholek jaki teraz mozna dodac
		for(int i = 0; i < vertexNo; i++){
			if(!partOfTree[i]){
				if(costOfAdding[i] < cheapestAdd){
					cheapestVertex = i;
					cheapestAdd = costOfAdding[i];
				}
			}
		}
		
		//B - dodaj go
		answerTotal += cheapestAdd;
		for(int i = 0; i < vertexNo; i++){
			if(partOfTree[i]){
				if(values[i*vertexNo + cheapestVertex] == cheapestAdd){
					answerSize++;
					answer = (int*) realloc(answer, answerSize*2*sizeof(int));
					answer[2*answerSize-2] = i;
					answer[2*answerSize-1] = cheapestVertex;
					break;
				}
			}
		}
		partOfTree[cheapestVertex] = true;
		
		if(answerSize == (vertexNo-1)) break; //mamy MDR
		
		//C - podlicz krawedzie wychodzace z nowo dodanego wierzcholka
		for(int i = 0; i < vertexNo; i++){
			cheapestAdd = values[cheapestVertex*vertexNo + i];
			if(cheapestAdd != -1) costOfAdding[i] = min(costOfAdding[i], cheapestAdd);
		}
	}
	
	if(output){
		cout << "Algorytm Prima, na macierzy, rozpoczeto od " << startingPoint << "\nWynik: " << answerTotal << "\n";
		for(int i = 0; i < answerSize*2; i += 2){
			cout << answer[i] << "-" << answer[i+1] << ", ";
		}
		cout << "\n";
	}
	
	free(answer);
}

void PrimList(ListGraph* target, bool output){
	//szybszy dostep
	int vertexNo = (target->vertexNo);
	int* outEdges = (target->outEdges);
	int** values = (target->values);
	
	int costOfAdding[vertexNo];
	bool partOfTree[vertexNo];
	for(int i = 0; i < vertexNo; i++){
		partOfTree[i] = false;
	}
	
	//Krok 1 - zainicjalizuj pierwszy wierzcholek
	int startingPoint = rng(0, vertexNo-1);
	partOfTree[startingPoint] = true;
	
	for(int i = 0; i < vertexNo; i++){
		//na poczatku nigdzie nie ma dostepu
		costOfAdding[i] = MAXINT;
	}
	
	for(int i = 0; i < outEdges[startingPoint]*2; i += 2){
		//poczatkowy koszt dodania to sasiedzi startowego wierzcholka
		costOfAdding[values[startingPoint][i]] = values[startingPoint][i+1];
	}
	
	//Krok 2 - petla dodawania kolejnych wierzcholkow
	int answerSize = 0; //ile krawedzi juz jest w odpowiedzi
	int answerTotal = 0; //suma wag w drzewie
	int* answer = (int*) malloc(0); //kazda para liczb to krawedz od a do b
	
	int cheapestVertex, cheapestAdd, targetV;
	
	while(1){
		cheapestAdd = MAXINT;
		
		//A - znajdz najtanszy wierzcholek jaki teraz mozna dodac
		for(int i = 0; i < vertexNo; i++){
			if(!partOfTree[i]){
				if(costOfAdding[i] < cheapestAdd){
					cheapestVertex = i;
					cheapestAdd = costOfAdding[i];
				}
			}
		}
		
		//B - dodaj go
		answerTotal += cheapestAdd;
		for(int i = 0; i < 2*outEdges[cheapestVertex]; i += 2){
			if(partOfTree[values[cheapestVertex][i]]){
				if(values[cheapestVertex][i+1] == cheapestAdd){
					answerSize++;
					answer = (int*) realloc(answer, answerSize*2*sizeof(int));
					answer[2*answerSize-2] = values[cheapestVertex][i];
					answer[2*answerSize-1] = cheapestVertex;
					break;
				}
			}
		}
		partOfTree[cheapestVertex] = true;
		
		if(answerSize == (vertexNo-1)) break; //mamy MDR
		
		//C - podlicz krawedzie wychodzace z nowo dodanego wierzcholka
		for(int i = 0; i < 2*outEdges[cheapestVertex]; i += 2){
			targetV = values[cheapestVertex][i];
			costOfAdding[targetV] = min(costOfAdding[targetV], values[cheapestVertex][i+1]);
		}
	}
	
	if(output){
		cout << "Algorytm Prima, na liscie, rozpoczeto od " << startingPoint << "\nWynik: " << answerTotal << "\n";
		for(int i = 0; i < answerSize*2; i += 2){
			cout << answer[i] << "-" << answer[i+1] << ", ";
		}
		cout << "\n";
	}
	
	free(answer);
}
