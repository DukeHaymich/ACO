#include <type_traits>
#include <climits>
#include <vector>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <sstream>
#include <iostream>

using namespace std;

class ACO {
    private:
        int NumberOfAnt;
        int NumberOfVertex;
        int InitVertex;
        double ALPHA;
        double BETA;
        double RHO;
        vector<vector<int>> map;
        vector<vector<double>> Pheromone;
        vector<vector<double>> DeltaPheromone;
        vector<vector<int>> RouteOfAnt;
        vector<vector<double>> Prob;
        // Result
        int BEST_LENGTH;
        vector<int> BEST_ROUTE;
    public:
        ACO(const int& nVertices, const int& nAnts, const int& initVertex = 0);
        void addEdge(const int& i, const int& j, const int& length);
        void optimze(const int& ITERATION, const int& InitVertex = 0);
        void setAlpha(const double& a);
        void setBeta(const double& b);
        void setRho(const double& r);
        string result();
    private:
        int length_of_route(const int&);
        int predict_Vertex();
        double random();
        double sum_Of_P(const int&, const int&);
        double P(const int&, const int&, const int&, const double&);
        bool visited(const int&, const int&);
        void route(const int&);
        bool checkvalidRoute(const int&);
        void updatePheromone();
};