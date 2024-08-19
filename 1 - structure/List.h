#include "Random.h"
#include "QPC.h"
using namespace std;

class ListNode{
	public:
	int value;
	ListNode *prev, *next;
	
	ListNode(int Ivalue);
};

class List{
	public:
	ListNode *first, *last; //wskaznik na pierwszy i ostatni element listy
	
	List();
	
	void experiment(int runs, int number, int min, int max);
	
	void display(); //pokaz zawartosc listy
	void readFromFile();
	
	ListNode* findIndex(int index); //zwraca wskaznik na element listy o indeksie index. Zwraca NULL jesli lista jest mniejsza i nie ma takiej pozycji
	ListNode* findValue(int find); //szuka czy dana wartosc jest w liscie i zwraca tam wskaznik
	int findValue2(int find);      //szuka czy dana wartosc jest w liscie i zwraca numer indeksu
	
	void addFront(int add); //dodaj wartosc add na poczatek listy
	void addBack(int add); //dodaj wartosc add na koniec listy
	void addSpecific(int add, int pos); //dodaj wartosc na wskazana pozycje. Jezeli lista jest mniejsza, dodaje zamiast tego na koniec listy
	
	void deleteFront(); //usuwa pierwszy element
	void deleteBack(); //usuwa ostatni element
	void deleteSpecific(int pos); //usuwa dany element. Jezeli nie ma takiego elementu (lista jest mniejsza) to nie usuwa nic
	void deleteValue(int value); //usuwa dana wartosc jezeli istnieje wewnatrz listy
};
