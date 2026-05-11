#ifndef BANCODADOS_RH_H
#define BANCODADOS_RH_H

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "colaborador.h"

using namespace std;

class BancoDados_RH
{
public:
    // Exporta os dados do vetor para o arquivo CSV (incluindo status ativo/inativo)
    void exportarPlanilha(const vector<Colaborador>& colaboradores);

    // Carrega os dados do arquivo CSV e reconstrói os objetos Colaborador
    void carregarPlanilha(vector<Colaborador>& colaboradores, const vector<Cargo>& listaCargos);

    // Métodos reservados para implementação futura de banco de dados SQL
    void salvarBanco(); 
    void carregarBanco(); 
};

#endif