#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "Table.h"
using namespace std;

void Table::display(){
	for (int i = 0; i < size; i++){
		cout << values[i] << ", ";
	}
	cout << "\n";
}

void Table::readFromFile(){
	ifstream myfile("input.txt");
	int counter, input;
	myfile >> counter;
	while(counter){
		myfile >> input;
		addBack(input);
		counter--;
	}
	myfile.close();
}

void Table::experiment(int runs, int number, int min, int max){
	
	int add, losowo;
	double time[7][number];
	
	for(int i = 0; i < 7; i++){
		for(int j = 0; j < number; j++){
			time[i][j] = 0;
		}
	}
	
	for(int run_number = 0; run_number < runs; run_number++){
		
		//0: TEST DODAWANIA DANYCH OD PRZODU (poczatek tablicy)
		//1: TEST SZUKANIA WARTOSCI
		for(int i = 0; i < number; i++){
			add = rng(min, max);
			startCounter();
			addFront(add);
			time[0][i] += getCounter();
			
			add = rng(min, max);
			startCounter();
			findValue(add);
			time[1][i] += getCounter();
		}
		
		//2: TEST USUWANIA OD PRZODU (poczatek tablicy)
		for(int i = number-1; i >= 0; i--){
			startCounter();
			deleteFront();
			time[2][i] += getCounter();
		}
		
		//3: TEST DODAWANIA OD TYLU (koniec tablicy)
		for(int i = 0; i < number; i++){
			add = rng(min, max);
			startCounter();
			addBack(add);
			time[3][i] += getCounter();
		}
		
		//4: TEST USUWANIA OD TYLU (koniec tablicy)
		for(int i = number-1; i >= 0; i--){
			startCounter();
			deleteBack();
			time[4][i] += getCounter();
		}
		
		//5: TEST DODAWANIA LOSOWO
		for(int i = 0; i < number; i++){
			add = rng(min, max);
			losowo = rng(0, i);
			startCounter();
			addSpecific(add, losowo);
			time[5][i] += getCounter();
		}
		
		//6: TEST USUWANIA LOSOWO
		for(int i = number-1; i >= 0; i--){
			losowo = rng(0, i);
			startCounter();
			deleteSpecific(losowo);
			time[6][i] += getCounter();
		}
		
		cout << run_number+1 << ",";
	}
	
	cout << "\n";
	
	ofstream foutput("output_T.txt");
	
	for(int i = 0; i < number; i++){
		for(int j = 0; j < 7; j++){
			time[j][i] /= runs;
			foutput << time[j][i] << " ";
		}
		foutput << "\n";
	}
	
	foutput.close();
}

Table::Table(){
	size = 0;
	values = (int*) malloc (0);
}

int Table::findIndex(int index){
	if (index < size) return values[index];
	else return 0;
}

int Table::findValue(int value){
	for (int i = 0; i < size; i++){
		if (values[i] == value) return i;
	}
	return -1;
}

void Table::addFront(int add){
	sizePlus();
	for(int i = size-1; i > 0; i--){
		values[i] = values[i-1];
	}
	values[0] = add;
}

void Table::addBack(int add){
	sizePlus();
	values[size-1] = add;
}

void Table::addSpecific(int add, int pos){
	if(pos < 0) return;
	sizePlus();
	for(int i = size-1; i > pos; i--){
		values[i] = values[i-1];
	}
	if(pos >= size) values[size-1] = add;
	else values[pos] = add;
}

void Table::deleteFront(){
	for(int i = 0; i < size-1; i++){
		values[i] = values[i+1];
	}
	sizeMinus();
}

void Table::deleteBack(){
	sizeMinus();
}

void Table::deleteSpecific(int pos){
	if(pos < 0) return;
	if(pos >= size) return;
	for(int i = pos; i < size-1; i++){
		values[i] = values[i+1];
	}
	sizeMinus();
}

void Table::deleteValue(int value){
	deleteSpecific(findValue(value));
}

void Table::sizePlus(){
	size++;
	values = (int*) realloc (values, size*sizeof(int));
}

void Table::sizeMinus(){
	if(size == 0) return;
	size--;
	values = (int*) realloc (values, size*sizeof(int));
}
