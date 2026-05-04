#include "bancoDados_RH.h"

// salva em arquivo csv
void BancoDados_RH::exportarPlanilha(const vector <Colaborador>& colaboradores) // acessa as informacoes de um vetor de objetos do tipo Colaborador
{
    ofstream planilha("ColaboradoresRH.csv"); // ofstream escreve dados no arquivo
    if (planilha.is_open()) // confere se o arquivo esta aberto
    {
        planilha << "ID;Nome;Cargo;CPF;Sexo" << endl; // cabecalho do arquivo

        for (int i = 0; i < colaboradores.size(); i++) // loop roda o mesmo numero de vezes que o numero de colaboradores que podem ser cadastrados no vetor
        {
            planilha << colaboradores[i].getID() << ";";
            planilha << colaboradores[i].getNome() << ";";
            planilha << colaboradores[i].getNomeCargo() << ";";
            planilha << colaboradores[i].getCPF() << ";";
            planilha << colaboradores[i].getSexo() << endl;
        }
        planilha.close();    
        cout << "Dados salvos com sucesso!\n";
    } 

    else // caso o arquivo nao esteja aberto
    {
        cout << "Erro ao abrir o arquivo!\n";
    }
}

void BancoDados_RH::carregarPlanilha(vector <Colaborador>& colaboradores, const vector <Cargo>& listaCargos) // pega informacoes em arquivo csv 
{
    ifstream arquivo("ColaboradoresRH.csv"); // ifstream le dados no arquivo
    if (arquivo.is_open()) // confere se o arquivo esta aberto
    {
        string linha; // variavel auxiliar para salvar as linhas lidas do arquivo
        getline (arquivo, linha); // copia a primeira linha de cabecalho (eliminar)

        while (getline(arquivo, linha)) // enquanto tiver texto no arquivo copia as linhas para a variavel linha
        { 
            if (linha.empty() || linha.length() < 2) // verifica se a linha esta vazia ou desformatada (poucos caracteres)
            {
                continue;
            }

            string dados_colab[5]; // Vetor temporário para guardar os pedaços da linha
            size_t pos = 0;

            for (int i = 0; i < 4; i++) { // Faz o corte para as 4 primeiras posicoes do vetor
                pos = linha.find(";");
                if (pos == string::npos) // verifica se foi acessado posicao invalida
                {
                    break;
                }
                dados_colab[i] = linha.substr(0, pos); // cria uma substring ate o ; e copia para o vetor auxiliar
                linha.erase(0, pos + 1); // apagar o que ja foi extraido
            }
            
            dados_colab[4] = linha; // O que sobrou na linha é o último dado (Sexo)

            try 
            {
                string nomeCargoArquivo = dados_colab[2]; 
                Cargo cargoLocalizado;

                for(const auto& cargoDaLista : listaCargos) 
                {
                    if(cargoDaLista.getNome() == nomeCargoArquivo) // procura na lista de cargos pelo nome de cargo que estava salvo na planilha do colaborador
                    {
                        cargoLocalizado = cargoDaLista; // copia os dados da lista de cargos para dentro da planilha - id do cargo, nome e salario
                        break;
                    }
                }

                int id_aux = stoi(dados_colab[0]);
                Colaborador colab_aux(id_aux, dados_colab[1], cargoLocalizado, dados_colab[3], dados_colab[4]); // dados do colaborador, o cargo fica salvo como objeto com as informacoes de ID do cargo e salario base
                colaboradores.push_back(colab_aux); // atribui os dados de colab_aux para o vetor colaboradores
            } 
            catch (...) 
            { 
                cout << "Erro ao processar uma linha do arquivo. Pulando..." << endl; // Se o stoi falhar, o catch elimina o erro e o loop continua
            }
        }
        arquivo.close();
        cout << "Dados de colaboradores carregados com sucesso!\n";
    }
    else {
        cout << "Erro ao abrir o arquivo\n";
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