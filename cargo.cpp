#include "cargo.h"
#include "colaborador.h"

// Inicialização do contador estático
int Cargo::contador_id_cargo = 0;

Cargo::Cargo() 
{
    this->id_cargo = ++contador_id_cargo;
    this->nome = "Nao preenchido";
    this->salarioBase = 0;
    this->ativo = true;
}


Cargo::Cargo(int id_cargo_arq, string nome_arq, float salario_arq, bool ativo_arq) 
{
    this->id_cargo = id_cargo_arq;
    this->nome = nome_arq;
    this->salarioBase = salario_arq;
    this->ativo = ativo_arq;
}


void Cargo::atualizarContador(const vector<Cargo>& lista) 
{
    int maior = 0;
    for (const auto& c : lista) 
    {
        if (c.getID_Cargo() > maior) maior = c.getID_Cargo();
    }
    contador_id_cargo = maior;
}


void Cargo::extrairCargosPlanilha(vector<Cargo>& cargos) 
{
    ifstream arquivo("TabelaCargos.csv");
    if (arquivo.is_open()) 
    {
        string linha;
        getline(arquivo, linha); // Pular cabeçalho

        while (getline(arquivo, linha)) 
        {
            if (linha.empty() || linha.length() < 2) continue;
            
            string dados[4]; 
            size_t pos = 0;
            
            // Split da linha por ponto e vírgula
            for (int i = 0; i < 3; i++) 
            {
                pos = linha.find(";");
                if (pos == string::npos) break;
                dados[i] = linha.substr(0, pos);
                linha.erase(0, pos + 1);
            }
            dados[3] = linha; 

            try 
            {
                int id = stoi(dados[0]);
                float sal = stof(dados[2]);
                bool status = (dados[3] == "1"); 
                cargos.push_back(Cargo(id, dados[1], sal, status));
            } 
            catch (...) { continue; }
        }
        arquivo.close();
    }
}


void Cargo::salvarCargosPlanilha(const vector<Cargo>& cargos) 
{
    ofstream arquivo("TabelaCargos.csv");
    if (arquivo.is_open()) 
    {
        arquivo << "ID;Nome;SalarioBase;Ativo" << endl;
        for (const auto& c : cargos) 
        {
            arquivo << c.getID_Cargo() << ";" 
                    << c.getNome() << ";" 
                    << c.getSalario() << ";" 
                    << (c.isAtivo() ? "1" : "0") << endl;
        }
        arquivo.close();
    }
}


void Cargo::adicionarCargo(vector<Cargo>& lista) 
{
    string nome;
    float salario;
    cout << "\n--- Cadastro de Novo Cargo ---\n";
    cout << "Nome do Cargo: ";
    cin >> ws;
    getline(cin, nome);
    cout << "Salario Base: ";
    cin >> salario;

    Cargo novo; 
    novo.setNome(nome);
    novo.setSalario(salario);
    novo.setAtivo(true);
    
    lista.push_back(novo);
    cout << "[SISTEMA] Cargo '" << nome << "' cadastrado com ID " << novo.getID_Cargo() << "!\n";
}


void Cargo::editarCargo(vector<Cargo>& lista) 
{
    int id;
    cout << "Digite o ID do cargo para editar: ";
    cin >> id;
    for (auto& c : lista) 
    {
        if (c.getID_Cargo() == id) 
        {
            int op;
            cout << "Editando: " << c.getNome() << " | Salario: R$ " << c.getSalario() << endl;
            cout << "1. Mudar Nome\n2. Mudar Salario\nEscolha: ";
            cin >> op;
            
            if (op == 1) 
            {
                string n; cout << "Novo nome: "; cin >> ws; getline(cin, n);
                c.setNome(n);
            } 
            else if (op == 2) 
            {
                float s; cout << "Novo salario: "; cin >> s;
                c.setSalario(s);
            }
            cout << "[SISTEMA] Cargo atualizado com sucesso!\n";
            return;
        }
    }
    cout << "[!] ID nao encontrado.\n";
}


void Cargo::deletarCargo(vector<Cargo>& lista, const vector<Colaborador>& colaboradores) 
{
    int id;
    cout << "Digite o ID do cargo para Ativar/Desativar: ";
    cin >> id;

    for (auto& c : lista) 
    {
        if (c.getID_Cargo() == id) 
        {
            if (c.isAtivo()) 
            {
                // Validação de vínculo antes de desativar
                for (const auto& colab : colaboradores) 
                {
                    if (colab.getNomeCargo() == c.getNome() && colab.isAtivo()) 
                    {
                        cout << "[!] Erro: Nao e possivel desativar. Existem colaboradores ativos neste cargo!\n";
                        return;
                    }
                }
                c.setAtivo(false);
                cout << "[SISTEMA] Cargo '" << c.getNome() << "' DESATIVADO.\n";
            } 
            else 
            {
                c.setAtivo(true);
                cout << "[SISTEMA] Cargo '" << c.getNome() << "' REATIVADO.\n";
            }
            return; 
        }
    }
    cout << "[!] Cargo nao encontrado.\n";
}

int Cargo::getID_Cargo() const { return id_cargo; }
string Cargo::getNome() const { return nome; }
float Cargo::getSalario() const { return salarioBase; }