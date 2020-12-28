#include <vector>

class Graph {
    private:
        int nVertices;
        vector<vector<int>> map;
        vector<vector<int>> pheromone;
    public:
        Graph(const int& = 1);
        Graph(const Graph&);
        Graph(Graph&&);
        Graph operator= (const Graph&);
        Graph operator= (Graph&&);
        ~Graph();
        void setLength(const int&, const int&, const int&);
        void setPheromone(const int&, const int&, const int&);
        int getLength(const int&, const int&);
        int getPheromone(const int&, const int&);
    private:
        void validate();
};
Graph::Graph(const int& nVertices) : nVertices(nVertices) {
    this->map = vector<vector<int>>(nVertices, vector<int>(nVertices, 0));
    this->pheromone = vector<vector<int>>(nVertices, vector<int>(nVertices, 0));
}
Graph(const Graph& rVal) {
    this->map = rVal.map;
    this->pheromone = rVal.pheromone;
}
Graph(Graph&& rVal) {
    this->map = std::move(rVal.map);
    this->pheromone = std::move(rVal.pheromone);
}
Graph operator= (const Graph& rVal) {
    this->map = rVal.map;
    this->pheromone = rVal.pheromone;
}
Graph operator= (Graph&& rVal) {
    this->map = std::move(rVal.map);
    this->pheromone = std::move(rVal.pheromone);
}
Graph::~Graph() {}
void Graph::validate(const int& vFrom, const int& vTo) {
    if (vFrom < 0 || vFrom >= this->nVertices || vTo < 0 || vTo >= this->nVertices) {
        throw std::out_of_range("The vertex number is invalid (out of range)!");
    }
}
void Graph::setLength(const int& vFrom, const int& vTo, const int& length) {
    validate(vFrom, vTo);
    this->map[vFrom][vTo] = length;
}
void Graph::setPheromone(const int& vFrom, const int& vTo, const int& pheromone) {
    validate(vFrom, vTo);
    this->pheromone[vFrom][vTo] = pheromone;
}
int Graph::getLength(const int& vFrom, const int& vTo) {
    validate(vFrom, vTo);
    return this->map[vFrom][vTo];
}
int Graph::getPheromone(const int& vFrom, const int& vTo) {
    validate(vFrom, vTo);
    return this->pheromone[vFrom][vTo];
}
