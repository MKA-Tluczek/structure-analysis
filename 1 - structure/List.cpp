#include <iostream>
#include <fstream>
#include "List.h"
using namespace std;

ListNode::ListNode(int Ivalue){
	prev = NULL;
	next = NULL;
	value = Ivalue;
}



List::List(){
	first = NULL;
	last = NULL;
}

void List::experiment(int runs, int number, int min, int max){
	
	int add, losowo;
	double time[7][number];
	
	for(int i = 0; i < 7; i++){
		for(int j = 0; j < number; j++){
			time[i][j] = 0;
		}
	}
	
	for(int run_number = 0; run_number < runs; run_number++){
		
		//0: TEST DODAWANIA DANYCH OD PRZODU (poczatek listy)
		//1: TEST SZUKANIA WARTOSCI
		for(int i = 0; i < number; i++){
			add = rng(min, max);
			startCounter();
			addFront(add);
			time[0][i] += getCounter();
			
			add = rng(min, max);
			startCounter();
			findValue2(add);
			time[1][i] += getCounter();
		}
		
		//2: TEST USUWANIA OD PRZODU (poczatek listy)
		for(int i = number-1; i >= 0; i--){
			startCounter();
			deleteFront();
			time[2][i] += getCounter();
		}
		
		//3: TEST DODAWANIA OD TYLU (koniec listy)
		for(int i = 0; i < number; i++){
			add = rng(min, max);
			startCounter();
			addBack(add);
			time[3][i] += getCounter();
		}
		
		//4: TEST USUWANIA OD TYLU (koniec listy)
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
	
	ofstream foutput("output_L.txt");
	
	for(int i = 0; i < number; i++){
		for(int j = 0; j < 7; j++){
			time[j][i] /= runs;
			foutput << time[j][i] << " ";
		}
		foutput << "\n";
	}
	
	foutput.close();
}

void List::display(){
	ListNode *reader = first;
	while(1){
		if(reader == NULL) break; //koniec listy
		cout << reader->value << ", ";
		reader = reader->next;
	}
	cout << "\n";
}

void List::readFromFile(){
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

ListNode* List::findIndex(int index){
	ListNode *temp = first;
	while(index > 0){
		if (temp == NULL) break; //dotarlismy do konca, nie ma gdzie isc dalej
		temp = temp -> next;
		index--;
	}
	return temp;
}

ListNode* List::findValue(int find){
	ListNode *temp = first;
	while(1){
		if (temp == NULL) return NULL; //dotarlismy do konca, nie ma gdzie szukac dalej
		if (temp->value == find) return temp; //znaleziono
		temp = temp -> next; //nie? To nastepny element
	}
}

int List::findValue2(int find){
	int counter = 0;
	ListNode *temp = first;
	while(1){
		if (temp == NULL) return -1;
		if (temp->value == find) return counter;
		temp = temp -> next;
		counter++;
	}
}

void List::addFront(int add){
	ListNode *neo = new ListNode(add);
	if (first != NULL){ //jezeli lista nie jest pusta, to stworzmy polaczenie z dotychczasowym pierwszym elementem
		first -> prev = neo;
		neo -> next = first;
	}
	else last = neo; //jezeli lista jest pusta, to nowy element jest jednoczesnie pierwszy i ostatni
	first = neo;
}

void List::addBack(int add){
	ListNode *neo = new ListNode(add);
	if (last != NULL){ //jezeli lista nie jest pusta, to stworzmy polaczenie z dotychczasowym ostatnim elementem
		last -> next = neo;
		neo -> prev = last;
	}
	else first = neo; //jezeli lista jest pusta, to nowy element jest jednoczesnie pierwszy i ostatni
	last = neo;
}

void List::addSpecific(int add, int pos){
	
	if (pos == 0){
		addFront(add); //bedzie prosciej uzyc gotowej funkcji od tego w takim wypadku
		return;
	}
	ListNode *targetPos = findIndex(pos);
	if (targetPos == NULL){
		addBack(add); //to samo
		return;
	}
	
	ListNode *neo = new ListNode(add);
	
	//wpychamy wartosc miedzy targetPos a poprzednia wartosc
	neo -> next = targetPos;
	neo -> prev = targetPos -> prev;
	
	//aktualizujemy polaczenia sasiadow
	neo -> prev -> next = neo;
	neo -> next -> prev = neo;
}

void List::deleteFront(){
	if (first == NULL) return;
	if (first == last){ //usuwamy jedyny element listy
		delete first;
		first = NULL;
		last = NULL;
		return;
	}
	first = first->next;
	delete first->prev;
	first->prev = NULL;
}

void List::deleteBack(){
	if (last == NULL) return;
	if (first == last){ //usuwamy jedyny element listy
		delete last;
		first = NULL;
		last = NULL;
		return;
	}
	last = last->prev;
	delete last->next;
	last->next = NULL;
}

void List::deleteSpecific(int pos){
	if (pos == 0){
		deleteFront();
		return;
	}
	ListNode *toDelete = findIndex(pos);
	if (toDelete == NULL) return;
	if (toDelete == last){
		deleteBack();
		return;
	}
	
	toDelete -> next -> prev = toDelete -> prev;
	toDelete -> prev -> next = toDelete -> next;
	delete toDelete;
};

void List::deleteValue(int value){
	ListNode *toDelete = findValue(value);
	if (toDelete == NULL) return;
	if (toDelete == first){
		deleteFront();
		return;
	}
	if (toDelete == last){
		deleteBack();
		return;
	}
	
	toDelete -> next -> prev = toDelete -> prev;
	toDelete -> prev -> next = toDelete -> next;
	delete toDelete;
};
