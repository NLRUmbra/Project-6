#ifndef GRAPH_H
#define GRAPH_H
using namespace std;
#include "Vertex.h"
#include "GraphBase.h"
#include <string>
#include <vector>
#include <stdio.h>
#include <set>


class Graph :public GraphBase {
private:
	int count = 0;
	unsigned long path;
	vector<Vertex> stuff;
	vector<vector<unsigned long>*> matrix;
public:
	void addVertex(string label);
	void removeVertex(string label);
	void addEdge(string label_1, string label_2, unsigned long weight);
	void removeEdge(string label_1, string label_2);
	unsigned long shortestPath(string StartLabel, string endLabel, vector<string> &path);
};

#endif