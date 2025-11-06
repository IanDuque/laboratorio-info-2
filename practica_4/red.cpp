#include "red.h"
#include <iostream>
#include <cctype>

red::~red() {
    for (auto& par : enrutadores)
        delete par.second;
}

void red::agregarEnrutador(char id) {
    id = toupper(id);
    if (enrutadores.count(id) == 0)
        enrutadores[id] = new enrutador(id);
    else
        cout << "El enrutador ya existe." << endl;
}

void red::eliminarEnrutador(char id) {
    id = toupper(id);
    if (enrutadores.count(id)) {
        delete enrutadores[id];
        enrutadores.erase(id);
        for (auto& par : enrutadores)
            par.second->eliminarEnlace(id);
    }
}

void red::agregarEnlace(char origen, char destino, int costo) {
    origen = toupper(origen);
    destino = toupper(destino);
    if (enrutadores.count(origen) && enrutadores.count(destino)) {
        enrutadores[origen]->agregarEnlace(destino, costo);
        enrutadores[destino]->agregarEnlace(origen, costo);
    }
}

void red::eliminarEnlace(char origen, char destino) {
    origen = toupper(origen);
    destino = toupper(destino);
    if (enrutadores.count(origen) && enrutadores.count(destino)) {
        enrutadores[origen]->eliminarEnlace(destino);
        enrutadores[destino]->eliminarEnlace(origen);
    }
}

void red::mostrarRed() const {
    for (auto& par : enrutadores)
        par.second->mostrarTabla();
}

void red::dijkstra(char origen, char destino) {
    origen = toupper(origen);
    destino = toupper(destino);

    if (!enrutadores.count(origen) || !enrutadores.count(destino)) {
        cout << "Enrutador no encontrado." << endl;
        return;
    }

    map<char, int> dist;
    map<char, char> previo;
    const int INF = numeric_limits<int>::max();

    for (auto& par : enrutadores)
        dist[par.first] = INF;

    dist[origen] = 0;

    priority_queue<pair<int, char>, vector<pair<int, char>>, greater<pair<int, char>>> pq;
    pq.push({0, origen});

    while (!pq.empty()) {
        char actual = pq.top().second;
        int distancia = pq.top().first;
        pq.pop();

        for (auto& vecino : enrutadores[actual]->getTabla()) {
            char v = vecino.first;
            int peso = vecino.second;
            if (distancia + peso < dist[v]) {
                dist[v] = distancia + peso;
                previo[v] = actual;
                pq.push({dist[v], v});
            }
        }
    }

    if (dist[destino] == INF) {
        cout << "No existe camino entre los enrutadores." << endl;
        return;
    }

    // Reconstruccion del camino mas corto
    vector<char> camino;
    for (char v = destino; v != origen; v = previo[v])
        camino.push_back(v);
    camino.push_back(origen);
    reverse(camino.begin(), camino.end());

    cout << "Camino mas corto: ";
    for (char c : camino)
        cout << c << " ";
    cout << "\nCosto total: " << dist[destino] << endl;
}

void red::generarRedAleatoria(int n) {
    enrutadores.clear();
    srand(time(0));

    for (int i = 0; i < n; i++) {
        char id = 'A' + i;
        agregarEnrutador(id);
    }

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (rand() % 2 == 1) {
                int costo = rand() % 10 + 1;
                agregarEnlace('A' + i, 'A' + j, costo);
            }
        }
    }
}
