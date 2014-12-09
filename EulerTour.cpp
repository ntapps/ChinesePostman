#include <iostream>
#include <vector>
using namespace std;

vector<int> generateTour(int edges[][NODES], int degrees[], int start);
void printEuler(int degree[], int edges[][NODES]);

//int main() {
//
//    int degrees[NODES] = {2, 4, 4, 4, 4, 2};
//    int edges[NODES][NODES]; //adjacency matrix;
//    edges[0][0] = 1;
//    edges[0][1] = 1;
//    edges[0][2] = 1;
//    edges[0][3] = 0;
//    edges[0][4] = 0;
//    edges[0][5] = 0;
//    edges[1][0] = 1;
//    edges[1][1] = 1;
//    edges[1][2] = 1;
//    edges[1][3] = 1;
//    edges[1][4] = 1;
//    edges[1][5] = 0;
//    edges[2][0] = 1;
//    edges[2][1] = 1;
//    edges[2][2] = 1;
//    edges[2][3] = 3;
//    edges[2][4] = 1;
//    edges[2][5] = 0;
//    edges[3][0] = 0;
//    edges[3][1] = 1;
//    edges[3][2] = 3;
//    edges[3][3] = 1;
//    edges[3][4] = 1;
//    edges[3][5] = 1;
//    edges[4][0] = 0;
//    edges[4][1] = 1;
//    edges[4][2] = 1;
//    edges[4][3] = 1;
//    edges[4][4] = 1;
//    edges[4][5] = 1;
//    edges[5][0] = 0;
//    edges[5][1] = 0;
//    edges[5][2] = 0;
//    edges[5][3] = 1;
//    edges[5][4] = 1;
//    edges[5][5] = 1;
//
//    printEuler(degrees, edges);
//
//    return 0;
//}


