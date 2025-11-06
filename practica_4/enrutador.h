#ifndef ENRUTADOR_H
#define ENRUTADOR_H

#include <map>
#include <iostream>
using namespace std;

class enrutador {
private:
    char id;                    // Identificador del enrutador
    map<char, int> tabla;       // Enrutadores y sus costos

public:
    // Inicializa el enrutador con su ID
    enrutador(char id);

    // Devuelve el identificador del enrutador
    char getId() const;

    // Agrega o actualiza el costo de un enlace
    void agregarEnlace(char destino, int costo);

    // Elimina el enlace entre enrutadores
    void eliminarEnlace(char destino);

    // Devuelve la tabla de enlaces del enrutador
    const map<char, int>& getTabla() const;

    // Muestra la tabla de enrutadores
    void mostrarTabla() const;
};

#endif
