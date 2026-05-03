#include "folhaPagamento.h"

void FolhaPagamento::enviaFinanceiro() // inicialmente vai apenas gerar um arquivo csv com os dados e na segunda etapa envia para o financeiro
{
    return;
}

void FolhaPagamento::recebeFinanceiro() // receber impostos do financeiro - avaliar desenvolvimento na segunda etapa
{
    return;
}

float FolhaPagamento::calculaBruto(Colaborador& colaboradorA) // Acesso indireto via metodo publico
{
    float salarioBruto = colaboradorA.getSalarioBase(); // puxa o salario base de dentro da classe colaborador utilizando metodo publico
    return salarioBruto;
}

float FolhaPagamento::calculaLiquido(Colaborador& colaboradorA)
{
    float salarioBruto;
    salarioBruto = calculaBruto(colaboradorA);
    float salarioLiquido = salarioBruto * (1 - impostos); // desconta os impostos do bruto
    return salarioLiquido;
}