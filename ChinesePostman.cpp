#include "ChinesePostman.h"
using namespace std;

ChinesePostman::ChinesePostman()
{
	solveRan = false;
}

ChinesePostman::ChinesePostman(string filename)
{
	solveRan = false;
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

void ChinesePostman::addEdge(string lab, int u, int v, double cost)
{
	;
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