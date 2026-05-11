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

float FolhaPagamento::calculaLiquido(const Colaborador& colab, float horas) {
    // Cálculo: (Salário / 220 horas padrão) * horas trabalhadas
    float valorHora = colab.getSalarioBase() / 220.0;
    float brutoProporcional = valorHora * horas;
    
    return brutoProporcional * (1 - impostos);
}

void FolhaPagamento::gerarFolhaPagamento(const vector <Colaborador>& colaboradores) {
    if(colaboradores.empty()) {
        cout << "Nenhum colaborador cadastrado!\n";
        return;
    }

    int qtdFolhas;
    cout << "Digite o numero de folhas de pagamento que voce deseja gerar: ";
    cin >> qtdFolhas;
    
    vector<int> idsEscolhidos(qtdFolhas);

    for(int j = 0; j < qtdFolhas; j++) {
        cout << "\n--- COLABORADORES ATIVOS ---\n";
        for (const auto& c : colaboradores) {
            if (c.isAtivo()) {
                cout << "ID: " << c.getID() << " | Nome: " << c.getNome() << endl;
            }
        }

        cout << "Digite o ID para a folha " << j + 1 << ": ";
        cin >> idsEscolhidos[j];

        // Validação básica
        bool idValido = false;
        for(const auto& c : colaboradores) {
            if(c.getID() == idsEscolhidos[j] && c.isAtivo()) {
                idValido = true;
                break;
            }
        }
        while(!idValido) {
            cout << "ID invalido! Digite um ID ativo: ";
            cin >> idsEscolhidos[j];
            for(const auto& c : colaboradores) {
                if(c.getID() == idsEscolhidos[j] && c.isAtivo()) idValido = true;
            }
        }
    } // Fim do for de seleção

    // Processamento
    for(int k = 0; k < qtdFolhas; k++) {
        for(const auto& colab : colaboradores) {
            // Erro 1 corrigido: Usando idsEscolhidos[k] em vez de idBusca
            if(colab.getID() == idsEscolhidos[k]) {
                
                float h;
                cout << "\n>>> Digite as horas trabalhadas para " << colab.getNome() << ": ";
                cin >> h;

                cout << "\n===== Folha de Pagamento =====";
                cout << "\nNome: " << colab.getNome();
                cout << "\nHoras: " << h;
                cout << "\nSalario Bruto (Base): " << colab.getSalarioBase();
                
                // Erro 2 corrigido: Passando colab E h para a função
                float liquido = calculaLiquido(colab, h);
                cout << "\nSalario Liquido: " << liquido << endl;
                
                string nomeArquivo = "Folha_" + colab.getNome() + ".csv";
                ofstream planilha(nomeArquivo);
                
                if (planilha.is_open()) {
                    planilha << "ID;Nome;Horas;Salario Bruto;Salario Liquido" << endl;
                    planilha << colab.getID() << ";"
                             << colab.getNome() << ";"
                             << h << ";"
                             << colab.getSalarioBase() << ";"
                             << liquido << endl;
                    planilha.close();
                }
                break; 
            }
        }
    }
} // Chave de fechamento da função (Erro de "expected '}'" resolvido)