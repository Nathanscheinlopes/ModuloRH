#ifndef FOLHAPAGAMENTO_H
#define FOLHAPAGAMENTO_H

#include "colaborador.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <iomanip> // Necessário para formatar casas decimais

using namespace std;


class FolhaPagamento
{
    private:
        float impostos = 0.12; // Alíquota fixa de 12% (estudar integração financeira futura)
                
    public:             
        // Cálculos
        float calculaBruto(const Colaborador& colab);
        float calculaLiquido(const Colaborador& colab, float horas);

        // Interface e Geração de Arquivos
        void gerarFolhaPagamento(const vector<Colaborador>& colaboradores);
};

#endif