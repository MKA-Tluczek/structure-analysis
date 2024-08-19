#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "MaxHeap.h"
using namespace std;

bool MaxHeap::integrityCheck(){
	int LS;
	for(int i = 0; i < size; i++){
		LS = i*2 + 1;
		if(LS < size) if(values[i] < values[LS]) return false;
		LS++;
		if(LS < size) if(values[i] < values[LS]) return false;
	}
	return true;
}

void MaxHeap::display(){
	
	/*
	Format wyswietlania:
	P1: 0
	P2: 1 2
	P3: 3 4 5 6
	P4: 7 8 9 10 11 12 13 14...
	*/
	
	int layer = 1, layerPos = 1, layerSize = 1;
	cout << "P1: ";
	for(int i = 0; i < size; i++){
		
		if (layerPos > layerSize){ //przechodzimy do kolejnej warstwy
			layer++;
			cout << "\nP" << layer << ": ";
			layerSize *= 2;
			layerPos = 1;
		}
		
		cout << values[i] << " ";
		layerPos++;
	}
	cout << "\n";
}

void MaxHeap::treeDisplay(){
	if(size != 0) treePrint(0, 0);
}

void MaxHeap::arrayDisplay(){
	for (int i = 0; i < size; i++){
		cout << values[i] << ", ";
	}
	cout << "\n";
}

void MaxHeap::readFromFile(){
	ifstream myfile("input.txt");
	int counter, input;
	myfile >> counter;
	while(counter){
		myfile >> input;
		addValue(input);
		counter--;
	}
	myfile.close();
}

void MaxHeap::experiment(int runs, int number, int min, int max){
	
	int add, losowo;
	double time[5][number];
	
	for(int i = 0; i < 5; i++){
		for(int j = 0; j < number; j++){
			time[i][j] = 0;
		}
	}
	
	for(int run_number = 0; run_number < runs; run_number++){
		
		//0: TEST DODAWANIA DANYCH
		//1: TEST SZUKANIA WARTOSCI
		for(int i = 0; i < number; i++){
			add = rng(min, max);
			startCounter();
			addValue(add);
			time[0][i] += getCounter();
			
			add = rng(min, max);
			startCounter();
			findValue(0, add);
			time[1][i] += getCounter();
		}
		
		//2: TEST USUWANIA KORZENIA
		for(int i = number-1; i >= 0; i--){
			startCounter();
			deleteIndex(0);
			time[2][i] += getCounter();
		}
		
		//(wygeneruj szybko kopiec jeszcze raz do kolejnego testu...)
		for(int i = 0; i < number; i++){
			add = rng(min, max);
			addValue(add);
		}
		
		//3: TEST USUWANIA NAJWIEKSZEGO LISCIA
		for(int i = number-1; i >= 0; i--){
			startCounter();
			deleteIndex(i);
			time[3][i] += getCounter();
		}
		
		//(jeszcze raz...)
		for(int i = 0; i < number; i++){
			add = rng(min, max);
			addValue(add);
		}
		
		//4: TEST USUWANIA LOSOWO
		for(int i = number-1; i >= 0; i--){
			losowo = rng(0, i);
			startCounter();
			deleteIndex(losowo);
			time[4][i] += getCounter();
		}
		
		cout << run_number+1 << ",";
	}
	
	cout << "\n";
	
	ofstream foutput("output_MH.txt");
	
	for(int i = 0; i < number; i++){
		for(int j = 0; j < 5; j++){
			time[j][i] /= runs;
			foutput << time[j][i] << " ";
		}
		foutput << "\n";
	}
	
	foutput.close();
}

MaxHeap::MaxHeap(){
	size = 0;
	values = (int*) malloc(0);
}

int MaxHeap::findValue(int index, int value){
	/* funkcja rekurencyjna; pierwsze uruchomienie w kodzie jest dla korzenia,
	 * a kazdy wierzcholek uruchamia ta funkcje dla swoich dzieci i zwraca wartosc do swojego ojca,
	 * az korzen zwraca ostateczny wynik.
	 */
	
	if (index >= size) return -1;
	
	if (values[index] == value) return index;
	
	if (values[index] < value) return -1; //zadna z wartosci nizej nie bedzie juz rowna szukanej wiec przerwijmy ta galaz
	
	//pierwszy if tej funkcji sprawdza czy dany element istnieje, wiec nie sprawdamy czy synowie istnieja
	
	int candidate = findValue(index*2 + 1, value);
	if(candidate != -1) return candidate; //jezeli lewy syn cos znalazl, to koniec
	
	return findValue(index*2 + 2, value); //cokolwiek zwroci prawy syn jest rowniez moim wynkiem
}

int MaxHeap::findIndex(int index){
	if (index < size) return values[index];
	else return -1;
}

void MaxHeap::addValue(int value){
	size++;
	values = (int*) realloc (values, size*sizeof(int));
	values[size-1] = value;
	heapifyUp(size-1);
}

void MaxHeap::deleteIndex(int index){
	
	if(index >= size) return;
	
	//zamiana usuwanego elementu z ostatnim, ale nie ruszamy ostatniego elementu bo i tak go "ucinamy"
	values[index] = values[size-1];
	size--;
	values = (int*) realloc (values, size*sizeof(int));
	
	/* Kazda z metod heapify ma wewnatrz siebie sprawdzanie
	 * czy w danym kierunku trzeba w ogole cos robic,
	 * wiec nie robimy tego sprawdzania w metodzie deleteIndex.
	 */
	heapifyDown(index);
	heapifyUp(index);
}

void MaxHeap::deleteValue(int value){
	int target = findValue(0, value);
	if (target != -1) deleteIndex(target);
}

void MaxHeap::treePrint(int index, int level){
	int S = index*2 + 2;
	if(S < size) treePrint(S, level+1);
	for(int i = 0; i < level; i++) cout << "  ";
	cout << values[index] << "\n";
	S--;
	if(S < size) treePrint(S, level+1);
}

void MaxHeap::heapifyUp(int index){
	
	if(index == 0) return;
	
	int father = (index+1)/2-1;
	if(values[index] > values[father]){ //czy ta wartosc jest wieksza od swojego ojca?
		int temp = values[index];
		values[index] = values[father];
		values[father] = temp;
		heapifyUp(father); //kontynuuj w gore
	}
}

void MaxHeap::heapifyDown(int index){
	
	int leftSon = index*2 + 1, rightSon = leftSon + 1, whereSwap = 0;
	//whereSwap -> -1 z lewym, 0 z niczym, 1 z prawym
	
	if(rightSon < size){ //obaj synowie istnieja
		if(values[index] < values[leftSon]){ //lewy syn jest wiekszy...
			if(values[leftSon] >= values[rightSon]) whereSwap = -1; //...rowniez od prawego
			else whereSwap = 1; //...ale prawy jest jeszcze wiekszy
		}
		
		else if(values[index] < values[rightSon]) whereSwap = 1; //lewy syn jest mniejszy, ale prawy wiekszy
	}
	
	else if(leftSon < size){ //tylko lewy syn istnieje
		if(values[index] < values[leftSon]) whereSwap = -1;
	}
	
	if(whereSwap != 0){
		if(whereSwap == 1) whereSwap = rightSon;
		else whereSwap = leftSon;
		
		int temp = values[index];
		values[index] = values[whereSwap];
		values[whereSwap] = temp;
		heapifyDown(whereSwap); //kontynuuj w dol
	}
}
