#include <iostream>
#include <problem.h>
#include <random.hpp>
#include <string>
#include<map>
#include <util.h>
// Real problem class
#include "pincrem.h"
#include <filesystem>
// All all algorithms
#include "brutesearch.h"
#include "greedy.h"
#include "randomsearch.h"
#include "snimp.h"

using namespace std;
namespace fs= std::filesystem;

int main(int argc, char *argv[]) {
  vector<long int> semillas;
  if(argc>=2){
    for(int i=1; i<argc; ++i){
      semillas.push_back(atoi(argv[i]));
    }
  }
  else{
    semillas.push_back(42);
  }

  string directorio="./datos";
  vector<string> archivos;
  for (const auto &archivo :fs::directory_iterator(directorio)){
    if (archivo.path().extension()==".txt"){
      archivos.push_back(archivo.path().string());
    }
  }

  if (archivos.empty()){
    cerr<<"Error, no se encontraron archivos en el directorio"<<endl;
    return 1;
  }

  // Seed the random number generator
  
 
  

  // Create the algorithms
  RandomSearch ralg;
  //BruteSearch rbrute = BruteSearch();
  GreedySearch rgreedy;
  //MH *mh = &rgreedy;
  // Create the specific problem
  //ProblemIncrem rproblem = ProblemIncrem(10);
  // Solve using evaluations
  vector<pair<string, MH *>> algoritmos = {
                                           make_pair("RandomSearch", &ralg),
                                           make_pair("Greedy", &rgreedy)};
  map<string, tuple<double,double,int>> resultados;

  for (string &archivo: archivos){
    SNIMP problema=SNIMP(6);
    problema.leerArchivos(archivo);
    cout<<"Leido el archivo: "<<archivo<<endl;
    Problem *problem = &problema;
    
    for (long int semilla:semillas){
      Random::seed(semilla);
      cout<<"\nSemilla: "<<semilla<<endl;
      for (int i = 0; i < algoritmos.size(); i++) {
        cout << algoritmos[i].first << endl;
        auto comienzo=chrono::high_resolution_clock::now();
        MH *mh = algoritmos[i].second;
        ResultMH result = mh->optimize(problem, 1000);
        auto final=chrono::high_resolution_clock::now();
        chrono::duration<double> tiempo= final-comienzo;

        auto &[sumafitness,sumatiempo, ejecuciones]=resultados[algoritmos[i].first];
        sumafitness+=result.fitness;
        sumatiempo+=tiempo.count();
        ejecuciones++;
        //cout << "Best solution: " << result.solution << endl;
        cout << "Best fitness: " << result.fitness << endl;
        cout << "Evaluations: " << result.evaluations << endl;
      }
    }
  }
  cout<<"Conclusiones:"<<endl;
  for (auto & [nombre, datos]: resultados){
    auto& [sumafitness, sumatiempo, evaluaciones]=datos;
    cout<<"\nAlgoritmo:"<<nombre<<endl;;
    cout<<"Fitness promedio: "<<(sumafitness/evaluaciones)<<endl;
    cout<<"Tiempo promedio: "<<(sumatiempo/evaluaciones)<<"s"<<endl;
    cout<<"Total ejecuciones: "<<evaluaciones<<endl;
  }
  

  return 0;
}
