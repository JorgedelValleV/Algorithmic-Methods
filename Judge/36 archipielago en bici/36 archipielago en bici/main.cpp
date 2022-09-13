#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include <climits>
#include "GrafoValorado.h"
#include "PriorityQueue.h"

using namespace std;
void visitar(GrafoValorado<int> const& grafo, int v, vector<int> & marcas, PriorityQueue<pair<int, int>> & pq, vector<int> & distTo) {
	marcas[v] = true;
	for (auto e : grafo.ady(v)) {
		int w = e.otro(v);
		if (!marcas[w] && e.valor() < distTo[w]) {
			distTo[w] = e.valor();
			pq.push({distTo[w], w });
		}
	}
}
pair<bool, int> resolver(GrafoValorado<int> const& grafo) {
	pair<bool, int> solucion = { true, 0 };
	PriorityQueue<pair<int,int>> pq;
	vector<int> marcas(grafo.V());
	vector<int> distTo(grafo.V());
	for (int i = 0; i < grafo.V(); ++i) {
		distTo[i] = INT_MAX;//2147483647
	}
	distTo[0] = 0;
	pq.push({ 0,0 });
	while (!pq.empty()) {
		int v = pq.top().second;
		pq.pop();
		visitar(grafo, v, marcas, pq, distTo);
	}
	int suma = 0;
	for (int i = 0; i < grafo.V(); ++i) {
		suma += distTo[i];
		if (!marcas[i]) solucion.first = false;
	}
	solucion.second = suma;
	return solucion;
}

bool resuelveCaso() {
	int islas;
	cin >> islas;
	if (!cin)return false;
	int puentes;
	cin >> puentes;
	int orig, dest, coste;
	GrafoValorado<int> conexiones(islas);
	for (int i = 0; i < puentes; ++i) {
		cin >> orig >> dest >> coste;
		conexiones.ponArista({ orig-1,dest-1,coste });
	}
	pair<bool, int> sol = resolver(conexiones);
	if(sol.first)cout << sol.second << "\n";
	else cout << "No  hay puentes suficientes\n";
	
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