#include "Random.h"
#include "QPC.h"
using namespace std;

class TreeNode{
	public:
	bool black, rightSon; //czy jestem czarny, czy jestem prawym synem (przyjmujemy ze korzen jest prawym synem, ale nie ma to znaczenia)
	int value;
	TreeNode *F, *LS, *RS; //father, left son, right son. Korzen ma NULL jako ojca
	
	TreeNode(TreeNode *FC, int valueC, bool rightSonC);
	
	void print(int level); //wypisuje zawartosc wezla, poprzedzajac ja wczesniej jakas liczba spacji dla widocznosci
	
	int deleteSelf(); //deleteValue() z drzewa bedzie uruchamiac ta procedure. Zwraca cos innego niz 0 w specjalnej sytuacji gdy drzewo sklada sie tylko z >= 2 wezlow
	
	void doubleBlackHandling(); //element zauwaza ze jest podwojnie czarny, i cos z tym robi
	void redParentHandling(); //element sprawdza czy jest czerwony i ma czerwonego rodzica, i cos z tym robi jezeli tak jest
	
	bool integrityCheckSub(); //sprawdza czy wlasciwosci drzewa sa zachowane
	
	private:
	void rotateLeft(); //moj prawy syn staje sie moim ojcem, a ja jego lewym synem
	void rotateRight(); //moj lewy syn staje sie moim ojcem, a ja jego prawym synem
};

class RBTree{
	public:
	TreeNode *root;
	
	bool integrityCheck(); //sprawdza czy wlasciwosci drzewa sa zachowane
	
	void display();
	void readFromFile();
	
	RBTree();
	
	void experiment(int runs, int number, int min, int max);
	
	TreeNode* findValue(int valueC); //zwraca wezel z podana wartoscia
	
	void addValue(int valueC);
	void deleteValue(int valueC);
};
