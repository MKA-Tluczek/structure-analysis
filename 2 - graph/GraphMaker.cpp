#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "Random.h"
#include "MatrixGraph.h"
#include "ListGraph.h"
#include "GraphMaker.h"
using namespace std;

void readFromFile(MatrixGraph* targetM, ListGraph* targetL){
	ifstream myfile("input.txt");
	int v, e, inputFrom, inputTo, inputWeight;
	myfile >> e >> v;
	targetM->changeSize(v);
	targetL->changeSize(v);
	targetM->clear();
	targetL->clear();
	
	while(e){
		myfile >> inputFrom >> inputTo >> inputWeight;
		targetM->addEdge(inputFrom, inputTo, inputWeight);
		targetL->addEdge(inputFrom, inputTo, inputWeight);
		e--;
	}
	myfile.close();
}

void generate(int v, int g, MatrixGraph* targetM, ListGraph* targetL){
	targetM->changeSize(v);
	targetL->changeSize(v);
	targetM->clear();
	targetL->clear();
	
	int Eleft = (v*v - v)/2; //ile jest mozliwych krawedzi
	int Etoadd = Eleft*g / 100; //ile krawedzi trzeba jeszcze dodac
	bool edge[v*v]; //edge[a*v + b] = czy istnieje krawedz miedzy a i b
	for(int i = 0; i < v*v; i++) edge[i] = false;
	
	//Krok 1 - aby zapewnic spojnosc grafu, zaczniemy generacje od losowego drzewa
	bool isInTree[v]; //jezeli isInTree[x] == true, to x jest elementem spojnego drzewa
	for(int i = 0; i < v; i++) isInTree[i] = false;
	isInTree[rng(0, v-1)] = true; //losowy wierzcholek jest punktem startowym dla drzewa startowego
	
	if(Etoadd < v-1) cout << "Uwaga: Podana gestosc jest za mala aby wygenerowac spojne drzewo ze wszystkich wierzcholkow. Algorytmy MDR nie beda dzialac.\n";
	
	int look, a, b, weight, exist, notexist;
	for(int i = 0, limit = min(Etoadd, v-1); i < limit; i++){
		look = 0; a = -1; b = -1;
		
		   exist = rng(1, i+1); //ktory wierzcholek ktory juz jest w grafie?
		notexist = rng(1, v-i-1); //ktory wierzcholek ktory tam jeszcze nie jest?
		
		while((a == -1) || (b == -1)){
			if(isInTree[look]){
				exist--;
				if(exist == 0) a = look; //wez dany wierzcholek z drzewa do jednej "reki"
			}
			else{
				notexist--;
				if(notexist == 0){
					b = look; //wez dany wierzcholek spoza drzewa do drugiej "reki"
					isInTree[b] = true; //i dodaj go do drzewa
				}
			}
			look++;
		}
		
		//te dwa wierzcholki maja teraz polaczenie
		edge[a*v + b] = true;
		edge[b*v + a] = true;
		
		weight = rng(0,1000); //wylosuj wage krawedzi
		
		if(rng(0,1)){ //wylosuj kierunek krawedzi
			targetM->addEdge(a,b,weight);
			targetL->addEdge(a,b,weight);
		}
		else{
			targetM->addEdge(b,a,weight);
			targetL->addEdge(b,a,weight);
		}
		
		Eleft--;
		Etoadd--;
	}
	
	//Krok 2 - wypelnianie reszty grafu losowymi krawedziami
	//rng(1, Eleft) <= Etoadd
	for(int from = 0; from < v; from++){
		for(int to = from+1; to < v; to++){ //nie rozpatruj kazdej krawedzi dwa razy
			if(edge[from*v + to] == false){ //jezeli ta krawedz juz zostala dodana w pierwszym kroku to pomin
				if(rng(1, Eleft) <= Etoadd){ //szansa_ze_krawedz_zostanie_dodana = (ile_krawedzi_trzeba_dodac)/(ile_krawedzi_jeszcze_zostanie_rozpatrzonych)
					weight = rng(0,9);
					if(rng(0,1)){ //wylosuj kierunek krawedzi
						targetM->addEdge(from,to,weight);
						targetL->addEdge(from,to,weight);
					}
					else{
						targetM->addEdge(to,from,weight);
						targetL->addEdge(to,from,weight);
					}
					Etoadd--;
				}
				Eleft--;
			}
		}
	}
}
