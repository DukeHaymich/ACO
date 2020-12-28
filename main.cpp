#include "ACO.h"
#include <iostream>

using namespace std;

int main() {
    int graph[4][4] = {{0, 10, 15, 20},
                       {10, 0, 35, 25},
                       {15, 35, 0, 30},
                       {20, 25, 30, 0}},
        nVertices = sizeof(graph[0])/sizeof(graph[0][0]);
    ACO solver(nVertices, 20);
    for (int i = 0; i < nVertices; ++i) {
        for (int j = 0; j < nVertices; ++j) {
            solver.addEdge(i, j, graph[i][j]);
        }
    }
    solver.optimze(50);
    cout << solver.result() << endl;
    return 0;
}