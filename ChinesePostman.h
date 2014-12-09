#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <queue>

#ifndef CHINESEPOSTMAN_H
#define CHINESEPOSTMAN_H

const int NONE = -1; // anything < 0

struct VertexPair
{
	int i, j;
	std::vector<std::vector<double>> &cost; // pointer to cost array
	VertexPair(int i, int j, std::vector<std::vector<double>> &cost) : i(i), j(j), cost(cost) {}
	VertexPair(const VertexPair &orig) : i(orig.i), j(orig.j), cost(orig.cost) {}
	
	VertexPair& operator=(VertexPair &rt) { i = rt.i; j = rt.j; cost = rt.cost; return *this; }
};

// for min-priority queue
inline bool operator<(const VertexPair &lt, const VertexPair &rt)
{
	return lt.cost[lt.i][lt.j] > lt.cost[rt.i][rt.j];
}

class ChinesePostman
{
public:
	// Constructors
	ChinesePostman();
	ChinesePostman(std::string filename);

	// Solve the Chinese Postman Problem
	void solve();
	double optimalCost();	// cost of an optimal Chinese Postman Problem
	void printEuler();	// print results. Must run solve() first.

private:
	// Private Member Functions
	void addEdge(std::string lab, int u, int v, double c);
	void findLeastCostPaths();									// Floyd-Warshall Algorithm?
	void findOddVertices();
	void makeEulerian();										// Add paths to make Eulerian Graph
	std::vector<int> generateTour(int start, std::vector<std::vector<int>> &tempEdges);

	// Member variables
	bool solveRan;											// has the user run solve() yet?
	int nVertices;											// number of vertices
	std::vector<int> degree;								// degrees of vertices
	std::vector<int> odd;									// odd vertices
	std::vector<std::vector<int>> edges;					// adjacency matrix, counts edges between vertices
	std::vector<std::vector<std::string>> label;			// lables of arcs (for each vertex pair). A lable is the edge identifier.
	std::vector<std::vector<double>> cost;					// costs of cheapest edges
	std::vector<std::vector<std::string>> cheapestLabel;	// labels of cheapest edges
	std::vector<std::vector<bool>> defined;					// whether path cost is defined between vertices
	std::vector<std::vector<int>> path;						// spanning tree of the graph
	double basicCost;										// total cost of traversing each edge once

	bool compareVertexPair(VertexPair &lt, VertexPair &rt);
};

#endif