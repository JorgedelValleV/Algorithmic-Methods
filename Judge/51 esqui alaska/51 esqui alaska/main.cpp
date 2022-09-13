#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
using namespace std;
int minDist(std::vector<int> & hights, std::vector<int> & skis) {
	std::sort(hights.begin(), hights.end());
	std::sort(skis.begin(), skis.end());
	int suma = 0;
	for (int i = 0; i < skis.size(); ++i) {
		suma += abs(hights[i] - skis[i]);
	}
	return suma;
}

bool resuelveCaso() {
	int n;
	cin >> n;
	if (n == 0)return false;
	int elem;
	vector<int> hights, skiers;
	for (int i = 0; i < n; ++i) {
		cin >> elem;
		hights.push_back(elem);
	}
	for (int j = 0; j < n; ++j) {
		std::cin >> elem;
		skiers.push_back(elem);
	}
	cout << minDist(hights, skiers) << '\n';
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