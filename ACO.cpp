#include<bits/stdc++.h>
#include "Graph.cpp"

using namespace std;

class ACO {
    private:
        Graph map;
        int NumberOfAnt;
        int NumberOfVertex;
        int InitVertex;
        vector<vector<double>> DeltaPheromone;
        vector<vector<int>> RouteOfAnt;
        vector<vector<double>> Prob;
    public:
}


//Calc Length of Route of Ant_k_th
int length_of_route(int antk){
    int sum=0;
    for(int i=0; i<NumberOfVertex-1; i++){
        sum+=getLength(RouteOfAnt[antk][i], RouteOfAnt[antk][i+1]);
    }
    sum+=getLength(RouteOfAnt[antk][i+1],InitVertex);
    return sum;
}

double sum_Of_P(int i, int antk){
    double sum=0;
    for(int j=0; j<NumberOfVertex; j++){
        if(map[i][j]!=0){
            if(!visited(antk, j)){
                sum+=pow(Pheromone[i][j], ALPHA);
                double temp=1/pow(getLength[i][j], BETA);
                sum+=temp;
            }
        }
    }
    return sum;
}
double P(int i, int j, int antk, double sum_Of_P){
    double T=pow(Pheromone[i][j], ALPHA);
    double N=pow(getLength[i][j], BETA);
    T/=N;
    T/=sum_Of_P;
    return T;
}
//Pick random 1 city
int predictVertex () {
	double xi = random();//random(0-1);
	int i = 0;
	double sum = Prob[i][0];
	while (sum < xi) {
	 	i++;
	 	sum += Prob[i][0];
	}
	return (int) Prob[i][1];
}

bool visited(int antk, int vertex){
    for(int i=0; i<NumberOfVertex; i++){
        if(RouteOfAnt[antk][i]==-1) return false;
        if(RouteOfAnt[antk][i]==vertex) return true;
    }
    return false;
}



//Generate route of antk
void route(int antk){
    
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
        RouteOfAnt[antk][i+1]=predictVertex();
    }
}

bool checkvalidRoute(int antk){
    for(int i=0; i<NumberOfVertex; i++){
        if(RouteOfAnt[antk][i]==-1) return false;  
    }
    if(map  [RouteOfAnt[antk][NumberOfVertex-1]] [InitVertex]==0) return false; //Check diem cuoi voi diem dau cua chu trinh coi lien ket nhau ko
    return true;
}


void updatePheromone(){
    for(int i=0; i<NumberOfAnt; i++){
        int route_length=length_of_route(i);
        for(int j=0; j<NumberOfVertex-1; j++){
            int vertex_i=RouteOfAnt[i][j];
            int vertex_j=RouteOfAnt[i][j+1];
            DeltaPheromone[vertex_i][vertex_j]+=1/route_length;
            DeltaPheromone[vertex_i][vertex_j]+=1/route_length;

        }
    }
    for (int i=0; i<NumberOfVertex;i++){
        for(int j=0; j<NumberOfVertex; j++){
            Pheromone[i][j]+=(Pheromone[i][j]*(1-RO)+DeltaPheromone[i][j];
            DeltaPheromone[i][j]=0;
        }
    }
}


void optimze(int ITERATION, int InitVertex){
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
            if(route_length<BEST_LENGTH) BEST_LENGTH=route_length;
        }

        updatePheromone();

        for(int k=0; k<NumberOfAnt; k++){
            for(int l=0; l<NumberOfVertex;l++){
                RouteOfAnt[k][l]=-1;
            }
        }
    }   
}