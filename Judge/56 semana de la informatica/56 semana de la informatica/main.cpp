#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
using namespace std;
bool resuelveCaso() {
	int nActividades;
	cin >> nActividades;
	if (nActividades == 0)return false;
	int start, end;
	vector<int> beginnings, finals;
	for (int i = 0; i < nActividades; ++i) {
		cin >> start;
		beginnings.push_back(start);
		cin >> end;
		finals.push_back(end);
	}
	sort(beginnings.begin(), beginnings.end());
	sort(finals.begin(), finals.end());
	int cont = 0;
	int pos = 0;
	end = finals[0];
	for (int i = 1; i < beginnings.size(); ++i) {
		if (beginnings[i] < end) {//comienza la actividad antes de que acabe la anterior
			++cont;
		}
		else {
			++pos;
			end = finals[pos];
		}
	}

	std::cout << cont << '\n';
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