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

void FolhaPagamento::gerarFolhaPagamento(const vector <Colaborador>& colaboradores) {
    if(colaboradores.empty()) {
        cout << "Nenhum colaborador cadastrado!\n";
        return;
    }

    int qtdFolhas;
    cout << "Digite o numero de folhas de pagamento que voce deseja gerar: ";
    cin >> qtdFolhas;
    
    // Usando vector em vez de array comum para maior segurança
    vector<int> idsEscolhidos(qtdFolhas);

    for(int j = 0; j < qtdFolhas; j++) {
        cout << "\n--- COLABORADORES ATIVOS ---\n";
        for (int i = 0; i < colaboradores.size(); i++) {
            // TRAVA: Só mostra quem está ativo
            if (colaboradores[i].isAtivo()) {
                cout << "ID: " << colaboradores[i].getID() << " | Nome: " << colaboradores[i].getNome() << endl;
            }
        }

        cout << "Digite o ID do colaborador para a folha " << j + 1 << ": ";
        cin >> idsEscolhidos[j];

        // Validação: Verificar se o ID existe E se o colaborador está ativo
        bool idValido = false;
        for(const auto& c : colaboradores) {
            if(c.getID() == idsEscolhidos[j] && c.isAtivo()) {
                idValido = true;
                break;
            }
        }

        while(!idValido) {
            cout << "ID invalido ou colaborador inativo! Digite um ID da lista acima: ";
            cin >> idsEscolhidos[j];
            for(const auto& c : colaboradores) {
                if(c.getID() == idsEscolhidos[j] && c.isAtivo()) {
                    idValido = true;
                    break;
                }
            }
        }
    }
    
    // Geração das folhas
    for(int k = 0; k < qtdFolhas; k++) {
        // Busca o colaborador pelo ID selecionado
        for(const auto& colab : colaboradores) {
            if(colab.getID() == idsEscolhidos[k]) {
                
                cout << "\n===== Gerando Folha de Pagamento =====";
                cout << "\nNome: " << colab.getNome() << " | CPF: " << colab.getCPF();
                cout << "\nSalario Bruto: " << colab.getSalarioBase();
                cout << "\nSalario Liquido: " << calculaLiquido(colab) << endl;
                
                // Gravação no arquivo CSV
                string nomeArquivo = "Folha_" + colab.getNome() + ".csv";
                ofstream planilha(nomeArquivo); 
                
                if (planilha.is_open()) {
                    planilha << "ID;Nome;CPF;Cargo;Salario Bruto;Salario Liquido" << endl;
                    planilha << colab.getID() << ";"
                             << colab.getNome() << ";"
                             << colab.getCPF() << ";"
                             << colab.getNomeCargo() << ";"
                             << colab.getSalarioBase() << ";"
                             << calculaLiquido(colab) << endl;
                    planilha.close();
                    cout << "Arquivo '" << nomeArquivo << "' gerado com sucesso!\n"; 
                } else {
                    cout << "Erro ao abrir o arquivo para o colaborador " << colab.getNome() << endl;
                }
                break; // Sai do loop de busca pois já achou o colaborador
            }
        }
    }
}