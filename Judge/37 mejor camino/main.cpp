#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include <climits>
#include "GrafoValorado.h"
#include "IndexPQ.h"

using namespace std;
void relax(Arista<int> e, vector<int> & distTo, IndexPQ<int> & pq, vector<int> & nivel,int v,int salida,int & nivelmin) {
	int w = e.otro(v);
	if (distTo[w] > distTo[v] + e.valor()) {
		distTo[w] = distTo[v] + e.valor();
		pq.update(w, distTo[w]);
		nivel[w] = nivel[v] + 1;
		if (w == salida && nivel[w] != -1 && nivel[w] < nivelmin)nivelmin = nivel[w];
	}
}

pair<int,bool> resolver(GrafoValorado<int> const& g, int origen, int salida) {
	vector<int> timeTo(g.V(), INT_MAX);
	vector<int> nivel(g.V(),-1);
	nivel[origen] = 0;
	int nivelmin = INT_MAX;
	IndexPQ<int> pq(g.V());
	timeTo[origen] = 0;
	pq.push(origen, 0);
	while (!pq.empty()) {
		int v = pq.top().elem;
		pq.pop();
		for (Arista<int> e : g.ady(v)) {
			relax(e, timeTo, pq,nivel,v,salida,nivelmin);
		}
	}
	return { timeTo[salida],nivel[salida] == nivelmin };
}

bool resuelveCaso() {
	int inter;
	cin >> inter;
	if (!cin)return false;
	int calles;
	cin >> calles;
	int orig, dest, longitud;
	GrafoValorado<int> ciudad(inter);
	for (int i = 0; i < calles; ++i) {
		cin >> orig >> dest >> longitud;
		ciudad.ponArista({ orig-1,dest-1,longitud });
	}
	int casos;
	cin >> casos;
	for (int j = 0; j < casos; ++j) {
		cin >> orig >> dest;
		//ver si puedo ir de origen a destino y si lo hago en el numero minimo de calles
		auto sol = resolver(ciudad, orig-1, dest-1);
		if (sol.first != INT_MAX) {
			cout << sol.first << ' ';
			if (sol.second)cout << "SI\n";
			else cout << "NO\n";
		}
		else cout << "SIN CAMINO\n";
	}
	cout << "---\n";
	
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