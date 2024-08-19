#include <iostream>
#include "MatrixGraph.h"
#include "Random.h"
using namespace std;

MatrixGraph::MatrixGraph(){
	values = (int*) malloc(0);
	vertexNo = 0;
	directed = false;
}

MatrixGraph::~MatrixGraph(){
	free(values);
}

void MatrixGraph::print(){
	int output;
	for(int y = 0; y < vertexNo; y++){
		for(int x = 0; x < vertexNo; x++){
			output = values[vertexNo*y + x];
			if(output == -1) cout << "- ";
			else cout << output << " ";
		}
		cout << "\n";
	}
}

void MatrixGraph::changeSize(int newSize){
	vertexNo = newSize;
	values = (int*) realloc(values, newSize*newSize*sizeof(int));
}

void MatrixGraph::clear(){
	for(int i = 0; i < vertexNo*vertexNo; i++) values[i] = -1;
}

void MatrixGraph::addEdge(int from, int to, int weight){
	if(!directed) values[to*vertexNo + from] = weight;
	values[from*vertexNo + to] = weight;
}

void MatrixGraph::setDirected(bool value){
	directed = value;
}
