#pragma once
#include <algorithm>
#include <heuristicproblem.h>

class ProblemIncrem : public HeuristicProblem {
  size_t size;

public:
  ProblemIncrem(size_t size) : HeuristicProblem() { this->size = size; }
  tFitness fitness(const tSolution &solution) override;
  tSolution createSolution() override;
  size_t getSolutionSize() override { return size; }
  std::pair<tDomain, tDomain> getSolutionDomainRange() override {
    return std::make_pair(false, true);
  }

  vector<tHeuristic> heuristic(tSolution &sol, const vector<tOption> &options);
};
/*
Algorithm 1 ICM (G=(V,E),S,p,ev)
I<-0
for i que pertenece 1 ... ev do
  A*<-S
  A<-A
  while A distinto 0 do
    B<-0
    for v que pertence A do
      for (u,v) que pertenece E do 
         if rnd(0,1) <= p then  //Por cada vecino de cada nodo en A  se comprueba si se ha infectado
            B<- B U {u}
         end if
      end for
    end for  
    A*<- A* U B     //Se añaden los nuevos. En la siguiente iteración se van a explorar los vecinos de los nuevos nodos influidos
    A <- B
  end while
  I <- I + |A*|
end for 
return I/ev //Se devuelve el promedio de nodos infectados en las 10 iteraciones del bucle

//A* es ell conjunto de nodos activados, I su tamaño
//B es  el conjunto de nuevos nodos
*/
