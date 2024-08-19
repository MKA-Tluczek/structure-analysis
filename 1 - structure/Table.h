#include "Random.h"
#include "QPC.h"
using namespace std;

class Table{
	public:
	int* values;
	int size;
	
	Table();
	
	void display();
	void readFromFile();
	
	void experiment(int runs, int number, int min, int max);
	
	int findIndex(int index); //zwraca wartosc na danym indeksie
	int findValue(int find); //zwraca indeks na jakim znajduje sie dana wartosc, jezeli istnieje. -1 w przeciwnym wypadku
	
	void addFront(int add); //dodaj wartosc na poczatek tablicy
	void addBack(int add); //dodaj wartosc na koniec tablicy
	void addSpecific(int add, int pos); //dodaj wartosc na wskazana pozycje. Jezeli tablica jest mniejsza, dodaje zamiast tego na koniec listy. Nic nie robi jesli podana zostanie ujemna pozycja
	
	void deleteFront(); //usuwa pierwszy element
	void deleteBack(); //usuwa ostatni element
	void deleteSpecific(int pos); //usuwa dany element. Jezeli nie ma takiego elementu (lista jest mniejsza) to nie usuwa nic
	void deleteValue(int value); //usuwa dana wartosc jezeli istnieje wewnatrz listy
	
	private:
	void sizePlus(); //powiekszenie tablicy o 1
	void sizeMinus(); //zmniejszenie tablicy o 1
};
