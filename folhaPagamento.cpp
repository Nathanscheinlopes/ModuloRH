#include "folhaPagamento.h"

/**
 * @brief Retorna o salário base do colaborador.
 */
float FolhaPagamento::calculaBruto(const Colaborador& colab) 
{
    return colab.getSalarioBase();
}


float FolhaPagamento::calculaLiquido(const Colaborador& colab, float horas) 
{
    // Cálculo: (Salário Mensal / 220h) * horas trabalhadas
    float valorHora = colab.getSalarioBase() / 220.0f;
    float brutoProporcional = valorHora * horas;
    
    // Aplicação do desconto de impostos
    return brutoProporcional * (1.0f - impostos);
}


void FolhaPagamento::gerarFolhaPagamento(const vector<Colaborador>& colaboradores) 
{
    if (colaboradores.empty()) 
    {
        cout << "[!] Erro: Nenhum colaborador cadastrado no sistema.\n";
        return;
    }

    int qtdFolhas;
    cout << "\n>>> Quantas folhas de pagamento deseja gerar agora? ";
    cin >> qtdFolhas;
    
    vector<int> idsEscolhidos(qtdFolhas);

    // 1. Fase de Seleção de IDs
    for (int j = 0; j < qtdFolhas; j++) 
    {
        cout << "\n--- COLABORADORES DISPONIVEIS (ATIVOS) ---\n";
        for (const auto& c : colaboradores) 
        {
            if (c.isAtivo()) 
            {
                cout << "ID: " << c.getID() << " | Nome: " << c.getNome() << endl;
            }
        }

        cout << "Digite o ID para a folha " << j + 1 << ": ";
        cin >> idsEscolhidos[j];

        // Validação de existência e status
        bool idValido = false;
        while (!idValido) 
        {
            for (const auto& c : colaboradores) 
            {
                if (c.getID() == idsEscolhidos[j] && c.isAtivo()) 
                {
                    idValido = true;
                    break;
                }
            }
            if (!idValido) 
            {
                cout << "[!] ID invalido ou inativo. Tente novamente: ";
                cin >> idsEscolhidos[j];
            }
        }
    }

    // 2. Fase de Processamento e Gravação
    cout << "\n--- PROCESSANDO PAGAMENTOS ---\n";
    for (int k = 0; k < qtdFolhas; k++) 
    {
        for (const auto& colab : colaboradores) 
        {
            if (colab.getID() == idsEscolhidos[k]) 
            {
                float h;
                cout << "\nColaborador: " << colab.getNome() << endl;
                cout << "Informe as horas trabalhadas no mes: ";
                cin >> h;

                float liquido = calculaLiquido(colab, h);

                // Exibição formatada no console
                cout << fixed << setprecision(2);
                cout << "------------------------------------" << endl;
                cout << "RESUMO DA FOLHA (ID: " << colab.getID() << ")" << endl;
                cout << "Nome: " << colab.getNome() << endl;
                cout << "Salario Base (220h): R$ " << colab.getSalarioBase() << endl;
                cout << "Horas Informadas: " << h << "h" << endl;
                cout << "VALOR LIQUIDO A PAGAR: R$ " << liquido << endl;
                cout << "------------------------------------" << endl;
                
                // Geração do arquivo CSV individual
                string nomeArquivo = "Folha_ID_" + to_string(colab.getID()) + "_" + colab.getNome() + ".csv";
                ofstream planilha(nomeArquivo);
                
                if (planilha.is_open()) 
                {
                    planilha << "ID;Nome;Horas;SalarioBruto;SalarioLiquido" << endl;
                    planilha << colab.getID() << ";"
                             << colab.getNome() << ";"
                             << h << ";"
                             << colab.getSalarioBase() << ";"
                             << liquido << endl;
                    planilha.close();
                    cout << "[SISTEMA] Arquivo '" << nomeArquivo << "' gerado com sucesso.\n";
                }
                break; 
            }
        }
    }
}
