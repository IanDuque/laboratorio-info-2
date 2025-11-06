#ifndef RED_H
#define RED_H

#include "enrutador.h"
#include <map>
#include <queue>
#include <vector>
#include <limits>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

//------------------------------------------------------
// Clase red
// Contiene varios enrutadores y sus enlaces.
// Permite calcular rutas, agregar, eliminar y generar redes.
//------------------------------------------------------
class red {
private:
    map<char, enrutador*> enrutadores; // Coleccion de enrutadores

public:

    // Agrega un nuevo enrutador
    void agregarEnrutador(char id);

    // Elimina un enrutador
    void eliminarEnrutador(char id);

    // Agrega o actualiza un enlace entre enrutadores
    void agregarEnlace(char origen, char destino, int costo);

    // Elimina un enlace entre dos enrutadores
    void eliminarEnlace(char origen, char destino);

    // Muestra todas las tablas de enrutamiento de la red
    void mostrarRed() const;

    // Calcula la ruta mas corta entre enrutadores
    void dijkstra(char origen, char destino);

    // Genera una red aleatoria de n enrutadores
    void generarRedAleatoria(int n);

    // Destructor de clase
    ~red();
};

#endif
