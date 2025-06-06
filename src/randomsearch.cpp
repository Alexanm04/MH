#include <cassert>
#include <randomsearch.h>

using namespace std;

/**
 * Create random solutions until maxevals has been achieved, and returns the
 * best one.
 *
 * @param problem The problem to be optimized
 * @param maxevals Maximum number of evaluations allowed
 * @return A pair containing the best solution found and its fitness
 */
ResultMH RandomSearch::optimize(Problem *problem, int maxevals) {
  assert(maxevals > 0);
  SNIMP *snimp_problem=dynamic_cast<SNIMP*> (problem);
    if (!snimp_problem){
        cerr<<"Error: Se esperaba un problema de tipo SNIMP"<<endl;
        tSolution sol={};
        tFitness fitness=-1;
        unsigned evals=0;
        return ResultMH(sol,fitness,evals);
    }
  tSolution best;
  float best_fitness = -1;

  for (int i = 0; i < maxevals; i++) {
    tSolution solution = problem->createSolution();
    float fitness = problem->fitness(solution);

    if (fitness > best_fitness || best_fitness < 0) {
      best = solution;
      best_fitness = fitness;
    }
  }

  return ResultMH(best, best_fitness, maxevals);
}
