#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
using namespace std;
bool resuelveCaso() {
	int Nedificios;
	cin >> Nedificios;
	if (Nedificios == 0)return false;
	int ini, fin;
	vector<pair<int,int>> buildings; //final,inicio asi para no ponerse a redefinir el orden
	for (int j = 0; j < Nedificios; ++j) {
		cin >> ini >> fin;
		buildings.push_back({ fin, ini });
	}
	sort(buildings.begin(), buildings.end());
	int tunels = 1;
	int pos = buildings[0].first - 1;
	for (int i = 0; i < Nedificios; ++i) {
		if (buildings[i].second > pos) {
			++tunels;
			pos = buildings[i].first - 1;
		}
	}
	cout << tunels << '\n';
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