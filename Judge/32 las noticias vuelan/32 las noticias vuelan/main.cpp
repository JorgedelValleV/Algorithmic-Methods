#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include <queue>
#include "Grafo.h"

using namespace std;

enum tColor { blanco, gris, negro };
//blanco significa que no se ha comprobado todavia
// gris que se ha puesto en la cola para ser comprobado por estar en la lista de adyacencia
// negro ya has comprobado todos los elementos de la lista de adyacencia de ese elemento

int bfs(int v, Grafo const & grafo, vector<tColor> & marcas, vector<int> & compcon) {
	queue <int> q;
	q.push(v);
	marcas[v] = gris;
	compcon[v] = v;
	int cont = 1;
	while (!q.empty()) {
		int x = q.front();
		q.pop();
		vector<int> ady = grafo.ady(x);
		int i = 0;
		while (i < ady.size()) {
			int k = ady[i];
			if (marcas[k] == blanco) {
				marcas[k] = gris;
				q.push(k);
				compcon[k] = v;
				cont++;
			}
			++i;
		}
		marcas[x] = negro;
	}
	return cont;
}
vector<int> resolver(Grafo const & grafo) {
	vector<int> compcon(grafo.V(), grafo.V() + 1);
	vector<tColor> marcas(grafo.V(), blanco);
	vector<int> sol(grafo.V());
	int v = 0;
	while (v < grafo.V()) {
		if (marcas[v] == blanco) {//no has comprobado ningun elemnto de su misma componente conexa
			sol[v] = bfs(v, grafo, marcas, compcon);
		}
		else {
			sol[v] = sol[compcon[v]];//en compcon[v] se guarda el primer elemnto de la componente conexa que aparecio que ya tiene la solucion calculada
		}
		++v;
	}
	return sol;
}
bool resuelveCaso() {
	// leer los datos de la entrada
	int Nusers;
	cin >> Nusers;;
	if (!cin)
		return false;
	int grupos;
	cin >> grupos;
	Grafo grafo(Nusers);
	for (int i = 0; i < grupos; ++i) {
		int miembros, primero, demas;
		std::cin >> miembros;
		if (miembros != 0) {
			std::cin >> primero;
			for (int j = 1; j < miembros; ++j) {
				cin >> demas;
				grafo.ponArista(primero - 1, demas - 1);
			}
		}
	}
	vector<int> sol = resolver(grafo);
	for (int i = 0; i < sol.size(); ++i) {
		cout << sol[i];
		if(i == sol.size()-1)cout << '\n';
		else cout << ' ';
	}
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