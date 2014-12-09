#include <iostream>
#include <vector>
using namespace std;


const int NODES = 6;

vector<int> generateTour(int edges[][NODES], int degrees[], int start);
void printEuler(int degree[], int edges[][NODES]);

int main() {

    int degrees[NODES] = {2, 4, 4, 4, 4, 2};
    int edges[NODES][NODES]; //adjacency matrix;
    edges[0][0] = 1;
    edges[0][1] = 1;
    edges[0][2] = 1;
    edges[0][3] = 0;
    edges[0][4] = 0;
    edges[0][5] = 0;
    edges[1][0] = 1;
    edges[1][1] = 1;
    edges[1][2] = 1;
    edges[1][3] = 1;
    edges[1][4] = 1;
    edges[1][5] = 0;
    edges[2][0] = 1;
    edges[2][1] = 1;
    edges[2][2] = 1;
    edges[2][3] = 3;
    edges[2][4] = 1;
    edges[2][5] = 0;
    edges[3][0] = 0;
    edges[3][1] = 1;
    edges[3][2] = 3;
    edges[3][3] = 1;
    edges[3][4] = 1;
    edges[3][5] = 1;
    edges[4][0] = 0;
    edges[4][1] = 1;
    edges[4][2] = 1;
    edges[4][3] = 1;
    edges[4][4] = 1;
    edges[4][5] = 1;
    edges[5][0] = 0;
    edges[5][1] = 0;
    edges[5][2] = 0;
    edges[5][3] = 1;
    edges[5][4] = 1;
    edges[5][5] = 1;

    printEuler(degrees, edges);

    return 0;
}

vector<int> generateTour(int edges[][NODES], int degrees[], int start) {

    vector<int> nodeList;
    nodeList.push_back(start);
                
    int current = start;
                
    do {
        for (int j = 0; j < NODES; j++) {
            if (current != j) {
                if (start == j && edges[current][start] > 0) {
                    //you can complete a loop using unused edge, so do so
                    //usedEdges[current][start]++;
                    //usedEdges[start][current]++;
                    edges[current][start]--;
                    edges[start][current]--;
					degrees[start]--;
					degrees[current]--;
                    current = start;
                    nodeList.push_back(current);
                    break;
                } else {
                    if (edges[current][j] > 0) {
                        //this "edge" has uses left, so take one
                        //usedEdges[current][j]++;
                        //usedEdges[j][current]++;
                        edges[current][j]--;
                        edges[j][current]--;
						degrees[j]--;
						degrees[current]--;
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

void printEuler(int degrees[], int edges[][NODES]) {

    int level = 0;
    int start = 0;
    //int usedEdges[NODES][NODES];

    /*for (int i = 0; i < NODES; i++) {
        for (int j = 0; j < NODES; j++) {
            usedEdges[i][j] = 0;
        }
    }*/

    vector<vector<int>> tours;
    bool edgesExist = false;

    do {
		edgesExist = false;
		tours.push_back(generateTour(edges, degrees, start));
		for (int i = 0; i < NODES; i++) {
			for (int j = 0; j < NODES; j++) {
				if (edges[i][j] > 0 && (i != j)) {
					edgesExist = true;
				}
			}
		}
		for (int i = 0; i < tours[level].size(); i++) {
			if (degrees[tours[level][i]] > 0) {
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
            }
        }
	}

    for (int i = 0; i < tours[0].size(); i++) {
        cout << tours[0][i] << " -> ";
    }
                
}
