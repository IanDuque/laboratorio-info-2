#include "red.h"
#include <iostream>
using namespace std;

int main() {
    red r;
    int opcion;

    do {
        cout << "\n--- MENU ---\n";
        cout << "1. Agregar enrutador\n";
        cout << "2. Eliminar enrutador\n";
        cout << "3. Agregar enlace\n";
        cout << "4. Eliminar enlace\n";
        cout << "5. Mostrar red\n";
        cout << "6. Camino mas corto\n";
        cout << "7. Generar red aleatoria\n";
        cout << "0. Salir\n";
        cout << "Opcion: ";
        cin >> opcion;

        char a, b;
        int costo, n;

        switch (opcion) {
        case 1:
            cout << "ID del enrutador: ";
            cin >> a;
            r.agregarEnrutador(a);
            break;
        case 2:
            cout << "ID del enrutador: ";
            cin >> a;
            r.eliminarEnrutador(a);
            break;
        case 3:
            cout << "Origen destino costo: ";
            cin >> a >> b >> costo;
            r.agregarEnlace(a, b, costo);
            break;
        case 4:
            cout << "Origen destino: ";
            cin >> a >> b;
            r.eliminarEnlace(a, b);
            break;
        case 5:
            r.mostrarRed();
            break;
        case 6:
            cout << "Origen y destino: ";
            cin >> a >> b;
            r.dijkstra(a, b);
            break;
        case 7:
            cout << "Numero de enrutadores: ";
            cin >> n;
            r.generarRedAleatoria(n);
            break;
        }
    } while (opcion != 0);

    return 0;
}
