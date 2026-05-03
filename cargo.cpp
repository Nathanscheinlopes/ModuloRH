#include "cargo.h"

Cargo::Cargo() // metodo construtor sem parametros
{
    this->id_cargo = 0;
    this->nome = "Nao preenchido";
    this->salarioBase = 0;
}

Cargo::Cargo(int id_cargo_arq, string nome_arq, float salario_arq) // metodo construtor para o metodo extrairCargosPlanilha - informacoes extraidas de arquivo csv
{
    this->id_cargo = id_cargo_arq;
    this->nome = nome_arq;
    this->salarioBase = salario_arq;
}

void Cargo::extrairCargosPlanilha(vector <Cargo>& cargos)
{
    ifstream arquivo("TabelaCargos.csv"); // ifstream le dados no arquivo
    if (arquivo.is_open()) // confere se o arquivo esta aberto
    {
        string linha; // variavel auxiliar para salvar as linhas lidas do arquivo
        getline (arquivo, linha); // copia a primeira linha de cabecalho (eliminar)

        while (getline(arquivo, linha)) 
        {
            if (linha.empty() || linha.length() < 2) {
                    continue;
            }
            
            string dados_cargos[3]; // Vetor temporário para guardar os pedaços da linha
            size_t pos = 0;

            for (int i = 0; i < 2; i++) // Faz o corte para as 2 primeiras posicoes
            {
                pos = linha.find(";");
                if (pos == string::npos) break;
                
                dados_cargos[i] = linha.substr(0, pos); // cria uma substring ate o ; e copia para o vetor auxiliar
                linha.erase(0, pos + 1); // apagar o que ja foi extraido
            }
            dados_cargos[2] = linha; // O que sobrou é o salário

            try {
                int id_cargo_aux = stoi(dados_cargos[0]); // converter o ID de string para int
                float salario_aux = stof(dados_cargos[2]);// converter o salario de string para float
                Cargo cargo_aux(id_cargo_aux, dados_cargos[1], salario_aux);
                cargos.push_back(cargo_aux); 
            }
            catch (...) {
                continue; // Se o stoi ou stof falhar, o catch elimina o erro e o loop continua
            }
        }
        arquivo.close();
        cout << "Dados de cargos carregados com sucesso!\n";
    }
    else 
    {
        cout << "Erro ao abrir o arquivo\n";
    }   
}

int Cargo::getID_Cargo() const 
{ 
    return id_cargo; 
}

string Cargo::getNome() const 
{ 
    return nome; 
}

float Cargo::getSalario() const 
{ 
    return salarioBase; 
}