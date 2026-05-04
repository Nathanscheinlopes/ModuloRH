#include "colaborador.h"

int Colaborador::contador_ID = 0; //inicializa o contador de IDs de colaboradores

Colaborador::Colaborador() // metodo construtor - inicializa todos os membros da classe Colaborador
{
    this->id = ++contador_ID; // atribui id e soma 1 ao contador (id sequencial do sistema)
    this->nome = "Nao preenchido";
    this->cpf = "00000000000";
    this->sexo = "Nao preenchido";
    struct tm data_admissao = {0};
    struct tm data_desligamento = {0}; // logica da data de desligamento deve entrar no metodo deleteColaborador
}

Colaborador::Colaborador(int id_arquivo, string nome_arq, Cargo cargo_obj, string cpf_arq, string sexo_arq) // metodo contrutor para pegar dados de arquivo
{
    this->id = id_arquivo;
    this->nome = nome_arq;
    this->objetoCargo = cargo_obj;
    this->cpf = cpf_arq;
    this->sexo = sexo_arq;

    if (id_arquivo > contador_ID) 
    {
        contador_ID = id_arquivo;
    }
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

    cout << "Colaborador " << this->nome << " com ID " << this->id << " cadastrado com sucesso. Admissao em: " << data_admissao_aux << endl;
}

void Colaborador::editColaborador() // DESENVOLVER!!
{ 
    return; 
}
void Colaborador::deleteColaborador() // DESENVOLVER!!
{ 
    return; 
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