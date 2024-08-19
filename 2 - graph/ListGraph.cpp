#include <iostream>
#include "ListGraph.h"
#include "Random.h"
using namespace std;

ListGraph::ListGraph(){
	values = (int**) malloc(0);
	outEdges = (int*) malloc(0);
	vertexNo = 0;
	directed = false;
}

ListGraph::~ListGraph(){
	while(vertexNo){
		vertexNo--;
		free(values[vertexNo]);
	}
	free(values);
	free(outEdges);
}

void ListGraph::print(){
	for(int from = 0; from < vertexNo; from++){
		cout << from << ": ";
		for(int to = 0; to < 2*outEdges[from]; to += 2){
			cout << "->" << values[from][to] << "(" << values[from][to+1] << "), ";
		}
		cout << "\n";
	}
}

void ListGraph::changeSize(int newSize){
	if(newSize < vertexNo){
		for(int i = vertexNo-1; i > newSize-1; i--){
			free(values[i]);
		}
	}
	values = (int**) realloc(values, newSize*sizeof(int*));
	outEdges = (int*) realloc(outEdges, newSize*sizeof(int));
	if(newSize > vertexNo){
		for(int i = vertexNo; i < newSize; i++){
			values[i] = (int*)malloc(0);
			outEdges[i] = 0;
		}
	}
	vertexNo = newSize;
}

void ListGraph::clear(){
	for(int i = 0; i < vertexNo; i++){
		values[i] = (int*) realloc(values[i], 0);
		outEdges[i] = 0;
	}
}

void ListGraph::addEdge(int from, int to, int weight){
	values[from] = (int*) realloc(values[from], (outEdges[from] + 1)*2*sizeof(int));
	int top = (outEdges[from]*2);
	values[from][top] = to;
	values[from][top+1] = weight;
	outEdges[from]++;
	if(!directed){
		values[to] = (int*) realloc(values[to], (outEdges[to] + 1)*2*sizeof(int));
		top = (outEdges[to]*2);
		values[to][top] = from;
		values[to][top+1] = weight;
		outEdges[to]++;
	}
}

void ListGraph::setDirected(bool value){
	directed = value;
}
