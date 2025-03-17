#include <cassert>
#include <greedy.h>
#include<snimp.h>


using namespace std;

template <class T> void print_vector(string name, const vector<T> &sol) {
  cout << name << ": ";

  for (auto elem : sol) {
    cout << elem << ", ";
  }
  cout << endl;
}

float GreedySearch::calcularHeuristica(int u, SNIMP* snimp){
  int du=snimp->tamvecinos(u);
  int sum_dv=0;
  for(int v:snimp->vecinos(u)){
    sum_dv+=snimp->tamvecinos(v);
  }
  return du +sum_dv;
}
/**
 * Create random solutions until maxevals has been achieved, and returns the
 * best one.
 *
 * @param problem The problem to be optimized
 * @param maxevals Maximum number of evaluations allowed
 * @return A pair containing the best solution found and its fitness
 */
ResultMH GreedySearch::optimize(Problem *problem, int maxevals) {
  assert(maxevals > 0);
  maxevals=1;
  SNIMP* snimp=dynamic_cast<SNIMP*>(problem);
  tSolution sol (problem->getSolutionSize(),0);
  vector<int>CL;

  for (int i = 0; i < problem->getSolutionSize(); i++) {
    CL.push_back(i);
  }

  if (!CL.empty()){
    int indice=Random::get<int>(0,CL.size()-1);
    int v0=CL[indice];
    sol[v0]=1;
    CL.erase(CL.begin()+indice);
  }

  while (count(sol.begin(),sol.end(),1)<snimp->getK() && !CL.empty()){
    vector<float> heuristica;
    vector<int>RCL=CL;
    for(int u:RCL){
      heuristica.push_back(calcularHeuristica(u, snimp));
    }

    auto max=max_element(heuristica.begin(),heuristica.end());
    int pos=distance(heuristica.begin(),max);
    int u=RCL[pos];

    sol[u]=1;
    CL.erase(remove(CL.begin(),CL.end(),u),CL.end());
    
  }
  
  tFitness fitness = problem->fitness(sol);
  return ResultMH(sol, fitness,maxevals );
}
