#ifndef __SNIMP_H
#define __SNIMP_H

#include "problem.h"
#include <vector>
#include <set>
#include <random>
#include <algorithm>
#include <iostream>
using namespace std;

typedef vector<vector<int>> grafo;

class SNIMP: public Problem{
    public:
        SNIMP(int k_valor);
        tFitness fitness(const tSolution &solution) override;
        tSolution createSolution() override;
        size_t getSolutionSize() override;
        pair<tDomain,tDomain> getSolutionDomainRange() override;
        void leerArchivos(string &archivo);
        void inicializarGrafo(int tam);
        int getK();
        int tamvecinos(int u)const;
        const vector<int> vecinos(int u) const;
    private:
        grafo g;
        int k;
        double p=0.01;
        unsigned ev=10;
        size_t size;
};
#endif