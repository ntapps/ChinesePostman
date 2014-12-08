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
		degree[u]++;
		degree[v]++;
	}

	fin.close();
}

void ChinesePostman::solve()
{
	cout << "Solving..." << endl;
	findLeastCostPaths();
	checkValid();
	findOddVertices();
	findFeasible();
	cout << "Solved." << endl;
}

double ChinesePostman::optimalCost()
{
	if (!solveRan) {
		cout << "You must run solve() before using this function" << endl;
		return -1;
	}

	double phi = 0;
	for (int i=0; i<nVertices; i++) {
		for (int j=0; j<nVertices; j++) {
			phi += cost[i][j]*repEdge[i][j];
		}
	}

	return basicCost * phi;
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
	//degree[u]++;			// Only for directed graphs. Must comment out line in constructor
	//degree[v]++;			// Only for directed graphs. Must comment out line in constructor
}

void ChinesePostman::findLeastCostPaths()
{
	for (int k=0; k<nVertices; k++) {
		for (int i=0; i<nVertices; i++) {
			if (defined[i][k]) {
				for (int j=0; j<nVertices; j++) {
					if (defined[k][j] && (!defined[i][j] || cost[i][j] > cost[i][k] + cost[k][j])) {
						path[i][j] = path[i][k];
						cost[i][j] = cost[i][k] + cost[k][j];
						defined[i][j] = true;
						if (i == j && cost[i][j] < 0) return; // stop on negative cycle
					}
				}
			}
		}
	}
}

void ChinesePostman::checkValid()
{
	for (int i=0; i<nVertices; i++) {
		for (int j=0; j<nVertices; j++) {
			if (!defined[i][j]) {
				cout << "Error: Graph is not strongly connected." << endl; // not sure what this is supposed to mean.
				cout << "Exiting..." << endl;
				exit(1);
			}
		}
		if (cost[i][i] < 0) {
			cout << "Error: Graph has a negative weight cycle." << endl;
			cout << "Exiting..." << endl;
			exit(1);
		}
	}
}

void ChinesePostman::findOddVertices()
{
	for (int i=0; i<nVertices; i++) {
		if (degree[i] % 2 != 0) {
			odd.push_back(i);
		}
	}
}

void ChinesePostman::findFeasible()
{
	// Maybe this function stays the same since we added the equivalent of directed edges going both ways?
	// Now that I think of it...will have to cancel paths going in both directions when deciding the path.

	// delete next 3 lines to be faster, but non-reentrant (not sure what that means right now)
	vector<int> d = degree;

	for (int u=0; u<odd.size(); u++) {
		int i = odd[u];
		for (int v=0; v<odd.size(); v++) {
			// I don't know what's going on in this function anymore...;
		}
	}
}

int ChinesePostman::findPath(int from, vector<vector<int>>repEd)
{
	for (int i=0; i<nVertices; i++) {
		if (repEdge[from][i] > 0) return i;
	}

	return NONE;
}