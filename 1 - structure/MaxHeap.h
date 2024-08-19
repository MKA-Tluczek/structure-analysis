#include "Random.h"
#include "QPC.h"
using namespace std;

class MaxHeap{
	public:
	int *values;
	int size;
	
	MaxHeap();
	
	bool integrityCheck(); //sprawdza czy wlasciwosci kopca sa zachowane
	
	void display(); //wyswietla kopiec graficznie warstwami
	void treeDisplay(); //wyswietla kopiec graficznie w formie drzewa (w taki sam sposob jak drzewo RB)
	void arrayDisplay(); //wyswietla kopiec jako tablice
	
	void readFromFile();
	
	void experiment(int runs, int number, int min, int max);
	
	int findValue(int index, int value); //szuka wartosci i zwraca jej indeks w kopcu, lub -1 jezeli takiej wartosci nie ma. Kopiec jest przeszukiwany od lewej do prawej
	int findIndex(int index); //zwraca wartosc we wskazanym indeksie
	
	void addValue(int value); //dodaj wartosc do kopca
	
	void deleteIndex(int index); //usun wartosc na wskazanej pozycji
	void deleteValue(int value); //usun dana wartosc z kopca jezeli taka istnieje
	
	private:
	void treePrint(int index, int level); //uzywane w treeDisplay() do rozpatrywania kazdego wierzcholka osobno podczas wypisywania
	void heapifyUp(int index); //przywracanie wlasnosci kopca idac w gore (uzywane przy dodawaniu elementow) Uruchamiane z perspektywy dolnego elementu sposrod porownywanych
	void heapifyDown(int index); //przywracanie wlasnosci kopca idac w dol (uzywane przy usuwaniu elementow) Uruchamiane z perspektywy gornego elementu sposrod trzech porownywanych
};
