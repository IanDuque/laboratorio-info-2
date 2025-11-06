#include "enrutador.h"
#include <cctype>

enrutador::enrutador(char id) : id(toupper(id)) {}

char enrutador::getId() const {
    return id;
}

void enrutador::agregarEnlace(char destino, int costo) {
    destino = toupper(destino);
    tabla[destino] = costo;
}

void enrutador::eliminarEnlace(char destino) {
    destino = toupper(destino);
    tabla.erase(destino);
}

const map<char, int>& enrutador::getTabla() const {
    return tabla;
}

void enrutador::mostrarTabla() const {
    cout << "Enrutador " << id << " -> ";
    for (auto& enlace : tabla)
        cout << enlace.first << ":" << enlace.second << " ";
    cout << endl;
}
