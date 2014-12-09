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
		cost.push_back(vector<double>());
		cheapestLabel.push_back(vector<string>());
		defined.push_back(vector<bool>());
		path.push_back(vector<int>());

		for (int j=0; j<nVertices; j++) {
			edges[i].push_back(int());
			label[i].push_back(string());
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
	findOddVertices();
	makeEulerian();

	solveRan = true;
	cout << "Solved." << endl;
}

double ChinesePostman::optimalCost()
{
	if (!solveRan) {
		cout << "You must run solve() before using this function" << endl;
		return -1;
	}

	// add costs of all edges
	double totalCost = 0;
	for(int i = 0; i < nVertices; i++) // loop over undirected graph (count each edge only once)
		for(int j = i+1; j < nVertices; j++)
			totalCost += edges[i][j]*cost[i][j];

	return totalCost;
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

void ChinesePostman::findOddVertices()
{
	for (int i=0; i<nVertices; i++) {
		if (degree[i] % 2 != 0) {
			odd.push_back(i);
		}
	}
}

// for min-priority queue
bool ChinesePostman::compareVertexPair(VertexPair &lt, VertexPair &rt)
{
	return cost[lt.i][lt.j] > cost[rt.i][rt.j];
}

void ChinesePostman::makeEulerian()
{
	// Push all pairs of odd-degreed vertices into a min-priority queue
	std::priority_queue<VertexPair> q;
	for(int i = 0; i < odd.size(); i++)
	{
		for(int j = i+1; j < odd.size(); j++)
		{
			VertexPair pair(odd[i], odd[j], cost);
			q.push(pair);
		}
	}

	// Make a boolean vector to keep track of which odd-degreed vertices have been "paired off",
	// i.e., "upgraded" to even degree
	std::vector<bool> vertPairedOff(nVertices, false); // start with no vertices paired off

	// Extract pairs in lowest-path-cost order
	while(!q.empty())
	{
		VertexPair pair = q.top(); // access min element
		q.pop(); // for some reason the STL doesn't have a single extract-min function

		if(!vertPairedOff[pair.i] && !vertPairedOff[pair.j])
		{
			// If both vertices i and j have not yet been paired off, then this pairing is the
			// lowest-cost way to upgrade them to even degree, and thus we'll choose it.
			vertPairedOff[pair.i] = vertPairedOff[pair.j] = true;

			// Add new edges along the (shortest) path between these vertices
			int curVert = pair.j;
			while(curVert != pair.i) // walk the shortest-paths predecessor tree from j back to i
			{
				// Connect curVert to predecessor[curVert] in the path from i to curVert
				int predecessor = path[curVert][pair.i];
				addEdge(label[curVert][predecessor], curVert, predecessor, cost[curVert][predecessor]);
				addEdge(label[predecessor][curVert], predecessor, curVert, cost[predecessor][curVert]);
				degree[curVert]++;
				degree[predecessor]++;

				// Walk one node back on the predecessor tree from i to curVert
				curVert = path[curVert][pair.i];
			}
		}
	}

	// Now, all odd-degree vertices have been "paired off" in a least-cost manner to upgrade them
	// to even-degree vertices. This guarantees the existence of an Eulerian path.
}

vector<int> ChinesePostman::generateTour(int start, vector<vector<int>> &tempEdges) {

    vector<int> nodeList;
    nodeList.push_back(start);

    int current = start;
                
    do {
        for (int j = 0; j < nVertices; j++) {
            if (current != j) {
                if (start == j && tempEdges[current][start] > 0) {
                    //you can complete a loop using unused edge, so do so
                    tempEdges[current][start]--;
                    tempEdges[start][current]--;
					degree[start]--;
					degree[current]--;
                    current = start;
                    nodeList.push_back(current);
                    break;
                } else {
                    if (tempEdges[current][j] > 0) {
                        //this "edge" has uses left, so take one
                        tempEdges[current][j]--;
                        tempEdges[j][current]--;
						degree[j]--;
						degree[current]--;
                        current = j;
                        //add this guy to the chain.
                        nodeList.push_back(current);
                        break;
                    }
                }
            }
        }
    } while (current != start);

    return nodeList;
}

void ChinesePostman::printEuler() {

	if (!solveRan) {
		cout << "You must run solve() before using this function" << endl;
		return;
	}

	vector<vector<int>> tempEdges;
	tempEdges = edges;

    int level = 0;
    int start = 0;
	
    vector<vector<int>> tours;
    bool edgesExist = false;

    do {
		edgesExist = false;
		tours.push_back(generateTour(start, tempEdges));
		for (int i = 0; i < nVertices; i++) {
			for (int j = 0; j < nVertices; j++) {
				if (tempEdges[i][j] > 0 && (i != j)) {
					edgesExist = true;
					break;
				}
			}
		}
		for (int i = 0; i < tours[level].size(); i++) {
			if (degree[tours[level][i]] > 0) {
				start = tours[level][i];
				break;
			}
		}
		level++;
    } while(edgesExist);

    int size = tours.size();
    for (int i = 0; i < size - 1; i++) {
        int num = tours[i+1][0];
		int tour_i_size = tours[i].size();
        for (int j = 0; j < tour_i_size; j++) {
            if (tours[i][j] == num) {
                auto it = tours[0].begin()+i+j+1;
                tours[0].insert(it, tours[i+1].begin()+1, tours[i+1].end());
				break;
            }
        }
	}

    for (int i = 0; i < tours[0].size()-1; i++) {
        //cout << tours[0][i] << " -> ";

		// The label is for the edge betwen startNode and endNode
		int startNode = tours[0][i];
		int endNode = tours[0][(i+1) % tours[0].size()];
		cout << "Take: " << label[startNode][endNode] << " From " << startNode << " to " << endNode << endl;
		if (i < tours[0].size()-2) {
			cout << " -> ";
		}
    }

	cout << "\n\nTotal cost: " << optimalCost() << endl;
}