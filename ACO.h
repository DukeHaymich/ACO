#include <vector>
#include <math.h>
#include <stdlib.h>
#include <time.h>

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
        vector<vector<int>> Pheromone;
        vector<vector<double>> DeltaPheromone;
        vector<vector<int>> RouteOfAnt;
        vector<vector<double>> Prob;
        // Result
        int BEST_LENGTH;
        vector<int> BEST_ROUTE;
    public:
        ACO(const int&, const int&, const int& = 0);
        void addEdge(const int&, const int&, const int&);
        void optimze(const int&, const int&);
        void setAlpha(const double&);
        void setBeta(const double&);
        void setRho(const double&);
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