#ifndef FOLHAPAGAMENTO_H
#define FOLHAPAGAMENTO_H

#include "colaborador.h"
#include <string>
#include <vector>
#include <iostream> // Para usar cout/cin
#include <ctime>    // Para usar struct tm e time_t

class FolhaPagamento
{
        
    private:
        
        float salario;
        float impostos = 0.12; // valor fixo de 12% por enquanto - estudar possibilidade de receber esta informacao do modulo financeiro depois
        float total_hh;
                
    public:
        
        void enviaFinanceiro(); // inicialmente vai apenas gerar um arquivo csv com os dados e na segunda etapa envia para o financeiro
            
        void recebeFinanceiro(); // receber impostos do financeiro - avaliar desenvolvimento na segunda etapa
                    
        float calculaBruto(const Colaborador& colaboradorA); // Acesso indireto via metodo publico
                
        float calculaLiquido(const Colaborador& colaboradorA); // Acesso indireto via metodo publico

        void gerarFolhaPagamento(const vector <Colaborador>& colaboradores); // Acesso indireto via metodo publico

}; // fim da classe

#endif