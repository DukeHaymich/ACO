#include <vector>
#include <math.h>


template <class T>
class ACO {
    public:
        class Graph;
    private:
        int *pheromoneCoeff;
        int *edgeCoeff;
        Graph map;
    public:
        class Graph {
            public:
                class Vertex;
            private:
                vector<Vertex> *vertices;
            public:
                Graph (const int& nVertices = 1) {
                    this->vertices = new vector<Vertex>(nVertices, Vertex());
                }
                Graph (const Graph& rVal) {
                    this->vertices = rVal.vertices;
                }
                Graph (Graph&& rVal) {
                    this->vertices = std::move(rVal.vertices);
                }
                Graph operator= (const Graph& rVal) {
                    this->vertices = rVal.vertices;
                    return *this;
                }
                Graph operator= (Graph&& rVal) {
                    this->vertices = std::move(rVal.vertices);
                    return *this;
                }
                ~Graph () {
                    delete this->vertices;
                }
            public:
                class Vertex {
                    public:
                        class Edge;
                    private:
                        static int count;
                        int id;
                        T data;
                        list<Edge> adj;
                        friend class Graph;
                    public:
                        class Edge {
                            private:
                                int *length;
                                int *pheromone;
                                Vertex *tail;
                            public:
                                Edge(const T& tail, const int& length = 0) {
                                    this->datTenGiBayGio = 
                                }
                        };
                    public:

                };
        };
    public:
};