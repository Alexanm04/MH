#include "snimp.h"
#include <unordered_set>
#include <fstream>
#include<sstream>
#include<vector>
SNIMP::SNIMP(int k_valor):k(k_valor),p(0.01),ev(10),size(0){}

tFitness SNIMP::fitness(const tSolution &solution)
{
    double infectados_total=0.0;

    for (int i=0; i<ev; ++i){
        set<int> nodos_influidos;
        set<int> nodos_activos;//(A)

        for (size_t j=0; j<solution.size(); ++j){
            if(solution[j]==1){
                nodos_activos.insert(j);
                nodos_influidos.insert(j);
            }
        }

        while (!nodos_activos.empty()){
            set<int> nuevos_nodos_activos;
            for (int nodo:nodos_activos){ 
                for(/*size_t vecino=0; vecino<g[nodo].size(); ++vecino*/ int u:g[nodo]){
                    if (/*g[nodo][vecino]==1 &&*/ Random::get(0.0,1.0)<= p && nodos_influidos.find(/*vecino*/ u)==nodos_influidos.end()){
                        nuevos_nodos_activos.insert(/*vecino*/u);
                        nodos_influidos.insert(/*vecino*/u);
                    }
                }
            }
            nodos_activos=nuevos_nodos_activos;
        }
        infectados_total+=nodos_influidos.size();
    } 
    return infectados_total/ev;
}

void SNIMP::inicializarGrafo(int tam){
    g.resize(tam);

}

int SNIMP::getK()
{
    return k;
}

int SNIMP::tamvecinos(int u) const
{
    return g[u].size();
}

const vector<int> SNIMP::vecinos(int u) const
{
    return g[u];
}

tSolution SNIMP::createSolution(){
    tSolution new_solution(g.size(),0);
    unordered_set<int> nodos_seleccionados;
    int k_valido=min(k,static_cast<int>(g.size()));

    while (nodos_seleccionados.size()<k_valido){
        int ind= Random::get<int>(0,g.size()-1);
        nodos_seleccionados.insert(ind);
    }

    for (int nodo: nodos_seleccionados){
        new_solution[nodo]=1;
    }

    return new_solution;
}

size_t SNIMP::getSolutionSize(){
    return g.size();
}

void SNIMP::leerArchivos(string &archivo){
    ifstream arch(archivo);
    if (arch.is_open()){
        string linea;
        size_t nodos=0, aristas=0;
        bool encontrados=false;

        while (getline(arch,linea)){
            if (linea.empty()){
                continue;
            }

            auto pos=linea.find("Nodes:");
            if(pos!=string::npos){
                istringstream is(linea);
                string s;
                while(is>>s){
                    if (s=="Nodes:"){
                        is>>nodos;
                    }
                    else if (s=="Edges:"){
                        is>>aristas;
                    }
                }
                encontrados=true;
                break;
            }
        }
        if (!encontrados){
            cerr<<"Error: NO se encontró la linea de nodos y aristas."<<endl;
            arch.close();
            return;
        }
        else{
            cout<<"Se encontró la linea de nodos y aristas."<<endl;
        }

        bool cabecera=false;
        while(getline(arch, linea)){
            if (linea.find("FromNodeId	ToNodeId") != string::npos){
                cabecera=true;
                break;
            }
        }

        if (!cabecera){
            cerr<<"Error: NO se encontró la linea de inicio de las aristas."<<endl;
            arch.close();
            return;
        }
        inicializarGrafo(nodos);
        cout<<"\nTAMAÑO: "<<g.size()<<endl;
        int u,v;
        while(arch >>u>>v){
            /*if (u>=0 && u<static_cast<int> (nodos) && v>=0 && v<static_cast<int>(nodos)){
                g[u][v]=1;
            }*/
           g[v].push_back(u);
        }
        arch.close();
        cout<<"Archivo leido correctamente"<<endl;
        cout<<"NÚMERO DE NODOS: "<<nodos <<", NÚMERO DE ARISTAS: "<<aristas<<endl;

    }
    else{
        cerr<<"Error al abrir el archivo."<<endl;
    }
}

pair<tDomain, tDomain> SNIMP::getSolutionDomainRange(){
    return make_pair(0.0,1.0);
}
/*
ResultMH SNIMP::optimize(Problem *problem, int maxevals) {
    assert(maxevals > 0);
    tSolution best;
    float best_fitness = -1;
    SNIMP *snimp_problem= dynamic_cast<SNIMP*> (problem);
    for (int i = 0; i < maxevals; i++) {
      tSolution solution = problem->createSolution();
      float fitness = problem-> fitness(solution);
  
      if (fitness < best_fitness || best_fitness < 0) {
        best = solution;
        best_fitness = fitness;
      }
    }
  
    return ResultMH(best, best_fitness, maxevals);
  }
  */