#include "bancoDados_RH.h"
#include <sstream>

vector<string> separar(const string& s, char delimitador) {
    vector<string> tokens;
    string token;
    istringstream tokenStream(s);
    while (getline(tokenStream, token, delimitador)) {
        tokens.push_back(token);
    }
    return tokens;
}


// salva em arquivo csv
void BancoDados_RH::exportarPlanilha(const vector <Colaborador>& colaboradores)
{
    ofstream planilha("ColaboradoresRH.csv");
    if (planilha.is_open())
    {
        // Adicionamos "Ativo" ao cabeçalho
        planilha << "ID;Nome;Cargo;CPF;Sexo;Ativo" << endl; 

        for (int i = 0; i < colaboradores.size(); i++)
        {
            planilha << colaboradores[i].getID() << ";";
            planilha << colaboradores[i].getNome() << ";";
            planilha << colaboradores[i].getNomeCargo() << ";";
            planilha << colaboradores[i].getCPF() << ";";
            planilha << colaboradores[i].getSexo() << ";";
            // Gravamos 1 para true e 0 para false
            planilha << (colaboradores[i].isAtivo() ? "1" : "0") << endl;
        }
        planilha.close();    
        cout << "Dados salvos com sucesso!\n";
    } 
    else {
        cout << "Erro ao abrir o arquivo!\n";
    }
}

void BancoDados_RH::carregarPlanilha(vector <Colaborador>& colaboradores, const vector <Cargo>& listaCargos)
{
    ifstream arquivo("ColaboradoresRH.csv");
    if (arquivo.is_open())
    {
        string linha;
        getline(arquivo, linha); // Pula cabeçalho
    
        while (getline(arquivo, linha)) {
            vector<string> dados_colab = separar(linha, ';'); // Sua função de split

           
            int id_aux = stoi(dados_colab[0]);
            string nomeCargoArquivo = dados_colab[2]; 
            bool ativo_aux = (dados_colab[5] == "1"); // Supondo que 1 seja ativo

            Cargo cargoLocalizado;
            for(const auto& cargoDaLista : listaCargos) {
                if(cargoDaLista.getNome() == nomeCargoArquivo) {
                    cargoLocalizado = cargoDaLista;
                    break;
                }
            }

            // Agora o id_aux e ativo_aux existem para serem passados aqui:
            Colaborador colab_aux(id_aux, dados_colab[1], cargoLocalizado, dados_colab[3], dados_colab[4], ativo_aux);
            colaboradores.push_back(colab_aux);
        }   
        arquivo.close();
    }
}

void BancoDados_RH::salvarBanco() 
{ 
    return; 

}

void BancoDados_RH::carregarBanco() 
{ 
    return; 
}