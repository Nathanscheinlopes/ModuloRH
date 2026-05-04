#include "folhaPagamento.h"

void FolhaPagamento::enviaFinanceiro() // inicialmente vai apenas gerar um arquivo csv com os dados e na segunda etapa envia para o financeiro
{
    return;
}

void FolhaPagamento::recebeFinanceiro() // receber impostos do financeiro - avaliar desenvolvimento na segunda etapa
{
    return;
}

float FolhaPagamento::calculaBruto(const Colaborador& colaboradorA) // Acesso indireto via metodo publico
{
    float salarioBruto = colaboradorA.getSalarioBase(); // puxa o salario base de dentro da classe colaborador utilizando metodo publico
    return salarioBruto;
}

float FolhaPagamento::calculaLiquido(const Colaborador& colaboradorA)
{
    float salarioBruto;
    salarioBruto = calculaBruto(colaboradorA);
    float salarioLiquido = salarioBruto * (1 - impostos); // desconta os impostos do bruto
    return salarioLiquido;
}

void FolhaPagamento::gerarFolhaPagamento(const vector <Colaborador>& colaboradores)
{
    int folha_aux;
    int folha_aux2 = 0;

    if(colaboradores.size() == 0)
    {
        cout << "Nenhum colaborador cadastrado!\n";
    }

    cout << "Digite o numero de folhas de pagamento que voce deseja gerar: ";
    cin >> folha_aux2;
    
    int folha_aux3[folha_aux2];

    for(int j =0; j < folha_aux2; j++)
    {
        cout << "Digite o numero correspondente ao ID do colaborador para gerar a folha de pagamento: \n";
        for (int i = 0; i < colaboradores.size(); i++) 
        {
            cout << colaboradores[i].getID() << ". " << colaboradores[i].getNome() << endl;
        }
        cin >> folha_aux3[j];

        while(folha_aux3[j] < 1 || folha_aux3[j] > colaboradores.size()) 
        {
            cout << "ID invalido! Escolha entre 1 e " << colaboradores.size() << ": ";
            cin >> folha_aux3[j];
        }
    }
    
    for(int k = 0; k < folha_aux2; k++)
    {
        cout << "=====Folha de Pagamento=====\n";
        cout << "Dados do colaborador - |Nome: " << colaboradores[folha_aux3[k] - 1].getNome() << "| |CPF: " << colaboradores[folha_aux3[k] - 1].getCPF() << "|\n";
        cout << "Horas trabalhadas: \n"; // necessario desenvolver a parte do ponto para incluir esta informacao
        cout << "Salario Bruto: " << colaboradores[folha_aux3[k] - 1].getSalarioBase() << "\n";
        cout << "Salario Liquido: " << calculaLiquido(colaboradores[folha_aux3[k] - 1]) << "\n";
        
        ofstream planilha("Folha " + colaboradores[folha_aux3[k] - 1].getNome() + ".csv"); // ofstream escreve dados no arquivo
        if (planilha.is_open()) // confere se o arquivo esta aberto
        {
            planilha << "ID;Nome;CPF;Cargo;Salario Bruto; Salario Liquido" << endl; // cabecalho do arquivo
            planilha << colaboradores[folha_aux3[k] - 1].getID() << ";";
            planilha << colaboradores[folha_aux3[k] - 1].getNome() << ";";
            planilha << colaboradores[folha_aux3[k] - 1].getCPF() << ";";
            planilha << colaboradores[folha_aux3[k] - 1].getNomeCargo() << ";";
            planilha << colaboradores[folha_aux3[k] - 1].getSalarioBase() << ";";
            planilha << calculaLiquido(colaboradores[folha_aux3[k] - 1]) << endl;

            planilha.close();
            cout << "Dados salvos com sucesso!\n"; 
        }

        else // caso o arquivo nao esteja aberto
        {
            cout << "Erro ao abrir o arquivo!\n";
        }
    }
}