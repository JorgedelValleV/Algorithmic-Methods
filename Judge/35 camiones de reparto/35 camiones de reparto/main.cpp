#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include "GrafoValorado.h"

using namespace std;

void alcanzados(GrafoValorado<int> const& ciudad, int orig, int ancho, vector<bool> & marcados) {
	marcados[orig] = true;
	for (Arista<int> calle : ciudad.ady(orig)) {
		if (calle.valor() >= ancho) {// si el camion pasa por la calle
			if (!marcados[calle.otro(orig)]) { // si todavia no se han comprobado los alcanzados de la interseccion que queda en el otro lado de la calle de orig
				alcanzados(ciudad, calle.otro(orig), ancho, marcados);
			}
		}
	}

}
bool resolver(GrafoValorado<int> const& ciudad, int orig, int dest, int ancho) {
	vector<bool> marcas(ciudad.V(), false);
	alcanzados(ciudad, orig, ancho, marcas);//vemos que intersecciones podemos alcanzar
	return marcas[dest];
}
bool resuelveCaso() {
	int inter;
	cin >> inter;
	if (!cin)return false;
	int calles;
	cin >> calles;
	int orig, dest, ancho;
	GrafoValorado<int> ciudad(inter);
	for (int i = 0; i < calles; ++i) {
		cin >> orig >> dest >> ancho;
		ciudad.ponArista({ orig-1,dest-1,ancho });
	}
	int casos;
	cin >> casos;
	for (int j = 0; j < casos; ++j) {
		cin >> orig >> dest >> ancho;
		//ver si puedo ir de origen a destino con un camion de ancho

		if (resolver(ciudad, orig-1, dest-1, ancho))cout << "SI\n";
		else cout << "NO\n";
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