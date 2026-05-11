#include "bancoDados_RH.h"
#include <sstream>

/**
 * @brief Função auxiliar para dividir strings com base em um delimitador (split).
 */
vector<string> separar(const string& s, char delimitador) 
{
    vector<string> tokens;
    string token;
    istringstream tokenStream(s);
    
    while (getline(tokenStream, token, delimitador)) 
    {
        tokens.push_back(token);
    }
    return tokens;
}

void BancoDados_RH::exportarPlanilha(const vector<Colaborador>& colaboradores)
{
    ofstream planilha("ColaboradoresRH.csv");
    
    if (planilha.is_open())
    {
        // Cabeçalho do arquivo CSV
        planilha << "ID;Nome;Cargo;CPF;Sexo;Ativo" << endl; 

        for (const auto& colab : colaboradores)
        {
            planilha << colab.getID() << ";"
                     << colab.getNome() << ";"
                     << colab.getNomeCargo() << ";"
                     << colab.getCPF() << ";"
                     << colab.getSexo() << ";"
                     << (colab.isAtivo() ? "1" : "0") << endl; // Soft Delete: 1=Ativo, 0=Inativo
        }
        
        planilha.close();    
        cout << "[SISTEMA] Dados dos colaboradores exportados com sucesso!\n";
    } 
    else 
    {
        cout << "[ERRO] Nao foi possivel abrir o arquivo para escrita!\n";
    }
}


void BancoDados_RH::carregarPlanilha(vector<Colaborador>& colaboradores, const vector<Cargo>& listaCargos)
{
    ifstream arquivo("ColaboradoresRH.csv");
    
    if (arquivo.is_open())
    {
        string linha;
        getline(arquivo, linha); // Ignora a linha de cabeçalho do CSV
    
        while (getline(arquivo, linha)) 
        {
            if (linha.empty()) continue; // Pula linhas vazias acidentais

            vector<string> dados_colab = separar(linha, ';'); 

            // Extração de dados com conversão de tipos
            int id_aux = stoi(dados_colab[0]);
            string nomeCargoArquivo = dados_colab[2]; 
            bool ativo_aux = (dados_colab[5] == "1");

            // Busca o objeto Cargo correspondente pelo nome (Vínculo de tabelas)
            Cargo cargoLocalizado;
            for (const auto& cargoDaLista : listaCargos) 
            {
                if (cargoDaLista.getNome() == nomeCargoArquivo) 
                {
                    cargoLocalizado = cargoDaLista;
                    break;
                }
            }

            // Instancia o colaborador com os dados recuperados
            Colaborador colab_aux(id_aux, dados_colab[1], cargoLocalizado, dados_colab[3], dados_colab[4], ativo_aux);
            colaboradores.push_back(colab_aux);
        }   
        
        arquivo.close();
        cout << "[SISTEMA] Dados dos colaboradores carregados com sucesso!\n";
    }
}
