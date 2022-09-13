#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include <climits>
#include "GrafoDirigidoValorado.h"
#include "IndexPQ.h"

using namespace std;
void relax(AristaDirigida<int> e, vector<int> & distTo, IndexPQ<int> & pq) {
	int v = e.from(), w = e.to();
	if (distTo[w] > distTo[v] + e.valor()) {
		distTo[w] = distTo[v] + e.valor();
		pq.update(w, distTo[w]);
	}
}

vector<int> resolver(GrafoDirigidoValorado<int> const& g, int origen) {
	vector<int> timeTo(g.V());
	IndexPQ<int> pq(g.V());
	for (int i = 0; i < g.V(); ++i) {
		timeTo[i] = INT_MAX;
	}
	timeTo[origen] = 0;
	pq.push(origen, 0);
	while (!pq.empty()) {
		int v = pq.top().elem;
		pq.pop();
		for (AristaDirigida<int> e : g.ady(v)) {
			relax(e, timeTo, pq);
		}
	}
	return timeTo;
}


bool resuelveCaso() {
	int celdas;
	cin >> celdas;
	if (!cin)return false;
	int salida,tiempo,pasadizos;
	cin >> salida>> tiempo >> pasadizos;
	int orig, dest, duracion;
	GrafoDirigidoValorado<int> laberinto(celdas);
	for (int i = 0; i < pasadizos; ++i) {
		cin >> orig >> dest >> duracion;
		// colocamos las aristas en orden inverso para llegar de la salida a el resto de celdas, lo que significa que de esa celda se llega a la salida que es lo que buscamos
		laberinto.ponArista({ dest-1,orig-1,duracion });
	}
	auto sol = resolver(laberinto, salida - 1);
	int cont = 0;
	for (int j = 0; j < celdas; ++j) {
		if (j!=salida-1 &&  sol[j]<= tiempo)
			cont += 1;
	}
	cout << cont << "\n";
	
	return true;
}
int main() {
	// ajuste para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("casos.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

	while (resuelveCaso());

	// restablecimiento de cin
#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	system("pause");
#endif
	return 0;
}