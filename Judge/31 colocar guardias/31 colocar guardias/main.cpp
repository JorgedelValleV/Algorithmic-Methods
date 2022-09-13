#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include <stack>
#include <queue>
#include "Grafo.h"

using namespace std;

enum tColor {
	blanco, rojo
};

tColor contrario(tColor color) {
	if (color == blanco) return rojo;
	else return blanco;
}
bool resolver(Grafo grafo, int v, vector<tColor> &solucion_a, vector<tColor> &solucion_b, int &cant_a, int &cant_b, tColor c) {
	bool dev = true;
	if (c == rojo) {
		solucion_a[v] = rojo;
		++cant_a;
	}
	else {
		solucion_b[v] = rojo;
		++cant_b;
	}

	if (solucion_a[v] && solucion_b[v])
		return false;
	for (int w : grafo.ady(v)) {
		//para una calle entre A-----B , si he colocado un guardia en A para la solucion a/b observo la posibilidad de colocarlo en B para la solucion b/a
		if ((solucion_a[v] && !solucion_b[w]) || (!solucion_a[w] && solucion_b[v]))
			if (!resolver(grafo, w, solucion_a, solucion_b, cant_a, cant_b, contrario(c)))
				dev = false;
	}
	return dev;
}

bool resuelveCaso() {
	int n;
	cin >> n;
	if (!cin)return false;
	int calles;
	cin >> calles;
	Grafo Abudajh(n);
	//he usado un tColor a,es posible hacerlo con valores booleanos
	vector<tColor> solucion_a(n, blanco);
	vector<tColor> solucion_b(n, blanco);
	bool haySolucion = true;
	int guardias = 0;
	int orig, dest;
	for (int i = 0; i < calles; ++i) {
		cin >> orig >> dest;
		Abudajh.ponArista(orig - 1, dest - 1);
	}
	for (int i = 0; i < Abudajh.V() && haySolucion; ++i) {
		if (solucion_a[i] == 0 && solucion_b[i] == 0) {
			int cant_a = 0; int cant_b = 0;
			tColor c = blanco;
			if (resolver(Abudajh, i, solucion_a, solucion_b, cant_a, cant_b, c))
				guardias += min(cant_a, cant_b);
			else haySolucion = false;
		}
	}
	if (haySolucion)cout << guardias << '\n';
	else cout << "IMPOSIBLE\n";
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