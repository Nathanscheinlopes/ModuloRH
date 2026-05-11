#include "colaborador.h"
#include <algorithm>
#include <cctype>

// Inicialização do contador global de colaboradores
int Colaborador::contador_ID = 0;

Colaborador::Colaborador() 
{
    this->id = ++contador_ID;
    this->nome = "Nao preenchido";
    this->cpf = "00000000000";
    this->sexo = "Nao preenchido";
    this->ativo = false; 
    this->horasTrabalhadas = 0.0;
    this->data_admissao = {0};
    this->data_desligamento = {0};
}

Colaborador::Colaborador(int id_arquivo, string nome_arq, Cargo cargo_obj, string cpf_arq, string sexo_arq, bool ativo_arq) 
{
    this->id = id_arquivo;
    this->nome = nome_arq;
    this->objetoCargo = cargo_obj;
    this->cpf = cpf_arq;
    this->sexo = sexo_arq;
    this->ativo = ativo_arq;
}

string Colaborador::getNomeCargo() const { return objetoCargo.getNome(); }
float Colaborador::getSalarioBase() const { return objetoCargo.getSalario(); }


void Colaborador::addColaborador(const vector<Cargo>& listaCargos)
{
    string nome_Temp, sexo_Temp, cpf_Temp;
    int cargo_aux;
   
    // Captura do tempo real do sistema
    time_t tempoBruto = time(0);
    struct tm* dataAtual = localtime(&tempoBruto);
    this->data_admissao = *dataAtual;
    
    char data_formatada[11];
    strftime(data_formatada, 11, "%d/%m/%Y", &this->data_admissao);
    
    cout << "\n===== CADASTRO DE COLABORADOR =====" << endl;
    cout << "Nome Completo: ";
    getline(cin >> ws, nome_Temp);

    cout << "CPF (apenas numeros): ";
    cin >> cpf_Temp;

    cout << "Sexo (M/F): ";
    cin >> sexo_Temp;
    while(sexo_Temp != "m" && sexo_Temp != "M" && sexo_Temp != "f" && sexo_Temp != "F") {
        cout << "[!] Invalido. Digite M ou F: ";
        cin >> sexo_Temp;
    }
    transform(sexo_Temp.begin(), sexo_Temp.end(), sexo_Temp.begin(), ::toupper);

    cout << "Selecione o Cargo:\n";
    for (const auto& c : listaCargos) {
        if(c.isAtivo()) // Opcional: só mostra cargos ativos para novos cadastros
            cout << c.getID_Cargo() << ". " << c.getNome() << endl;
    }
    cin >> cargo_aux;

    this->nome = nome_Temp;
    this->cpf = cpf_Temp;
    this->sexo = sexo_Temp;
    this->objetoCargo = listaCargos[cargo_aux - 1]; // Assume IDs sequenciais começando em 1
    this->ativo = true; 

    cout << "[SISTEMA] " << this->nome << " cadastrado (ID: " << this->id << ") em " << data_formatada << endl;
}

void Colaborador::editColaborador(vector<Colaborador>& lista, const vector<Cargo>& listaCargos) 
{
    int idBusca;
    cout << "Digite o ID para editar: ";
    cin >> idBusca;

    Colaborador* alvo = nullptr;
    for (auto& c : lista) {
        if (c.getID() == idBusca) {
            alvo = &c;
            break;
        }
    }

    if (!alvo) {
        cout << "[!] Colaborador nao encontrado.\n";
        return;
    }

    int opcao = 0;
    do {
        cout << "\n--- EDITANDO: " << alvo->getNome() << " (Status: " << (alvo->isAtivo() ? "Ativo" : "Inativo") << ") ---\n";
        cout << "1. Nome | 2. Cargo | 3. Sexo | 4. Alterar Status | 0. Sair\nEscolha: ";
        cin >> opcao;

        if (opcao == 1) {
            cout << "Novo nome: "; cin >> ws; getline(cin, alvo->nome);
        } else if (opcao == 2) {
            int nCargo;
            cout << "Novo Cargo (ID): "; cin >> nCargo;
            if (nCargo >= 1 && nCargo <= listaCargos.size()) 
                alvo->objetoCargo = listaCargos[nCargo - 1];
        } else if (opcao == 3) {
            cout << "Novo sexo (M/F): "; cin >> alvo->sexo;
            transform(alvo->sexo.begin(), alvo->sexo.end(), alvo->sexo.begin(), ::toupper);
        } else if (opcao == 4) {
            alvo->setAtivo(!alvo->isAtivo());
            cout << "Novo status definido.\n";
        }
    } while (opcao != 0);
}

void Colaborador::atualizarContador(const vector<Colaborador>& lista) 
{
    int maior = 0;
    for (const auto& c : lista) {
        if (c.getID() > maior) maior = c.getID();
    }
    contador_ID = maior;
}

void Colaborador::deleteColaborador(vector<Colaborador>& lista, int idParaExcluir) 
{
    for (auto& c : lista) {
        if (c.getID() == idParaExcluir && c.isAtivo()) {
            c.setAtivo(false);
            cout << "[SISTEMA] Colaborador desativado.\n";
            return;
        }
    }
    cout << "[!] ID ativo nao encontrado.\n";
}

void Colaborador::buscarColaborador(const vector<Colaborador>& lista, string termoBusca) 
{
    string termoUpper = termoBusca;
    transform(termoUpper.begin(), termoUpper.end(), termoUpper.begin(), ::toupper);

    cout << "\n" << string(100, '=') << "\n";
    printf("%-4s | %-10s | %-12s | %-6s | %-15s | %-20s\n", "ID", "STATUS", "CPF", "SEXO", "CARGO", "NOME");
    cout << string(100, '-') << "\n";

    bool achei = false;
    for (const auto& colab : lista) {
        string nUpper = colab.getNome();
        transform(nUpper.begin(), nUpper.end(), nUpper.begin(), ::toupper);
        
        if (to_string(colab.getID()) == termoBusca || nUpper.find(termoUpper) != string::npos || colab.getCPF() == termoBusca) {
            printf("%-4d | %-10s | %-12s | %-6s | %-15s | %-20s\n", 
                   colab.getID(), (colab.isAtivo() ? "ATIVO" : "EXCLUIDO"), 
                   colab.getCPF().c_str(), colab.getSexo().c_str(), 
                   colab.getNomeCargo().c_str(), colab.getNome().c_str());
            achei = true;
        }
    }

    if (!achei) cout << "[!] Nenhuma correspondencia encontrada para: " << termoBusca << endl;
    cout << string(100, '=') << "\n";
}

int Colaborador::getID() const { return id; }
string Colaborador::getNome() const { return nome; }
string Colaborador::getCPF() const { return cpf; }
string Colaborador::getSexo() const { return sexo; }