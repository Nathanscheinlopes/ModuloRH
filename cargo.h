#ifndef CARGO_H
#define CARGO_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

// Pré-declaração para evitar dependência cíclica com Colaborador
class Colaborador; 

class Cargo 
{
private:
    int id_cargo;
    string nome;
    float salarioBase;
    bool ativo; 
    static int contador_id_cargo; // Controle global de IDs para novos cadastros

public:
    // Construtores
    Cargo();
    Cargo(int id_cargo_arq, string nome_arq, float salario_arq, bool ativo_arq);

    // Persistência de Dados
    void extrairCargosPlanilha(vector<Cargo>& cargos);
    void salvarCargosPlanilha(const vector<Cargo>& cargos);
    static void atualizarContador(const vector<Cargo>& lista);

    // Getters e Setters
    int getID_Cargo() const;
    string getNome() const;
    float getSalario() const;
    bool isAtivo() const { return ativo; }
    
    void setNome(string n) { nome = n; }
    void setSalario(float s) { salarioBase = s; }
    void setAtivo(bool status) { ativo = status; }

    // Métodos de Gerenciamento Estáticos
    static void adicionarCargo(vector<Cargo>& lista);
    static void editarCargo(vector<Cargo>& lista);
    static void deletarCargo(vector<Cargo>& lista, const vector<Colaborador>& colaboradores);
};

#endif