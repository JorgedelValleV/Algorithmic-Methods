// Jorge
//DG30


#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include "TreeMap_AVL.h"

using namespace std;




bool resuelveCaso() {
	int n;
	cin >> n;
	if (n == 0)return false;
	map<int,int> avl;
	int val,min,max;
	for (int i = 0; i < n; i++)
	{
		cin >> val;
		avl.insert(val);
	}
	cin >> min >> max;
	avl.rango(min, max);
	cout << '\n';
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