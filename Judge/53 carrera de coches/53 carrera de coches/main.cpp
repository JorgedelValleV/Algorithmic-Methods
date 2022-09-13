#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
using namespace std;
void resuelveCaso() {
	int n, voltage;
	cin >> n >> voltage;
	vector<int> pilas(n);
	for (int i = 0; i < n; ++i) {
		cin >> pilas[i];
	}
	sort(pilas.begin(), pilas.end());// ordeno menor a mayor
	int ini = 0;
	int fin = n - 1;
	int suma = 0;
	while (ini < fin) {
		if (pilas[ini] + pilas[fin] < voltage) {//si la menor y la mayor no suman lo suficiente, la menor no lo sumara nunca con ninguna de las restantes
			++ini;
		}
		else {
			++suma;
			++ini;
			--fin;
		}
	}
	std::cout << suma << '\n';
}
int main() {
	// ajuste para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("casos.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
	int ncasos; cin >> ncasos; int i = 0;
	while (i<ncasos) {
		resuelveCaso();
		++i;
	}

	// restablecimiento de cin
#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	system("pause");
#endif
	return 0;
}