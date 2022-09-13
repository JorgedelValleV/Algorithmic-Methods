// Jorge del Valle
// DG30 
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include "TreeMap_AVL.h"

using namespace std;

bool resuelveCaso() {
	// leer los datos de la entrada
	int n, m,val;
	std::cin >> n;
	if (n == 0)
		return false;
	map <int, int> arbol;
	std::vector<int> v;
	for (int i = 0; i < n; ++i) {
		std::cin >> val;
		arbol.insert(val);
	}
	std::cin >> m;
	for (int i = 0; i < m; ++i) {
		std::cin >> val;
		v.push_back(val);
	}
	arbol.kesimo(v);
	std::cout << "---" << '\n';
	return true;

}

int main() {
	// Para la entrada por fichero.
	// Comentar para acepta el reto
#ifndef DOMJUDGE
	std::ifstream in("casos.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif 

	while (resuelveCaso());

	// Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
	std::cin.rdbuf(cinbuf);
	system("PAUSE");
#endif

	return 0;
}