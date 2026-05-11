#ifndef BANCODADOS_RH_H
#define BANCODADOS_RH_H

#include <iostream> // Para usar cout/cin
#include <ctime>    // Para usar struct tm e time_t
#include "colaborador.h"
#include <vector>
#include <fstream> // Necessário para manipulação de arquivos
#include <string>

using namespace std; // Se você estiver usando no .h, certifique-se de que é intencional

class BancoDados_RH
{
    public:
        // Salva o vetor de colaboradores no CSV, incluindo o status 'ativo' (Soft Delete)
        void exportarPlanilha(const vector<Colaborador>& colaboradores);

        // Lê o CSV e reconstrói `o vetor, filtrando ou marcando inativos conforme o campo 'Ativo'
        void carregarPlanilha(vector<Colaborador>& colaboradores, const vector<Cargo>& listaCargos);

        // Métodos para SQL (Segunda Avaliação)
        void salvarBanco(); 
        void carregarBanco(); 
};

#endif