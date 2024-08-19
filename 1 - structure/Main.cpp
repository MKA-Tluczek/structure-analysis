#include <iostream>
#include "Table.h"
#include "List.h"
#include "MaxHeap.h"
#include "RBTree.h"
using namespace std;

int main(){
	Table *tab = new Table;
	List *list = new List;
	MaxHeap *heap = new MaxHeap;
	RBTree *tree = new RBTree;
	
	prepareCounter();
	prepareSeed();
	
	char input;
	int a, b, c, d;
	
	while(1){
		
		cout << "1. Tablica\n";
		cout << "2. Lista\n";
		cout << "3. Kopiec\n";
		cout << "4. Drzewo\n";
		cout << "5. EKSPERYMENT\n";
		cout << "cokolwiek. Zakoncz\n";
		
		cin >> input;
		system("cls");
		
		switch(input){
			
			case '1':
				while(1){
					
					cout << "T A B L I C A\n";
					cout << "1. Wczytaj z pliku\n";
					cout << "2. Wyswietl\n";
					cout << "3. Zwroc wartosc z danego indeksu\n";
					cout << "4. Sprawdz czy dana wartosc znajduje sie w tablicy\n";
					cout << "5. Dodaj wartosc\n";
					cout << "6. Usun wartosc\n";
					cout << "cokolwiek. Wyjdz\n";
					
					cin >> input;
					
					switch(input){
						case '1':
							tab->readFromFile();
							system("cls");
							break;
						case '2':
							system("cls");
							tab->display();
							break;
						case '3':
							cout << "Podaj indeks ktory chcesz zwrocic: ";
							cin >> a;
							system("cls");
							cout << tab->findIndex(a) << "\n";
							break;
						case '4':
							cout << "Podaj wartosc ktora chcesz znalezc: ";
							cin >> a;
							system("cls");
							b = tab->findValue(a);
							if(b == -1) cout << "Nie znaleziono.\n";
							else cout << a << " znajduje sie na pozycji " << b << ".\n";
							break;
						case '5':
							cout << "Podaj pozycje, na ktora chcesz dodac wartosc, a potem wartosc.\n";
							cout << "Podaj pozycje \"-1\" aby dodac na koniec.\n";
							cin >> a >> b;
							
							if(a == 0) tab->addFront(b);
							else if(a == -1) tab->addBack(b);
							else tab->addSpecific(b, a);
							
							system("cls");
							break;
						case '6':
							cout << "Podaj pozycje, ktora chcesz usunac.\n";
							cout << "Podaj pozycje \"-1\" aby usunac ostatnia wartosc.\n";
							cout << "Podaj pozycje \"-2\" i dodaj na koniec wartosc, aby sprobowac znalezc i usunac ta konkretna liczbe.\n";
							cin >> a;
							
							if(a == 0) tab->deleteFront();
							else if(a == -1) tab->deleteBack();
							else if(a == -2){
								cin >> b;
								tab->deleteValue(b);
							}
							else tab->deleteSpecific(a);
							
							system("cls");
							break;
					}
					if(input < '1' || input > '6') break;
				}
				break;
			
			case '2':
				while(1){
					
					cout << "L I S T A\n";
					cout << "1. Wczytaj z pliku\n";
					cout << "2. Wyswietl\n";
					cout << "3. Zwroc wartosc z danego indeksu\n";
					cout << "4. Sprawdz czy dana wartosc znajduje sie w liscie\n";
					cout << "5. Dodaj wartosc\n";
					cout << "6. Usun wartosc\n";
					cout << "cokolwiek. Wyjdz\n";
					
					cin >> input;
					ListNode *target;
					
					switch(input){
						case '1':
							list->readFromFile();
							system("cls");
							break;
						case '2':
							system("cls");
							list->display();
							break;
						case '3':
							cout << "Podaj indeks ktory chcesz zwrocic: ";
							cin >> a;
							system("cls");
							target = list->findIndex(a);
							if(target == NULL) cout << "Nie ma takiego indeksu.\n";
							else cout << target->value << "\n";
							break;
						case '4':
							cout << "Podaj wartosc ktora chcesz znalezc: ";
							cin >> a;
							system("cls");
							b = list->findValue2(a);
							if(b == -1) cout << "Nie znaleziono.\n";
							else cout << a << " znajduje sie na pozycji " << b << ".\n";
							break;
						case '5':
							cout << "Podaj pozycje, na ktora chcesz dodac wartosc, a potem wartosc.\n";
							cout << "Podaj pozycje \"-1\" aby dodac na koniec.\n";
							cin >> a >> b;
							
							if(a == 0) list->addFront(b);
							else if(a == -1) list->addBack(b);
							else list->addSpecific(b, a);
							
							system("cls");
							break;
						case '6':
							cout << "Podaj pozycje, ktora chcesz usunac.\n";
							cout << "Podaj pozycje \"-1\" aby usunac ostatnia wartosc.\n";
							cout << "Podaj pozycje \"-2\" i dodaj na koniec wartosc, aby sprobowac znalezc i usunac ta konkretna liczbe.\n";
							cin >> a;
							
							if(a == 0) list->deleteFront();
							else if(a == -1) list->deleteBack();
							else if(a == -2){
								cin >> b;
								list->deleteValue(b);
							}
							else list->deleteSpecific(a);
							
							system("cls");
							break;
					}
					if(input < '1' || input > '6') break;
				}
				break;
			
			case '3':
				while(1){
					
					cout << "K O P I E C\n";
					cout << "1. Wczytaj z pliku\n";
					cout << "2. Wyswietl\n";
					cout << "3. Zwroc wartosc z danego indeksu\n";
					cout << "4. Sprawdz czy dana wartosc znajduje sie w kopcu\n";
					cout << "5. Dodaj wartosc\n";
					cout << "6. Usun konkretny indeks\n";
					cout << "7. Usun wartosc\n";
					cout << "8. Sprawdz wlasciwosc kopca\n";
					cout << "cokolwiek. Wyjdz\n";
					
					cin >> input;
					
					switch(input){
						case '1':
							heap->readFromFile();
							system("cls");
							break;
						case '2':
							cout << "Jaki sposob wyswietlania?\n";
							cout << "0 - wartswy, 1 - drzewo, 2 - tablica\n";
							cin >> a;
							system("cls");
							if (a == 0) heap->display();
							else if (a == 1) heap->treeDisplay();
							else if (a == 2) heap->arrayDisplay();
							break;
						case '3':
							cout << "Podaj indeks ktory chcesz zwrocic: ";
							cin >> a;
							system("cls");
							b = heap->findIndex(a);
							cout << b << "\n";
							break;
						case '4':
							cout << "Podaj wartosc ktora chcesz znalezc: ";
							cin >> a;
							system("cls");
							b = heap->findValue(0, a);
							if(b == -1) cout << "Nie znaleziono.\n";
							else cout << a << " znajduje sie na pozycji " << b << ".\n";
							break;
						case '5':
							cout << "Podaj liczbe do dodania: ";
							cin >> a;
							heap->addValue(a);
							system("cls");
							break;
						case '6':
							cout << "Podaj indeks do usuniecia: ";
							cin >> a;
							heap->deleteIndex(a);
							system("cls");
							break;
						case '7':
							cout << "Podaj wartosc do usuniecia: ";
							cin >> a;
							heap->deleteValue(a);
							system("cls");
							break;
						case '8':
							system("cls");
							if(heap->integrityCheck()) cout << "Wszystko OK!\n";
							else cout << "...cos ewidentnie poszlo nie tak.\n";
							break;
					}
					if(input < '1' || input > '8') break;
				}
				break;
			
			case '4':
				while(1){
					
					cout << "D R Z E W O\n";
					cout << "1. Wczytaj z pliku\n";
					cout << "2. Wyswietl\n";
					cout << "3. Sprawdz czy dana wartosc istnieje w drzewie\n";
					cout << "4. Dodaj wartosc\n";
					cout << "5. Usun wartosc\n";
					cout << "6. Sprawdz wlasnosc drzewa\n";
					cout << "cokolwiek. Wyjdz\n";
					
					cin >> input;
					TreeNode *target2;
					
					switch(input){
						case '1':
							tree->readFromFile();
							system("cls");
							break;
						case '2':
							system("cls");
							tree->display();
							break;
						case '3':
							cout << "Podaj wartosc ktora chcesz znalezc: ";
							cin >> a;
							system("cls");
							target2 = tree->findValue(a);
							if(target2 == NULL) cout << "Nie znaleziono.\n";
							else cout << a << " znajduje sie w drzewie.\n";
							break;
						case '4':
							cout << "Podaj liczbe do dodania: ";
							cin >> a;
							tree->addValue(a);
							system("cls");
							break;
						case '5':
							cout << "Podaj liczbe do usuniecia: ";
							cin >> a;
							tree->deleteValue(a);
							system("cls");
							break;
						case '6':
							system("cls");
							if(tree->integrityCheck()) cout << "Wszystko OK!\n";
							else cout << "...cos ewidentnie poszlo nie tak.\n";
							break;
					}
					if(input < '1' || input > '6') break;
				}
				break;
			
			case '5':
				cout << "Podaj kolejno: Liczba prob, liczba danych, najmniejsza wartosc, najwieksza wartosc\n";
				cin >> a >> b >> c >> d;
				
				cout << "Czy wykonac eksperyment dla: Tablicy, Listy, Kopca, Drzewa?\n";
				cout << "Podaj kolejno cztery litery (y/n): ";
				
				cin >> input;
				if(input == 'y'){
					Table *tabE = new Table;
					tabE->experiment(a, b, c, d);
					delete tabE;
				}
				cin >> input;
				if(input == 'y'){
					List *listE = new List;
					listE->experiment(a, b, c, d);
					delete listE;
				}
				cin >> input;
				if(input == 'y'){
					MaxHeap *heapE = new MaxHeap;
					heapE->experiment(a, b, c, d);
					delete heapE;
				}
				cin >> input;
				if(input == 'y'){
					RBTree *treeE = new RBTree;
					treeE->experiment(a, b, c, d);
					delete treeE;
				}
				
				break;
			
			default:
				return 0;
		}
		
		system("cls");
	}
	
	return 0;
}
