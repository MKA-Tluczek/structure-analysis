#include <iostream>
#include "Random.h"
#include "QPC.h"
#include "MatrixGraph.h"
#include "ListGraph.h"
#include "GraphMaker.h"
#include "Prim.h"
#include "Kruskal.h"
#include "Dijkstra.h"
#include "BellmanFord.h"
using namespace std;
	
void experiment(MatrixGraph* graf1, ListGraph* graf2){
	
	//dla ilu wierzcholkow przeprowadzic kazda kolejna serie?
	int V[5] = {10, 20, 50, 100, 200};
	
	//dla jakiej gestosci przeprowadzic kazda kolejna serie?
	int G[4] = {25, 50, 75, 99};
	
	//ile prob w kazdej serii?
	int N = 100;
	
	double stats[8][20];
	for(int i = 0; i < 8; i++){
		for(int j = 0; j < 20; j++){
			stats[i][j] = 0.0;
		}
	}
	
	int re, czas, a, b;
	for(int i = 0; i < N; i++){
		for(int v = 0; v < 5; v++){
			for(int g = 0; g < 4; g++){
				graf1->setDirected(false);
				graf2->setDirected(false);
				generate(V[v], G[g], graf1, graf2);
				for(re = 0; re < 5; re++){
					
					startCounter();
					PrimMatrix(graf1, false);
					czas = getCounter();
					stats[0][v*4 + g] += czas;
					
					startCounter();
					PrimList(graf2, false);
					czas = getCounter();
					stats[1][v*4 + g] += czas;
					
					startCounter();
					KruskalMatrix(graf1, false);
					czas = getCounter();
					stats[2][v*4 + g] += czas;
					
					startCounter();
					KruskalList(graf2, false);
					czas = getCounter();
					stats[3][v*4 + g] += czas;
				}
				
				graf1->setDirected(true);
				graf2->setDirected(true);
				generate(V[v], G[g], graf1, graf2);
				for(re = 0; re < 5; re++){
					
					a = rng(0, V[v]-1);
					b = rng(0, V[v]-1);
					
					startCounter();
					DijkstraMatrix(graf1, a, b, false);
					czas = getCounter();
					stats[4][v*4 + g] += czas;
					
					startCounter();
					DijkstraList(graf2, a, b, false);
					czas = getCounter();
					stats[5][v*4 + g] += czas;
					
					startCounter();
					BellmanFordMatrix(graf1, a, b, false);
					czas = getCounter();
					stats[6][v*4 + g] += czas;
					
					startCounter();
					BellmanFordList(graf2, a, b, false);
					czas = getCounter();
					stats[7][v*4 + g] += czas;
				}
			}
		}
		cout << i << ".";
	}
	cout << "\n";
	
	for(int i = 0; i < 8; i++){
		cout << "WYNIKI DLA ALGORYTMU " << i << "\n";
		for(int v = 0; v < 5; v++){
			for(int g = 0; g < 4; g++){
				cout << "[V:" << V[v] << "][G:" << G[g] << "]" << (stats[i][v*4 + g])/double(N)/5.0 << "ms\n";
			}
		}
	}
}

int main(){
	prepareSeed();
	prepareCounter();
	MatrixGraph* graf1 = new MatrixGraph();
	ListGraph* graf2 = new ListGraph();
	int input, input2;
	
	bool quit;
	while(1){
		cout << "0 aby uruchomic eksperyment, 1 dla MDR, 2 dla najkrotszej sciezki w grafie, 3 aby wyjsc: ";
		cin >> input;
		system("cls");
		switch(input){
			case 1:
				graf1->setDirected(false);
				graf1->clear();
				graf2->setDirected(false);
				graf2->clear();
				while(1){
					cout << "Wyznaczanie minimalnego drzewa rozpinajacego\n\n";
					cout << "1. Wczytaj plik\n";
					cout << "2. Wygeneruj graf\n";
					cout << "3. Pokaz graf macierzowo\n";
					cout << "4. Pokaz graf listowo\n";
					cout << "5. Algorytm Prima na macierzy\n";
					cout << "6. Algorytm Prima na liscie\n";
					cout << "7. Algorytm Kruskala na macierzy\n";
					cout << "8. Algorytm Kruskala na liscie\n";
					cout << "9. Wyjdz\n";
					cin >> input;
					switch(input){
						case 1:
							system("cls");
							readFromFile(graf1, graf2);
							break;
						case 2:
							cout << "Podaj liczbe wierzcholkow i gestosc grafu w procentach: ";
							cin >> input >> input2;
							system("cls");
							generate(input, input2, graf1, graf2);
							break;
						case 3:
							system("cls");
							graf1->print();
							cout << "\n";
							break;
						case 4:
							system("cls");
							graf2->print();
							cout << "\n";
							break;
						case 5:
							system("cls");
							PrimMatrix(graf1, true);
							cout << "\n";
							break;
						case 6:
							system("cls");
							PrimList(graf2, true);
							cout << "\n";
							break;
						case 7:
							system("cls");
							KruskalMatrix(graf1, true);
							cout << "\n";
							break;
						case 8:
							system("cls");
							KruskalList(graf2, true);
							cout << "\n";
							break;
						case 9:
							system("cls");
							break;
					}
					if(input == 9) break;
				}
				break;
			case 2:
				graf1->setDirected(true);
				graf1->clear();
				graf2->setDirected(true);
				graf2->clear();
				while(1){
					cout << "Wyznaczanie najkrotszej sciezki w grafie\n\n";
					cout << "1. Wczytaj plik\n";
					cout << "2. Wygeneruj graf\n";
					cout << "3. Pokaz graf macierzowo\n";
					cout << "4. Pokaz graf listowo\n";
					cout << "5. Algorytm Dijkstry na macierzy\n";
					cout << "6. Algorytm Dijkstry na liscie\n";
					cout << "7. Algorytm Bellmana-Forda na macierzy\n";
					cout << "8. Algorytm Bellmana-Forda na liscie\n";
					cout << "9. Wyjdz\n";
					cin >> input;
					switch(input){
						case 1:
							system("cls");
							readFromFile(graf1, graf2);
							break;
						case 2:
							cout << "Podaj liczbe wierzcholkow i gestosc grafu w procentach: ";
							cin >> input >> input2;
							system("cls");
							generate(input, input2, graf1, graf2);
							break;
						case 3:
							system("cls");
							graf1->print();
							cout << "\n";
							break;
						case 4:
							system("cls");
							graf2->print();
							cout << "\n";
							break;
						case 5:
							cout << "Podaj wierzcholek startowy i koncowy: ";
							cin >> input >> input2;
							system("cls");
							DijkstraMatrix(graf1, input, input2, true);
							cout << "\n";
							break;
						case 6:
							cout << "Podaj wierzcholek startowy i koncowy: ";
							cin >> input >> input2;
							system("cls");
							DijkstraList(graf2, input, input2, true);
							cout << "\n";
							break;
						case 7:
							cout << "Podaj wierzcholek startowy i koncowy: ";
							cin >> input >> input2;
							system("cls");
							BellmanFordMatrix(graf1, input, input2, true);
							cout << "\n";
							break;
						case 8:
							cout << "Podaj wierzcholek startowy i koncowy: ";
							cin >> input >> input2;
							system("cls");
							BellmanFordList(graf2, input, input2, true);
							cout << "\n";
							break;
						case 9:
							system("cls");
							break;
					}
					if(input == 9) break;
				}
				break;
			case 3:
				quit = true;
				break;
			case 0:
				experiment(graf1, graf2);
				break;
		}
		if(quit) break;
	}
}
