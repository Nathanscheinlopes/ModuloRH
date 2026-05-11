#ifndef COLABORADOR_H
#define COLABORADOR_H

#include <string>
#include <vector>
#include <iostream>
#include <ctime>
#include "cargo.h"

using namespace std;

/**
 * @class Colaborador
 * @brief Representa o funcionário no sistema, contendo dados pessoais e vínculo com Cargo.
 */
class Colaborador { 
    private:
        static int contador_ID;     // Gerador de ID incremental
        int id;
        string nome;
        Cargo objetoCargo;          // Composição: Colaborador "tem um" Cargo
        string cpf;
        string sexo;
        struct tm data_admissao;
        struct tm data_desligamento;
        bool ativo;
        float horasTrabalhadas;

    public:
        // Construtores
        Colaborador(); 
        Colaborador(int id_arquivo, string nome_arq, Cargo cargo_obj, string cpf_arq, string sexo_arq, bool ativo_arq); 

        // Getters e Setters
        int getID() const; 
        string getNome() const;
        string getCPF() const;
        string getSexo() const;
        string getNomeCargo() const;
        float getSalarioBase() const;
        void setHoras(float h) { this->horasTrabalhadas = h; }
        float getHoras() const { return horasTrabalhadas; }
        void setAtivo(bool estado) { ativo = estado; }
        bool isAtivo() const { return ativo; }

        // Métodos de Gerenciamento de Dados
        void addColaborador(const vector<Cargo>& listaCargos);
        void editColaborador(vector<Colaborador>& lista, const vector<Cargo>& listaCargos);
        
        // Métodos Estáticos (Operações em Lote/Busca)
        static void deleteColaborador(vector<Colaborador>& lista, int idParaExcluir);
        static void buscarColaborador(const vector<Colaborador>& lista, string termoBusca);
        static void atualizarContador(const vector<Colaborador>& lista);  
};

#endif