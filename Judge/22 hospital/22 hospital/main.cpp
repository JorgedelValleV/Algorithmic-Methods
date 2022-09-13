#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include "IndexPQ_cambiado.h"

using namespace std;
struct comp
{
	bool operator() (pair<int,int> a, pair<int, int> b) { return a.second > b.second || (a.second == b.second && a.first < b.first); }
};


bool resuelveCaso() {
	int n;
	std::cin >> n;
	if (n == 0)return false;
	vector<string> nombres(n); char accion; int prioridad;
	IndexPQ<std::pair<int,int>, comp> pqi(n);
	for (int i = 0; i < n; ++i){
		std::cin >> accion;
		if (accion == 'I') {
			std::cin >> nombres[i] >> prioridad;
			pqi.update(i, { i, prioridad });
		}
		else {// atender
			auto x=pqi.top();
			std::cout << nombres[x.elem] << '\n';
			pqi.pop();
		}
	}
	std::cout <<"---\n";
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