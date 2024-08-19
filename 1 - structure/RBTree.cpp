#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "RBTree.h"
using namespace std;

TreeNode::TreeNode(TreeNode *FC, int valueC, bool rightSonC){
	black = false;
	rightSon = rightSonC;
	value = valueC;
	F = FC;
	LS = NULL;
	RS = NULL;
}

void TreeNode::print(int level){
	if(RS != NULL) RS->print(level+1);
	
	for(int i = 0; i < level; i++) cout << "  ";
	cout << value;
	if(black) cout << "b";
	else cout << "r";
	cout << "\n";
	
	if(LS != NULL) LS->print(level+1);
}

int TreeNode::deleteSelf(){
	
	//Ile mam dzieci?
	int sCase = 0;
	if(LS != NULL) sCase += 1;
	if(RS != NULL) sCase += 2;
	
	if(F == NULL){
		if(sCase != 3){
			return sCase; //sytuacja wyjatkowa: Musimy usunac korzen, gdy w drzewie jest tylko 2 lub 1 wezlow
		}
	}
	
	switch(sCase){
		
		case 0: //bez dzieci
			if(black) doubleBlackHandling(); //null po mnie bedzie podwojnie czarny
			
			if(rightSon) F->RS = NULL;
			else F->LS = NULL;
			
			delete this; return 0;
		
		case 1: //tylko lewy syn
			
			//polaczenie mojego ojca i syna ze soba
			if(rightSon){
				F->RS = LS;
				LS->rightSon = true;
			}
			else{
				F->LS = LS;
				LS->rightSon = false;
			}
			LS->F = F;
			
			if(black && LS->black){
				LS->doubleBlackHandling(); //jezeli oboje bylismy czarni, to teraz moj syn jest podwojnie czarny
			}
			else LS->black = true; //w przeciwnym wypadku moj syn teraz na 100% jest czarny
			delete this; return 0;
		
		case 2: //tylko prawy syn
			
			//polaczenie mojego ojca i syna ze soba
			if(rightSon){
				F->RS = RS;
				RS->rightSon = true;
			}
			else{
				F->LS = RS;
				RS->rightSon = false;
			}
			RS->F = F;
			
			if(black && RS->black){
				RS->doubleBlackHandling(); //jezeli oboje bylismy czarni, to teraz moj syn jest podwojnie czarny
			}
			else RS->black = true; //w przeciwnym wypadku moj syn teraz na 100% jest czarny
			delete this; return 0;
		
		case 3: //dwaj synowie
			
			//Ja kopiuje wartosc swojego poprzednika...
			TreeNode *search = LS;
			while(search->RS != NULL) search = search->RS;
			value = search->value;
			
			//...a to poprzednik zostaje usuniety
			search->deleteSelf();
			return 0;
	}
}

void TreeNode::doubleBlackHandling(){
	if(F == NULL) return; //podwojnie czarny korzen - usuwamy jedna czern z calego drzewa
	
	if(rightSon){
		//Dotyczy 1 & 2: nie musimy sprawdzac czy brat istnieje - ojciec podwojnie czarnego elementu
		//na pewno ma conajmniej jeden czarny element w swoim drugim poddrzewie
		
		//Sytuacja 1: Moj brat jest czerwony - obrocmy ojca zeby tak nie bylo
		//Po obrocie moj brat na pewno jest czarny
		if(F->LS->black == false) F->rotateRight();
		
		//Sytuacja 2: Moj brat jest czarny i nie ma zadnego czerwonego syna
		TreeNode *brother = F->LS;
		bool pushup = true;
		if(brother->LS != NULL){
			if(brother->LS->black == false) pushup = false;
		}
		if(brother->RS != NULL){
			if(brother->RS->black == false) pushup = false;
		}
		
		//Przepchnij czern jeden poziom w gore
		if(pushup){
			brother->black = false;
			if(F->black) F->doubleBlackHandling(); //teraz ojciec ma podwojna czern
			else F->black = true;
			return;
		}
		
		//Sytuacja 3: Moj brat jest czarny i ma co najmniej jednego czerwonego syna
		//Najpierw czerwony syn musi byc synem tego samego typu - obrocmy brata jesli tak nie jest
		
		if(brother->LS == NULL){
			brother->rotateLeft();
			brother = brother->F;
		}
		else if(brother->LS->black == true){
			brother->rotateLeft();
			brother = brother->F;
		}
		
		//teraz obracamy ojca
		F->rotateRight();
		
		//wyrownanie kolorow na drugiej stronie:
		//po naszej stronie musimy usunac jedna czern (czyli nas)
		//a po drugiej dodac jedna czern
		brother->LS->black = true;
	}
	
	else{
		//1
		if(F->RS->black == false) F->rotateLeft();
		
		//2
		TreeNode *brother = F->RS;
		bool pushup = true;
		if(brother->LS != NULL){
			if(brother->LS->black == false) pushup = false;
		}
		if(brother->RS != NULL){
			if(brother->RS->black == false) pushup = false;
		}
		
		if(pushup){
			brother->black = false;
			if(F->black) F->doubleBlackHandling();
			else F->black = true;
			return;
		}
		
		//3
		if(brother->RS == NULL){
			brother->rotateRight();
			brother = brother->F;
		}
		else if(brother->RS->black == true){
			brother->rotateRight();
			brother = brother->F;
		}
		
		F->rotateLeft();
		brother->RS->black = true;
	}
}

void TreeNode::redParentHandling(){
	
	if(F == NULL) return;
	
	//najpierw test
	if(!black && F -> black == false){
		
		//Podejscie 1: czy wujek jest czerwony (i czy w ogole istnieje)?
		bool pushdown = false;
		
		if(F->rightSon){
			if(F->F->LS != NULL)
			if(F->F->LS->black == false) pushdown = true;
		}
		else{
			if(F->F->RS != NULL)
			if(F->F->RS->black == false) pushdown = true;
		}
		
		if(pushdown){
			//Jezeli tak, to przepchnij czern w dol od dziadka
			TreeNode *G = F->F;
			G -> black = false;
			G -> RS -> black = true;
			G -> LS -> black = true;
			
			//dziadek jest teraz czerwony, wiec potencjalnie moglby miec czerwonego ojca
			G -> redParentHandling();
			return;
		}
		
		//Podejscie 2: Czy ja i moj ojciec jestesmy roznymi synami?
		//Jezeli tak, musimy sie najpierw obrocic zanim przejdziemy dalej
		if(rightSon != F->rightSon){
			if(rightSon){
				F->rotateLeft();
				LS->redParentHandling(); //teraz ja jestem ojcem, wiec musimy kontynuowac z perspektywy mojego syna
				return;
			}
			else{
				F->rotateRight();
				RS->redParentHandling();
				return;
			}
		}
		
		//Podejscie 3: Ja i moj ojciec jestesmy tymi samymi synami na pewno:
		//Obroc dziadka i ojca i zamien ich kolorami
		if(rightSon){
			F -> F -> rotateLeft();
			
			//moj nowy brat, ktory jest czerwony, moze miec czerwonego syna; trzeba to sprawdzic
			if(F->LS->LS != NULL) F->LS->LS->redParentHandling();
			return;
		}
		else{
			F -> F -> rotateRight();
			
			//moj nowy brat, ktory jest czerwony, moze miec czerwonego syna; trzeba to sprawdzic
			if(F->RS->RS != NULL) F->RS->RS->redParentHandling();
			return;
		}
	}
}

bool TreeNode::integrityCheckSub(){
	
	/*
	...
	Zasada 4: Czerwony wezel nie moze miec czerwonego syna
	Zasada 5: Sciezka do kazdego NIL liscia przechodzi przez tyle samo czarnych wezlow
	*/
	
	if(RS != NULL){
		if(black == false && RS->black == false) return false; //Naruszenie zasady 4
		if(RS->value < value)                    return false; //Naruszenie zasady 5
		if(RS->rightSon == false)                return false; //Naruszenie... czegos na pewno
		if(RS->integrityCheckSub() == false)     return false; //Naruszenie czegos glebiej w drzewie
	}
	if(LS != NULL){
		if(black == false && LS->black == false) return false;
		if(LS->value > value)                    return false;
		if(LS->rightSon == true)                 return false;
		if(LS->integrityCheckSub() == false)     return false;
	}
	return true;
}

void TreeNode::rotateLeft(){
	
	TreeNode *S = RS -> LS; //wnuk ktory zmienia ojca podczas obrotu
	
	//1: zamieniam sie kolorami z synem z ktorym sie obracam
	bool temp = black;
	black = RS->black;
	RS->black = temp;
	
	//2: Przelaczenie mojego ojca
	//2a: Jezeli nie jestem korzeniem, to moj ojciec ma nowego syna
	if(F != NULL){
		if(rightSon) F -> RS = RS;
		else F -> LS = RS;
	}
	
	//2b: syn z ktorym sie obracam ma nowego ojca, jest takim samym synem jak ja
	RS -> F = F;
	RS -> rightSon = rightSon;
	
	//3: Zmiana relacji z moim synem z ktorym sie obracam
	//3a: jego perspektywa
	RS -> LS = this;
	
	//3b: moja perspektywa
	F = RS;
	rightSon = false;
	
	//4: Przekazanie srodkowego wnuka
	//4a: Jego perspektywa, jezeli w ogole istnieje
	if(S != NULL){
		S -> F = this;
		S -> rightSon = true;
	}
	
	//4b: moja perspektywa
	RS = S;
}

void TreeNode::rotateRight(){
	
	//ta sama procedura co w rotateLeft, tylko lustrzane odbicie
	
	TreeNode *S = LS -> RS;
	
	//1
	bool temp = black;
	black = LS->black;
	LS->black = temp;
	
	//2
	if(F != NULL){
		if(rightSon) F -> RS = LS;
		else F -> LS = LS;
	}
	
	LS -> F = F;
	LS -> rightSon = rightSon;
	
	//3
	LS -> RS = this;
	F = LS;
	rightSon = true;
	
	//4
	if(S != NULL){
		S -> F = this;
		S -> rightSon = false;
	}
	
	LS = S;
}





bool RBTree::integrityCheck(){
	
	/*
	Zasada 1: Kazdy wezel jest czerwony lub czarny (spelniona automatycznie z implementacji)
	Zasada 2: Korzen jest czarny
	Zasada 3: Kazdy NIL lisc jest czarny (spelnione automatycznie z implementacji (a dokladnie NILe nie sa implementowane))
	Zasada 4: Czerwony wezel nie moze miec czerwonego syna
	Zasada 5: Sciezka do kazdego NIL liscia przechodzi przez tyle samo czarnych wezlow
	*/
	
	if(root == NULL) return true; //nie moge byc zepsutym jesli nie istnieje
	
	if(root->black == false) return false; //Naruszenie zasady 2
	
	return root->integrityCheckSub();
}

void RBTree::display(){
	if(root != NULL) root->print(0);
}

void RBTree::readFromFile(){
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

RBTree::RBTree(){
	root = NULL;
}

void RBTree::experiment(int runs, int number, int min, int max){
	
	int add, losowo, inside[number];
	double time[4][number];
	
	for(int i = 0; i < 4; i++){
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
			findValue(add);
			time[1][i] += getCounter();
		}
		
		//2: TEST USUWANIA KORZENIA
		for(int i = number-1; i >= 0; i--){
			startCounter();
			deleteValue(root->value);
			time[2][i] += getCounter();
		}
		
		//(wygeneruj szybko drzewo jeszcze raz do kolejnego testu...)
		
		/* ...z czego losowanie elementu z drzewa binarnego nie jest oczywiste,
		 * dlatego na potrzeby eksperymentu stworzona zostanie tablica wszystkich
		 * wartosci ktore sa w srodku, a potem test losowego usuwania bedzie bral
		 * losowa wartosc z tej tablicy
		 */
		for(int i = 0; i < number; i++){
			add = rng(min, max);
			addValue(add);
			inside[i] = add;
		}
		
		//3: TEST USUWANIA LOSOWO
		for(int i = number-1; i >= 0; i--){
			losowo = rng(0, i);
			add = inside[losowo];
			inside[losowo] = inside[i]; //aby usunac juz uzyte wartosci z tablicy pomocniczej
			startCounter();
			deleteValue(add);
			time[3][i] += getCounter();
		}
		
		cout << run_number+1 << ",";
	}
	
	cout << "\n";
	
	ofstream foutput("output_RBT.txt");
	
	for(int i = 0; i < number; i++){
		for(int j = 0; j < 4; j++){
			time[j][i] /= runs;
			foutput << time[j][i] << " ";
		}
		foutput << "\n";
	}
	
	foutput.close();
}

TreeNode* RBTree::findValue(int valueC){
	if(root == NULL) return NULL;
	
	TreeNode *search = root;
	
	while(1){
		if(search == NULL) return NULL;
		if(valueC == search->value) return search;
		
		if(valueC < search->value) search = search->LS; //lewe poddrzewo
		else search = search->RS; //prawe poddrzewo
	}
}

void RBTree::addValue(int valueC){
	if(root == NULL){
		root = new TreeNode(NULL, valueC, true);
		root -> black = true;
		return;
	}
	
	TreeNode *search = root;
	while(1){
		if(valueC < search->value){ //lewe poddrzewo
			if(search->LS == NULL){ //dotarlismy do miejsca gdzie ma sie znalezc nowy element
				search->LS = new TreeNode(search, valueC, false);
				search->LS->redParentHandling();
				break;
			}
			else search = search->LS; //schodzimy dalej
		}
		else{ //prawe poddrzewo
			if(search->RS == NULL){
				search->RS = new TreeNode(search, valueC, true);
				search->RS->redParentHandling();
				break;
			}
			else search = search->RS;
		}
	}
	
	//w wyniku obrotow, korzen moze byc teraz w innym miejscu drzewa, i musimy tam przejsc
	while(root->F != NULL) root = root->F;
	
	root->black = true; //korzen zawsze ma byc czarny po kazdej operacji kolorowania
}

void RBTree::deleteValue(int valueC){
	TreeNode *toDelete = findValue(valueC);
	if(toDelete == NULL) return;
	int response = toDelete->deleteSelf();
	
	if(response){ //specjalna sytuacja: usuwamy korzen z drzewa ktore ma tylko 2 lub 1 wezel
	
		if(response == 2){
			root = root->RS;
		}
		else{
			root = root->LS;
			root->rightSon = true;
		}
		
		delete root->F;
		root->F = NULL;
		root->black = true;
	}
	else while(root->F != NULL) root = root->F;
}
