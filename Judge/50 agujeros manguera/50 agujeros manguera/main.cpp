#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
using namespace std;
bool resuelveCaso() {
	long long int Nagujeros;
	cin >> Nagujeros;
	if (!cin) // fin de la entrada
		return false;
	int longitud;
	cin >> longitud;
	long long int pos;
	cin >> pos;
	long long int ini = pos;
	long Nparches = 1;
	for (int i = 1; i < Nagujeros; ++i) {
		cin >> pos;
		if (ini + longitud < pos) {
			ini = pos;
			++Nparches;
		}
	}
	std::cout << Nparches << '\n';
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