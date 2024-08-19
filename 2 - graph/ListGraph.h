using namespace std;

class ListGraph{
	public:
	int vertexNo; //ile wierzcholkow w grafie
	int* outEdges; //ile krawedzi wychodzi z tego wierzcholka
	int** values;
	bool directed;
	//values[a][2*n] = b -> istnieje krawedz od a do b
	//values[a][2*n+1] = c -> ta krawedz ma wage c
	
	ListGraph(); ~ListGraph();
	
	void print();
	void changeSize(int newSize);
	void clear();
	void addEdge(int from, int to, int weight);
	void setDirected(bool value);
};
