#include "ACO.h"

ACO::ACO(const int& nVertices, const int& nAnts, const int& initVertex) {
    this->NumberOfVertex = nVertices;
    this->NumberOfAnt = nAnts;
    this->map = vector<vector<int>>(nVertices, vector<int>(nVertices, 0));
    this->Pheromone = vector<vector<int>>(nVertices, vector<int>(nVertices, 0));
    this->DeltaPheromone = vector<vector<double>>(nVertices, vector<double>(nVertices, 0));
    this->RouteOfAnt = vector<vector<int>>(nAnts, vector<int>(nVertices, -1));
    this->Prob = vector<vector<double>>(nVertices, vector<double>(2, 0));
    this->InitVertex = initVertex;
    this->ALPHA = 1;
    this->BETA = 1;
    this->RHO = 0.8;
    srand(17 * nVertices + nAnts);
}

// Calc Length of Route of k_th Ant
int ACO::length_of_route(const int& antk) {
    int sum=0, i=0;
    for(; i<NumberOfVertex-1; i++){
        sum+=map[RouteOfAnt[antk][i]] [RouteOfAnt[antk][i+1]];
    }
    sum+=map[RouteOfAnt[antk][i]] [InitVertex];
    return sum;
}
//Pick random 1 city
int ACO::predict_Vertex () {
	double xi = random();//random(0-1);
	int i = 0;
	double sum = Prob[i][0];
	while (sum < xi) {
	 	i++;
	 	sum += Prob[i][0];
	}
	return (int) Prob[i][1];
}
// Random generator
double ACO::random() {
    return (double)rand() / RAND_MAX;
}
// Calc denominator of probability
double ACO::sum_Of_P(const int& i, const int& antk){
    double sum=0;
    for(int j=0; j<NumberOfVertex; j++){
        if(map[i][j]!=0){
            if(!visited(antk, j)){
                sum+=pow(Pheromone[i][j], ALPHA);
                double temp=1/pow(map[i][j], BETA);
                sum+=temp;
            }
        }
    }
    return sum;
}
// Calc probability
double ACO::P(const int& i, const int& j, const int& antk, const double& sum_Of_P){
    double T=pow(Pheromone[i][j], ALPHA);
    double N=pow(map[i][j], BETA);
    T/=N;
    T/=sum_Of_P;
    return T;
}

bool ACO::visited(const int& antk, const int& vertex){
    for(int i=0; i<NumberOfVertex; i++){
        if(RouteOfAnt[antk][i]==-1) return false;
        if(RouteOfAnt[antk][i]==vertex) return true;
    }
    return false;
}

//Generate route of antk
void ACO::route(const int& antk){
    
    RouteOfAnt[antk][0]=InitVertex;
    //diem hien tai la i, can tinh diem ke tiep la (i+1)
    for (int i=0; i<NumberOfVertex-1; i++){
        int vertex_i=RouteOfAnt[antk][i];
        int count=0;//dem cac dinh ke voi no ma chua di qua
        for(int vertex_j=0; vertex_j<NumberOfVertex; vertex_j++){
            if(vertex_j==vertex_i) continue;
            double sum=sum_Of_P(i, antk);
            
            if(map[vertex_i][vertex_j]!=0){
                if(!visited(antk, vertex_j)){
                    Prob[count][0]=P(vertex_i, vertex_i, antk, sum);
                    Prob[count][1]=vertex_j;
                    count++;
                }
            }
        }
        if(count==0) return; //Can't go anymore
        RouteOfAnt[antk][i+1]=predict_Vertex();
    }
}

bool ACO::checkvalidRoute(const int& antk){
    for(int i=0; i<NumberOfVertex; i++){
        if(RouteOfAnt[antk][i]==-1) return false;  
    }
    //Check diem cuoi voi diem dau cua chu trinh coi lien ket nhau ko
    if(map[RouteOfAnt[antk][NumberOfVertex-1]] [InitVertex]==0) return false;
    return true;
}


void ACO::updatePheromone(){
    for(int i=0; i<NumberOfAnt; i++){
        int route_length=length_of_route(i);
        for(int j=0; j<NumberOfVertex-1; j++){
            int vertex_i=RouteOfAnt[i][j];
            int vertex_j=RouteOfAnt[i][j+1];
            DeltaPheromone[vertex_i][vertex_j]+=1/route_length;
            DeltaPheromone[vertex_i][vertex_j]+=1/route_length;

        }
    }
    for (int i=0; i<NumberOfVertex; i++){
        for(int j=0; j<NumberOfVertex; j++){
            Pheromone[i][j] += Pheromone[i][j]*(1-RHO) + DeltaPheromone[i][j];
            DeltaPheromone[i][j] = 0;
        }
    }
}

void ACO::optimze(const int& ITERATION, const int& InitVertex){
    this->InitVertex=InitVertex;
    for(int i=0; i<ITERATION; i++){
        for(int antk=0; antk<NumberOfAnt; antk++){
            while(!checkvalidRoute(antk)){
                for(int j=0; j<NumberOfVertex; j++){
                    RouteOfAnt[antk][j]=-1;
                }
                route(antk);
            }
            int route_length=length_of_route(antk);
            if(route_length<BEST_LENGTH){
                BEST_LENGTH=route_length;
                for(int k=0;k<NumberOfVertex; k++){
                    BEST_ROUTE[k]=RouteOfAnt[antk][k];
                }
            }
        }

        updatePheromone();

        for(int k=0; k<NumberOfAnt; k++){
            for(int l=0; l<NumberOfVertex;l++){
                RouteOfAnt[k][l]=-1;
            }
        }
    }   
}

void ACO::addEdge(const int& i, const int& j, const int& length) {
    this->map[i][j] = length;
}

string ACO::result() {
    stringstream ss;

    ss << "Number of ants worked: " << this->NumberOfAnt
       << "\nNumber of vertices: " << this->NumberOfVertex
       << "\nALPHA: " << this->ALPHA << "\tBETA: " << this->BETA << "\tRHO: " << this->RHO
       << "\nBest length: " << this->BEST_LENGTH
       << "\nTraverse order:";
    for (size_t i = 0; i < this->BEST_ROUTE.size(); ++i) {
        ss << ' ' << BEST_ROUTE[i];
    }
    return ss.str();
}

void ACO::setAlpha(const double& a) {
    this->ALPHA = a;
}
void ACO::setBeta(const double& b) {
    this->BETA = b;
}
void ACO::setRho(const double& r) {
    this->RHO = r;
}