#ifndef FOLHAPAGAMENTO_H
#define FOLHAPAGAMENTO_H

#include "colaborador.h"

class FolhaPagamento
{
        
    private:
        
        float salario;
        float impostos = 0.12; // valor fixo de 12% por enquanto - estudar possibilidade de receber esta informacao do modulo financeiro depois
        float total_hh;
                
    public:
        
        void enviaFinanceiro(); // inicialmente vai apenas gerar um arquivo csv com os dados e na segunda etapa envia para o financeiro
            
        void recebeFinanceiro(); // receber impostos do financeiro - avaliar desenvolvimento na segunda etapa
                    
        float calculaBruto(Colaborador& colaboradorA); // Acesso indireto via metodo publico
                
        float calculaLiquido(Colaborador& colaboradorA); // Acesso indireto via metodo publico

}; // fim da classe

#endif