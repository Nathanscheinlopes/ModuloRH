#ifndef BANCODADOS_RH_H
#define BANCODADOS_RH_H

#include "colaborador.h"
#include <vector>

// classe para salvar/pegar dados de colaboradores em arquivo csv ou banco de dados (implementacao futura)
class BancoDados_RH
{
    public:

        // salva em arquivo csv
        void exportarPlanilha(const vector <Colaborador>& colaboradores); // acessa as informacoes de um vetor de objetos do tipo Colaborador

        void carregarPlanilha(vector <Colaborador>& colaboradores, vector <Cargo>& listaCargos); // pega informacoes em arquivo csv 

        void salvarBanco(); // metodo a ser desenvolvido na segunda avaliacao

        void carregarBanco(); // metodo a ser desenvolvido na segunda avaliacao
        
}; // fim da classe

#endif