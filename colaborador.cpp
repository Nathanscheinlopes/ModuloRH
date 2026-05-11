#include "colaborador.h"
#include <algorithm> // Necessário para o transform
#include <cctype>    // Necessário para o ::toupper

int Colaborador::contador_ID = 0; //inicializa o contador de IDs de colaboradores

Colaborador::Colaborador() // metodo construtor - inicializa todos os membros da classe Colaborador
{
    this->id = ++contador_ID; // atribui id e soma 1 ao contador (id sequencial do sistema)
    this->nome = "Nao preenchido";
    this->cpf = "00000000000";
    this->sexo = "Nao preenchido";
    this->ativo = false; // Inicialmente, o colaborador não está ativo
    this->horasTrabalhadas = 0.0; // Inicialmente, o colaborador não trabalhou horas
    struct tm data_admissao = {0};
    struct tm data_desligamento = {0}; // logica da data de desligamento deve entrar no metodo deleteColaborador
}

Colaborador::Colaborador(int id_arquivo, string nome_arq, Cargo cargo_obj,string cpf_arq, string sexo_arq, bool ativo_arq) 
{
    this->id = id_arquivo;
    this->nome = nome_arq;
    this->objetoCargo = cargo_obj;
    this->cpf = cpf_arq;
    this->sexo = sexo_arq;
    this->ativo = ativo_arq; // Atribui o estado vindo do CSV
}

string Colaborador::getNomeCargo() const
{
    return objetoCargo.getNome();
}

float Colaborador::getSalarioBase() const
{
    return objetoCargo.getSalario();                
}

void Colaborador::addColaborador(const vector <Cargo>& listaCargos)
{
    string nome_Temp, sexo_Temp, cpf_Temp; // variaveis temporarias para guardar entradas do usuario
    int cargo_aux;
   
    // Lógica para obter a data atual e salvar no membro data de admissao
    time_t tempoBruto = time(0); // Pega o tempo agora
    struct tm* dataAtual = localtime(&tempoBruto); // Converte para struct tm
    this->data_admissao = *dataAtual; // atribui ao membro da classe
    char data_admissao_aux[100]; // variavel auxiliar para salvar a data atual
    strftime(data_admissao_aux, 100, "%d/%m/%Y", &this->data_admissao); // converter os elementos da struct tm na data formatada
    
    // dados de entrada do usuario salvos em variaveis temporarias
    cout << "=====Cadastro de novo colaborador=====" << endl;
    cout << "Digite o Nome: ";
    getline(cin >> ws, nome_Temp); // 'ws' limpa o buffer para aceitar espaços

    cout << "Digite o CPF (apenas numeros): ";
    cin >> cpf_Temp;

    cout << "Digite o Sexo (M/F): ";
    cin >> sexo_Temp;
    while(sexo_Temp != "m" && sexo_Temp != "M" && sexo_Temp != "f" && sexo_Temp != "F")
    {
        cout << "Informacao invalida! Digite M ou F novamente.\n";
        cin >> sexo_Temp;
    }
    transform(sexo_Temp.begin(), sexo_Temp.end(), sexo_Temp.begin(), ::toupper); // deixando a letra maiuscula

    cout << "Digite o numero correspondente ao cargo: \n";
    for (int i = 0; i < listaCargos.size(); i++) 
    {
        cout << listaCargos[i].getID_Cargo() << ". " << listaCargos[i].getNome() << endl; // puxa os cargos atualizados de um arquivo de cargos (associacao do vetor com o arquivo de cargos no main)
    }
    cin >> cargo_aux;
    while(cargo_aux < 1 || cargo_aux > listaCargos.size()) 
    {
        cout << "Cargo invalido! Escolha entre 1 e " << listaCargos.size() << ": ";
        cin >> cargo_aux;
    }

    this->nome = nome_Temp;
    this->cpf = cpf_Temp;
    this->sexo = sexo_Temp;
    this->objetoCargo = listaCargos[cargo_aux - 1]; // - 1 pois o vetor de cargos comeca a contar em zero
    this->ativo = true; // Novo colaborador começa como ativo 

    cout << "Colaborador " << this->nome << " com ID " << this->id << " cadastrado com sucesso. Admissao em: " << data_admissao_aux << endl;
}

void Colaborador::editColaborador(std::vector<Colaborador>& lista, const std::vector<Cargo>& listaCargos) {
    int idBusca;
    cout << "Digite o ID do colaborador que deseja editar: ";
    cin >> idBusca;

    Colaborador* colabParaEditar = nullptr;

    // Localiza o colaborador na lista
    for (auto& c : lista) {
        if (c.getID() == idBusca) {
            colabParaEditar = &c;
            break;
        }
    }

    if (colabParaEditar == nullptr) {
        cout << "[!] Colaborador com ID " << idBusca << " nao encontrado.\n";
        return;
    }

    // Se o colaborador estiver excluído, avisar o usuário
    if (!colabParaEditar->isAtivo()) {
        cout << "[!] Aviso: Este colaborador esta inativo (EXCLUIDO).\n";
    }

    int opcao = 0;
    do {
        cout << "\n--- EDITANDO: " << colabParaEditar->getNome() << " ---\n";
        cout << "1. Alterar Nome\n";
        cout << "2. Alterar Cargo\n";
        cout << "3. Alterar Sexo\n";
        cout << "4. Reativar/Desativar Colaborador\n";
        cout << "0. Finalizar Edicao\n";
        cout << "Escolha uma opcao: ";
        cin >> opcao;

        switch (opcao) {
            case 1: {
                string novoNome;
                cout << "Nome atual: " << colabParaEditar->getNome() << endl;
                cout << "Digite o novo nome: ";
                cin >> ws;
                getline(cin, novoNome);
                colabParaEditar->nome = novoNome; // Certifique-se de que o atributo 'nome' permita acesso ou use um setter
                cout << "Nome alterado com sucesso!\n";
                break;
            }
            case 2: {
                int novoCargoID;
                cout << "Cargo atual: " << colabParaEditar->getNomeCargo() << endl;
                cout << "Selecione o novo cargo:\n";
                for (const auto& cargo : listaCargos) {
                    cout << cargo.getID_Cargo() << ". " << cargo.getNome() << endl;
                }
                cin >> novoCargoID;
                if (novoCargoID >= 1 && novoCargoID <= listaCargos.size()) {
                    colabParaEditar->objetoCargo = listaCargos[novoCargoID - 1];
                    cout << "Cargo atualizado!\n";
                } else {
                    cout << "ID de cargo invalido.\n";
                }
                break;
            }
            case 3: {
                string novoSexo;
                cout << "Digite o novo sexo (M/F): ";
                cin >> novoSexo;
                transform(novoSexo.begin(), novoSexo.end(), novoSexo.begin(), ::toupper);
                if (novoSexo == "M" || novoSexo == "F") {
                    colabParaEditar->sexo = novoSexo;
                    cout << "Sexo atualizado!\n";
                } else {
                    cout << "Entrada invalida.\n";
                }
                break;
            }
            case 4: {
                colabParaEditar->setAtivo(!colabParaEditar->isAtivo());
                cout << "Status alterado para: " << (colabParaEditar->isAtivo() ? "ATIVO" : "INATIVO") << endl;
                break;
            }
            case 0:
                cout << "Edicao finalizada.\n";
                break;
            default:
                cout << "Opcao invalida.\n";
        }
    } while (opcao != 0);
}

void Colaborador::atualizarContador(const vector<Colaborador>& lista) {
    int maior = 0;
    for (const auto& c : lista) {
        if (c.getID() > maior) {
            maior = c.getID();
        }
    }
    contador_ID = maior; // O próximo ID será maior + 1
}

void Colaborador::deleteColaborador(std::vector<Colaborador>& lista, int idParaExcluir) 
{
    bool encontrado = false;
    for (auto& c : lista) {
        if (c.getID() == idParaExcluir && c.isAtivo()) {
            c.setAtivo(false); // Aqui acontece o Soft Delete
            std::cout << "Colaborador desativado com sucesso!\n";
            encontrado = true;
            break;
        }
    }
    if (!encontrado) {
        std::cout << "ID ativo nao encontrado.\n";
    }
}

void Colaborador::buscarColaborador(const vector<Colaborador>& lista, string termoBusca) {
    bool encontrado = false;
    
    // Normalização do termo de busca
    string termoUpper = termoBusca;
    transform(termoUpper.begin(), termoUpper.end(), termoUpper.begin(), ::toupper);

    cout << "\n================================================ DETALHES DA BUSCA ================================================" << endl;
    // Cabeçalho ajustado
    printf("%-4s | %-10s | %-12s | %-6s | %-15s | %-20s\n", "ID", "STATUS", "CPF", "SEXO", "CARGO", "NOME");
    cout << "-------------------------------------------------------------------------------------------------------------------" << endl;

    for (const auto& colab : lista) {
        string nomeUpper = colab.getNome();
        transform(nomeUpper.begin(), nomeUpper.end(), nomeUpper.begin(), ::toupper);
        
        string idStr = to_string(colab.getID());

        // Critérios de busca: ID, Nome ou CPF
        if (idStr == termoBusca || 
            nomeUpper.find(termoUpper) != string::npos || 
            colab.getCPF() == termoBusca) {
            
            string statusTexto = colab.isAtivo() ? "ATIVO" : "EXCLUIDO";
            
            // Usando printf para manter as colunas alinhadas independentemente do tamanho do nome
            printf("%-4d | %-10s | %-12s | %-6s | %-15s | %-20s\n", 
                   colab.getID(), 
                   statusTexto.c_str(), 
                   colab.getCPF().c_str(), 
                   colab.getSexo().c_str(), 
                   colab.getNomeCargo().c_str(), 
                   colab.getNome().c_str());
            
            encontrado = true;
        }
    }

    if (!encontrado) {
        cout << "\n[!] Nenhum colaborador encontrado para o termo: " << termoBusca << endl;
    }
    cout << "===================================================================================================================\n" << endl;
}

int Colaborador::getID() const 
{ 
    return id; 
}

string Colaborador::getNome() const 
{ 
    return nome; 
}

string Colaborador::getCPF() const 
{ 
    return cpf; 
}

string Colaborador::getSexo() const 
{ 
    return sexo; 
}