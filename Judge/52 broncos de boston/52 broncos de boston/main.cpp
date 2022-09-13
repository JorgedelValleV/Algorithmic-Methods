#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
using namespace std;
bool resuelveCaso() {
	int Npartidos;
	cin >> Npartidos;
	if (Npartidos == 0) return false;
	vector<int> rivals(Npartidos), broncos(Npartidos);
	for (int k = 0; k < Npartidos; ++k) {
		std::cin >> rivals[k];
	}
	sort(rivals.begin(), rivals.end());
	for (int j = 0; j < Npartidos; ++j) {
		cin >> broncos[j];
	}
	sort(broncos.begin(), broncos.end());
	int suma = 0;
	int i = 0;
	bool continua = true;
	while (continua && i < Npartidos) {
		if (rivals[i] < broncos[Npartidos - i - 1]) {
			suma += broncos[Npartidos - 1 - i] - rivals[i];
		}
		else continua = false;
		++i;
	}
	cout << suma << '\n';
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