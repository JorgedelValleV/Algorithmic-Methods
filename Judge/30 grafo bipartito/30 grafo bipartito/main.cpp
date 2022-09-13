#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include "Grafo.h"

using namespace std;

enum tColor {
	blanco, rojo, TRANSparente
};

tColor contrario(tColor color) {
	if (color == blanco) return rojo;
	else return blanco;
}

bool colorearAdacentes(Grafo const& grafo, std::vector<tColor> & vcolores, tColor colorotro, int v) {
	bool bipartito = true;
	int i = 0;
	while (bipartito && i < grafo.ady(v).size()) {
		if (vcolores[grafo.ady(v)[i]] == TRANSparente) {
			vcolores[grafo.ady(v)[i]] = colorotro;
			bipartito = colorearAdacentes(grafo, vcolores, contrario(colorotro), grafo.ady(v)[i]);
		}
		else if (vcolores[grafo.ady(v)[i]] == contrario(colorotro)) {
			bipartito = false;
		}
		++i;
	}
	return bipartito;
}



bool bipartito(Grafo const& grafo) {
	bool bipartito = true;
	std::vector<tColor> vcolores(grafo.V(), TRANSparente);
	int i = 0;
	while (i < grafo.V() && bipartito) {
		if (vcolores[i] == TRANSparente) {
			vcolores[i] = blanco;
			bipartito = colorearAdacentes(grafo, vcolores, rojo, i);
		}
		++i;
	}
	return bipartito;
}

bool resuelveCaso() {
	int v;
	cin >> v;
	if (!cin)return false;
	int a;
	cin >> a;
	Grafo grafo(v);
	int o, d;
	for (int i = 0; i < a; ++i){
		cin >> o >> d;
		grafo.ponArista(o, d);
	}
	if(bipartito(grafo))cout << "SI\n";
	else cout << "NO\n";
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