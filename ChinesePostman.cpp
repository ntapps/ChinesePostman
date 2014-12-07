#include "ChinesePostman.h"
using namespace std;

ChinesePostman::ChinesePostman()
{
	solveRan = false;
	nVertices = 0;
	basicCost = 0.0;
}

ChinesePostman::ChinesePostman(string filename)
{
	solveRan = false;
	basicCost = 0.0;

	ifstream fin(filename);
	if (fin.fail()) {
		cout << "Failed to open file: " << filename << endl;
		cout << "Exiting..." << endl;
		exit(1);
	}

	fin >> nVertices;
	for (int i=0; i<nVertices; i++) {
		degree.push_back(int());
		edges.push_back(vector<int>());
		label.push_back(vector<string>());
		repEdge.push_back(vector<int>());
		cost.push_back(vector<double>());
		cheapestLabel.push_back(vector<string>());
		defined.push_back(vector<bool>());
		path.push_back(vector<int>());

		for (int j=0; j<nVertices; j++) {
			edges[i].push_back(int());
			label[i].push_back(string());
			repEdge[i].push_back(int());
			cost[i].push_back(double());
			cheapestLabel[i].push_back(string());
			defined[i].push_back(bool());
			path[i].push_back(int());
		}
	}

	int u, v, w;
	string lab;
	while (fin >> u >> v >> w >> lab) {
		addEdge(lab, u, v, w);
		addEdge(lab, v, u, w); // because it's an undirected graph
		basicCost += w;
		edges[u][v]++;
		edges[v][u]++;
		degree[u]++;
		degree[v]++;
	}

	fin.close();
}

void ChinesePostman::solve()
{
	;
}

double ChinesePostman::optimalCost()
{
	if (!solveRan) {
		cout << "You must run solve() before using this function" << endl;
		return -1;
	}

	return 0.0;
}

void ChinesePostman::print()
{
	if (!solveRan) {
		cout << "You must run solve() before using this function" << endl;
		return;
	}
}

void ChinesePostman::addEdge(string lab, int u, int v, double c)
{
	label[u][v] = lab;
	//basicCost += cost;	// Only if using a directed graph. Must comment out adding cost in the constructor
	if (!defined[u][v] || cost[u][v] > c) {
		cost[u][v] = c;
		cheapestLabel[u][v] = lab;
		defined[u][v] = true;
		path[u][v] = v;
	}
	edges[u][v]++;
	//edges[u]++;			// Only for directed graphs. Must comment out line in constructor
	//edges[v]++;			// Only for directed graphs. Must comment out line in constructor
}

void ChinesePostman::findLeastCostPaths()
{
	;
}

void ChinesePostman::checkValid()
{
	;
}

void ChinesePostman::findOddVertices()
{
	;
}

void ChinesePostman::findFeasible()
{
	;
}

bool ChinesePostman::improvements()
{
	return false;
}

int ChinesePostman::findPath(int from, vector<vector<int>>repEd)
{
	return 0;
}