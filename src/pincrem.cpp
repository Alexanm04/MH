#include <algorithm>
#include <pincrem.h>
#include <random.hpp>
#include<unordered_set>
using namespace std;

tFitness ProblemIncrem::fitness(const tSolution &solution) {
  tFitness count = 0;

  for (int i = 0; i < solution.size(); i++) {
    if (solution[i]) {
      if (i % 2 == 0) {
        count += 1;
      } else {
        count -= 1;
      }
    }
  }
  return count;
}

tSolution ProblemIncrem::createSolution() {
  tSolution solution(size);
  for (int i = 0; i < solution.size(); i++) {
    solution[i] = Random::get<bool>();
  }
  return solution;
}
/*
tSolution ProblemIncrem::createSolution() {
  tSolution solution(size,false);
  int numnodos=Random::get<int>(1,size);
  unordered_set<int> indiceselegidos;

  while (indiceselegidos.size() < numnodos){
    int indice= Random::get<int>(1,size-1);
    indiceselegidos.insert(indice);
  }

  for (auto x=indiceselegidos.begin(); x!=indiceselegidos.end(); ++x){
    solution[*x]=true;
  }

  return solution;
}
/*
tSolution ProblemIncrem::createSolution(){
  tSolution solution(size,false);
  int numnodos=Random::get<int>(1,size);

  vector<int> indices(size);

}*/

vector<tHeuristic> ProblemIncrem::heuristic(tSolution &sol,
                                            const vector<tOption> &options) {
  vector<tHeuristic> values;

  for (auto option : options) {
    tHeuristic value = ((option % 2) == 1 ? sol.size() - option : sol.size());
    values.push_back(value);
  }

  return values;
}
