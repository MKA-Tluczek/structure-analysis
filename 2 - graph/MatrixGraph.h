using namespace std;

class MatrixGraph{
	public:
	int vertexNo; //ile wierzcholkow w grafie
	int* values; //krawedz od A do B ma indeks [vertexNo*A + B]
	bool directed;
	
	MatrixGraph(); ~MatrixGraph();
	
	void print();
	void changeSize(int newSize);
	void clear();
	void addEdge(int from, int to, int weight);
	void setDirected(bool value);
};
